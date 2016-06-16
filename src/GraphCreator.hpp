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

	void add(const Oligo&);

	void addFirst(const Oligo&);

	void generateGraph();

	GraphNodePtr getRoot()
	{
		return _root;
	}

private:

	GraphNodePtr _root;
	std::vector<GraphNodePtr> _nodes;

	typedef std::map<std::string, std::vector<GraphNodePtr>> ShortcutsContainer;

	ShortcutsContainer _shortcuts;
};


#endif //ISBH_GRAPHCREATOR_HPP
