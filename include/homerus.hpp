#pragma once
#include <iterator>
#include <limits>
#include "homerus/adaptor.hpp"
namespace folklore{ namespace homerus
{
	namespace impl_
	{
		template <typename AT_>
		class homerus_data_iterator;
	}
	template <typename AT_>
	class homerus final
	{
	public:
		typedef typename AT_::value_type        value_type;
		typedef std::ptrdiff_t             difference_type;
		typedef std::size_t                      size_type;
		typedef value_type*                        pointer;
		typedef const value_type*            const_pointer;
		typedef value_type&                      reference;
		typedef const value_type&          const_reference;
		typedef impl_::homerus_data_iterator<AT_> iterator;
	private:
		typedef AT_ analyzer_type;
		bool is_open;
		analyzer_type* analyzer; 
		value_type tmp;
		bool next(void)
		{
			if(analyzer) return analyzer->next();
			return false;
		}
		const value_type& get() const
		{
			if(analyzer) return analyzer->get();
			return value_type();
		}
		value_type& get()
		{
			if(analyzer) return analyzer->get();
			return tmp;
		}
		friend impl_::homerus_data_iterator<AT_>;
	public:
		homerus(const homerus<AT_>&)=delete;
		const homerus<AT_>& operator=(const homerus<AT_>&)=delete;
		explicit homerus()
			:is_open(false)
		{
			analyzer=new analyzer_type();
		}
		template <typename T>
		homerus(const char* fname,const T& m)
		{
			analyzer=new analyzer_type();
			is_open=open(fname,m);
		}
		homerus(const char* fname)
		{
			analyzer=new analyzer_type();
			is_open=open(fname);
		}
		~homerus()
		{
			close();
			if(analyzer) delete analyzer;
		}
		bool open(const char* fname)
		{
			if(analyzer)
				return analyzer->open(fname);
			else
				return false;
		}
		template <typename T>
		bool open(const char* fname,const T& m)
		{
			if(analyzer)
				return analyzer->open(fname,m);
			else
				return false;
		}
		void close()
		{
			if(analyzer) analyzer->close();
			is_open=false;
		}
		iterator begin()
		{
			return iterator(this,0);
		}
		iterator end() const
		{
			return iterator();
		}
		explicit operator bool() const
		{
			return is_open;
		}
		template <typename Ad_>
		homerus<AT_>& operator|(folklore::homerus::adaptor<Ad_> a)
		{
			analyzer->register_adaptor(a);
			return *this;
		}
	};
	namespace impl_
	{
		template <typename AT_>
		class homerus_data_iterator final
			:public std::iterator<std::input_iterator_tag,typename homerus<AT_>::value_type>
		{
   		private:
			typedef homerus<AT_>                     homerus_type;
			typedef typename homerus_type::value_type  value_type;
			typedef homerus_data_iterator<AT_>          this_type;
			homerus_type* hp;
			size_t       evt;
			void initialize()
			{
					hp  = nullptr;
					evt = std::numeric_limits<size_t>::max();
			}
			homerus_data_iterator<AT_>()
			{
				initialize();
			}
			friend homerus<AT_>;
		public:
			homerus_data_iterator<AT_>(homerus_type* pt,size_t s)
				:hp(pt),evt(s)
			{}
			homerus_data_iterator<AT_>(homerus_type* pt)
				:hp(pt),evt(0)
			{}
			this_type operator++(int)
			{
				++evt;
				this_type ret(this);
				if(!hp->next())
				{
					initialize();
					return *this;
				}
				return ret;
			}
			this_type operator++()
			{
				++evt;
				if(!hp->next()) initialize();
				return *this;
			}
			bool operator==(const this_type& ar) const
			{
				return hp==ar.hp&&evt==ar.evt;
			}
			bool operator!=(const this_type& ar) const
			{
				return !(*this==ar);
			}
			const value_type& operator*() const
			{
				return hp->get(); 
			}
			const value_type& operator->() const
			{
				return hp->get();
			}
		};
	}
}} // namespace folklore::homerus
