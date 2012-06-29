#include <cstdio>
#include <cstdlib>
#include "mip_model.hpp"

class Minilp {
public:
	Minilp(MinimipModel* model);
	~Minilp();

	int simplex();

	void printTableaux(char* str="\0");

	void printSolution();

private:
	//std::ostream logger;

	MinimipModel* model;
	std::map<int, double> cmz;
	double* theta;
	int* row_vars;

	std::map<int, double> solution;
};
