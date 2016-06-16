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

void GraphCreator::add(const Oligo& oligo)
{
	auto newNode = std::make_shared<GraphNode>(oligo, oligo.count);

	if (oligo.sequence == _firstSequence)
		_root = newNode;

	if (oligo.sequence == _lastSequence)
		_last = newNode;

	std::string shortcut;
	for (int i = 0; i < oligo.sequence.size() - 1; ++i)
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

			if (_shortcuts.find(edgeShortcut) != _shortcuts.end())
				for (auto& ngbh : _shortcuts[edgeShortcut])
				{
					// printf("Found %s\n", (*ngbh)->oligo.sequence.c_str());
					currentNode->links.push_back(GraphEdge(edgeVal, ngbh));

					if (!isChecked[ngbh->oligo.sequence])
					{
						nodesToCheck.push_back(ngbh);
						isChecked[ngbh->oligo.sequence] = true;
					}
				}
		}

		++_processed;
	}
}

void GraphCreator::markFirst(const std::string &sequence)
{
	_firstSequence = sequence;
}

void GraphCreator::markLast(const std::string &sequence)
{
	_lastSequence = sequence;
}









