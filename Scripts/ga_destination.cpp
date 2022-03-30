#include "ga_destination.h"

void init_genes(MySolution& p,const std::function<double(void)> &rnd01)
{
	p.p1 = rnd01();
	p.a1 = 3.0*rnd01();
	p.a2 = 3.0*rnd01();
	p.a3 = 3.0*rnd01();
	p.a4 = 3.0*rnd01();
	p.a5 = 3.0*rnd01();
}

bool eval_solution(const MySolution& p,MyMiddleCost &c)
{
	double p1 = p.p1;
	double a1 = p.a1;
	double a2 = p.a2;
	double a3 = p.a3;
	double a4 = p.a4;
	double a5 = p.a5;
	simulator* s = new simulator(p1,a1,a2,a3,a4,a5);
	s->populate();
	// s->normalise_agents();
	s->read_data();
	c.simout = s->run();
	s->~simulator();

	// the middle comupations of cost:
	// c.cost_A=log(1.0+x*sqrt(x*y));
	// c.cost_B=98.0-100.0*(1.0-1.0/(1.0+y*sqrt(x*y)));

	return true; // genes are accepted
}

MySolution mutate(const MySolution& X_base,const std::function<double(void)> &rnd01,double shrink_scale)
{
	MySolution X_new;
	bool in_range_p1,in_range_a1, in_range_a2, in_range_a3, in_range_a4, in_range_a5;
	do{
		X_new=X_base;
		X_new.p1+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.a1+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.a2+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.a3+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.a4+=0.2*(rnd01()-rnd01())*shrink_scale;
		X_new.a5+=0.2*(rnd01()-rnd01())*shrink_scale;

		in_range_p1= (X_new.p1>=0.0 && X_new.p1<1.0);
		in_range_a1= (X_new.a1>=0.0 && X_new.a1<3.0);
		in_range_a2= (X_new.a2>=0.0 && X_new.a2<3.0);
		in_range_a3= (X_new.a3>=0.0 && X_new.a3<3.0);
		in_range_a4= (X_new.a4>=0.0 && X_new.a4<3.0);
		in_range_a5= (X_new.a5>=0.0 && X_new.a5<3.0);

	} while( !in_range_p1 || !in_range_a1 || !in_range_a2 || !in_range_a3 || !in_range_a4 || !in_range_a5);
	return X_new;
}

MySolution crossover(const MySolution& X1,const MySolution& X2,const std::function<double(void)> &rnd01)
{
	MySolution X_new;
	double r;
	r=rnd01();
	X_new.p1=r*X1.p1+(1.0-r)*X2.p1;
	r=rnd01();
	X_new.a1=r*X1.a1+(1.0-r)*X2.a1;
	r=rnd01();
	X_new.a2=r*X1.a2+(1.0-r)*X2.a2;
	r=rnd01();
	X_new.a3=r*X1.a3+(1.0-r)*X2.a3;
	r=rnd01();
	X_new.a4=r*X1.a4+(1.0-r)*X2.a4;
	r=rnd01();
	X_new.a5=r*X1.a5+(1.0-r)*X2.a5;
	return X_new;
}

double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X)
{
	double fitnesscore = 0.0;
	double denom = 0.0;
		for(int i = 0; i< X.middle_costs.simout.size(); i++)
			for(int j = 0; j< X.middle_costs.simout[i].size();j++)
			{denom += X.middle_costs.simout[i][j];}
		fitnesscore = denom;
		return fitnesscore;
	// finalize the cost
}

void SO_report_generation(int generation_number, const EA::GenerationType<MySolution,MyMiddleCost> &last_generation, const MySolution& best_genes)
{
	std::ofstream output_file;
	output_file.open("./bin/result_ga_dest_so.txt");
	// output_file<<"step"<<"\t"<<"x_best"<<"\t"<<"y_best"<<"\t"<<"cost_avg"<<"\t"<<"cost_best"<<"\n";

	std::cout
		<<"Generation ["<<generation_number<<"], "
		<<"Best="<<last_generation.best_total_cost<<", "
		<<"Average="<<last_generation.average_cost<<", "
		<<"Best genes=("<<best_genes.to_string()<<")"<<", "
		<<"Exe_time="<<last_generation.exe_time
		<<std::endl;

	output_file
		<<generation_number<<"\t"
		<<best_genes.p1<<"\t"
		<<best_genes.a1<<"\t"
		<<best_genes.a2<<"\t"
		<<best_genes.a3<<"\t"
		<<best_genes.a4<<"\t"
		<<best_genes.a5<<"\t"
		<<last_generation.average_cost<<"\t"
		<<last_generation.best_total_cost<<"\n";

	output_file.close();

}
