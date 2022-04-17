#include <iostream>

#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for.h>

void oneway()
{
	tbb::concurrent_vector<int> v = { 3, 14, 15, 92 };
	for (int i = 100; i < 1000; ++i)
	{
		v.push_back(i * 100 + 11);
		v.push_back(i * 100 + 22);
		v.push_back(i * 100 + 33);
		v.push_back(i * 100 + 44);
	}

	for (int n : v)
		std::cout << n << '\n';
}

void allways()
{
	tbb::concurrent_vector<int> v = { 3, 14, 15, 92 };
	tbb::parallel_for(100, 999, [&v](int i)
	{
		v.push_back(i * 100 + 11);
		v.push_back(i * 100 + 22);
		v.push_back(i * 100 + 33);
		v.push_back(i * 100 + 44);
	});

	for (int n : v)
		std::cout << n << '\n';
}

int main()
{
	oneway();
	allways();
	return 0;
}
