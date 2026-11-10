
class Solution {
public:
    static int climbStairs(int n, vector<int>& costs) {
        int x=0,y=0,z=0;
        for(int cost: costs){
            int ans=x+cost+1;
            ans=min(ans, y+cost+4);
            ans=min(ans, z+cost+9);
            z=exchange(y,x);
            x=ans;
        }
        return x;
    }
};