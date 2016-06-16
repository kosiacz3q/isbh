#include "GraphElements.hpp"
#include <limits>

int resolveMin(const int count)
{
	if (count == 1)
		return 1;

	if (count > 1 && count <= 3)
		return 2;

	if (count > 3 && count <= 5)
		return 4;

	return 7;
}

int resolveMax(const int count)
{
	if (count == 1)
		return 3;

	if (count > 1 && count <= 3)
		return 5;

	if (count > 3 && count <= 5)
		return std::numeric_limits<int>::max();

	return std::numeric_limits<int>::max();
}

GraphNode::GraphNode(Oligo oligo, int count)
	:oligo(oligo), minCount(resolveMin(count)), maxCount(resolveMax(count))
{

}

