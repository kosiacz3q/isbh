#include "../catch/catch.hpp"

#include <Oligo.hpp>
#include <GraphCreator.hpp>
#include <algorithm>
#include <DnaAssembler.hpp>
#include "../src/utils.hpp"


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
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc" && edge.coverage == 1; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.coverage == 2; } ) != root->links.end());
	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.coverage == 3; } ) != root->links.end());

	auto gttc = (std::find_if(root->links.begin(), root->links.end(),
							 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc"; } ))->target;
	REQUIRE(gttc->oligo.sequence == "gttc");
	REQUIRE(gttc->links.size() == 1);
	REQUIRE(gttc->links[0].target->oligo.sequence == "ctgc");
	REQUIRE(gttc->links[0].coverage == 1);

	auto tgcc = (std::find_if(root->links.begin(), root->links.end(),
							  [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc"; } ))->target;
	REQUIRE(tgcc->links.size() == 1);
	REQUIRE(tgcc->links[0].target->oligo.sequence == "ctgc");
	REQUIRE(tgcc->links[0].coverage == 1);

	auto ctgc = (std::find_if(root->links.begin(), root->links.end(),
							  [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc";} ))->target;
	REQUIRE(ctgc->links.size() == 2);
	REQUIRE(std::find_if(ctgc->links.begin(), ctgc->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.coverage == 3; } ) != ctgc->links.end());
	REQUIRE(std::find_if(ctgc->links.begin(), ctgc->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.coverage == 1; } ) != ctgc->links.end());

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "gggg gggg", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("gggg");;

	graphCreator.add(Oligo("gggg", 2));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() >= 1);

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gggg" && edge.coverage == 3; } ) != root->links.end());

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
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgaaaaaaaaaaaaaaa" && edge.coverage == 3; } ) != root->links.end());

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "check first", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("tggg", 1));
	graphCreator.add(Oligo("ctgaaaaaaaaaaaaaaa", 1));
	graphCreator.add(Oligo("tgc", 1));
	graphCreator.add(Oligo("tgtc", 1));


	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(graphCreator.getRoot()->oligo.sequence == "actg");

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "invalid graph", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("gggt");

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

TEST_CASE( "sorted by coverage", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("agggg");

	graphCreator.add(Oligo("agggg", 1));
	graphCreator.add(Oligo("ggt", 1));
	graphCreator.add(Oligo("gggt", 1));
	graphCreator.add(Oligo("gt", 1));
	graphCreator.add(Oligo("ggggt", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	REQUIRE(root->links.size() >= 4);

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ggggt" && edge.coverage == 4; } ) != root->links.end());

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gggt" && edge.coverage == 3; } ) != root->links.end());

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ggt" && edge.coverage == 2; } ) != root->links.end());

	REQUIRE(std::find_if(root->links.begin(), root->links.end(),
						 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gt" && edge.coverage == 1; } ) != root->links.end());

	REQUIRE(graphCreator.isValid() == true);
}

TEST_CASE( "create ctgatgca", "[Graph]" )
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("ctga");

	graphCreator.add(Oligo("tgca", 1));
	graphCreator.add(Oligo("ctga", 1));
	graphCreator.add(Oligo("atgc", 1));
	graphCreator.add(Oligo("tgat", 1));
	graphCreator.add(Oligo("gatg", 1));

	graphCreator.generateGraph();
}

TEST_CASE( "assemble actga", "[DnaAssembler]" )
{
	auto dnaAssembler = DnaAssembler();

	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("ctga", 1));

	graphCreator.generateGraph();

	REQUIRE(dnaAssembler.getSequence(graphCreator.getRoot(), 5) == "actga");
}

TEST_CASE( "assemble gggg", "[DnaAssembler]" )
{
	auto dnaAssembler = DnaAssembler();

	auto graphCreator = GraphCreator();

	graphCreator.markFirst("ggg");

	graphCreator.add(Oligo("ggg", 2));

	graphCreator.generateGraph();

	REQUIRE(dnaAssembler.getSequence(graphCreator.getRoot(), 4) == "gggg");
}

TEST_CASE( "assemble actgactg", "[DnaAssembler]" )
{
	auto dnaAssembler = DnaAssembler();

	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("gact", 1));
	graphCreator.add(Oligo("ctga", 1));
	graphCreator.add(Oligo("actg", 2));
	graphCreator.add(Oligo("tgac", 1));

	graphCreator.generateGraph();

	REQUIRE(dnaAssembler.getSequence(graphCreator.getRoot(), 8) == "actgactg");
}

TEST_CASE( "assemble ctgatgca", "[DnaAssembler]" )
{
	auto dnaAssembler = DnaAssembler();

	auto graphCreator = GraphCreator();

	graphCreator.markFirst("ctga");

	graphCreator.add(Oligo("tgca", 1));
	graphCreator.add(Oligo("ctga", 1));
	graphCreator.add(Oligo("atgc", 1));
	graphCreator.add(Oligo("tgat", 1));
	graphCreator.add(Oligo("gatg", 1));

	graphCreator.generateGraph();

	REQUIRE(dnaAssembler.getSequence(graphCreator.getRoot(), 8) == "ctgatgca");
}

TEST_CASE( "clear flag", "[utils]")
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("gttc", 1));
	graphCreator.add(Oligo("tgcc", 1));
	graphCreator.add(Oligo("ctgc", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();

	resetFlag(root, true);

	REQUIRE(root->flag);

	auto next = std::find_if(root->links.begin(), root->links.end(),
							 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.coverage == 3 && edge.target->flag == true; } ) ;

	REQUIRE(next != root->links.end());

	next = std::find_if(next->target->links.begin(), next->target->links.end(),
						[](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.coverage == 3 && edge.target->flag == true; } ) ;

	REQUIRE(next != next->target->links.end());

	next = std::find_if(root->links.begin(), root->links.end(),
							 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc" && edge.coverage == 1 && edge.target->flag == true; } ) ;

	REQUIRE(next != root->links.end());


	resetFlag(root, false);

	REQUIRE(root->flag == false);

	next = std::find_if(root->links.begin(), root->links.end(),
							 [](const GraphEdge& edge) { return edge.target->oligo.sequence == "ctgc" && edge.coverage == 3 && edge.target->flag == false; } ) ;

	REQUIRE(next != root->links.end());

	next = std::find_if(next->target->links.begin(), next->target->links.end(),
						[](const GraphEdge& edge) { return edge.target->oligo.sequence == "tgcc" && edge.coverage == 3 && edge.target->flag == false; } ) ;

	REQUIRE(next != next->target->links.end());

	next = std::find_if(root->links.begin(), root->links.end(),
						[](const GraphEdge& edge) { return edge.target->oligo.sequence == "gttc" && edge.coverage == 1 && edge.target->flag == false; } ) ;

	REQUIRE(next != root->links.end());
}

TEST_CASE( "filter to set", "[utils]")
{
	auto graphCreator = GraphCreator();

	graphCreator.markFirst("actg");

	graphCreator.add(Oligo("actg", 1));
	graphCreator.add(Oligo("gttc", 1));
	graphCreator.add(Oligo("tgcc", 99));
	graphCreator.add(Oligo("ctgc", 1));

	graphCreator.generateGraph();

	auto root = graphCreator.getRoot();
	std::set<GraphNodePtr> set;

	resetFlag(root, false);

	filterToSet(root, set, [](const GraphNodePtr& current){ return current->minCount > 2;});

	REQUIRE(set.size() == 1);
	REQUIRE((*set.begin())->oligo.sequence == "tgcc");

}


TEST_CASE( "assemble big one", "[big check]" )
{
	auto dnaAssembler = DnaAssembler();

	auto graphCreator = GraphCreator();

	std::string sequence = "agggcgtgttcgagtaggtggttatatggt";

	graphCreator.markFirst("agggc");

	graphCreator.add(Oligo("cgtgtt",1));
	graphCreator.add(Oligo("gtggtta",1));
	graphCreator.add(Oligo("ttatatgg",1));
	graphCreator.add(Oligo("tgttcga",1));
	graphCreator.add(Oligo("ggcgt",1));
	graphCreator.add(Oligo("gttatatg",1));
	graphCreator.add(Oligo("ggttatat",1));
	graphCreator.add(Oligo("tggttata",1));
	graphCreator.add(Oligo("taggtg",1));
	graphCreator.add(Oligo("aggtgg",1));
	graphCreator.add(Oligo("gagtag",1));
	graphCreator.add(Oligo("agggc",1));
	graphCreator.add(Oligo("gcgtgt",1));
	graphCreator.add(Oligo("tcgagta",1));
	graphCreator.add(Oligo("gggcg",1));
	graphCreator.add(Oligo("gtgttc",1));
	graphCreator.add(Oligo("agtaggt",1));
	graphCreator.add(Oligo("tatatggt",1));
	graphCreator.add(Oligo("ttcgagt",1));
	graphCreator.add(Oligo("ggtggt",1));

	graphCreator.generateGraph();

	REQUIRE(dnaAssembler.getSequence(graphCreator.getRoot(), sequence.length()) == sequence.c_str());
}

TEST_CASE( "assemble even bigger one", "[big check]" )
{
	auto dnaAssembler = DnaAssembler();

	auto graphCreator = GraphCreator();

	std::string sequence = "ctaaggacccagtaagacttagcgatctgtccctatttagctacccagtttctacttgcgcacatgacccgaacgaaaagaagatggtctatatatgcgc";

	graphCreator.markFirst("ctaagga");

	graphCreator.add(Oligo("catgacc",1));
	graphCreator.add(Oligo("aaggacc",1));
	graphCreator.add(Oligo("taagactta",1));
	graphCreator.add(Oligo("acccgaa",1));
	graphCreator.add(Oligo("cagtttct",1));
	graphCreator.add(Oligo("acttagc",1));
	graphCreator.add(Oligo("cccagta",1));
	graphCreator.add(Oligo("agaagatg",1));
	graphCreator.add(Oligo("ctaagga",1));
	graphCreator.add(Oligo("acttgcg",1));
	graphCreator.add(Oligo("atgaccc",1));
	graphCreator.add(Oligo("cttagcg",1));
	graphCreator.add(Oligo("agacttag",1));
	graphCreator.add(Oligo("ggtctata",1));
	graphCreator.add(Oligo("gtttctac",1));
	graphCreator.add(Oligo("ttagctac",1));
	graphCreator.add(Oligo("cgatctg",1));
	graphCreator.add(Oligo("tctatatat",1));
	graphCreator.add(Oligo("agctacc",1));
	graphCreator.add(Oligo("agtttcta",1));
	graphCreator.add(Oligo("tgtccct",1));
	graphCreator.add(Oligo("atttagcta",1));
	graphCreator.add(Oligo("cccagtt",1));
	graphCreator.add(Oligo("tacttgc",1));
	graphCreator.add(Oligo("cctattta",1));
	graphCreator.add(Oligo("gcgatct",1));
	graphCreator.add(Oligo("tctgtcc",1));
	graphCreator.add(Oligo("cgaaaaga",1));
	graphCreator.add(Oligo("tatgcgc",1));
	graphCreator.add(Oligo("acatgac",1));
	graphCreator.add(Oligo("taaggac",1));
	graphCreator.add(Oligo("gtctatata",1));
	graphCreator.add(Oligo("gtaagact",1));
	graphCreator.add(Oligo("gatggtc",1));
	graphCreator.add(Oligo("tatttagct",1));
	graphCreator.add(Oligo("ctaccca",1));
	graphCreator.add(Oligo("ggaccc",1));
	graphCreator.add(Oligo("tatatatgc",1));
	graphCreator.add(Oligo("acccagt",2));
	graphCreator.add(Oligo("tctacttg",1));
	graphCreator.add(Oligo("gaccca",1));
	graphCreator.add(Oligo("gaacgaaa",1));
	graphCreator.add(Oligo("cgaacga",1));
	graphCreator.add(Oligo("tacccag",1));
	graphCreator.add(Oligo("ccagtaa",1));
	graphCreator.add(Oligo("gacccg",1));
	graphCreator.add(Oligo("ccgaac",1));
	graphCreator.add(Oligo("gtcccta",1));
	graphCreator.add(Oligo("gaaaagaa",1));
	graphCreator.add(Oligo("tatatgcg",1));
	graphCreator.add(Oligo("aaagaagat",1));
	graphCreator.add(Oligo("atctgtc",1));
	graphCreator.add(Oligo("ctatatatg",1));
	graphCreator.add(Oligo("ctatttag",1));
	graphCreator.add(Oligo("gatctgt",1));
	graphCreator.add(Oligo("aacgaaaa",1));
	graphCreator.add(Oligo("ccagttt",1));
	graphCreator.add(Oligo("tccctatt",1));
	graphCreator.add(Oligo("aagatggt",1));
	graphCreator.add(Oligo("agcgatc",1));
	graphCreator.add(Oligo("cacatga",1));
	graphCreator.add(Oligo("cagtaaga",1));
	graphCreator.add(Oligo("cgcacat",1));
	graphCreator.add(Oligo("agtaagac",1));
	graphCreator.add(Oligo("atggtcta",1));
	graphCreator.add(Oligo("tggtctat",1));
	graphCreator.add(Oligo("gcgcac",1));
	graphCreator.add(Oligo("tttctactt",1));
	graphCreator.add(Oligo("gcacatg",1));
	graphCreator.add(Oligo("ttagcgat",1));
	graphCreator.add(Oligo("aaaagaaga",1));
	graphCreator.add(Oligo("ccctattt",1));
	graphCreator.add(Oligo("acgaaaag",1));
	graphCreator.add(Oligo("ttgcgca",1));

	graphCreator.generateGraph();

	REQUIRE(dnaAssembler.getSequence(graphCreator.getRoot(), sequence.length()) == sequence.c_str());
}