/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:39:51 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/25 11:10:36 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
/* #include <time.h> */
/* #include <stdlib.h> */
/* #include <locale> */
/* #include <sstream> */
/* #include <algorithm> */
/* #include <iterator> */

#define DELIMETER ','

using namespace std;

	/* line trasnformet to a vector of double */
/* class CsvVector : public vector<double> */
/* { */
	/* private: */
	/* 	string			line_; */

	/* public: */
	/* 	CsvVector(): */
	/* 		line_(0) */
	/* 	{}; */
/* }; */

	/* line from the csv file */
class CsvLine : public string
{
	private:

	public:
		CsvLine()
		{};
		virtual ~CsvLine() {};
};

	/* the data subsets, data descriptors */
class CsvSubsets : public CsvLine
{
	private:
		vector<int>		deprecates_;
		vector<int>		subsetsIndex_;
		int				size_;

		int		indexOf(int indx)
		{
			for (int i = 0; i < subsetsIndex_.size(); i++){
				if (subsetsIndex_[i] == indx){
					return i;
				}
			}
			return -1;
		}
	public:
		CsvSubsets():
			deprecates_(0), subsetsIndex_(0), size_(1)
		{};
		virtual ~CsvSubsets() {};

		void	indexing()
		{
			subsetsIndex_.emplace_back(0);
			int	nextDelimeter = 0;
			while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
				subsetsIndex_.emplace_back(nextDelimeter + 1);
				size_ += 1;
			}
		}
		bool	deprecate(string s)
		{
			int pos = 0;
			if ((pos = this->find(s)) == -1){
				return false;
			}
			deprecates_.emplace_back(indexOf(pos));
			return true;
		}
};

	/* main class */
class CsvData
{
	private:
		string					fileDescriptor_;
		vector<CsvLine>			lines_;
		vector<vector<double> >	data_;
		CsvSubsets				subsets_;
		/* vector<CsvVector>	data_; */

		void	getData();

	public:
	CsvData(string fileDescriptor):
		fileDescriptor_(fileDescriptor), lines_(0), data_(0), subsets_()
	{
		getData();
	};
	virtual	~CsvData() {};
	bool	deprecate(string s) {return subsets_.deprecate(s);}
};

/* class my_ctype : public std::ctype<char> { */
/* 	public: */
/* 	    std::vector<mask> my_table; */
/* 	public: */
/* 		my_ctype(size_t refs=0): */
/* 			my_table(table_size), std::ctype<char>(my_table.data(), false, refs) */ 
/* 		{ */
/* 			std::copy_n(classic_table(), table_size, my_table.data()); */
/* 			my_table[',']=(mask)space; */
/* 		} */
/* }; */

/* template <class T> */
/* class converter { */
/* 	public: */
/* 		std::stringstream	buffer; */
/* 		my_ctype			*m; */
/* 		std::locale			l; */
/* 	public: */
/* 	    converter(): */
/* 			m(new my_ctype), l(std::locale::classic(), m) */
/* 		{ */
/* 			buffer.imbue(l); */
/* 		} */

/*     	std::vector<T> operator()(std::string const &in) */
/* 		{ */
/*         	buffer.clear(); */
/*         	buffer<<in; */
/*         	return std::vector<T> {std::istream_iterator<T>(buffer),std::istream_iterator<T>()}; */        
/*     	} */
/* }; */

/* int main() { */
/*     std::ifstream						in("somefile.csv"); */
/*     std::vector<std::vector<double>>	numbers; */

/*     std::string			line; */
/*     converter<double>	cvt; */

/*     clock_t start=clock(); */
/*     while (std::getline(in, line)) */
/*         numbers.push_back(cvt(line)); */
/*     clock_t stop=clock(); */
/*     std::cout<<double(stop-start)/CLOCKS_PER_SEC << " seconds\n"; */
/* } */
