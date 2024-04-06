#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

typedef vector<vector<int>> M;
unordered_map<int, int> rr, cc;

M sep_matrix(int k,  M &m, int row, int col)
{
    M tmp;
    tmp.resize(row, vector<int>(col, 0));
    int st_row = row * rr[k], st_col = col * cc[k];
    for(int i = st_row, ci = 0; ci < row; i++, ci++)
        for(int j = st_col, cj = 0; cj < col; j++, cj++)
            tmp[ci][cj] = m[i][j];
    return tmp;
}

void get_together(int k, M &res, M &t, int row, int col)
{
    int st_row = row * rr[k], st_col = col * cc[k];
    for(int i = st_row, ci = 0; ci < row; i++, ci++)
        for(int j = st_col, cj = 0; cj < col; j++, cj++)
            res[i][j] = t[ci][cj];
}

void print(M &t, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
            cout << t[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

struct str_for_matrix
{
    int row, col;
    vector<vector<int>> data;
    str_for_matrix(int rows, int cols)
    {
        row = rows;
        col = cols;
        data.resize(rows, vector<int>(cols, 0));
    }

    M add_matrix( str_for_matrix &B) 
    {
        M c(row, vector<int>(col, 0));
        if (B.row != row || B.col != col)
        {
            puts("B can't match with A, addition failed");
            return c;
        }
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                c[i][j] = data[i][j] + B.data[i][j];
        return c;
    }

    M operator+( str_for_matrix &B) 
    {
        return add_matrix(B);
    }

    M operator-( str_for_matrix &B) 
    {
        str_for_matrix tmp = str_for_matrix(row, col);
        if (B.row != row || B.col != col)
        {
            puts("B can't match with A, addition failed");
            return tmp.data;
        }
        for (int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                tmp.data[i][j] = -B.data[i][j];
        return add_matrix(tmp);
    }

    M simple_mul( M &A,  M &B, int row, int col)
    {
        M res(row, vector<int> (col, 0));
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
            {
                int sum = 0;
                for(int k = 0; k < row; k++) //一定是方的
                    sum += A[i][k] * B[i][k];
                res[i][j] = sum;
            }
        return res;
    }

    M simple_sub( M& A,  M& B, int row, int col)
    {
        M res(row, vector<int> (col, 0));
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                res[i][j] = A[i][j] - B[i][j];
        return res;
    }

    M simple_add( M& A,  M& B, int row, int col)
    {
        M res(row, vector<int> (col, 0));
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                res[i][j] = A[i][j] + B[i][j];
        return res;
    }

    M mul_matrix( str_for_matrix &B) 
    {
        int n_row = row/2, n_col = col/2;
        M p[9];
        for(int i = 1; i <= 7; i++)
            p[i].resize(n_row, vector<int>(n_col, 0));
        if(col != B.row)
        {
            puts("B can't match with A, addition failed");
            return p[0];
        }   
        double _log = log2(row);
        if(_log != (int)_log)
        {
            puts("can't deal with this matrix");
            return p[0];
        }
        M subA[4], subB[4];
        for(int i = 0; i < 4; i++)
        {
            subA[i].resize(n_row, vector<int> (n_col, 0));
            subB[i].resize(n_row, vector<int> (n_col, 0));
            subA[i] = sep_matrix(i, data, row/2, col/2);
            subB[i] = sep_matrix(i, B.data, row/2, col/2);
        }
        M tmp_res(n_row, vector<int>(n_col, 0)), tmp_res_2(n_row, vector<int>(n_col, 0));

        tmp_res = simple_sub(subB[1], subB[3], n_row, n_col); 
        p[1] = simple_mul(subA[0], tmp_res, n_row, n_col);
        
        tmp_res = simple_add(subA[0], subA[1], n_row, n_col);
        p[2] = simple_mul(tmp_res, subB[3], n_row, n_col);

        tmp_res = simple_add(subA[2], subA[3], n_row, n_col); 
        p[3] = simple_mul(tmp_res, subB[0], n_row, n_col);

        tmp_res = simple_sub(subB[2], subB[0], n_row, n_col);
        p[4] = simple_mul(subA[3], tmp_res, n_row, n_col);

        tmp_res = simple_add(subA[0], subA[3], n_row, n_col);tmp_res_2 = simple_add(subB[0], subB[3], n_row, n_col);
        p[5] = simple_mul(tmp_res, tmp_res_2, n_row, n_col);

        tmp_res = simple_sub(subA[1], subA[3], n_row, n_col); tmp_res_2 = simple_add(subB[2], subB[3], n_row, n_col);
        p[6] = simple_mul(tmp_res, tmp_res_2, n_row, n_col);

        tmp_res = simple_sub(subA[0], subA[2], n_row, n_col); tmp_res_2 = simple_add(subB[0], subB[1], n_row, n_col);
        p[7] = simple_mul(tmp_res, tmp_res_2, n_row, n_col);

        M ans[4];
        for(int i = 0; i < 4; i++)
            ans[i].resize(n_row, vector<int>(n_col, 0));
        
        tmp_res = simple_add(p[5], p[4], n_row, n_col);tmp_res_2 = simple_sub(p[2], p[6], n_row, n_col);
        ans[0] = simple_sub(tmp_res, tmp_res_2, n_row, n_col);

        ans[1] = simple_add(p[1], p[2], n_row, n_col);

        ans[2] = simple_add(p[3], p[4], n_row, n_col);

        tmp_res = simple_add(p[1], p[5], n_row, n_col); tmp_res_2 = simple_add(p[3], p[7], n_row, n_col);
        ans[3] = simple_sub(tmp_res, tmp_res_2, n_row, n_col);

        str_for_matrix c = str_for_matrix(row, col);
        for(int i = 0; i < 4; i++)
            get_together(i, c.data, ans[i], n_row, n_col);

        for(int i = 1; i <= 7; i++)
        {
            printf("%d\n", i);
            print(p[i], n_row, n_col);
        }

        return c.data;
    }

    M operator * (str_for_matrix &B)
    {
        return mul_matrix(B);
    }
};

str_for_matrix A = str_for_matrix(1, 1), B = str_for_matrix(1, 1);


void init()
{
    rr[0] = 0;rr[1] = 0;rr[2] = 1;rr[3] = 1;
    cc[0] = 0;cc[1] = 1;cc[2] = 0;cc[3] = 1;
}

void get_matrix(str_for_matrix &t)
{
    int rows, cols;
    cin >> rows >> cols;
    t = str_for_matrix(rows, cols);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            cin>>t.data[i][j];
}

int main()
{
    freopen("output.txt", "r", stdin);
    init();
    get_matrix(A);
    get_matrix(B);
    str_for_matrix ans = str_for_matrix(A.row, A.col);
    ans.data = A*B;
    print(ans.data, ans.row, ans.col);
    return 0;
}
