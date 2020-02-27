/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:39:51 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/27 12:36:15 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <Eigen/Dense>

#define DELIMETER ','

using namespace std;
using namespace Eigen;

	/* line from the csv file */
class CsvLine : public string
{
	private:
		/* int	size_; */

	public:
		CsvLine()
		{};
		virtual ~CsvLine() {};
		vector<string>	toVecString(const vector<int>& desprecate={});
		vector<double>	toVecDouble(const vector<int>& desprecate={});
		ArrayXd			toArrayDouble(const int& size, const vector<int>& desprecate={});
		string			toString(const int& id);
		double			toDouble(const int& id);
};

	/* the data subsets, data descriptors */
class CsvSubsets : public CsvLine
{
	private:
		vector<int>				deprecates_;
		vector<int>				subsetsIndex_;
		int						subsetsNum_;

		int		indexOf(int indx);

	public:
		CsvSubsets():
			deprecates_(0), subsetsIndex_(0), subsetsNum_(0)
		{};
		virtual ~CsvSubsets() {};
		void		indexing();
		bool		deprecate(const string& s);
		bool		deprecate(const int& num);
		bool		hashNeeded(const int& num);
		
		vector<int>	deprecates() {return deprecates_;}
		int			subsetsNum() {return subsetsNum_;}
		int			subsetsNeeded() {return subsetsNum_ - deprecates_.size();}
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
	MatrixXd				toMatrixDouble();
	vector<vector<string> >	toVecVecString();
	vector<vector<double> >	toVecVecDouble();
	vector<string>			toVectorString(const int& id);
	vector<double>			toVectorDouble(const int& id);

	string					line(const int lineNum) {return static_cast<string>(lines_[lineNum]);}
	string					infoLine() {return static_cast<string>(subsets_);}
	bool					deprecate(const string& s) {return subsets_.deprecate(s);}
	bool					deprecate(const int& num) {return subsets_.deprecate(num);}
};
