//
// Created by lucas on 16.06.16.
//

#include <list>
#include <algorithm>
#include "GraphCreator.hpp"

GraphCreator::GraphCreator()
	:_shortcuts(ShortcutsContainer()), _count(0),_processed(0)
{

}

void GraphCreator::add(const Oligo oligo)
{
	auto newNode = std::make_shared<GraphNode>(oligo, oligo.count);

	if (oligo.sequence == _firstSequence)
	{
		_root = newNode;
		//printf("root node is id[%i] seq[%s]\n", _root->uniqueId, _root->oligo.sequence.c_str());
	}

	std::string shortcut;
	for (unsigned int i = 0; i < oligo.sequence.size() - 1; ++i)
	{
		shortcut += oligo.sequence[i];
		_shortcuts[shortcut].push_back(newNode);
	}

	++_count;
}

void GraphCreator::generateGraph()
{
	//sorting by length descending
	for (auto& kv : _shortcuts)
	{
		std::sort(kv.second.begin(), kv.second.end(), [](const GraphNodePtr& left, const GraphNodePtr& right) {
			return left->oligo.sequence.size() >  right->oligo.sequence.size();
		});
	}

	auto nodesToCheck = std::list<GraphNodePtr>();

	std::map<GraphNodePtr, bool> isChecked = std::map<GraphNodePtr, bool>();

	nodesToCheck.push_back(_root);
	isChecked[_root] = true;
	//printf("root %i\n", _root->uniqueId);
	std::string edgeShortcut = "";

	while(!nodesToCheck.empty())
	{
		auto currentNode = nodesToCheck.front();
		nodesToCheck.pop_front();

		//printf("checking %i\n", currentNode->uniqueId);

		int edgeVal = 0;
		edgeShortcut = "";

		for (int i = (int) (currentNode->oligo.sequence.size() - 1); i > 0; --i)
		{
			edgeShortcut = currentNode->oligo.sequence[i] + edgeShortcut;
			//printf("%s\n", edgeShortcut.c_str());
			++edgeVal;

			if (_shortcuts.find(edgeShortcut) != _shortcuts.end())
				for (auto& ngbh : _shortcuts[edgeShortcut])
				{
					// printf("Found %s\n", (*ngbh)->oligo.sequence.c_str());

					/*
					auto iter = std::find_if(currentNode->links.begin(), currentNode->links.end(), [&](const GraphEdge& item){
						return item.target == ngbh;
					});

					if (iter != currentNode->links.end())
					{
						if (iter->coverage < edgeVal)
							iter->coverage = edgeVal;
					}
					else
					*/

					currentNode->links.push_back(GraphEdge(edgeVal, ngbh));

					if (!isChecked[ngbh])
					{
						nodesToCheck.push_back(ngbh);
						isChecked[ngbh] = true;
					}
				}
		}

		//sort by coverage
		std::sort(currentNode->links.begin(), currentNode->links.end(), [](const GraphEdge& left, const GraphEdge& right) {
			return left.coverage > right.coverage;
		});

		++_processed;
	}
}

void GraphCreator::markFirst(const std::string &sequence)
{
	_firstSequence = sequence;
}









