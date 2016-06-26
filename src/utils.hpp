#ifndef ISBH_UTILS_HPP
#define ISBH_UTILS_HPP

#include <functional>
#include <GraphElements.hpp>
#include <set>

void resetFlag(const GraphNodePtr root,const bool flag);
void filterToSet(const GraphNodePtr root, std::set<GraphNodePtr>& container, std::function<bool (const GraphNodePtr&)> filter);

#endif //ISBH_UTILS_HPP
