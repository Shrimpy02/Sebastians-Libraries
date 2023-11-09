
#pragma once
// include libraries
#include <vector>

using namespace std;


class MergeSort
{
public:
	/**
	* \brief Constructor for the Merge sorting algorithm
	*/
	MergeSort()
	{
		
	}

	/**
	* \brief recursively breaks down a vector
	* into sub vectors then sorts them while merging back
	* \param nums The vector to be sorted
	* \param start The start index of the vector, generally 0
	* \param end The end index of the vector, vector.size() - 1
	 */
	void sort(vector<float>& nums, int start, int end) {

		if (start < end)
		{
			int middle = start + (end - start) / 2;

			sort(nums, start, middle);
			sort(nums, middle + 1, end);

			merge(nums, start, middle, end);
		}
	}

		/**
		 * \brief Sub function of merge sort, this is what
		 * actually sorts and re merges the vectors.
		 * \param nums the input vector for merging 
		 * \param start the starting index of input vector
		 * \param middle the middle index of input vector
		 * \param end the end index of input vector
		 */
		void merge(vector<float>& nums, int start, int middle, int end)
		{
				int indexstart = middle - start + 1;
				int indexend = end - middle;

				vector<float> leftside(indexstart);
				vector<float> rightside(indexend);

				for (int i = 0; i < indexstart; i++)
					leftside[i] = nums[start + i];
				for (int i = 0; i < indexend; i++)
					rightside[i] = nums[middle + i + 1];

				int i = 0, j = 0, k = start;
				while (i < indexstart && j < indexend)
				{
					if (leftside[i] <= rightside[j])
					{
						nums[k] = leftside[i];
						i++;
					}
					else {
						nums[k] = rightside[j];
						j++;
					}
					k++;
				}

				while (i < indexstart) // remaining left
				{
					nums[k] = leftside[i];
					i++;
					k++;
				}
				while (j < indexend) // remaining right
				{
					nums[k] = rightside[j];
					j++;
					k++;

				}
		}
};