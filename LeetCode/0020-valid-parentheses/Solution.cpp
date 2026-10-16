
class Solution {
public:
    bool isValid(string s) {
        string st = "";

        for (char ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                st += ch;
            } else {
                if (st.empty()) return false;

                char top = st.back();

                if (ch == ')' && top != '(') return false;
                if (ch == ']' && top != '[') return false;
                if (ch == '}' && top != '{') return false;

                st.pop_back();
            }
        }

        return st.empty();
    }
};
