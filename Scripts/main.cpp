#include <string>
#include <iostream>
#include <fstream>
#include "simulator.h"
#include "ga_destination.h"
#include "openga.hpp"

int main()
{
	//SO
	EA::Chronometer timer;
	timer.tic();
	GA_Type ga_obj;
	ga_obj.problem_mode= EA::GA_MODE::SOGA;
	// ga_obj.multi_threading=true;
	ga_obj.multi_threading=true;
	ga_obj.idle_delay_us=1; // switch between threads quickly
	ga_obj.verbose=false;
	ga_obj.population=40;
	ga_obj.generation_max=1000;
	ga_obj.calculate_SO_total_fitness=calculate_SO_total_fitness;
	ga_obj.init_genes= init_genes;
	ga_obj.eval_solution= eval_solution;
	ga_obj.mutate= mutate;
	ga_obj.crossover= crossover;
	ga_obj.SO_report_generation= SO_report_generation;
	ga_obj.best_stall_max=10;
	ga_obj.elite_count=10;
	ga_obj.crossover_fraction=0.45;
	ga_obj.mutation_rate=0.3;
	std::cout<<"N_thread:  "<< ga_obj.N_threads << std::endl;
	ga_obj.solve();

// 	simulator* s = new simulator(0.761059, 1.815692, 1.917239, 2.831702, 1.157506, 0.225870);
// 	s->populate();
// 	s->read_data();
// 	s->run();
// 	std::vector< std::vector<double> > v = s->pass_output_data();
// 	s->~simulator();
// 	std::ofstream output_file2;
// 	output_file2.open("destinationsimflow-sim00.csv");
// 	for(int i = 0; i  < v.size(); i++){
// 		for(int j = 0; j< v[i].size(); j++){
// 			double a = v[i][j]; //population_resolution
// 			output_file2 << a << ',';
// 		}
// 		output_file2 << '\n';
// 	}
// 	output_file2.close();
return 0;
}
