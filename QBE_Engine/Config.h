#pragma once
#include <string>
using namespace std;

class Config
{
public:
	Config();
	bool load(string fileName);

	string getString();
private:
	string myString;
};

