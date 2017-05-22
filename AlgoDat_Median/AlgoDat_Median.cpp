// AlgoDat_Median.cpp : Defines the entry point for the console application.
//

#include <cstdint>
#include <cassert>
#include "stdafx.h"
#include <fstream>
#include <sstream>

#include "Timer.h"
#include "XorShift.h"

// print the Array to console
template <typename T>
void printArray(T *array, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		std::cout << array[i] << " " << std::endl;
	}
	std::cout << std::endl;
}
/*
template <typename T>
int partitionQuickS(T *array, size_t left, size_t right)
{
	size_t l = left;
	size_t r = right - 1;

	//T pivot = array[r];
	T pivot = array[rand() % (right-left) + l];

	while (l < r) {
		while (array[r] > pivot && r > l) {
			r--;
		}

		while (array[l] < pivot && l <= r) {
			l++;
		}

		if (l < r) {
			std::swap(array[l], array[r]);
			l++;
		}
	}
	return l;
}
*/

// partition array around pivot element 
template <typename T>
int partition(T *array, size_t left, size_t right)
{ 
	// gets the pivot element from randomized partition -> pivot at end
	T pivot = array[right];
	int i = left - 1;
	// partition
	for (int j = left; j < right; j++) {
		if (array[j] <= pivot) {
			i++;
			std::swap(array[i], array[j]);
		}
	}
	// swap back the pivot element and return the location
	std::swap(array[i + 1], array[right]);
	return i + 1;
}

// quickSort algorithm
template <typename T>
void quickSort(T *array, size_t left, size_t right)
{
	size_t size = right - left;

	if (size >= 1) {
		// call randomized partition to partition around random pivot element
		int p = Randomized_Partition(array, left, right);

		// recursion -> call once for left part of pivot and once for right part
		if (left < p) { 
			quickSort(array, left, p-1); }
		if (p < right) { 
			quickSort(array, p+1, right); }
	}
}

// select random pivot in the correct range of given input data
template <typename T>
int Randomized_Partition(T *array, size_t left, size_t right)
{
	int i = rand() % (right - left) + left; 
	// swap pivot with end element of array
	std::swap(array[i], array[right]);
	// call the partition function -> swaps pivot back to correct pos
	return partition(array, left, right);
}

// Randomized Select Recursive Algorithm
template <typename T>
int Randomized_Select(T *array, size_t left, size_t right, size_t i)
{
	// size of 1 -> return element
	if (left == right)
		return array[left];
	// call random partition routine and partition the array into two subarrays
	int q = Randomized_Partition(array, left, right);
	// calculate number of elements in the low part of the array
	int k = q - left + 1;
	// if it is the ith smallest element return it
	if (i == k)
		return array[q];
	// call only the half where the ith element is inside
	// if i is smaller then the element is in the lower half
	else if (i < k)
		return Randomized_Select(array, left, q - 1, i);
	// if not the element is in the higher half
	else return Randomized_Select(array, q + 1, right, i - k);
}

template <typename T>
int medianofmedians_select(T *array, size_t left, size_t right, int n)
{
	int pivotindex;
	if (left == right)
	{
		return left;
	}
	while(true)
	{
		pivotindex = medianofmedians_pivot(array, left, right);
		pivotindex = medianofmedians_partition(array, left, right, pivotindex);
		if (n == pivotindex) return n;
		else if (n < pivotindex) right = pivotindex - 1;
		else left = pivotindex + 1;
	}
	return 0;
}
template <typename T>
void medianofmedians_Swap(T *array, int left, int right)
{
	T swapValue  = array[left];
	array[left]  = array[right];
	array[right] = swapValue;
}

template <typename T>
int medianofmedians_partition(T *array, size_t left, size_t right, int pivotindex)
{
	T pivotValue = array[pivotindex];
	medianofmedians_Swap(array,pivotindex,right);

	int storeIndex = left;
	for (int i = left; i <= right - 1; i++)
	{
		if (array[i] < pivotValue)
		{
			medianofmedians_Swap(array, storeIndex, i);
			storeIndex++;
		}
	}
	medianofmedians_Swap(array,storeIndex,right);
	return storeIndex;
}

template <typename T>
int insertionSort(T* array, size_t left, size_t right)
{
	for (int i = left; i < right-1; i++)
	{
		T x = array[i];
		int j = i;
		while (j > 0 && array[j - 1] > x)
		{
			array[j] = array[j - 1];
			j = j - 1;
		}
		array[j] = x;
	}
	return floor((left+right)/2);
}

template <typename T>
int medianofmedians_pivot(T* array, size_t left, size_t right)
{
	if (right - left < 5)
		return insertionSort(array, left, right);
	for (int i = left; i < right; i+=5)
	{
		int subright = i+4;
		if (subright > right) subright = right;
		int median5 = insertionSort(array, i, subright);
		medianofmedians_Swap(array, median5, left + (floor((i - left) / 5)));
	}
	return medianofmedians_select(array, left, left + ceil((right - left) / 5) - 1, left + (right - left) / 10);
}

void saveTestData(std::string filename, int* array, int length)
{
	using namespace std;
	ofstream file;

	file.open(filename);
	for (int i = 0; i < length; i++)
	{
		file << array[i] << '\n';
	}
	file.close();
}

int main(void)
{
	int numberofTests = 10;
	TimerFunc timer;
	size_t size = 2000000;
	XorShift* generator = new XorShift(3, 12, 49, 158);
	int *array = new int[size];
	int *array_q = new int[size];
	int *array_t = new int[size];
	int *array_m = new int[size];

	std::cout << "Time-Format: hh:mm:ss.ms\n";

	for (int j = 0; j < numberofTests; j++)
	{
		float median = 0;
		// create random numbers with XorShift algorithm and store it in arrays for the computation
		for (int i = 0; i < size; ++i) {
			array[i] = generator->Random();
			array_q[i] = array[i];
			array_t[i] = array[i];
			array_m[i] = array[i];
		}
		std::string filename = "testdata" + std::to_string(j) + ".txt";
		saveTestData(filename, array, size);

		//printArray(array, size);
		timer.startTimer();
		// Median using nth Element ***********************************
		std::nth_element(array, array + (size - 1) / 2, array + size);
		median = array[(size - 1) / 2];
		timer.stopTimer('n');

		std::cout << "nth-Element Median = " << median << std::endl;

		timer.startTimer();
		// quicksort with fixed pivot element *************************
		quickSort(array_q, 0, size - 1);
		timer.stopTimer('q');

		median = array_q[(size - 1) / 2];

		std::cout << "Quicksort Random-Pivot Median = " << median << std::endl;

		int out;
		timer.startTimer();
		// randomized select ******************************************
		// -> find kth smallest element -> size + 1 (not starting from 0)
		out = Randomized_Select(array_t, 0, size - 1, (size + 1) / 2);
		timer.stopTimer('r');

		std::cout << "Randomized Select Median = " << out << std::endl;

		int medianofmedians;
		timer.startTimer();
		// medianofmedians select ******************************************
		medianofmedians = medianofmedians_select(array_m, 0, size - 1, (size - 1) / 2);
		timer.stopTimer('m');

		std::cout << "Median of Medians Median = " << array_m[medianofmedians] << std::endl;

		//printArray(array_q, size);

	}
	timer.saveTimes("testresults.txt");

	delete[] array;
	delete[] array_q;
	delete[] array_t;
	delete[] array_m;

	getchar();
	return 0;
}



