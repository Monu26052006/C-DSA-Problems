class Solution {
public:
    bool isValid(string& str) {
        // Odd length strings can never have valid pairs
        if (str.size() % 2)
            return false;

        int j = 0; // Stack pointer

        for (char i : str) {
            // Opening brackets: '(', '[', '{' do not end in binary '01' (val & 3 != 1)
            if ((i & 3) != 1) {
                str[j++] = i;
            } 
            // Closing bracket encountered:
            // 1. Check if stack is empty (j == 0)
            // 2. Pop and check if ASCII difference matches 1 or 2 via ((diff + 1) >> 1) == 1
            else if (j == 0 || ((i - str[--j] + 1) >> 1) != 1) {
                return false;
            }
        }

        // Valid only if all opened brackets have been popped
        return j == 0;
    }
};