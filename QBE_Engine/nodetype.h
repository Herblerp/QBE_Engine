#pragma once
class Nodetype
{
private:
	unsigned short id;

	unsigned char color_r_value;
	unsigned char color_g_value;
	unsigned char color_b_value;
public:
	Nodetype(unsigned short ID, unsigned char R, unsigned char G, unsigned char B);
};

