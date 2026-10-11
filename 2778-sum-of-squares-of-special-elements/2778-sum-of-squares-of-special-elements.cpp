class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        const int n=nums.size();
        static unsigned long long isSq=(1<<1)+(1<<4)+(1<<9)+(1<<16)
        +(1<<25)+(1ULL<<36)+(1ULL<<49);
        int sum=nums[0]*nums[0];
        if (n==1) return sum;
        sum+=nums[n-1]*nums[n-1];
        int n0=n-((isSq>>n)&1), i=2;
        for( ; i*i<=n0; i++){
            auto [j, r]=div(n, i);
            if (r==0) 
                sum+=nums[i-1]*nums[i-1]+(nums[j-1]*nums[j-1]);
        }
        return sum+((isSq>>n)&1)*(nums[i-1]*nums[i-1]);
    }
};