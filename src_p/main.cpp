#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>

#include "Oligo.hpp"
#include "GraphCreator.hpp"
#include "DnaAssembler.hpp"
#include "PrepareData.h"

using namespace std;


void generate(GraphCreator &, int &, string);
void oldGenerate(GraphCreator &, int &, string );


int main(int argc, char** argv)
{
	auto graphCreator = GraphCreator();
	int expectedLength = 0;

	{
		generate(graphCreator, expectedLength, argv[1]);
	}

	graphCreator.generateGraph();

	if (!graphCreator.isValid())
	{
		printf("Feed is invalid (there are unreachable oligos)\n");
		exit(1);
	}

	auto start = std::chrono::high_resolution_clock::now();
	

	std::string seq = DnaAssembler().getSequence(graphCreator.getRoot(), expectedLength);

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	
	std::cout<< microseconds << ";"<<seq<<std::endl;



	fstream ppp;
	ppp.open("wyniki.txt", fstream::out);
	if (ppp.good())
		ppp << seq;
	ppp.close();

	return 0;
}


void generate(GraphCreator &graphCreator, int &expectedLength, string path)
{
	PrepareData *pd = new PrepareData(path);

	auto data = pd->generate();

	expectedLength = pd->solution.size();
	graphCreator.markFirst(pd->first);

	for (auto x : data)
	{
		graphCreator.add(Oligo(x.first, x.second));
	}
}

void oldGenerate(GraphCreator &graphCreator, int &expectedLength, string path)
{
	std::string inputFile = std::string(path);
	std::ifstream infile(inputFile);

	std::string meta;

	infile >> meta; //header
	//printf("result sequence should be [%s]\n", meta.c_str());
	expectedLength = (int)std::string(meta).length();

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

	infile.close();
}