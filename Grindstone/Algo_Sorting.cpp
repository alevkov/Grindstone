//
//  Algo_Sorting.cpp
//  Grindstone
//
//  Created by sphota on 8/14/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#include "Algo_Sorting.hpp"

template <typename T> // assume that < operator is valid / overloaded
void insertionSort(std::vector<T> array) {
	int i, j;
	for (i = 1; i < array.size(); i++) {
		j = i;
		while((j > 0) && array[j] < array[j - 1]) {
			std::swap(array[j], array[j - 1]);
			j = j - 1;
		}
	}
}

//[0, 1, 3, 2, 3, 5, 4, 7]