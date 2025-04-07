#include <iostream>
#include <vector>

void selectionSort(int* arr, int N) {
	for (int i = 0; i < N - 1; i++) {
		int min = i;
		for (int j = i + 1; j < N; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
	}
}

void printArray(int* arr, int N) {
	for (int i = 0; i < N; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void KthLargest(int* arr, int N, int K) {
	selectionSort(arr, N);

	std::cout << arr[N - 1 - K] << std::endl;
}

int minDistance(int* arr, int N) {
	std::vector<int> v1 = { 1, 4, 2, 3, 5 };
	std::vector<int> v2 = { 5, 3, 2, 4, 1 };
	int minDist = INT_MAX;

	for (int i = 1; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			int x = std::sqrt(((v1[i] - v1[j]) * (v1[i] - v1[j])) + (v2[i] - v2[j]) * (v1[i] - v1[j]));
			minDist = std::min(minDist, x);
		}
	}
	return minDist;
}

int main() {
	int arr[] = { 2,3,4,1,5,2,2 };
	int N = 7;
	int K = 1;

	selectionSort(arr, N);
	printArray(arr, N);
	KthLargest(arr, N, K);

	return 0;
}