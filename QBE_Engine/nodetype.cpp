#include "nodetype.h"

Nodetype::Nodetype(unsigned short ID, unsigned char R, unsigned char G, unsigned char B)
{
	this->id = ID;
	this->color_r_value = R;
	this->color_g_value = G;
	this->color_b_value = B;
}
