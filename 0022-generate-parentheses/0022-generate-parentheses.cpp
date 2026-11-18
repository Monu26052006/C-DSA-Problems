
class Solution {
public:

    void solve(int n, int open, int close,
               string &current, vector<string>& ans) {

        // Base case
        if(current.size() == 2 * n) {
            ans.push_back(current);
            return;
        }

        // Choice 1: Opening bracket
        if(open < n) {
            current.push_back('(');

            solve(n, open + 1, close, current, ans);

            current.pop_back();  // Backtrack
        }

        // Choice 2: Closing bracket
        if(close < open) {
            current.push_back(')');

            solve(n, open, close + 1, current, ans);

            current.pop_back();  // Backtrack
        }
    }

    vector<string> generateParenthesis(int n) {

        vector<string> ans;
        string current = "";

        solve(n, 0, 0, current, ans);

        return ans;
    }
};
