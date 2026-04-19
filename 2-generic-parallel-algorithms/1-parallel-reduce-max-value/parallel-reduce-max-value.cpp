#include <iostream>
#include <tbb/tbb.h>
#include <vector>

int getMaxValue(const std::vector<int> &values)
{
	int maxValue = tbb::parallel_reduce(
	  tbb::blocked_range<int>(0, values.size()), // the range to process
	  std::numeric_limits<int>::min(),// identity value for the reduction

    // lambda function to process a subrange and return the maximum value in that subrange
	  [&](const tbb::blocked_range<int> &range, int max) {
		  for (int i = range.begin(); i < range.end(); ++i)
		  {
			  max = std::max(max, values[i]);
		  }
		  return max;
	  },

    // reduction function to combine results from different threads
	  [](int left, int right)
    {
      return std::max(left, right);
    });
	return maxValue;
}

int main()
{
	std::vector<int> values = {3, 2, 5, 1, 4, 11, 7, 10, 6, 9, 8, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
	int maxValue = getMaxValue(values);
	std::cout << "Max value: " << maxValue << std::endl;
	return 0;
}
