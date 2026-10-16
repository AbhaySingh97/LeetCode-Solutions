
class Solution {
public:
    vector<string> ans;
    string s;

    void solve(int open, int close, int n) {
        if (s.size() == 2 * n) {
            ans.push_back(s);
            return;
        }

        if (open < n) {
            s.push_back('(');
            solve(open + 1, close, n);
            s.pop_back();
        }

        if (close < open) {
            s.push_back(')');
            solve(open, close + 1, n);
            s.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        ans.clear();
        s.clear();
        solve(0, 0, n);
        return ans;
    }
};
