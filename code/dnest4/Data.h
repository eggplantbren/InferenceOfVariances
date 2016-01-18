#ifndef DNest4_ABC_Data
#define DNest4_ABC_Data

#include <vector>

class Data
{
	private:
		std::vector<double> x;

		// Summaries
		double x_mean, x_var;

	public:
		Data();
		void load(const char* filename);
		const std::vector<double>& get_x() const { return x; }
		double get_x_mean() const { return x_mean; }
		double get_x_var() const { return x_var; }

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif

