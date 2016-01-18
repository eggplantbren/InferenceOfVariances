#include "Data.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Data Data::instance;

Data::Data()
{

}

void Data::load(const char* filename)
{
	fstream fin(filename, ios::in);
	if(!fin)
	{
		cerr<<"# ERROR: Couldn't open file "<<filename<<"."<<endl;
		return;
	}

	double temp;
	x.clear();
	while(fin>>temp)
		x.push_back(temp);
	cout<<"# Loaded "<<x.size()<<" points from file "<<filename<<"."<<endl;

	fin.close();

	// Compute the summaries
	x_mean = 0.;
	for(const double& xx: x)
		x_mean += xx;
	x_mean /= x.size();

	x_var = 0.;
	for(const double& xx: x)
		x_var += pow(xx - x_mean, 2);
	x_var /= x.size();	
}

