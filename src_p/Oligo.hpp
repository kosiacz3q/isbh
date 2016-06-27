//
// Created by lucas on 15.06.16.
//

#ifndef ISBH_OLIGO_HPP
#define ISBH_OLIGO_HPP

#include <string>


class Oligo
{
public:

	Oligo(const std::string& rep, int count);

	int getTemperature() const
	{
		return _temperature;
	}

	std::string sequence;

	int count;

private:


	int _temperature;
};


#endif //ISBH_OLIGO_HPP
