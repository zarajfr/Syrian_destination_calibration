#ifndef SOME_HEADER_GUARD_FOR_DESTINATION_GA
#define SOME_HEADER_GUARD_FOR_DESTINATION_GA

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "math.h"
#include "simulator.h"
#include "openga.hpp"

struct MySolution{
	double p1;
	double a1;
	double a2;
	double a3;
	double a4;
	double a5;

	std::string to_string() const
	{
		return
			"{p1:"+std::to_string(p1)+
			", a1:"+std::to_string(a1)+
			", a2:"+std::to_string(a2)+
			", a3:"+std::to_string(a3)+
			", a4:"+std::to_string(a4)+
			", a5:"+std::to_string(a5)+
			"}";
	}
};
struct MyMiddleCost{
	// This is where the results of simulation
	// is stored but not yet finalized.
	// double cost_A;
	// double cost_B;
	std::vector< std::vector < double > > simout;
};

typedef EA::Genetic<MySolution,MyMiddleCost> GA_Type;
typedef EA::GenerationType<MySolution,MyMiddleCost> Generation_Type;

void init_genes(MySolution& p,const std::function<double(void)> &rnd01);
bool eval_solution(const MySolution& p, MyMiddleCost &c);
MySolution mutate(const MySolution& X_base,const std::function<double(void)> &rnd01,double shrink_scale);
MySolution crossover(const MySolution& X1,const MySolution& X2,const std::function<double(void)> &rnd01);

double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X);
void SO_report_generation(int generation_number, const EA::GenerationType<MySolution,MyMiddleCost> &last_generation, const MySolution& best_genes);

#endif
