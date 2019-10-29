#include <iostream>
#include "Config.h"
#include "INIReader.h"

Config::Config() 
{
	//Do some setup
}

bool Config::Load(string fileName) 
{
	INIReader reader(fileName);

	if (reader.ParseError() != 0) {
		std::cout << "Can't load " << fileName << "\n";
		return false;
	}

	//Get values here
	Config::myString = reader.Get("" , "myString" , "UNKNOWN");

	std::cout << "File loaded\n";
}

string Config::GetString()
{
	return this->myString;
}

