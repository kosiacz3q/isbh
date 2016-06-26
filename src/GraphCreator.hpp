//
// Created by lucas on 16.06.16.
//

#ifndef ISBH_GRAPHCREATOR_HPP
#define ISBH_GRAPHCREATOR_HPP

#include <GraphElements.hpp>
#include <map>

class GraphCreator
{
public:

	GraphCreator();

	void add(const Oligo);

	void markFirst(const std::string &sequence);

	void generateGraph();

	bool isValid() const
	{
		return _count == _processed;
	}

	GraphNodePtr getRoot()
	{
		return _root;
	}

private:

	GraphNodePtr _root;

	typedef std::map<std::string, std::vector<GraphNodePtr>> ShortcutsContainer;

	ShortcutsContainer _shortcuts;

	std::string _firstSequence;
	std::string _lastSequence;
	int _count;
	int _processed;
};


#endif //ISBH_GRAPHCREATOR_HPP
