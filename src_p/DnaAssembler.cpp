#include "DnaAssembler.hpp"

#include <algorithm>
#include <set>

#include "utils.hpp"

std::string sequence;
std::set<GraphNodePtr> minimalIsNotReach;

bool checkIfMinimumIsReached(const GraphNodePtr current)
{
	if (!current->flag)
	{
		current->flag = true;

		if (current->currentCount < current->minCount)
			return false;

		for (auto& link : current->links)
		{
			if(!checkIfMinimumIsReached(link.target))
				return false;
		}
	}

	return true;
}

bool dfs(const GraphNodePtr current, const int countLeft)
{
	if (countLeft < 0)
	{
		return false;
	}

	++(current->currentCount);

	if (current->currentCount == current->minCount)
		minimalIsNotReach.erase(current);

	if (countLeft == 0 && minimalIsNotReach.empty())
	{
		sequence = current->oligo.sequence;
		return true;
	}

	for (auto& link : current->links)
	{
		if (link.target->currentCount < link.target->maxCount)
			if (dfs(link.target, (const int) (countLeft - (link.target->oligo.sequence.length() - link.coverage))))
			{
				sequence = current->oligo.sequence.substr(0, current->oligo.sequence.length() - link.coverage) + sequence;
				return true;
			}
	}

	if (current->currentCount == current->minCount)
		minimalIsNotReach.insert(current);

	--(current->currentCount);

	return false;
}

std::string DnaAssembler::getSequence(const GraphNodePtr first, const int expectedLength)
{
	sequence = "not found";
	minimalIsNotReach = std::set<GraphNodePtr>();

	resetFlag(first, false);
	filterToSet(first, minimalIsNotReach, [](const GraphNodePtr& current){ return current->currentCount < current->minCount;});

	dfs(first, (const int) (expectedLength - first->oligo.sequence.length()));

	return sequence;
}

