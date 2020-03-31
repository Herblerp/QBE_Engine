#include "nodetype.h"

namespace Data {
	Nodetype::Nodetype(uint16_t ID, uint8_t R, uint8_t G, uint8_t B)
	{
		this->id = ID;
		this->color_r_value = R;
		this->color_g_value = G;
		this->color_b_value = B;
	}

	uint16_t Nodetype::GetId()
	{
		return this->id;
	}

	uint8_t Nodetype::GetColor_r_value()
	{
		return this->color_r_value;
	}

	uint8_t Nodetype::GetColor_g_value()
	{
		return this->color_g_value;
	}

	uint8_t Nodetype::GetColor_b_value()
	{
		return this->color_b_value;
	}
}