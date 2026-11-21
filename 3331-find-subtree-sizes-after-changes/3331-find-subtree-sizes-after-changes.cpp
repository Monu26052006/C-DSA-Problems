class Solution {
public:
    unordered_map<int, vector<int>> adj;
    vector<int> v;
    vector<int> ans;

    void solve(string& s, vector<int>& parent, int curr) {
        int c = s[curr] - 'a';
        int last = v[c];
        v[c] = curr;
        for (auto it : adj[curr]) {
            solve(s, parent, it);
        }
        v[c] = last;

        if (curr != 0) {
            int t = parent[curr];
            if(last != -1){
                t = last;
            }
            parent[curr] = t;
            ans[t] += ans[curr];
        }
    }
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }
        ans.assign(n, 1);
        v.assign(26,-1);
        solve(s,parent,0);
        return ans;
    }
};