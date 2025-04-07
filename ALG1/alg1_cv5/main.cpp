#include <iostream>
#include <stack>


void bubbleSort(int* arr, int N) {
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void printArray(int* arr, int N) {
	for (int i = 0; i < N; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void printTowers(std::stack<int> A, std::stack<int> B, std::stack<int> C, int M) {
	for (int i = M; i > 0; i--) {
		if (A.size() == i) {
			std::cout << A.top() << "\t";
			A.pop();
		}
		else {
			std::cout << "|\t";
		}
		if (B.size() == i) {
			std::cout << A.top() << "\t";
			A.pop();
		}
		else {
			std::cout << "|\t";
		}
		if (A.size() == i) {
			std::cout << A.top();
			A.pop();
		}
		else {
			std::cout << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool isMoveValid(std::stack<int> src, std::stack<int> dest) {
	return (!src.empty() && (dest.empty() || src.top() < dest.top()));
}

void moveDisk(std::stack<int>& src, std::stack<int>& dest) {
	if (isMoveValid(src, dest)) {
		dest.push(src.top());
		src.pop();
	}
	else {
		src.push(dest.top());
		dest.pop();
	}
}

void towersOfHanoi(std::stack<int>& src, std::stack<int>& aux, std::stack<int>& dest, int M) {
	if (M == 1) {
		moveDisk(src, dest);
		return;
	}
	towersOfHanoi(src, dest, aux, M - 1);
	moveDisk(src, dest);
	towersOfHanoi(aux, src, dest, M - 1);
}

int main() {
	/*int N = 5;
	int arr[] = { 4, 3, 1, 5, 2 };*/

	/*bubbleSort(arr, N);
	printArray(arr, N);*/

	int M = 4;
	std::stack<int> A;
	std::stack<int> B;
	std::stack<int> C;

	for (int i = M; i > 0; i--) {
		A.push(i);
	}

	printTowers(A, B, C, M);
	towersOfHanoi(A, B, C, M);
	printTowers(A, B, C, M);

	return 0;
}