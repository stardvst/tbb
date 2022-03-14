#include <iostream>
#include <tbb/flow_graph.h>

int main()
{
	tbb::flow::graph graph;

	tbb::flow::function_node<int, std::string> firstNode(graph,
		tbb::flow::unlimited,
		[](int in)
	{
		std::cout << "first node received: " << in << '\n';
		return std::to_string(in);
	});

	tbb::flow::function_node<std::string> secondNode(graph,
		tbb::flow::unlimited,
		[](const std::string &in)
	{
		std::cout << "second node received: " << in << '\n';
	});

	tbb::flow::make_edge(firstNode, secondNode);

	firstNode.try_put(10);

	graph.wait_for_all();

	return 0;
}
