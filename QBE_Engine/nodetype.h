#pragma once
#include <string>

using namespace std;

class Nodetype
{
private:
	uint16_t id;

	uint8_t color_r_value;
	uint8_t color_g_value;
	uint8_t color_b_value;
public:
	Nodetype(uint16_t ID, uint8_t R, uint8_t G, uint8_t B);

	uint16_t GetId();
	uint8_t GetColor_r_value();
	uint8_t GetColor_g_value();
	uint8_t GetColor_b_value();
};

