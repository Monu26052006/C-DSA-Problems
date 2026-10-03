class Solution {
public:
    int longestValidParentheses(string s) {

        stack<int> st;
        int n = s.size();

        st.push(-1); // Base index
        int max_len = 0;

        for (int i = 0; i < n; i++) {

            // Opening bracket: push its index
            if (s[i] == '(') st.push(i);

            // Closing bracket: pop the top index
            else {

                st.pop();

                // If stack is empty, update the boundary
                if (st.empty()) st.push(i);

                // Calculate the valid substring length
                else max_len = max(max_len, i - st.top());

            }
        }

        return max_len;
        
    }
};