//
//  Algo_DP.cpp
//  Grindstone
//
//  Created by sphota on 8/23/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#include "Algo_DP.hpp"

/* Minimum path sum in a m x n grid */
int minPathSum(std::vector<std::vector<int>>& grid) {
	int n = (int)grid.size(), m = (int)grid[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0 and j == 0)
				continue;
			else if (i == 0)
				grid[i][j] += grid[i][j - 1];
			else if (j == 0)
				grid[i][j] += grid[i - 1][j];
			else
				grid[i][j] += std::min(grid[i][j - 1], grid[i - 1][j]);
		}
	}
	return grid[n - 1][m - 1];
}