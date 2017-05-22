#pragma once
#include "stdafx.h"

class XorShift
{
public:
	XorShift(int x, int y, int z, int w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
	}

	inline uint32_t Random()
	{
		static int a = 15;
		static int b = 21;
		static int c = 4;

		int tmp = (x ^ (x << a));
		x = y;
		y = z;
		z = w;
		return w = (w ^ (w >> b)) ^ (tmp ^ (tmp >> c));
	}

	void SetSeeds(int newX, int newY, int newZ, int newW)
	{

		x = newX;
		y = newY;
		z = newZ;
		w = newW;
	}

private:
	int x;
	int y;
	int z;
	int w;
};