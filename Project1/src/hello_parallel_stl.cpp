#include <algorithm>
#include <execution>
#include <vector>
#include <string>
#include <iostream>

int main()
{
	std::vector<std::string> v { "Hello", "Parallel STL!" };
	std::for_each(std::execution::par, std::begin(v), std::end(v),
		[](const std::string &s) { std::cout << s << std::endl; });
	return 0;
}
