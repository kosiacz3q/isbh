//
// Created by lucas on 16.06.16.
//

#include <list>
#include "GraphCreator.hpp"

GraphCreator::GraphCreator()
	:_shortcuts(ShortcutsContainer())
{

}

void GraphCreator::add(const Oligo& oligo)
{
	auto newNode = std::make_shared<GraphNode>(oligo, oligo.count);

	_nodes.push_back(newNode);

	std::string shortcut;
	for (int i = 0; i < oligo.sequence.size() - 1; ++i)
	{
		shortcut += oligo.sequence[i];
		//printf("Adding shortcut %s for %s\n", shortcut.c_str(), oligo.sequence.c_str());
		_shortcuts[shortcut].push_back(newNode);
	}
}

void GraphCreator::generateGraph()
{
	auto nodesToCheck = std::list<GraphNodePtr>();

	std::map<std::string, bool> isChecked;

	nodesToCheck.push_back(_root);
	isChecked[_root->oligo.sequence] = true;

	while(!nodesToCheck.empty())
	{
		auto currentNode = nodesToCheck.front();
		nodesToCheck.pop_front();

		int edgeVal = 0;
		std::string edgeShortcut = "";

		for (int i = (int) (currentNode->oligo.sequence.size() - 1); i > 0; --i)
		{

			edgeShortcut = currentNode->oligo.sequence[i] + edgeShortcut;
			//printf("%s\n", edgeShortcut.c_str());
			++edgeVal;

			for (const GraphNodePtr& ngbh : _shortcuts[edgeShortcut])
			{
				//printf("Found\n");
				currentNode->links.push_back(GraphEdge(edgeVal, ngbh));

				if (!isChecked[ngbh->oligo.sequence])
				{
					nodesToCheck.push_back(ngbh);
					isChecked[ngbh->oligo.sequence] = true;
				}
			}
		}

	}
}

void GraphCreator::addFirst(const Oligo &oligo)
{
	add(oligo);

	_root = _nodes.front();
	_nodes.pop_back();
}







