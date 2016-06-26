#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

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
		//printf("result sequence should be [%s]\n", meta.c_str());
		expectedLength = (int) std::string(meta).length();

		infile >> meta; //first oligo
		//printf("first oligo should be [%s]\n", meta.c_str());
		graphCreator.markFirst(meta);

		std::string subSequence;
		int count;

		auto container = std::vector<Oligo>();

		while (infile >> subSequence >> count)
		{
			//container.push_back(Oligo(subSequence, count));
			//printf("[%s] %i\n", subSequence.c_str(), count);
			graphCreator.add(Oligo(subSequence, count));
		}
	}

	graphCreator.generateGraph();

	if (!graphCreator.isValid())
	{
		printf("Feed is invalid (there are unreachable oligos)\n");
		exit(1);
	}

	const clock_t begin_time = clock();

	std::string seq = DnaAssembler().getSequence(graphCreator.getRoot(), expectedLength);
	const clock_t end_time = clock();

	std::cout<<"time spent "<< (float( end_time - begin_time ) /  CLOCKS_PER_SEC ) << " seq "<<seq<<std::endl;

	return 0;
}