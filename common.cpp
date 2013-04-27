#include "common.hpp"

float screenToWorld(int val)
{
	return val * METER_PER_PIXELS;
}

int worldToScreen(float val)
{
	return val * PIXELS_PER_METER;
}
