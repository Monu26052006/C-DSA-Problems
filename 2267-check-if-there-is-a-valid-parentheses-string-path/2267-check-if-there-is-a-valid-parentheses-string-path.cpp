#include <vector>

class Solution {
private:
    // mem[i][j][k] stores whether a valid path can be formed from (i, j) with current balance k
    // 0: Unvisited, 1: Valid path possible, 2: Invalid path
    char mem[101][101][101]; 
    int max_m, max_n;

    bool dfs(int i, int j, int k, const std::vector<std::vector<char>>& grid) {
        // Track balance changes: '(' adds 1, ')' subtracts 1
        k += (grid[i][j] == '(') ? 1 : -1;

        // Pruning: if balance drops below 0, it's invalid
        if (k < 0) return false;

        // Pruning: if current balance exceeds remaining steps left to take, it can never reach 0
        int remaining_steps = (max_m - 1 - i) + (max_n - 1 - j);
        if (k > remaining_steps) return false;

        // Base case: Reached the bottom-right corner
        if (i == max_m - 1 && j == max_n - 1) {
            return k == 0;
        }

        // Return cached result if already calculated
        if (mem[i][j][k] != 0) {
            return mem[i][j][k] == 1;
        }

        bool match = false;
        // Move Down
        if (i + 1 < max_m) {
            match = match || dfs(i + 1, j, k, grid);
        }
        // Move Right
        if (j + 1 < max_n) {
            match = match || dfs(i, j + 1, k, grid);
        }

        // Cache the result (1 for true, 2 for false)
        mem[i][j][k] = match ? 1 : 2;
        return match;
    }

public:
    bool hasValidPath(std::vector<std::vector<char>>& grid) {
        max_m = grid.size();
        max_n = grid[0].size();

        // 1. Initial Validation: Total length of the path must be even
        if ((max_m + max_n - 1) % 2 != 0) return false;

        // 2. Initial Validation: Must start with '(' and end with ')'
        if (grid[0][0] == ')' || grid[max_m - 1][max_n - 1] == '(') return false;

        // Reset the memoization table
        std::memset(mem, 0, sizeof(mem));

        return dfs(0, 0, 0, grid);
    }
};