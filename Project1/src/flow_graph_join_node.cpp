#include <iostream>
#include <tbb/tbb.h>

int main()
{
	tbb::flow::graph graph;

	tbb::flow::function_node<int, std::string> firstNode(graph,
		tbb::flow::unlimited,
		[](int in)
	{
		std::cout << "string node received: " << in << '\n';
		return std::to_string(in);
	});

	tbb::flow::function_node<int, double> secondNode(graph,
		tbb::flow::unlimited,
		[](int in)
	{
		std::cout << "double node received: " << in << '\n';
		return double(in);
	});

	tbb::flow::join_node<std::tuple<std::string, double>, tbb::flow::queueing> joinNode(graph);

	tbb::flow::function_node<std::tuple<std::string, double>, int> finalNode(graph,
		tbb::flow::unlimited,
		[](const std::tuple<std::string, double> &in)
	{
		std::cout << "final node received: " << std::get<0>(in) << " and " << std::get<1>(in) << '\n';
		return 0;
	});

	make_edge(firstNode, tbb::flow::input_port<0>(joinNode));
	make_edge(secondNode, tbb::flow::input_port<1>(joinNode));
	make_edge(joinNode, finalNode);

	firstNode.try_put(1);
	secondNode.try_put(2);

	graph.wait_for_all();
}
