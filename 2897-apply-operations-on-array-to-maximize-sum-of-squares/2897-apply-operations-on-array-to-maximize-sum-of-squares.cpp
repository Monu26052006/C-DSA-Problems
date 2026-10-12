#pragma GCC optimize("O3")
#include <vector>

class Solution {
public:
    int maxSum(std::vector<int>& nums, int k) {
        // Fast I/O
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);

        const int MOD = 1'000'000'007;
        // nums[i] <= 10^9, which requires up to 30 bits (2^30 > 10^9)
        int bitCount[30] = {0};

        // Step 1: Count the frequency of set bits at each position
        for (int num : nums) {
            for (int i = 0; i < 30; ++i) {
                if ((num >> i) & 1) {
                    bitCount[i]++;
                }
            }
        }

        long long totalSumOfSquares = 0;

        // Step 2: Greedily construct the k largest elements
        for (int step = 0; step < k; ++step) {
            long long currentNum = 0;
            for (int i = 0; i < 30; ++i) {
                if (bitCount[i] > 0) {
                    currentNum |= (1 << i);
                    bitCount[i]--; // Consume the bit for the current largest number
                }
            }
            // Accumulate the square of the constructed number modulo 10^9 + 7
            totalSumOfSquares = (totalSumOfSquares + (currentNum * currentNum) % MOD) % MOD;
        }

        return totalSumOfSquares;
    }
};