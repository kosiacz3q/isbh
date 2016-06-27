#include "PrepareData.h"

#include <fstream>

PrepareData::PrepareData(std::string path)
{
	std::ifstream file(path);

	file >> solution;
	file >> first;

	while (!file.eof())
	{
		std::string inStr;
		file >> inStr;
		int val;
		file >> val;
		lista.push_back(std::make_pair(inStr, val));
	}
	if (lista.back().first == "")
		lista.pop_back();

	file.close();
}

std::vector<std::pair<std::string, int>> PrepareData::generate()
{
	int tabSize = lista.size();

	int **table = new int*[tabSize];
	for (int i = 0; i < tabSize; i++)
		table[i] = new int[tabSize];

	for (int i = 0; i < tabSize; i++)
	for (int j = 0; j < tabSize; j++)
	if (i != j)
		table[i][j] = max(lista[i].first, lista[j].first);
	else
		table[i][j] = 0;


	int temp = 22;
	int threshold = temp / 4;

	std::vector<std::pair<std::string, int>> output;

	for (int i = 0; i < tabSize; i++)
	{
		for (int j = 0; j < tabSize; j++)
		{
			if (table[i][j] > threshold && lista[i].first != first && lista[j].first != first)
			{
				if (lista[i].second > 0 && lista[j].second > 0)
				{
					output.push_back(std::make_pair(lista[i].first + lista[j].first.substr(table[i][j], lista[j].first.size()), 1));
					lista[i].second--;
					lista[j].second--;
				}
			}
		}
	}

	for (int i = 0; i < tabSize; i++)
	{
		if (lista[i].second > 0)
			output.push_back(lista[i]);
	}

	for (int i = 0; i < tabSize; i++)
		delete[] table[i];
	delete[] table;

	return output;
}

int PrepareData::max(std::string a, std::string b)
{
	int len = a.size();
	for (int i = 1; i < a.size(); i++)
	{
		std::string temp = a.substr(i, len);
		std::string temp2 = b.substr(0, temp.size());

		if (temp == temp2)
		{
			return len - i;
		}
	}
	return 0;
}

PrepareData::~PrepareData()
{
}
