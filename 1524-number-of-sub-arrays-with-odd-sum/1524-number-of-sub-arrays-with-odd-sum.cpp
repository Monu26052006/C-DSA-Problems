class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        vector<int> oddPrefixes(arr.size(), 0);
        long long ans = 0, MOD = 1e9+7, sum = 0, total;

        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            if (i > 0) oddPrefixes[i] = oddPrefixes[i-1];
            if (sum % 2) oddPrefixes[i]++;
        }

        sum = arr[0];
        if (sum % 2) ans++;

        for (int i = 1; i < arr.size(); i++) {
            sum += arr[i];

            if (sum % 2) {
                total = i;
                ans = (ans + total - oddPrefixes[i-1] + 1) % MOD;
            } else {
                ans = (ans + oddPrefixes[i-1]) % MOD;
            }
        }

        return ans;
    }
};