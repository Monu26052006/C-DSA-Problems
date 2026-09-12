class Solution {
public:

    struct Node {
        long long w = 0;
        array<int,4> idx;

        Node() {
            idx.fill(1e9);
        }
    };

    static bool better(const Node& a, const Node& b) {

        if(a.w != b.w)
            return a.w > b.w;

        return a.idx < b.idx;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        vector<array<int,4>> arr;

        for(int i=0;i<n;i++) {
            arr.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(arr.begin(), arr.end(),
            [&](auto &a, auto &b){
                return a[1] < b[1];
            });

        vector<int> ends;

        for(auto &v: arr)
            ends.push_back(v[1]);

        vector<int> prev(n);

        for(int i=0;i<n;i++) {

            int l = arr[i][0];

            prev[i] =
                lower_bound(
                    ends.begin(),
                    ends.end(),
                    l
                ) - ends.begin() - 1;
        }

        vector<vector<Node>> dp(n+1,
            vector<Node>(5));

        for(int i=1;i<=n;i++) {

            auto &[l,r,w,id] = arr[i-1];

            for(int k=0;k<=4;k++) {

                dp[i][k] = dp[i-1][k];

                if(k==0) continue;

                Node cand;

                int p = prev[i-1];

                if(p==-1)
                    cand = Node();
                else
                    cand = dp[p+1][k-1];

                cand.w += w;

                for(int t=0;t<4;t++) {
                    if(cand.idx[t] == (int)1e9) {
                        cand.idx[t] = id;
                        break;
                    }
                }

                sort(cand.idx.begin(), cand.idx.end());

                if(better(cand, dp[i][k])) {
                    dp[i][k] = cand;
                }
            }
        }

        Node best;

        for(int k=0;k<=4;k++) {
            if(better(dp[n][k], best))
                best = dp[n][k];
        }

        vector<int> ans;

        for(int x: best.idx) {
            if(x != (int)1e9)
                ans.push_back(x);
        }

        return ans;
    }
};