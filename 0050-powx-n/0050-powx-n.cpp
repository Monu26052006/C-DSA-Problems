
class Solution {
public:
    double myPow(double x, int n) {

        // Store exponent in long long to avoid overflow
        long long power = n;

        // Use long double for better precision
        long double base = x;
        long double ans = 1.0;

      
        if(power < 0) {
            base = 1.0L / base;
            power = -power;
        }
        while(power > 0) {
            if(power % 2 == 1) {
                ans = ans * base;
            }
            base = base * base;
            power = power / 2;
        }

        return (double)ans;
    }
};
