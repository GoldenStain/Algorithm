import math
import torch
import torch.nn as nn

class GroupedQueryAttention(nn.Module):
    def __init__(self, d_model: int, n_heads: int, n_kv_heads: int, dropout: float) -> None:
        super().__init__()
        assert d_model % n_heads == 0, "d_model must be divisible by n_heads"
        assert n_heads % n_kv_heads == 0, "n_heads must be divisible by n_kv_heads"

        self.d_model = d_model
        self.n_heads = n_heads          # total query heads
        self.n_kv_heads = n_kv_heads    # number of key/value head groups
        self.dropout = nn.Dropout(dropout)

        self.d_k = d_model // n_heads
        self.heads_per_group = n_heads // n_kv_heads  # how many Q heads share one K/V pair

        # Linear projections
        self.w_q = nn.Linear(d_model, d_model)                        # (d_model, d_model)
        self.w_k = nn.Linear(d_model, n_kv_heads * self.d_k)         # (d_model, g * d_k)
        self.w_v = nn.Linear(d_model, n_kv_heads * self.d_k)         # (d_model, g * d_k)
        self.w_o = nn.Linear(d_model, d_model)

    @staticmethod
    def attention(query: torch.Tensor, key: torch.Tensor, value: torch.Tensor, mask: torch.Tensor, dropout: nn.Dropout) -> tuple[torch.Tensor, torch.Tensor]:
        # query: (batch_size, n_heads, seq_len, d_k)
        # key:   (batch_size, n_kv_heads, seq_len, d_k)
        # value: (batch_size, n_kv_heads, seq_len, d_k)

        d_k = query.shape[-1]
        batch_size = query.shape[0]

        # Compute attention scores
        attention_scores = torch.matmul(query, key.transpose(-1, -2)) / math.sqrt(d_k)  # (b, h, s, s)

        if mask is not None:
            attention_scores = attention_scores.masked_fill_(mask == 0, -1e9)

        attention_scores = attention_scores.softmax(dim=-1)
        if dropout is not None:
            attention_scores = dropout(attention_scores)

        output = torch.matmul(attention_scores, value)  # (b, h, s, d_k)
        return output, attention_scores

    def forward(self, q: torch.Tensor, k: torch.Tensor, v: torch.Tensor, mask: torch.Tensor) -> torch.Tensor:
        batch_size, seq_len, _ = q.shape

        # Linear projections
        query = self.w_q(q)  # (batch_size, seq_len, d_model)
        key = self.w_k(k)    # (batch_size, seq_len, n_kv_heads * d_k)
        value = self.w_v(v)  # (batch_size, seq_len, n_kv_heads * d_k)

        # Reshape and transpose: (batch_size, seq_len, heads * d_k) -> (batch_size, heads, seq_len, d_k)
        query = query.view(batch_size, seq_len, self.n_heads, self.d_k).transpose(1, 2)

        # Process key and value with n_kv_heads
        key = key.view(batch_size, seq_len, self.n_kv_heads, self.d_k).transpose(1, 2)
        value = value.view(batch_size, seq_len, self.n_kv_heads, self.d_k).transpose(1, 2)

        # Broadcast K and V to match the number of query heads
        # (batch_size, n_kv_heads, seq_len, d_k) -> (batch_size, n_heads, seq_len, d_k)
        key = key.repeat_interleave(self.heads_per_group, dim=1)
        value = value.repeat_interleave(self.heads_per_group, dim=1)

        # Apply attention
        x, self.attention_scores = self.attention(query, key, value, mask, self.dropout)

        # (batch_size, n_heads, seq_len, d_k) -> (batch_size, seq_len, d_model)
        x = x.transpose(1, 2).contiguous().view(batch_size, seq_len, self.d_model)
        return self.w_o(x)