#include <iostream>
#include <random>
using namespace std;
int main()
{
	default_random_engine generator;
	uniform_real_distribution<double> distribution(1, 100);

	return 0;
}