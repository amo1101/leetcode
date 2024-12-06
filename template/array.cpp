#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

static void printArray(vector<int>& nums) {
	for (auto i : nums) {
		printf("%d ", i);
	}
	printf("\n");
}

static int partition(vector<int>& nums, int lo, int hi) {
	if (lo == hi) {
		return lo;
	}

	srand(time(0));
	int pivotIndex = lo + rand() % (hi - lo + 1);
	swap(nums[pivotIndex], nums[hi]);
	int pivot = nums[hi];

	for (int i = lo; i < hi; ++i) {
		if (nums[i] < pivot) {
			swap(nums[i], nums[lo++]);
		}
	}

	swap(nums[lo], nums[hi]);
	return lo;
}

void myQuickSort(vector<int>& nums, int lo, int hi) {
	if (lo < hi) {
		int p = partition(nums, lo, hi);
		myQuickSort(nums, 0, p - 1);
		myQuickSort(nums, p + 1, hi);
	}
}

static void reverse(vector<int>& nums, int lo, int hi) {
	while (lo < hi) {
		swap(nums[lo++], nums[hi--]);
	}
}

void rotateWithReverse(vector<int>& nums, int k) {
	int numSize = nums.size();
	k %= numSize;
	reverse(nums, 0, numSize - 1);
	reverse(nums, 0, k -1);
	reverse(nums, k, numSize - 1);
}

// cyclic replacement 
void cyclicRotate(vector<int>& nums, int k) {
	int numSize = nums.size();
	k %= numSize;
	int prev = 0;
	int temp = 0;
	int i = 0, j = 0, start = 0, cnt = 0;
	while (cnt < numSize) {
		i = start;
		prev = nums[i];
		do {
			j = (i + k) % numSize;
			temp = nums[j];
			nums[j] = prev;
			prev = temp;
			cnt++;
			i = j;
		} while (i != start);
		start++;
	}
}

// Matrix diagonal traverse
void diagonalTraverse(vector<vector<int>>& nums, vector<int>& result) {
	int M = nums.size();
	int N = nums[0].size();
	int r = 0, c = 0;
	result.push_back(nums[0][0]); // frist upwards take
	
	while (1) {
		// downwards
		if (c + 1 < N) {
			result.push_back(nums[r][++c]);
		} else if (r + 1 < M) {
			result.push_back(nums[++r][c]);
		} else {
			break;
		}

		while (r + 1 < M && c - 1 >= 0) {
			result.push_back(nums[++r][--c]);
		}

		// upwards
		if (r + 1 < M) {
			result.push_back(nums[++r][c]);
		} else if (c + 1 < N) {
			result.push_back(nums[r][++c]);
		} else {
			break;
		}

		while (r - 1 >= 0 && c + 1 < N) {
			result.push_back(nums[--r][++c]);
		}
	}
}

void spiralTraverse(vector<vector<int>>& nums, vector<int>& result) {
	int M = nums.size();
	int N = nums[0].size();
	int left = 0;
	int right = N - 1;
	int up = 0;
	int down = M - 1;

	while (result.size() < M * N) {
		// left -> right
		for (int c = left; c <= right; ++c) {
			result.push_back(nums[up][c]);
		}

		// up -> down
		for (int r = up + 1; r <= down; ++r) {
			result.push_back(nums[r][right]);
		}

		// right -> left
		if (up != down) {
			for (int c = right - 1; c >= left; --c) {
				result.push_back(nums[down][c]);
			}
		}

		// down -> up
		if (left != right) {
			for (int r = down - 1; r > up; --r) {
				result.push_back(nums[r][left]);
			}
		}

		left++;
		right--;
		up++;
		down--;
	}
}

void testArray() {
	vector<vector<int>> nums({{ 1,2,3 }, { 4, 5, 6 }, { 7, 8, 9 }});
	vector<int> result;
	spiralTraverse(nums, result);
	printArray(result);
}