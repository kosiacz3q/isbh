//
// Created by lucas on 16.06.16.
//

#ifndef ISBH_DNAASSEMBLER_HPP
#define ISBH_DNAASSEMBLER_HPP


#include <string>
#include "GraphElements.hpp"

class DnaAssembler
{
public:
	std::string getSequence(const GraphNodePtr first, const int expectedLength);
};


#endif //ISBH_DNAASSEMBLER_HPP
