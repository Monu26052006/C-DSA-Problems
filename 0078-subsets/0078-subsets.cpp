
class Solution {
public:

    void solve(int index, vector<int>& nums,
               vector<int>& current,
               vector<vector<int>>& ans) {

        // Base case
        if (index == nums.size()) {
            ans.push_back(current);
            return;
        }

        // Case 1: Don't pick the element
        solve(index + 1, nums, current, ans);

        // Case 2: Pick the element
        current.push_back(nums[index]);

        solve(index + 1, nums, current, ans);

        // Backtracking
        current.pop_back();
    }

    vector<vector<int>> subsets(vector<int>& nums) {

        vector<vector<int>> ans;
        vector<int> current;

        solve(0, nums, current, ans);

        return ans;
    }
};
