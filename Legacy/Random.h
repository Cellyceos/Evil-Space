#pragma once

class Random 
{
public:
	Random();
	Random(int);

	virtual int Next();
	virtual int Next(int);
	virtual float Next(float);
	virtual int Next(int, int);
	virtual float Next(float, float);
	virtual double NextDouble();
	virtual ~Random();

protected:
	virtual double Sample();

private:
	int inext;
	int inextp;
	static const int MBIG = 2147483647;
	static const int MSEED = 161803398;
	static const int MZ = 0;
	int* SeedArray;

	double GetSampleForLargeRange();
	int InternalSample();
	void SeedGeneration(int);
};