
class Solution {
public:
    long long MOD = 1e9 + 7;

    long long power(long long base, long long exp) {

        long long ans = 1;

        while (exp > 0) {

            // If exponent is odd
            if (exp % 2 == 1) {
                ans = (ans * base) % MOD;
            }

            // Square the base
            base = (base * base) % MOD;

            // Divide exponent by 2
            exp = exp / 2;
        }

        return ans;
    }

    int countGoodNumbers(long long n) {

        long long even = (n + 1) / 2;
        long long odd = n / 2;

        long long first = power(5, even);
        long long second = power(4, odd);

        return (first * second) % MOD;
    }
};
