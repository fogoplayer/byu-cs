#ifndef QUICKSORT_H_
#define QUICKSORT_H_
#include <string>
#include <sstream>
#include <utility>

#include "QSInterface.h"

using namespace std;

template <typename T>
class QuickSort : public QSInterface<T>
{
private:
	size_t capacityCounter;
	size_t sizeCounter;
	T *ptrArray;

	void resize()
	{
		T *newPtrArray = new T[capacityCounter * 2];
		for (size_t i = 0; i < capacityCounter; i++)
		{
			newPtrArray[i] = ptrArray[i];
		}

		delete[] ptrArray;
		ptrArray = newPtrArray;
		capacityCounter *= 2;
	}

	bool recursiveSort(int first, int last)
	{
		int pivot = medianOfThree(first, last);
		pivot = partition(first, last, pivot);
		if (pivot > 0) // Negative pivot means too small range
		{
			recursiveSort(first, pivot);
			recursiveSort(pivot + 1, last);
		}
		return true;
	}

public:
	QuickSort(size_t capacityCounter) : capacityCounter(capacityCounter), ptrArray(new T[capacityCounter]()), sizeCounter(0)
	{
		// ptrArray = {0};
	}
	virtual ~QuickSort()
	{
		if (ptrArray != nullptr)
		{
			delete[] ptrArray;
			ptrArray = nullptr;
		}
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element)
	{

		if (ptrArray[capacityCounter - 1] != T())
		{
			resize();
		}

		ptrArray[sizeCounter] = element;
		++sizeCounter;

		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right)
	{
		return true;
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll()
	{
		recursiveSort(0, sizeCounter);
		return true;
	}

	/** Removes all items from the QuickSort array. */
	virtual bool clear()
	{
		sizeCounter = 0;

		return true;
	}

	/** Return size of the QuickSort array. */
	virtual size_t capacity() const
	{
		return capacityCounter;
	}

	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const
	{
		return sizeCounter;
	}

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	   middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if  1) the array is empty,
	              2) if either of the given integers is out of bounds,
	              3) or if the left index is not less than the right index.
	*/
	virtual int medianOfThree(size_t left, size_t right)
	{
		if (ptrArray == nullptr ||				// Array is empty
			left < 0 || left >= sizeCounter ||	// Left is out of bounds
			right < 0 || right > sizeCounter || // Right is out of bounds
			left > right - 1)					// Left isn't less than right
		{
			return -1;
		}

		size_t middle = (left + right) / 2;
		right = right - 1;
		// Initial: [3,2,1]
		if (ptrArray[left] > ptrArray[middle])
		{
			swap(ptrArray[left], ptrArray[middle]); // [2,3,1]
		}

		if (ptrArray[middle] > ptrArray[right])
		{
			swap(ptrArray[middle], ptrArray[right]); // [2,1,3]
		}

		if (ptrArray[left] > ptrArray[middle])
		{
			swap(ptrArray[left], ptrArray[middle]); // [1,2,3]
		}

		return middle; // Return middle index
	}

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values less than or equal to the pivot should be placed to the left of the pivot;
	the values greater than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if  1) the array is empty,
	              2) if any of the given indexes are out of bounds,
	              3) if the left index is not less than the right index.
	*/
	virtual int partition(size_t left, size_t right, size_t pivotIndex)
	{
		if (ptrArray == nullptr ||				// Array is empty
			left < 0 || left >= sizeCounter ||	// Left is out of bounds
			right < 0 || right > sizeCounter || // Right is out of bounds
			left >= right - 1)					// Left is less than right
		{
			return -1;
		}

		size_t up = left + 1;
		size_t down = right - 1;
		T pivotVal = ptrArray[pivotIndex];

		swap(ptrArray[left], ptrArray[pivotIndex]);

		do
		{
			while ((up != right - 1) && !(pivotVal < ptrArray[up]))
			{
				++up;
			}

			while (pivotVal < ptrArray[down])
			{
				--down;
			}

			if (up < down)
			{
				swap(ptrArray[up], ptrArray[down]);
			}

		} while (up < down);

		swap(ptrArray[left], ptrArray[down]);

		return down;
	}

	/** @return: comma delimited string representation of the array. */
	virtual std::string toString() const
	{
		if (sizeCounter == 0)
		{
			return " Empty";
		}

		ostringstream os;

		os << " " << ptrArray[0];
		for (size_t i = 1; i < sizeCounter; i++)
		{
			os << "," << ptrArray[i];
		}
		return os.str();
	}

	/**
	 * Overload the insertion operator
	 * @return an ostream with the contents of the array
	 */
	friend std::ostream &operator<<(std::ostream &os, QuickSort &qs)
	{
		os << qs.toString();
		return os;
	}
};

#endif /* QUICKSORT_H_ */
