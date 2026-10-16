
class Solution {
public:
    vector<string> ans;

    void solve(string &s, int pos, int open, int close, int n) {
        if (pos == 2 * n) {
            ans.push_back(s);
            return;
        }

        if (open < n) {
            s[pos] = '(';
            solve(s, pos + 1, open + 1, close, n);
        }

        if (close < open) {
            s[pos] = ')';
            solve(s, pos + 1, open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        ans.clear();
        string s(2 * n, ' ');
        solve(s, 0, 0, 0, n);
        return ans;
    }
};
