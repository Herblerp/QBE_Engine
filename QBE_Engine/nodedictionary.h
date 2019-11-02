#pragma once
#include <string>
#include <vector>
#include "nodetype.h"

using namespace std;

class Nodedictionary
{
private:
	bool isLoaded;
	vector<Nodetype> nodeDict;
	uint8_t ConvertColorValue(int value);

public:
	Nodedictionary();
	bool loadTypes();
	Nodetype& GetNodeType(int id);
};

