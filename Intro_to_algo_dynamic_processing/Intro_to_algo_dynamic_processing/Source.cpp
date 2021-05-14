#include <iostream>
#include <random>
using namespace std;

/* step means the stage on the assembly line, start1 means the start point on line 1, start2 means the start point on line 2, n for the scale of assembly_line*/
double back_trace(double** assembly_line, double** change_cost ,int step, double start1, double start2, int n, double minimum_trace, double present_trace)
{
	if (step >= n)
	{
		if (present_trace < minimum_trace)
		minimum_trace = present_trace;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			present_trace += 
		}
	}
}
int main()
{
	default_random_engine generator;
	uniform_real_distribution<double> distribution(1, 100);
	/* assembly_line for the time need to use on a certain step */
	double** assembly_line = new double* [2];
	/* change_time means the exchange time */
	/* As for exchange, it only need to generate n - 1 time */
	double** change_time = new double* [2];
	/* n for n steps on the line, need to update, now get from console */
	int n;
	cin >> n;
	for (int i = 0; i < 2; i++)
	{
		assembly_line[i] = new double[n];
		change_time[i] = new double[n - 1];
	}

	/* generate random data */
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			assembly_line[i][j] = distribution(generator);
		}
		for (int j = 0; j < n - 1; j++)
		{
			change_time[i][j] = distribution(generator);
		}
	}

	/* generate start time */
	double start_time_0 = distribution(generator);
	double start_time_1 = distribution(generator);

	
	for (int i = 0; i < 2; i++)
	{
		delete[] assembly_line[i];
		delete[] change_time[i];
	}
	delete[] assembly_line;
	delete[] change_time;


	return 0;
}