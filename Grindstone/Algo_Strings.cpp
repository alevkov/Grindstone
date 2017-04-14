//
//  Algo_Strings.cpp
//  Grindstone
//
//  Created by sphota on 8/11/16.
//  Copyright © 2016 Intellex. All rights reserved.
//

#include "Algo_Strings.hpp"

/* Function to reverse vowels in string */

static bool isVowel(char c) {
	if(c=='a'||c=='A'||c=='e'||c=='E'||c=='i'||c=='I'||c=='o'||c=='O'||c=='u'||c=='U') {
		return true;
	}
	else return false;
}

std::string reverseVowels(std::string s) {
	if (s.length() <= 1) return s;
	int i = 0;
	int j = (uint32_t)s.length() - 1;
	while (j != i) {
		if (isVowel(s[i]) && isVowel(s[j]))
			std::swap(s[i++], s[j--]);
		if (j == i || abs(j - i) == 1)
			break; // have to check twice because incrementing twice
		if (!isVowel(s[i])) i++;
		if (!isVowel(s[j])) j--;
	}
	return s;
}

/* Check if string is permutation of palindrome */

bool isPalindromePermutation(std::string & s) {
	if (s.length() <= 1) return true;
	int i = 0;
	while (i < s.length()) {
		char c = s[i];
		if (s.find(c, i + 1) != std::string::npos) {
			s.erase(s.begin() + i);
			size_t idx = s.find(c);
			s.erase(s.begin() + idx);
		} else
			i++;
	}
	return s.length() > 1 ? false : true;
}

/* Check if all chars in string are unique */

bool isUnique(std::string & s) {
	std::map<unsigned int, char> map;
	if (s.length() == 0 || s.length() == 1) return true;
	map[s[0]] = s[0];
	for (int i = 1; i < s.length(); i++) {
		if (map[s[i]] != '\0') return false;
		map[s[i]] = s[i];
	}
	return true;
}

std::string longestCommonPrefix(std::vector<std::string>& strs) {
	if (strs.empty()) return "";
	else if (strs.size() == 1) return strs[0];
	std::string prefix = strs[0];
	for (int i = 1; i < strs.size(); i++) {
		int j = 0, k = 0;
		while (j < prefix.length()) {
			if (prefix[j] == strs[i][j])
				k++;
			j++;
		}
		prefix = prefix.substr(0, k);
	}
	
	return prefix;
}

/* Super Reduced String */

int filterReduce(std::string & s) {
	int r = 0, i = 0;
	while (i < s.size() - 1) {
		if (s[i + 1] == s[i]) {
			s.erase(s.begin() + i);
			if (s.empty()) {
				return 0;
			}
			s.erase(s.begin() + i);
			if (s.empty()) {
				return 0;
			}
			r = 1;
		} else i++;
	}
	if (s.size() == 1)
		std::cout << s << std::endl;
	if (r == 0)
		std::cout << s << std::endl;
	return r;
}

std::string superReducedString(std::string & s) {
	int r = 1;
	while (r > 0) r = filterReduce(s);
	return s;
}

/* Length of Longest Path */

int lengthLongestPath(std::string input) {
	std::vector<int> depth(100, 0);
	int maxLength = 0;
	std::cout << input;
	std::string currentName;
	std::stringstream ss(input);
	while (getline(ss, currentName, '\n')) {
		int count = 0;
		size_t position = currentName.find_last_of(' ');
		if (position == std::string::npos) count = 0;
		else count = (int)position + 1;
		if (currentName.find(".") == std::string::npos)
			depth[count+1] = depth[count] + (int)currentName.size() - count;
		else {
			if (currentName.find(".jpeg") != std::string::npos || currentName.find(".png") != std::string::npos || currentName.find(".gif") != std::string::npos)
				maxLength = std::max(maxLength, (int)(depth[count]));
		}
	}
	return maxLength;
}

