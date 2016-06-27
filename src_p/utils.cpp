#include "utils.hpp"
#include <cstdio>

void resetFlag(const GraphNodePtr current,const bool flag)
{
	if (current->flag != flag)
	{
		current->flag = flag;

		for (auto& link : current->links)
			resetFlag(link.target, flag);
	}
}


void filterToSet(const GraphNodePtr current, std::set<GraphNodePtr>& container, std::function<bool (const GraphNodePtr&)> filter)
{
	if (!current->flag)
	{
		current->flag = true;

		if (filter(current))
			container.insert(current);

		for (auto& link : current->links)
			filterToSet(link.target, container, filter);
	}
}
