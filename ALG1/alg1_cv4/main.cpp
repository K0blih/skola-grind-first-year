#include <iostream>
#include <set>

void findValue(int value, int* arr, int N) {
	for (int i = 0; i < N; i++) {
		if (arr[i] == value) {
			std::cout << "Value found at index: " << i << std::endl;
			break;
		}
	}
}

//void uniqueValue(int* arr, int N) {
//	std::set<int> set = {arr, arr + N};
//
//	for (auto i : set) {
//		std::cout << i << " ";
//	}
//	std::cout << std::endl;
//}

void uniqueValue(int* arr, int N) {
	bool* unique = new bool[N];

	for (int i = 0; i < N; i++) {
		unique[i] = true;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) { // j = i + 1;
			if (i != j && arr[i] == arr[j]) { // arr[i] == arr[j]
				unique[i] = false;
				unique[j] = false;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (unique[i]) {
			std::cout << arr[i] << " ";
		}
	}
	std::cout << std::endl;
}

int factorial(int number) {
	if (number == 0) {
		return 1;
	}
	return number * factorial(number - 1);
}

int main() {
	
	int N = 100;
	int value = 9;
	int* arr = new int[N];

	for (int i = 0; i < N; i++) {
		arr[i] = 3; // i*i
	}
	arr[2] = 4;

	//findValue(9, arr, N);
	uniqueValue(arr, N);
	std::cout << factorial(5) << std::endl;

	delete[] arr;
	return 0;
}