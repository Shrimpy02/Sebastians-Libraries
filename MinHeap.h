#pragma once
#include <iostream>
using namespace std;

class MinHeap
{
public:
	/**
	 * \brief Constructor for the MaxHeap
	 * \param _size initializes the heap size
	 */
	MinHeap(int _size)
	{
		heapSize = _size;
	}

	/**
	 * \brief Function to insert a new value into the heap.
	 * \param _arr The array the heap should add an element too.
	 * \param _value The value to insert.
	 */
	void insertValue(double _arr[], double _value)
	{
		// increases the heap size since a new value is added. 
		heapSize++;

		// adds the new value to the last array index. 
		_arr[heapSize - 1] = _value;

		// calls heapify to order the now unordered array into a max heap.
		heapify(_arr, heapSize, heapSize - 1);
	}

	/**
	 * \brief Function to print the heap.
	 * \param _arr the array to print.
	 */
	void printHeap(double _arr[])
	{
		// prints the entire used part of the array.
		for (int i = 0; i < heapSize; ++i)
			cout << _arr[i] << " ";

		cout << "\n";
	}

	/**
	 * \brief Function to print the root of the heap, IE the largest value in the array.
	 * \param _arr the array to read.
	 */
	void printHeapRoot(double _arr[])
	{
		cout << _arr[0] << endl;
	}

	/**
	 * \brief A test function to try out the class functions.
	 */
	void testHeap()
	{
		// initializing of heap as a static array of size 1000.
		const int heapMaxSize = 1000;
		double testHeap[heapMaxSize] = { 10, 7, 11, 5, 4, 13 };
		int size = 6;
		int newValue = 1;

		// creating the heap object
		// this is not necessary in the test function, but is necessary outside of this class.
		MinHeap heap(size);

		// calling insert value with the new value
		heap.insertValue(testHeap, newValue);

		// printing the result.
		heap.printHeap(testHeap);
	}

private:
	/**
	 * \brief The heap size.
	 */
	int heapSize = 0;

	/**
	 * \brief A recursive helper function that orders the heap after a new value has been inserted.
	 * \param _arr the heap array to heapify.
	 * \param _size the size of the heap.
	 * \param _index the index the new value is located at.
	 */
	void heapify(double _arr[], int _size, int _index)
	{
		// gets the parent of the current value.
		int parent = (_index - 1) / 2;

		// checks if the value of the parent is greater than 0 
		if(_arr[parent] > 0)
		{
			if(_arr[parent] > _arr[_index])
			{
				// swaps the parent and the new value so the greater value becomes the highest. 
				swap(_arr[_index], _arr[parent]);
				// calls heapify recursively with the parent to make sure it gets the correct position. 
				heapify(_arr, _size, parent);
			}
			
		}
		
	}
};
