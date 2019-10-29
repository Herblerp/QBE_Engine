#pragma once
#include <string>
using namespace std;

class Config
{
public:
	Config();
	bool Load(string fileName);

	string GetString();
private:
	string myString;
};

