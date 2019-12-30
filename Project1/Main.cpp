#include <vector>
#include <assert.h>

inline
float distance(float x0, float y0, float x1, float y1)
{
	float a = x0 - x1;
	float b = y0 - y1;
	return sqrt(a * a + b * b);
}

// Performs n * n distance calculations
void naiveDistance(const std::vector<float>& x, const std::vector<float>& y, std::vector<float>* distances)
{
	assert(x.size() == y.size());
	const unsigned int numElements = x.size();

	for (unsigned int i = 0; i < numElements; i++)
	{
		for (unsigned int j = 0; j < numElements; j++)
		{			
			(*distances)[j + i * numElements] = distance(x[i], y[i], x[j], y[j]);
		}
	}
}

// Performs n + (n - 1) + (n - 2) ... + (n - (n-1)) distance calculations
// About half of what that the naiveDistance function does
void optimizedDistance(const std::vector<float>& x, const std::vector<float>& y, std::vector<float>* distances)
{
	assert(x.size() == y.size());
	const unsigned int numElements = x.size();
	const unsigned int numDistancesTotal = numElements * numElements;
	
	//const unsigned int halfElements = numElements / 2;
	// TODO: skip calculating distances between the same point (which is always 0)
	// without having to zero out the distance array before writing results

	for (unsigned int i = 0; i < numElements; i++)
	{
		const unsigned int numElementsProcessed = i * numElements;

		// Copy all distances that we've already calculated for this point
		//for (unsigned int j = 0; j < numElementsProcessed && j + numElementsProcessed < numDistancesTotal; j++)
		for(unsigned int j = 0; j < i; j++)
		{
			(*distances)[j + numElementsProcessed] = (*distances)[j + 1];
		}

		for (unsigned int j = i + 1; j < numElements; j++)
		{	
			(*distances)[j + numElementsProcessed] = distance(x[i], y[i], x[j], y[j]);
		}
	}
}

int main()
{
	const int numElements = 5;
	std::vector<float> x { 1, 5, 8, 10, 2};
	std::vector<float> y { 0, 0, 0, 0, 0 };

	std::vector<float> distancesNaive(numElements * numElements);
	naiveDistance(x, y, &distancesNaive);
	
	std::vector<float> distancesOpt(numElements * numElements);
	optimizedDistance(x, y, &distancesOpt);		

	//assert(memcmp(&distancesNaive, &distancesOpt, numElements * numElements * sizeof(float)) == 0);

	for (int i = 0; i < numElements * numElements; i++)
	{
		if (distancesNaive[i] != distancesOpt[i])
		{
			assert(false);
		}
	}

	return 0;
}