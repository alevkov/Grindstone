//
//  Algo_Misc.cpp
//  Grindstone
//
//  Created by sphota on 8/11/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#include "Algo_Misc.hpp"


/* Binary Search */
//std::vector<int> array = {1, 3, 4, 5, 7, 8, 9};
int search(const int & el, std::vector<int> & array, int start, int end) {
	int mid = (start + end) / 2;
	if (start <= end) {
		if (array[mid] == el)
			return mid;
		else if (array[mid] > el)
			return search(el, array, start, mid - 1);
		else
			return search(el, array, mid + 1, end);
	}
	return mid + 1;
}

// 2, 3, 4, 6, 7, 8, 10, 13
/*
 
 
 */

/* Search Insert */

int binarySearch(std::vector<int>& nums, int target, int low, int high) {
	int mid = (low + high) / 2;
	if (low <= high) {
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] > target) {
			return binarySearch(nums, target, low, mid - 1);
		} else {
			return binarySearch(nums, target, mid + 1, high);
		}
	} else {
		if (target >= nums[nums.size() - 1])
			return (int)nums.size();
		if (target < nums[0])
			return 0;
		return mid + 1; // return the position for insertion
	}
}

int searchInsert(std::vector<int>& nums, int target) {
	return binarySearch(nums, target, 0, (int)nums.size());
}

/* search 2x2 matrix */

int bisearch(const int & el, std::vector<int> & array, int start, int end) {
	if (start <= end) {
		int mid = (start + end) / 2;
		if (array[mid] == el)
			return el;
		else if (array[mid] > el)
			return bisearch(el, array, start, mid - 1);
		else
			return bisearch(el, array, mid + 1, end);
	}
	return -1;
}

bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
	for (std::vector<int> row : matrix) {
		if(bisearch(target, row, 0, (int)row.size()) != -1)
			return true;
		else continue;
	}
	return false;
}

/* FizzBuzz */

void fizzbuzz () {
	for (int i = 1; i <= 100; i++) {
		if (i % 3 != 0 && i % 5 != 0) std::cout << i;
		if (i % 3 == 0) std::cout << "fizz";
		if (i % 5 == 0) std::cout << "buzz";
		std::cout << "\n";
	}
}	

/* a^b[x, y] % 1337  --> BRUTE FORCE */

int superPow(int a, std::vector<int>& b) {
	int m = 1;
	int result = 1;
	int i = (int)b.size() - 1;
	for (; i >= 0; i--) { // O(n)
		b[i] *= m; // turn array into summable parts of exponent
		int p = pow((double)a, ((double)b[i])); // calculate power
		result *= (p % 1337); // calculate mod and accumulate by mutliplying (mod property)
		m *= 10;
	}
	return result % 1337;
}

/* exponentiation by squaring */

long long expBySquaring(long long a, float n) {
	if (n < 0) return expBySquaring(1.0 / a, -n);
	else if (n == 0) return 1;
	else if (n == 1) return a;
	if (((int)n % 2) == 0) {
		return expBySquaring(a * a, n / 2.0);
	} else {
		return a * expBySquaring(a * a, (n - 1) / 2.0);
	}
}

/* inverse of unsigned int */

unsigned int inverse (const int & num) {
	short bits = 0;
	unsigned int copy = num;
	while (copy) {
		copy = copy >> 1;
		bits++;
	}
	unsigned short mask = pow(2, bits) - 1;
	
	return (~num & mask);
}

/* Count set bits of elements in array */

int countBitsAux(int num) {
	int counter = 0;
	while (num > 0) {
		num = num & (num - 1);
		counter = counter + 1;
	}
	return counter;
}

std::vector<int> countBits(int num) {
	std::vector<int> arr(num + 1, 0);
	for (int i = 0; i <= num + 1; i++) {
		arr[i] = countBitsAux(i);
	}
	return arr;
}

/* Count 1's between 0...n */

int countOnesAux(int n) {
	int counter = 0;
	while (n > 0) {
		if (n % 10 == 1)
			counter++;
		n = n / 10;
	}
	return counter;
}

int countDigitOne(long n) {
	if (n == 0) return 0;
	int counter = 0;
	for(int i = 0; i <= n; i++) {
		counter = counter + countOnesAux(i);
	}
	return counter;
}

/* single number */

int singleNumber(std::vector<int>& nums) {
	// std::map<int, int> hm;
	// for (auto & el : nums) {
	//     if (hm.find(el) != hm.end())
	//         hm.erase(el);
	//     else
	//         hm[el] = el;
	// }
	// return hm.begin()->first;
	// std::sort(nums.begin(), nums.end());
	// for (int i = 0; i < nums.size(); i++) {
	//     if (i == 0) {
	//         if (nums[i + 1] != nums[i])
	//             return nums[i];
	//     } else if (i == nums.size() - 1) {
	//         if (nums[i - 1] != nums[i])
	//             return nums[i];
	//     } else {
	//         if (nums[i+1] != nums[i] && nums[i-1] != nums[i])
	//             return nums[i];
	//     }
	// }
	int ret = 0;
	for (int i = 0; i < nums.size(); i++) {
		ret ^= nums[i];
	}
	return ret;
}

