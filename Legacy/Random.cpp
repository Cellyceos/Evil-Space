#include "stdafx.h"
#include "Random.h"

using namespace std;

Random::Random()
{
	SeedGeneration(GetTickCount());
}
Random::Random(int seed)
{
	SeedGeneration(seed);
}

Random::~Random()
{
	delete SeedArray;
}

void Random::SeedGeneration(int seed)
{
	SeedArray = new int[56];

	int num2 = 161803398 - abs(seed);

	SeedArray[55] = num2;

	int num3 = 1;

	for (int i = 1; i < 55; i++)
	{
		int index = (21 * i) % 55;
		SeedArray[index] = num3;
		num3 = num2 - num3;
		if (num3 < 0)
		{
			num3 += 2147483647;
		}
		num2 = SeedArray[index];
	}

	for (int j = 1; j < 5; j++)
	{
		for (int k = 1; k < 56; k++)
		{
			SeedArray[k] -= SeedArray[1 + ((k + 30) % 55)];
			if (SeedArray[k] < 0)
			{
				SeedArray[k] += 2147483647;
			}
		}
	}

	inext = 0;
	inextp = 21;
	seed = 1;
}

double Random::GetSampleForLargeRange()
{
	int num = InternalSample();
	if ((((InternalSample() % 2) == 0) ? 1 : 0) != 0)
	{
		num = -num;
	}
	double num2 = num;
	num2 += 2147483646.0;
	return (num2 / 4294967293);
}

int Random::InternalSample()
{
	int next = inext;
	int nextp = inextp;
	if (++next >= 56)
	{
		next = 1;
	}
	if (++nextp >= 56)
	{
		nextp = 1;
	}
	int num = SeedArray[next] - SeedArray[nextp];
	if (num < 0)
	{
		num += 2147483647;
	}
	
	SeedArray[next] = num;
	inext = next;
	inextp = nextp;
	return num;
}

int Random::Next()
{
	return InternalSample();
}

int Random::Next(int maxValue)
{
	return (int) (Sample() * maxValue);
}

float Random::Next(float maxValue)
{
	return (float)(Sample() * maxValue);
}

int Random::Next(int minValue, int maxValue)
{
	long num = maxValue - minValue;
	if (num <= 2147483647L)
	{
		return (((int) (Sample() * num)) + minValue);
	}
	return (((int) ((long) (GetSampleForLargeRange() * num))) + minValue);
}

float Random::Next(float minValue, float maxValue)
{
	double num = maxValue - minValue;
	if (num <= 2147483647.0)
	{
		return (((float) (Sample() * num)) + minValue);
	}
	return (((float) ((double) (GetSampleForLargeRange() * num))) + minValue);
}

double Random::NextDouble()
{
	return Sample();
}

double Random::Sample()
{
	return (InternalSample() * 4.6566128752457969E-10);
}







