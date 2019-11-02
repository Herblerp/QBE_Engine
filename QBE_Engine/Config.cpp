#include <iostream>
#include "Config.h"
#include "INIReader.h"

Config::Config() 
{
	//Do some setup
}

bool Config::load(string fileName) 
{
	INIReader reader(fileName);

	if (reader.ParseError() != 0) {
		std::cout << "Can't load " << fileName << "\n";
		return false;
	}

	//Get values here
	Config::myString = reader.Get("" , "" , "UNKNOWN");

	std::cout << "Config file successfully loaded\n";
}

string Config::getString()
{
	return this->myString;
}

