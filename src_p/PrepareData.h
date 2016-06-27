#pragma once

#include <string>
#include <vector>
#include <utility>

class PrepareData
{
public:
	PrepareData(std::string path);
	~PrepareData();
	std::vector<std::pair<std::string, int>> generate();
	std::string solution;
	std::string first;
private:
	int max(std::string a, std::string b);	
	std::vector<std::pair<std::string, int>> lista;
};

