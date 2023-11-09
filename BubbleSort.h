
#pragma once
// Include Library
#include <vector>

using namespace std;


class BubbleSort
{
public:
	/**
	 * \brief Constructor for the bubble sorting algorithm
	 */
	BubbleSort()
	{
		
	}

		/**
		 * \brief Bubble sorts input iteratively 
		 * \param nums Address to the vector that gets sorted
		 */
		void sort(vector<float>& nums)
		{
			// Ends the sorting function if there is nothing to sort
			if (nums.empty()) return;

			// Checks elements one by one and swaps them if unsorted
			for (int i = 0; i < (nums.size() - 1); i++)
			{
				if (nums[i] > nums[i + 1])
					swap(nums, i);
			}

			// Checks if the order is correct, if not sort again
			if (!CheckOrder(nums))
				sort(nums);
		}

			/**
			 * \brief Swaps two elements in the given vector
			 * \param nums Address to the array that gets it's elements swapped
			 * \param i The indexes that should be swapped
			 */
			void swap(vector<float>& nums, int i)
			{
					float temp = nums[i];
					nums[i] = nums[i + 1];
					nums[i + 1] = temp;
			}

		/**
		 * \brief Checks if input is sorted in ascending order
		 * \param nums Address to he vector that has been sorted
		 * \return returns true if input successfully sorted
		 */
		bool CheckOrder(vector<float>& nums)
		{
			// Iteratively trough the vector, returns true if sorted
			for (int i = 0; i < (nums.size() - 1); i++)
			{
				if (nums[i] > nums[i + 1])
					return false;
			}
			return true;
		}
};




