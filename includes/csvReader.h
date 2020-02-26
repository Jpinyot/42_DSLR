/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:39:51 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/26 11:02:38 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
/* #include <time.h> */
/* #include <stdlib.h> */
/* #include <locale> */
/* #include <sstream> */
/* #include <algorithm> */
/* #include <iterator> */

#define DELIMETER ','

using namespace std;

	/* line from the csv file */
class CsvLine : public string
{
	private:
		/* int	size_; */

	public:
		CsvLine()
		{};
		virtual ~CsvLine() {};
		vector<string>	toStrings(const vector<int>& desprecate={});
		vector<double>	toDouble(const vector<int>& desprecate={});
		string			toString(const int& id);
		double			toDouble(const int& id);
};

	/* the data subsets, data descriptors */
class CsvSubsets : public CsvLine
{
	private:
		bool					hasHash_;
		vector<int>				deprecates_;
		vector<int>				hashedData_;
		vector<vector<string> >	hashTable_;
		vector<int>				subsetsIndex_;
		int						subsetsNum_;

		int		indexOf(int indx);

	public:
		CsvSubsets():
			hasHash_(false), deprecates_(0), hashedData_(0), hashTable_(0), subsetsIndex_(0), subsetsNum_(0)
		{};
		virtual ~CsvSubsets() {};
		void		indexing();
		bool		deprecate(const string& s);
		bool		deprecate(const int& num);
		bool		hashNeeded(const int& num);
		
		vector<int>	deprecates() {return deprecates_;}
		int			subsetsNum() {return subsetsNum_;}

		/* void		hashedData(const vector<vector<string> >& hashedData) {hashedData = } */
};

	/* main class */
class CsvData
{
	private:
		string					fileDescriptor_;
		vector<CsvLine>			lines_;
		vector<vector<double> >	data_;
		CsvSubsets				subsets_;

		void	getData();

	public:
	CsvData(string fileDescriptor):
		fileDescriptor_(fileDescriptor), lines_(0), data_(0), subsets_()
	{
		getData();
	};
	virtual	~CsvData() {};
	vector<vector<string> >	toMatrixString();
	vector<vector<double> >	toMatrixDouble(const bool& hashData=false);
	vector<string>			toVectorString(const int& id);
	vector<double>			toVectorDouble(const int& id);
	/* vector<double>			toVectorDouble(const string& id); */
	/* vector<string>			toVectorString(const string& id); */

	string					line(const int lineNum) {return static_cast<string>(lines_[lineNum]);}
	string					infoLine() {return static_cast<string>(subsets_);}
	bool					deprecate(const string& s) {return subsets_.deprecate(s);}
	bool					deprecate(const int& num) {return subsets_.deprecate(num);}
};
