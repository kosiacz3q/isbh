//
// Created by lucas on 16.06.16.
//

#ifndef ISBH_GRAPHNODE_HPP
#define ISBH_GRAPHNODE_HPP

#include <memory>
#include <vector>

#include <Oligo.hpp>

class GraphNode;
typedef std::shared_ptr<GraphNode> GraphNodePtr;

struct GraphEdge
{
	GraphEdge(const int cost, const GraphNodePtr target)
			:coverage(cost), target(target) {}

	int coverage;
	GraphNodePtr target;
};

class GraphNode
{
public:

	GraphNode(Oligo oligo, int count);

	std::vector<GraphEdge> links;
	Oligo oligo;

	int minCount;
	int maxCount;
	int currentCount;
	bool flag;
};

typedef std::shared_ptr<GraphNode> GraphNodePtr;

#endif //ISBH_GRAPHNODE_HPP
