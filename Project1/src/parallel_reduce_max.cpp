#include <vector>
#include <iostream>
#include <limits>
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

int parallel_max(const std::vector<int> &v)
{
	return tbb::parallel_reduce(
		tbb::blocked_range<int>{0, static_cast<int>(v.size())}, // the range
		std::numeric_limits<int>::min(), // identity
		[&](const tbb::blocked_range<int> &r, int init) // func
	{
		for (int i = r.begin(); i != r.end(); ++i)
			init = std::max(init, v[i]);
		/*tbb::parallel_for(r.begin(), r.end(), [&](int i)
		{
			init = std::max(init, v[i]);
		});*/
		return init;
	},
		[](int x, int y) // reduction
	{
		return std::max(x, y);
	});
}

int main()
{
	std::vector<int> v { 4, 12, 76, 33, 7, 96, 34, 55, 23, 8, 1, 64, 44, 9, 45, 25 };
	std::cout << parallel_max(v) << '\n';
}
