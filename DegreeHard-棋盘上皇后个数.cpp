#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> res;
        vector<bool> colUsed(n, false);
        // 对角线总数：2*n-1
        vector<bool> diag1(2 * n, false); // row - col ∈ [-n+1, n-1]，偏移+n
        vector<bool> diag2(2 * n, false); // row + col ∈ [0,2n-2]

        auto backtrack = [&](auto &&self, int row, vector<int> &path) -> void
        {
            if (row == n)
            {
                // 构造棋盘，存入结果（找到一组解）
                vector<string> board;
                for (int c : path)
                {
                    string s(n, '.');
                    s[c] = 'Q';
                    board.push_back(s);
                }
                res.push_back(board);
                return;
            }
            for (int col = 0; col < n; ++col)
            {
                int d1 = row - col + n;
                int d2 = row + col;
                if (!colUsed[col] && !diag1[d1] && !diag2[d2])
                {
                    colUsed[col] = true;
                    diag1[d1] = true;
                    diag2[d2] = true;
                    path.push_back(col);

                    self(self, row + 1, path);

                    // 回溯撤销
                    path.pop_back();
                    diag2[d2] = false;
                    diag1[d1] = false;
                    colUsed[col] = false;
                }
            }
        };
        vector<int> path;
        backtrack(backtrack, 0, path);
        return res;
    }
};

int main()
{
    Solution solution;
    int n = 4; // Example input
    vector<vector<string>> result = solution.solveNQueens(n);

    // Print the result
    for (const auto &board : result)
    {
        for (const auto &row : board)
        {
            cout << row << endl;
        }
        cout << endl;
    }

    return 0;
}
