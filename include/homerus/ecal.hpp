#pragma once
#include <random>
#include <utility>
#include <vector>
namespace folklore{ namespace homerus
{
	class simple_rand
	{
	private:
		std::random_device                dev;
		std::mt19937                      eng;
		std::uniform_real_distribution<> rand;
	public:
		explicit simple_rand(double a,double b)
			:dev(),eng(dev()),rand(a,b)
		{}
		double operator()(void) noexcept
		{
			return rand(eng);
		}
	};
	simple_rand rn(-0.5,0.5);
	struct ecal
	{
	private:
		size_t size_;
		struct param
		{
			double a,b;
		};
		std::vector<param>                 p_;
		std::random_device                dev;
		std::mt19937                      eng;
		std::uniform_real_distribution<> rand;
		double get_rand(void)
		{
			return rand(eng);
		}
		struct func_t
		{
			param        p;
			explicit func_t(param pp)
				:p(pp)
			{}
			template <typename T>
			double operator()(T e)
			{
				return p.a*e+p.b+rn();
			}
		};
	public:
		ecal()
			:dev(),eng(dev()),rand(-0.5,0.5)
		{
			ecal(".ecal");
		}
		ecal(const char* fname)
			:dev(),eng(dev()),rand(-0.5,0.5)
		{
			FILE* fp=fopen(fname,"r");
			if(fp)
			{
				for(;;)
				{
					double a,b;
					if(fscanf(fp,"%lf %lf",&a,&b)==EOF) break;
					p_.push_back(param{a,b});
				}
				size_=p_.size();
				fclose(fp);
			}
		}
		template <typename T>
		func_t operator[](size_t id) noexcept
		{
			return std::move(id<size_?func_t(p_[id]):func_t(param{0.,0.}));
		}
		template <typename T>
		double operator()(T e,size_t id) noexcept
		{
			return id<size_? p_[id].a*e+p_[id].b+rand(eng):e;
		}
	};
}}
