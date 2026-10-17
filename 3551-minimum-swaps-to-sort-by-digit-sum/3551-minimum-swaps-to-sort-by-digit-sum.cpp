constexpr int dN=83, M=1e5;
uint64_t A[M], A2[M];
uint8_t viz[M];
int DS[dN];
class Solution {
public:
    static inline int digitSum(int x){
        int sum=0;
        for(; x>0; x/=10){
            sum+=x%10;
        }
        return sum;
    }
    static inline uint64_t pack ( int ds , int x , int i ) {
        return ((uint64_t)ds<<47ULL)+((uint64_t)x<<17ULL)+i ;
    }
    static int minSwaps(vector<int>& nums) {
        const int n=nums.size();
        memset(DS, 0, sizeof(DS));
        for (int i=0; i<n; i++){
            const int x=nums[i], ds=digitSum(x);
            A[i]=pack(ds, x, i);
            DS[ds]++;
        }
        partial_sum(DS, DS+83, DS);
        for(int i=0; i<n; i++){
            const auto info=A[i];
            const int ds=info>>47;
            int idx=--DS[ds];
            A2[idx]=info;
        }
        for(int ds=1; ds<=81; ds++){
            sort(A2+DS[ds], A2+DS[ds+1]);
        }
        memset(viz, 0, n);
        int cnt=0, mask=(1<<17)-1;
        for(int i=0; i<n; i++){
            if (viz[i] || (A2[i]&mask)==i) continue;
            int cycle=0;
            for(int j=i; !viz[j]; j=A2[j]&mask){
                cycle++;
                viz[j]=1;
            }
            cnt+=(cycle-1);
        }
        return cnt;
    }
};
auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();