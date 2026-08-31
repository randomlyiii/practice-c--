#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool flag = false;
    void dfs(vector<vector<char>> &board, string word, int m, int n, int i,
             int j, int num)
    {
        if (flag)
        {
            return;
        }
        if (num >= word.size())
        {
            flag = true;
            return;
        }

        char tmpch = board[i][j];
        ;
        if (i + 1 < m && board[i + 1][j] == word[num])
        {
            board[i][j] = '#';
            dfs(board, word, m, n, i + 1, j, num + 1);
            board[i][j] = tmpch;
        }
        if (i - 1 >= 0 && board[i - 1][j] == word[num])
        {
            board[i][j] = '#';
            dfs(board, word, m, n, i - 1, j, num + 1);
            board[i][j] = tmpch;
        }
        if (j + 1 < n && board[i][j + 1] == word[num])
        {
            board[i][j] = '#';
            dfs(board, word, m, n, i, j + 1, num + 1);
            board[i][j] = tmpch;
        }
        if (j - 1 >= 0 && board[i][j - 1] == word[num])
        {
            board[i][j] = '#';
            dfs(board, word, m, n, i, j - 1, num + 1);
            board[i][j] = tmpch;
        }

        return;
    }

    bool exist(vector<vector<char>> &board, string word)
    {
        int m = board.size(), n = board[0].size();
        if (m == 0 || n == 0)
        {
            return false;
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == word[0])
                {
                    dfs(board, word, m, n, i, j, 1);
                }
                if (flag)
                    return true;
            }
        }

        return flag;
    }
};

int main()
{
    Solution solution;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};
    string word = "ABCCED";
    bool result = solution.exist(board, word);
    cout << (result ? "true" : "false") << endl;

    return 0;
}