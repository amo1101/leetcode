#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

// template 1, At least 1 element in the search space
// usage: 
// 1. find a specific number
// 2. find ceiling of a specific number, return low
// 3. find floor of a specific number, return high
int binarySearch1(vector<int>& nums, int target) {
	if (nums.size() == 0) {
		return -1;
	}

	int lo = 0;
	int hi = nums.size() - 1;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] < target) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}

	return -1;
}

// template 2
// At least 2 elements are in search space
// post process needed for the last element left
int binarySearch2(vector<int>& nums, int target) {
	if (nums.size() == 0) {
		return -1;
	}

	int lo = 0;
	int hi = nums.size();// let low get to nums.size()
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] < target) {
			lo = mid + 1;
		} else {
			hi = mid;
		}
	}

	if (lo != nums.size() && nums[lo] == target) {
		return lo;
	}
	return -1;
}

// template 3
// At least 3 elements are in search space
// post process needed for the last 2 elements left
int binarySearch2(vector<int>& nums, int target) {
	if (nums.size() == 0) {
		return -1;
	}

	int lo = 0;
	int hi = nums.size() - 1;
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (nums[mid] == target) {
			return mid;
		} else if (nums[mid] < target) {
			lo = mid;
		} else {
			hi = mid;
		}
	}

	if (nums[lo] == target) return lo;
	if (nums[hi] == target) return hi;
	return -1;
}


void testBinarySearch() {
	vector<int> nums({ 1,3,5,7,9,11,15 });
	int idx = binarySearch1(nums, 0);
	printf("value %d\n", idx);
}