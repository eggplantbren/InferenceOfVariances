#include "MyModel.h"
#include "DNest4/code/Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest4;

MyModel::MyModel()
:x_fake_latent(Data::get_instance().get_x().size())
{

}

void MyModel::from_prior(RNG& rng)
{
	mu = -10. + 20.*rng.rand();
	log_sigma = -10. + 20.*rng.rand();
	for(size_t i=0; i<x_fake_latent.size(); i++)
		x_fake_latent[i] = rng.randn();
}

double MyModel::perturb(RNG& rng)
{
	int which = rng.rand_int(3);

	if(which == 0)
	{
		mu += 20.*rng.randh();
		wrap(mu, -10., 10.);
	}
	if(which == 1)
	{
		log_sigma += 20.*rng.randh();
		wrap(log_sigma, -10., 10.);
	}
	if(which == 2)
	{
		int i = rng.rand_int(x_fake_latent.size());
		x_fake_latent[i] = rng.randn();
	}

	return 0.;
}

double MyModel::log_likelihood() const
{
	double x_mean = Data::get_instance().get_x_mean();
	double x_var = Data::get_instance().get_x_var();

	double sigma = exp(log_sigma);

	// Assemble fake dataset
	vector<double> x_fake = x_fake_latent;
	for(size_t i=0; i<x_fake.size(); i++)
		x_fake[i] = mu + sigma*x_fake[i];

	// Summary stats of fake dataset
	double x_fake_mean = 0.;
	for(size_t i=0; i<x_fake.size(); i++)
		x_fake_mean += x_fake[i];
	x_fake_mean /= x_fake.size();

	double x_fake_var = 0.;
	for(size_t i=0; i<x_fake.size(); i++)
		x_fake_var += pow(x_fake[i] - x_fake_mean, 2);
	x_fake_var /= x_fake.size();

	// Goodness
	double logL = 0.;

	logL -= pow(x_fake_mean - x_mean, 2);
	logL -= pow(sqrt(x_fake_var) - sqrt(x_var), 2);

	return logL;
}

void MyModel::print(std::ostream& out) const
{
	out<<mu<<' '<<log_sigma<<' ';
}

string MyModel::description() const
{
	return string("");
}

