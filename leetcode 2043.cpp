class Bank {
   public:
	Bank(vector<long long>& balance) {
		_balance = balance;
	}

	bool transfer(int account1, int account2, long long money) {
		// 检查账户编号有效性
		if (account1 < 1 || account1 > _balance.size() || account2 < 1 ||
			account2 > _balance.size()) {
			return false;
		}

		account1--;
		account2--;
		if (_balance[account1] < money)
			return false;
		_balance[account1] -= money;
		_balance[account2] += money;
		return true;
	}

	bool deposit(int account, long long money) {
		// 检查账户编号有效性
		if (account < 1 || account > _balance.size()) {
			return false;
		}
		account--;
		_balance[account] += money;
		return true;
	}

	bool withdraw(int account, long long money) {
		// 检查账户编号有效性
		if (account < 1 || account > _balance.size()) {
			return false;
		}
		account--;
		if (_balance[account] < money)
			return false;
		_balance[account] -= money;
		return true;
	}

   private:
	vector<long long> _balance;
};