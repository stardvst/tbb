#include <cstdio>
#include <array>
#include <chrono>
#include <iostream>

#include <tbb/tbb.h>
#include <tbb/tbbmalloc_proxy.h> // added to use tbbmalloc

class Timer
{
public:
	Timer()
	{
		m_startPoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		auto endPoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();
		auto duration = end - start;
		auto ms = duration * 0.001;
		auto s = ms * 0.001;

		std::cout << s << "s" << std::endl;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;
};

int main()
{
	const int N = 1'000'000;
	std::array<double *, N> a;

	Timer timer;
	tbb::parallel_for(0, N - 1, [&a](int i) { a[i] = new double; });
	tbb::parallel_for(0, N - 1, [&a](int i) { delete a[i]; });

	return 0;
}
