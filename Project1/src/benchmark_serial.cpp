#include <iostream>
#include <tbb/tbb.h>
#include <tbb/flow_graph.h>

void spinWaitForAtLeast(double sec)
{
	if (sec == 0) return;
	tbb::tick_count t0 = tbb::tick_count::now();
	while ((tbb::tick_count::now() - t0).seconds() < sec);
}

double serial(int num_trials, int N, double per_node_time)
{
	tbb::tick_count t0{}, t1{};
	for (int t = -1; t < num_trials; t++)
	{
		if (!t)
			t0 = tbb::tick_count::now();
		for (int i = 0; i < N; i++)
			spinWaitForAtLeast(per_node_time);
	}
	t1 = tbb::tick_count::now();
	return (t1 - t0).seconds() / num_trials;
}

int main()
{
	const int NUM_TRIALS = 2;
	const int H = 16;
	const int N = (1 << H) - 1;
	const int PER_NODE_TIMES = 4;
	double per_node_time[PER_NODE_TIMES] = { 1e-7, 1e-6, 1e-5, 1e-4 };

	std::cout << "time in seconds" << std::endl << std::endl
		<< "version, 100ns, 1us, 10us, 100us" << std::endl
		<< "serial";

	for (double tpn : per_node_time)
	{
		double serial_time = serial(NUM_TRIALS, N, tpn);
		std::cout << ", " << serial_time;
	}
	std::cout << std::endl;
	return 0;
}
