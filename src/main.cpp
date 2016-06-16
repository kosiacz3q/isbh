#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Oligo.hpp"
#include "GraphCreator.hpp"

using namespace std;


std::vector<Oligo> readOligosFromFile(const std::string file);

int main(int argc, char** argv)
{
	auto graphCreator = GraphCreator();

	{
		std::string inputFile = std::string(argv[1]);

		auto oligos = readOligosFromFile(inputFile);

		graphCreator.addFirst(oligos.front());

		for (auto iter = oligos.begin() + 1; iter != oligos.end(); ++iter)
			graphCreator.add(*iter);
	}

	return 0;
}


std::vector<Oligo> readOligosFromFile(const std::string file)
{
	std::ifstream infile(file);

	std::string subSequence;
	int count;

	infile >> subSequence; //header

	auto container = std::vector<Oligo>();

	while (infile >> subSequence >> count)
	{
		container.push_back(Oligo(subSequence, count));
	}

	return container;
}
