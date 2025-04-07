#include "Set.h"


int main()
{
	int arr1[] = { 1,2,2,3,3,3 };
	int arr2[] = { 2,4,4,4,4,5,5,5,5,5 };
	Set set1 = Set(arr1, 6);
	Set set2 = Set(arr2, 9);
	Set set3 = Set(arr1, 6);
	Set* setUnion = set1.unionSet(set2);
	Set* setCompelement = set3.complementSet(set2);

	setUnion->print();
	setCompelement->print();
	return 0;
}