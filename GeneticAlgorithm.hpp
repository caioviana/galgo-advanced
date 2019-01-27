#pragma once

namespace galgo {


	template <class T> class GeneticAlgorithm
	{
		template <class K> friend class Population;
		template <class K> friend class Chromosome;
		template <class K> using Func = std::vector<K> (*)(const std::vector<K>&);
		private:
			std::vector<PAR<T>> param;
			std::vector<T> lowerBound;
			std::vector<T> upperBound;
			std::vector<T> initialSet;

		public:

			Func<T> Objective;

			void (*Selection) (Population<T> &) = RWS;
			void (*Crossover) (const Population<T> &, CHR<T> &, CHR<T> &) = P1XO;
			void (*Mutation) (CHR<T> &) = SPM;
			void (*Adaptation) (Population<T> &) = nullptr;
			std::vector<T> (*Constraint) (const std::vector<T> &) = nullptr;

			T covrate  = 0.50;
			T mutrate  = 0.05;
			T SP       = 1.5;
			T tolerance  = 5;

			int elitpop =1;
			int matsize;
			int tntsize=10;
			int genstep=10;
			int precision=5;

			template<int...N> GeneticAlgorithm(Func<T> Objective, int popsize, int nbgen,bool output, const Parameter<T,N>&...args);
			void run();

			const CHR<T>& result() const;

		private:
			int nbbit;
			int bngen;
			int nogen =0;
			int nbparam;
			int popsize;
			bool output;

		   template <int I = 0, int...N>
		   class std::enable_if<I == sizeof...(N), void>::type init(const TUP<T,N...>&); 
		   // recursion for initializing parameter(s) data
		   template <int I = 0, int...N>
		   class std::enable_if<I < sizeof...(N), void>::type init(const TUP<T,N...>&);
					

		  
		   // check inputs validity
		   void check() const ;
		   // print results for each new generation
		   void print() const;        


	};
}