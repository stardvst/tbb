#include <iostream>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>

double parallel_pi(int num_intervals)
{
	double dx = 1.0 / num_intervals;
	double sum = tbb::parallel_reduce(
		tbb::blocked_range<int>(0, num_intervals),
		0.0,
		[dx](const tbb::blocked_range<int> &r, double init)
	{
		for (int i = r.begin(); i != r.end(); ++i)
		{
			double x = (i + 0.5) * dx;
			double h = std::sqrt(1 - x * x);
			init += h * dx;
		}
		return init;
	},
		[](double x, double y)
	{
		return x + y;
	});
	double pi = 4 * sum;
	return pi;
}

int main()
{
	std::cout.precision(10);
	std::cout << std::fixed << parallel_pi(10000) << '\n';
}
