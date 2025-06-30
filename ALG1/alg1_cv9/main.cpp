#include <iostream>
#include <vector>

bool binarySearchIterative(int* arr, int N, int value)
{
	int l = 0;
	int r = N - 1;

	while (l <= r)
	{
		int M = (l + r) / 2;

		if (value == arr[M])
		{
			return true;
		}
		if (value < arr[M])
		{
			r = M - 1;
		}
		if (value > arr[M])
		{
			l = M + 1;
		}
	}

	return false;
}

bool binarySearchRecursive(int* arr, int l, int r, int value)
{
	if (r < l)
	{
		return false;
	}

	int M = (l + r) / 2;

	if (value == arr[M])
	{
		return true;
	}
	if (value < arr[M])
	{
		return binarySearchRecursive(arr, l, M - 1, value);
	}
	if (value > arr[M])
	{
		return binarySearchRecursive(arr, M + 1, r, value);
	}
}

enum
{
	LEFT = -1,
	RIGHT = 1
};

class ArrowedInt
{
public:
	int value;
	int direction = LEFT;

	ArrowedInt(int value) { this->value = value; }
};

void printInts(std::vector<ArrowedInt*> aInts)
{
	for (auto aInt : aInts)
	{
		std::cout << aInt->value << "\t";
	}
	std::cout << std::endl;
}

bool isMobile(std::vector<ArrowedInt*> aInts, int index)
{
	int direction = aInts[index]->direction;
	if (index <= 0 && direction == LEFT)
	{
		return false;
	}
	if (index >= aInts.size() - 1 && direction == RIGHT)
	{
		return false;
	}
	if (aInts[index + direction]->value < aInts[index]->value)
	{
		return true;
	}

	return false;
}

int getLargestMobileIndex(std::vector<ArrowedInt*> aInts)
{
	int maxValue = INT_MIN;
	int maxIndex = -1;
	for (int i = 0; i < aInts.size(); i++)
	{
		int direction = aInts[i]->direction;
		if (aInts[i]->value > maxValue && isMobile(aInts, i))
		{
			maxValue = aInts[i]->value;
			maxIndex = i;
		}
	}

	return maxIndex;
}

void swapArrowedInts(ArrowedInt*& first, ArrowedInt*& second)
{
	ArrowedInt* temp = first;
	first = second;
	second = temp;
}

void changeDirections(std::vector<ArrowedInt*> aInts, ArrowedInt* aInt)
{
	for (auto arrowedInt : aInts)
	{
		if (arrowedInt->value > aInt->value)
		{
			arrowedInt->direction *= -1;
		}
	}
}

void johnsonTrotter(int N)
{
	std::vector<ArrowedInt*> aInts;

	for (int i = 1; i <= N; i++)
	{
		aInts.push_back(new ArrowedInt(i));
	}
	printInts(aInts);

	int index = getLargestMobileIndex(aInts);

	while (index >= 0)
	{
		int direction = aInts[index]->direction;
		changeDirections(aInts, aInts[index]);
		swapArrowedInts(aInts[index], aInts[index + direction]);

		printInts(aInts);

		index = getLargestMobileIndex(aInts);
	}
}

void printArray(int* arr, int N)
{
	for (int i = 0; i < N; i++)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}

void permute(int* arr, int N, int l, int r)
{
	if (l == r)
	{
		printArray(arr, N);
	}

	for (int i = l; i <= r; i++)
	{
		std::swap(arr[l], arr[i]);
		permute(arr, N, l + 1, r);
		std::swap(arr[l], arr[i]);
	}
}

int partition(int* arr, int l, int r)
{
	int pivot = arr[r];
	int j = l - 1;

	for (int i = l; i < r; i++)
	{
		if (arr[i] <= pivot)
		{
			j++;
			std::swap(arr[i], arr[j]);
		}
		
	}

	j++;
	std::swap(arr[j], arr[r]);

	return j;
}

void quickSort(int* arr, int l, int r)
{
	if (l >= r)
	{
		return;
	}

	int pivotIndex = partition(arr, l, r);

	quickSort(arr, l, pivotIndex - 1);
	quickSort(arr, pivotIndex + 1, r);
}

int main()
{
	int N = 4;
	int* arr = new int[N];

	arr[0] = 10;
	arr[1] = 2;
	arr[2] = 35;
	arr[3] = 1;
	//for (int i = 0; i < N; i++)
	//{
	//	arr[i] = i + 1;
	//}

	//int value = 0;

	//std::cout << "Value: " << value << (binarySearchIterative(arr, N, value) ? " " : " NOT ") 
	//	<< "found"	<< std::endl;
	//std::cout << "Value: " << value << (binarySearchRecursive(arr, 0, N - 1, value) ? " " : " NOT ")
	//	<< "found" << std::endl;

	//permute(arr, N, 0, N - 1);
	quickSort(arr , 0, N - 1);
	printArray(arr, N);

	delete[] arr;
	arr = nullptr;

	//johnsonTrotter(4);
}