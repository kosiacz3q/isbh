
#include <Oligo.hpp>
#include <GraphCreator.hpp>
#include <algorithm>

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

	graphCreator.addFirst(Oligo("actg", 1));
	graphCreator.add(Oligo("tgtg", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 1);
	REQUIRE(root->links[0].target->oligo.sequence == "tgtg");
	REQUIRE(root->links[0].target->links.size() == 1);
}

TEST_CASE( "actg ctga", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.addFirst(Oligo("actg", 1));
	graphCreator.add(Oligo("ctga", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 1);
	REQUIRE(root->links[0].target->oligo.sequence == "ctga");
	REQUIRE(root->links[0].target->links.size() == 1);
	REQUIRE(root->links[0].target->links[0].target->oligo.sequence == "actg");
}

TEST_CASE( "actg gttc tgcc ctgc", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.addFirst(Oligo("actg", 1));
	graphCreator.add(Oligo("gttc", 1));
	graphCreator.add(Oligo("tgcc", 1));
	graphCreator.add(Oligo("ctgc", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() == 3);

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc" && edge.cost == 1; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.cost == 2; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.cost == 3; } ) != root->links.end());

	auto gttc = (std::find_if(root->links.begin(), root->links.end(),
							 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc" && edge.cost == 1; } ))->target;
	REQUIRE(gttc->oligo.sequence == "gttc");
	REQUIRE(gttc->links.size() == 1);
	REQUIRE(gttc->links[0].target->oligo.sequence == "ctgc");
	REQUIRE(gttc->links[0].cost == 1);

	auto tgcc = (std::find_if(root->links.begin(), root->links.end(),
							  [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc"; } ))->target;
	REQUIRE(tgcc->links.size() == 1);
	REQUIRE(tgcc->links[0].target->oligo.sequence == "ctgc");
	REQUIRE(tgcc->links[0].cost == 1);

	auto ctgc = (std::find_if(root->links.begin(), root->links.end(),
							  [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc";} ))->target;
	REQUIRE(ctgc->links.size() == 2);
	REQUIRE(std::find_if(ctgc->links.begin(), ctgc->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.cost == 3; } ) != root->links.end());
	REQUIRE(std::find_if(ctgc->links.begin(), ctgc->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.cost == 1; } ) != root->links.end());
}