/* moves all 0's to end of array */

void moveZeroes(std::vector<int>& nums) {
	int i, j;
	for (i = 0; i < nums.size(); i++) {
		if(nums[i] == 0) {
			j = i;
			while(j < nums.size() - 1) {
				std::swap(nums[j], nums[j + 1]);
				j++;
			}
		}
	}
}

/* remove dupes from sorted array */

int removeDuplicates(std::vector<int>& nums) {
	if (nums.size() == 0) return 0;
	int lastUnique = 0;
	for (int i = 0; i < nums.size(); i++) {
		if (nums[lastUnique] != nums[i]) nums[++lastUnique] = nums[i];
	}
	return lastUnique + 1;
}

/* min sum path in triangle */

int minimumTotal(std::vector<std::vector<int>>& triangle) {
	if (triangle.empty() || triangle[0].empty()) return 0;
	for (int i = (int)triangle.size() - 2; i >= 0; i--) {
		for (int j = 0; j < (int)triangle[i].size(); j++) {
			triangle[i][j] = fmin(triangle[i][j] + triangle[i+1][j], triangle[i][j] + triangle[i+1][j+1]);
		}
	}
	return triangle[0][0];
}

/* flip integer */

int reverse(int x) {
	std::string s = std::to_string(x);
	if (s[0] == '-')
		std::reverse(s.begin() + 1, s.end());
	else
		std::reverse(s.begin(), s.end());
	long int num = strtol(s.c_str(), NULL, 10);
	if (num > INT_MAX || num < INT_MIN)
		return 0;
	return (int)num;
}

int maxSum(std::vector<int>& nums) {
	if (nums.empty()) return 0;
	std::vector<int> maxP;
	maxP.push_back(nums[0]);
	for (int i = 1; i < nums.size(); i++) {
		// [3, -4, 5, 1, -4, 3, 10, 7]
		maxP.push_back(std::max(maxP[i - 1] + nums[i], nums[i]));
	}
	return maxP.back();
}

/*
 1, 3, 5
 3, 4, 10
 2, 3, 1
 
 */

/* Atoi */

bool isDigit(char & c) {
	int i = c - '0';
	return (i >= 0 && i <= 9);
}
int myAtoi(std::string str) {
	long num = 0, m = 1;
	int sign = 1, offset = 0;
	int v[256];
	int size_v = 0;
	for (; offset < str.length(); offset++) {
		if (str[offset] != ' ')
			break;
	}
	if (str[offset] == '+')
		str.erase(str.begin() + offset);
	else if (str[offset] == '-') {
		sign = -1;
		str.erase(str.begin() + offset);
	}
	for (int j = offset; j < str.length(); j++, size_v++) {
		if (isDigit(str[j])) {
			int k = str[j] - '0';
			v[size_v] = k;
		} else break;
	}
	if (size_v == 0) return 0;
	m = sign * m;
	for (int l = size_v - 1; l >= 0 ; l--) {
		num += m * v[l];
		if (num > INT_MAX) return INT_MAX;
		if (num < INT_MIN) return INT_MIN;
		m *= 10;
	}
	return (int)num, m;
}

int solution(std::vector<int> &A) {
	// write your code in C++11 (g++ 4.8.2)
	if (A.size() == 0) {
		return -1;
	} else if (A.size() == 1) {
		return 0;
	} else {
		int sum = 0;
		for (int i = 0; i < A.size(); i++) {
			sum += A[i];
		}
		
		int second_sum = 0;
		for (int i = 0; i < A.size(); i++) {
			int sum_diff = sum - second_sum - A[i];
			
			if (sum_diff == second_sum) {
				return i;
			}
			
			second_sum += A[i];
		}
	}
	return -1;
}

/* Frequency Sort */

//static bool compFunction (std::string i, std::string j) { return (i.size() > j.size()); }

struct comparator {
	bool operator()(std::string f1, std::string f2) { return f1.length() < f2.length(); }
};

std::string frequencySort(std::string s) {
	std::string output = "";
	std::vector<std::string> freqTable;
	std::map<char, std::string> scanTable;
	for(int i = 0; i < s.length(); i++) {
		char key = s[i];
		if(scanTable.find(key) == scanTable.end()) {
			scanTable[key] = "";
		}
		scanTable[key].push_back(key);
	}
	for(auto it = scanTable.begin(); it != scanTable.end(); ++it ) {
		std::string value = it->second;
		freqTable.push_back(value);
	}
	make_heap(freqTable.begin(), freqTable.end(), comparator());
	//std::sort (freqTable.begin(), freqTable.end(), compFunction);
	while(!freqTable.empty()) {
		output += freqTable.front();
		pop_heap (freqTable.begin(), freqTable.end()); freqTable.pop_back();
		make_heap(freqTable.begin(), freqTable.end(), comparator());
	}
	// for(string s : freqTable) {
	//     output += s;
	// }
	
	return output;
}

