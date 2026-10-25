class Solution {
private:
    void Flood(vector<vector<int>>& grid,int i,int j){
        int n = grid[0].size();
        int m = grid.size();
        if(i<0 || i>=m || j<0 ||j>=n){
            return;
        }
        if(grid[i][j]==1){
            return;
        }
        grid[i][j]=1;
        Flood(grid,i+1,j);
        Flood(grid,i-1,j);
        Flood(grid,i,j+1);
        Flood(grid,i,j-1);
    }


    void Flush(vector<vector<int>>& grid,int i,int j){
        int n = grid[0].size();
        int m = grid.size();
        if(i<0 || i>=m || j<0 ||j>=n){
            return;
        }
        if(grid[i][j]==1){
            return;
        }
        grid[i][j]=1;
        Flush(grid,i+1,j);
        Flush(grid,i-1,j);
        Flush(grid,i,j+1);
        Flush(grid,i,j-1);
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        int n = grid[0].size();
        int m = grid.size();
        int ans = 0;
        for(int i{};i<m;i++){
            for(int j{};j<n;j++){
                if(grid[i][j]==0){
                    if(i==0 || i==m-1 || j==0 || j==n-1){
                        Flood(grid,i,j);
                    }
                }
            }
        }


        for(int i{};i<m;i++){
            for(int j{};j<n;j++){
                if(grid[i][j]==0){
                    ans+=1;
                    Flush(grid,i,j);
                }               
            }
        }

        return ans;
    }
};