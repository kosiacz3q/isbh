#include "DnaAssembler.hpp"

#include <algorithm>


GraphNodePtr rootNode;
GraphNodePtr lastNode;
int acceptedLeft;
std::string sequence;

void clearFlag(const GraphNodePtr current)
{
	if (current->flag)
	{
		current->flag = false;

		for (auto& link : current->links)
			clearFlag(link.target);
	}
}

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
	if (countLeft < -(acceptedLeft * 4) )
	{
		return false;
	}

	++(current->currentCount);

	if (current == lastNode && countLeft <= acceptedLeft && current->currentCount >= current->minCount)
	{
		clearFlag(rootNode);

		if(!checkIfMinimumIsReached(rootNode))
		{
			--(current->currentCount);
			return false;
		}

		sequence = current->oligo.sequence;
		// printf("Found %s\n", sequence.c_str());
		return true;
	}

	for (auto& link : current->links)
	{
		if (link.target->currentCount <= link.target->maxCount)
			if (dfs(link.target, (const int) (countLeft - (link.target->oligo.sequence.length() - link.coverage))))
			{
				// printf("Adding %s\n", (current->oligo.sequence.substr(0, current->oligo.sequence.length() - link.coverage)).c_str());
				sequence = current->oligo.sequence.substr(0, current->oligo.sequence.length() - link.coverage) + sequence;
				return true;
			}
	}

	--(current->currentCount);

	return false;
}

std::string DnaAssembler::getSequence(const GraphNodePtr first, const GraphNodePtr last, const int expectedLength)
{
	acceptedLeft = (int)(expectedLength * 0.1);
	lastNode = last;
	rootNode = first;

	sequence = "not found";

	dfs(first, (const int) (expectedLength - first->oligo.sequence.length()));

	return sequence;
}

