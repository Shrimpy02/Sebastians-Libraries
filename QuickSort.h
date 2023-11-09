
#pragma once
// include libraries
#include <vector>

using namespace std;


class QuickSort
{
public:
	/**
	 * \brief Constructor for the Quick sorting algorithm
	*/
	QuickSort()
	{
		
	}


	/**
	 * \brief Sorts the input recursively by dividing the data-sett between a pivot
	 * then sorting the smaller sections with the same method
	 * \param nums The vector to be sorted
	 * \param start The start index of the vector, generally 0
	 * \param end The end index of the vector, vector.size()-1
	 */
	void sort(vector<float>& nums, int start, int end)
	{
		// Ends sort if there are no elements
		if (nums.empty()) return;

		if (start < end) {
			int pivotIndex = partition(nums, start, end);
			sort(nums, start, pivotIndex - 1);
			sort(nums, pivotIndex + 1, end);
		}
	}

		/**
		 * \brief Moves elements less then or equal to the pivot point to the left of it
		 * and elements higher than the pivot point to the right of it
		 * \param nums The vector to be divided
		 * \param start The starting position of the vector
		 * \param end The ending position of the vector
		 * \return Returns itself as the pivot index
		 */
		int partition(vector<float>& nums, int start, int end)
		{
				float pivot = nums[end];
				int index = start - 1;

				for (int j = start; j < end; j++) {
					if (nums[j] < pivot) {
						index++;
						swap(nums[index], nums[j]);
					}
				}
				index++;
				swap(nums[index], nums[end]);
				return index;
		}

			/**
			 * \brief swaps values a with b through the values address
			 * \param a Location a
			 * \param b Location b
			 */
		void swap(float& a, float& b)
		{
			float temp = a;
			a = b;
			b = temp;
		}

};