#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Oligo.hpp"
#include "GraphCreator.hpp"
#include "DnaAssembler.hpp"

using namespace std;

int main(int argc, char** argv)
{
	auto graphCreator = GraphCreator();
	int expectedLength;

	{
		std::string inputFile = std::string(argv[1]);
		std::ifstream infile(inputFile);

		std::string meta;

		infile >> meta; //header
		expectedLength = std::string(meta).length();

		infile >> meta; //first oligo
		graphCreator.markFirst(meta);
		infile >> meta; //last oligo
		graphCreator.markLast(meta);

		std::string subSequence;
		int count;

		auto container = std::vector<Oligo>();

		while (infile >> subSequence >> count)
		{
			container.push_back(Oligo(subSequence, count));
		}

		container.pop_back();

		for (auto iter = container.begin() + 1; iter != container.end(); ++iter)
			graphCreator.add(*iter);
	}

	graphCreator.generateGraph();

	if (!graphCreator.isValid())
	{
		printf("Feed is invalid (there are unreachable oligos)\n");
		exit(1);
	}

	printf("%s", DnaAssembler().getSequence(graphCreator.getRoot(), graphCreator.getLast(), expectedLength).c_str());

	return 0;
}