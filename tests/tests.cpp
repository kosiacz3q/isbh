
#include <Oligo.hpp>
#include <GraphCreator.hpp>
#include <algorithm>
#include <DnaAssembler.hpp>

#include "../catch/catch.hpp"

TEST_CASE( "Oligo ctr actg", "[Oligo]" )
{
	std::string oligo = "actg";

	REQUIRE(Oligo(oligo, 0).getTemperature() == 12);
}

TEST_CASE( "Oligo ctr gggg", "[Oligo]" )
{
	std::string oligo = "gggg";

	REQUIRE(Oligo(oligo, 0).getTemperature() == 16);
}


TEST_CASE( "actg tgtg", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("tgtg", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 1);
	REQUIRE(root->links[0].target->oligo.sequence == "tgtg");
	REQUIRE(root->links[0].target->links.size() == 1);

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "actg ctga", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("ctga", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 1);
	REQUIRE(root->links[0].target->oligo.sequence == "ctga");
	REQUIRE(root->links[0].target->links.size() == 1);
	REQUIRE(root->links[0].target->links[0].target->oligo.sequence == "actg");

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "actg gttc tgcc ctgc", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("gttc", 1));
	graphCreator.add(Oligo("tgcc", 1));
	graphCreator.add(Oligo("ctgc", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 3);

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc" && edge.covering == 1; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.covering == 2; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.covering == 3; } ) != root->links.end());

	auto gttc = (std::find_if(root->links.begin(), root->links.end(),
							 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc"; } ))->target;
	REQUIRE(gttc->oligo.sequence == "gttc");
	REQUIRE(gttc->links.size() == 1);
	REQUIRE(gttc->links[0].target->oligo.sequence == "ctgc");
	REQUIRE(gttc->links[0].covering == 1);

	auto tgcc = (std::find_if(root->links.begin(), root->links.end(),
							  [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc"; } ))->target;
	REQUIRE(tgcc->links.size() == 1);
	REQUIRE(tgcc->links[0].target->oligo.sequence == "ctgc");
	REQUIRE(tgcc->links[0].covering == 1);

	auto ctgc = (std::find_if(root->links.begin(), root->links.end(),
							  [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc";} ))->target;
	REQUIRE(ctgc->links.size() == 2);
	REQUIRE(std::find_if(ctgc->links.begin(), ctgc->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.covering == 3; } ) != ctgc->links.end());
	REQUIRE(std::find_if(ctgc->links.begin(), ctgc->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.covering == 1; } ) != ctgc->links.end());

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "gggg gggg", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("gggg");
	graphCreator.markLast("gggg");

	graphCreator.add(Oligo("gggg", 2));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 3);

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gggg" && edge.covering == 1; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gggg" && edge.covering == 2; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gggg" && edge.covering == 3; } ) != root->links.end());

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "actg ctgaaaaaaaaaaaaaaa", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("ctgaaaaaaaaaaaaaaa", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 1);
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgaaaaaaaaaaaaaaa" && edge.covering == 3; } ) != root->links.end());

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "check first and last", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");
	graphCreator.markLast("tggg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("tggg", 1));
	graphCreator.add(Oligo("ctgaaaaaaaaaaaaaaa", 1));
	graphCreator.add(Oligo("tgc", 1));
	graphCreator.add(Oligo("tgtc", 1));


	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(graphCreator.getRoot()->oligo.sequence == "actg");
	REQUIRE(graphCreator.getLast()->oligo.sequence == "tggg");

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "invalid graph", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("gggt");
	graphCreator.markLast("cgt");

	graphCreator.add(Oligo("gggt", 1));
	graphCreator.add(Oligo("cgt", 1));

	REQUIRE(graphCreator.isValid() == false);
}

TEST_CASE( "longer shortcuts first", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("atc");

	graphCreator.add(Oligo("atc", 1));
	graphCreator.add(Oligo("cggg", 1));
	graphCreator.add(Oligo("cggggggg", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 2);
	REQUIRE(root->links[0].target->oligo.sequence == "cggggggg");

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "assemble actga", "[DnaAssembler]" )
{
	auto dnaAssembler = DnaAssembler();

	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");
	graphCreator.markLast("ctga");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("ctga", 1));

	graphCreator.generateGraph();

	REQUIRE(dnaAssembler.getSequence(graphCreator.getRoot(), graphCreator.getLast(), 5) == "actga");
}