/* Two Sum */

struct Pair {
	int i, j;
};

std::vector<int> twoSum(std::vector<int>& nums, int target) {
	int key = 0;
	int n = nums.size();
	std::vector<int> idx;
	std::map<int, Pair> hm;
	for(int i = 0; i < n; i++) {
		int k = nums[i];
		Pair p;
		hm[k] = p;
		hm[k].i = i;
		nums[i] = target - k;
	}
	for(int j = 0; j < n; j++) {
		int k = nums[j];
		if (hm.find(k) != hm.end() && hm[k].i != j) {
			idx.push_back(hm[k].i);
			idx.push_back(j);
			return idx;
		}
	}
	return idx;
}

/* Median of 2 Sorted Arrays */

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	unsigned long n = nums1.size() + nums2.size();
	vector<int> result(n, 0);
	nums1.push_back(INT_MAX);
	nums2.push_back(INT_MAX);
	int j, k = 0;
	for(int i = 0; i < n; i++) {
		if(nums1[j] <= nums2[k]) {
			result[i] = nums1[j];
			j++;
		} else {
			result[i] = nums2[k];
			k++;
		}
	}
	result.pop_back();
	result.pop_back();
	unsigned long median = n / 2;
	double val;
	if(result.size() % 2 == 0) {
		val = (double)(result[median] + result[median - 1]) / 2.0;
	} else {
		val = (double)(result[median]);
	}
	return val;
}

/* Missing Ranges */

vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
	vector<string> ranges;
	if(nums.empty()) {
		if(lower != upper)
			ranges.push_back(to_string(lower) + "->" + to_string(upper));
		else
			ranges.push_back(to_string(lower));
		return ranges;
	}
	if(lower == upper) return ranges;
	if(nums[0]!= lower) {
		if(nums[0] - lower > 1)
			ranges.push_back(to_string(lower) + "->" + to_string(nums[0] - 1));
		else
			ranges.push_back(to_string(lower));
	}
	for(int i = 0; i < nums.size() - 1; i++) {
		string c = "";
		if(nums[i+1] - nums[i] == 1) continue;
		if(nums[i] + 1 == nums[i + 1] - 1) {
			ranges.push_back(to_string(nums[i] + 1));
			continue;
		}
		c = to_string(nums[i] + 1) + "->" + to_string(nums[i + 1] - 1);
		ranges.push_back(c);
	}
	if(nums.back() != upper) {
		if(upper - nums.back() > 1)
			ranges.push_back(to_string(nums.back() + 1) + "->" + to_string(upper));
		else
			ranges.push_back(to_string(upper));
	}
	return ranges;
}

/* Summary Ranges */

vector<string> summaryRanges(vector<int>& nums) {
	vector<string> ranges;
	if(nums.empty())
		return ranges;
	if(nums.size() == 1) {
		ranges.push_back(to_string(nums[0]));
		return ranges;
	}
	int first = nums[0], last = 0;
	for(int i = 0; i < nums.size(); i++) {
		if(nums[i + 1] - nums[i] == 1)
			continue;
		else {
			last = nums[i];
			if(first == last) {
				ranges.push_back(to_string(first));
				first = nums[i + 1];
				continue;
			}
			ranges.push_back(to_string(first) + "->" + to_string(last));
			first = nums[i + 1];
		}
	}
	
	return ranges;
}

/* ZigZag Iterator */

class ZigzagIterator {
private:
	int currIdx = 0, k = 1;
	vector<int> vector1, vector2;
	bool doneV1 = false, doneV2 = false;
public:
	ZigzagIterator(vector<int>& v1, vector<int>& v2) {
		vector1 = v1;
		vector2 = v2;
	}
	
	int next() {
		doneV1 = currIdx >= vector1.size();
		doneV2 = currIdx >= vector2.size();
		if (k == 1 && !doneV1) {
			int el = vector1[currIdx];
			if (doneV2) {
				currIdx++;
				doneV1 = currIdx >= vector1.size();
				k = 1;
				return el;
			}
			k = 2;
			return el;
		} else if(!doneV2) {
			int el = vector2[currIdx];
			currIdx++;
			doneV1 = currIdx >= vector1.size();
			doneV2 = currIdx >= vector2.size();
			k = 1;
			return el;
		} else {
			return INT_MAX;
		}
	}
	
	bool hasNext() {
		if(vector1.empty() && vector2.empty())
			return false;
		return !(doneV1 && doneV2);
	}
};
