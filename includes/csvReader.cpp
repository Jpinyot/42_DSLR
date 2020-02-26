/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:41:28 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/26 11:04:04 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csvReader.h"

vector<string>	CsvLine::toStrings(const vector<int>& desprecate)
{
	vector<string>	ret = {};
	int				nextDelimeter = 0;
	int				passDelimeter = 0;
	int				despCnt = 0;
	int				i = 0;
	while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		if (!desprecate.size() || desprecate[despCnt] != i){
			ret.emplace_back(this->substr(passDelimeter, nextDelimeter - passDelimeter));
		}
		else {
			despCnt ++;
		}
		passDelimeter = nextDelimeter + 1;
		i ++;
	}
	if (!desprecate.size() || desprecate[despCnt] != i){
		ret.emplace_back(this->substr(passDelimeter, this->size() - passDelimeter));
	}
	return ret;
}

vector<double>	CsvLine::toDouble(const vector<int>& desprecate)
{
	vector<double>	ret = {};
	int				nextDelimeter = 0;
	int				passDelimeter = 0;
	int				despCnt = 0;
	int				i = 0;
	while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		if (!desprecate.size() || desprecate[despCnt] != i){
			ret.emplace_back(atof(this->substr(passDelimeter, nextDelimeter - passDelimeter).c_str()));
		}
		else {
			despCnt ++;
		}
		passDelimeter = nextDelimeter + 1;
		i ++;
	}
	if (!desprecate.size() || desprecate[despCnt] != i){
		ret.emplace_back(atof(this->substr(passDelimeter, nextDelimeter - passDelimeter).c_str()));
	}
	return ret;
}

string	CsvLine::toString(const int& id)
{
	int				nextDelimeter = 0;
	int				passDelimeter = 0;
	int				i = 0;
	while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		if (id == i){
			return this->substr(passDelimeter, nextDelimeter - passDelimeter);
		}
		passDelimeter = nextDelimeter + 1;
		i ++;
	}
	return 0;
}

double	CsvLine::toDouble(const int& id)
{
	int				nextDelimeter = 0;
	int				passDelimeter = 0;
	int				i = 0;
	while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		if (id == i){
			return atof(this->substr(passDelimeter, nextDelimeter - passDelimeter).c_str());
		}
		passDelimeter = nextDelimeter + 1;
		i ++;
	}
	return 0;
}

int		CsvSubsets::indexOf(int indx)
{
	for (int i = 0; i < subsetsIndex_.size(); i++){
		if (subsetsIndex_[i] == indx){
			return i;
		}
	}
	return -1;
}

void	CsvSubsets::indexing()
{
	subsetsIndex_.emplace_back(0);
	int	nextDelimeter = 0;
	while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		subsetsIndex_.emplace_back(nextDelimeter + 1);
		subsetsNum_ += 1;
	}
}

bool	CsvSubsets::deprecate(const string& s)
{
	int pos = 0;
	if ((pos = this->find(s)) == -1){
		return false;
	}
	deprecates_.emplace_back(indexOf(pos));
	return true;
}

bool	CsvSubsets::deprecate(const int& num)
{
	if (num > subsetsNum_){
		return false;
	}
	else {
		deprecates_.emplace_back(num);
		return true;
	}
}

void	CsvData::getData()
{
	ifstream file(fileDescriptor_);
	if (!file || !getline(file, subsets_)){
		string strError;
		strError.append("Espected file ");
		strError.append(fileDescriptor_);
		strError.append(" not found.");
		throw runtime_error(strError);
	}
	subsets_.indexing();
	CsvLine line;
	while (getline(file,line)){
		lines_.emplace_back(line);
	}
}

vector<vector<string> >	CsvData::toMatrixString()
{
	vector<int> deprecates = subsets_.deprecates();
	vector<vector<string> > strVect;
	for (int i = 0; i < lines_.size(); i++){
		strVect.emplace_back(lines_[i].toStrings(deprecates));
	}
	return strVect;
}

vector<vector<double> >	CsvData::toMatrixDouble(const bool& hashData)
{
	vector<int> deprecates = subsets_.deprecates();
	vector<vector<double> > ret;
	if (hashData){			//working on hashTable

	}
	for (int i = 0; i < lines_.size(); i++){
		if (hashData){

		}
		else {
			ret.emplace_back(lines_[i].toDouble(deprecates));
		}
	}
	return ret;
}

vector<string>	CsvData::toVectorString(const int& id)
{
	if (id > subsets_.subsetsNum()){
		return {};
	}
	vector<string> ret;
	for (int i = 0; i < lines_.size(); i++){
		ret.emplace_back(lines_[i].toString(id));
	}
	return ret;
}

vector<double>	CsvData::toVectorDouble(const int& id)
{
	if (id > subsets_.subsetsNum()){
		return {};
	}
	vector<double> ret;
	for (int i = 0; i < lines_.size(); i++){
		ret.emplace_back(lines_[i].toDouble(id));
	}
	return ret;
}



int	main()
{
	CsvData data("files/dataset_train.csv");
	data.deprecate("Index");
	data.deprecate("Defense Against the Dark Arts");
	data.deprecate("Charms");
	data.deprecate("Herbology");
	data.deprecate("Divination");
	data.deprecate("Muggle Studies");
	/* vector<vector<string> > dataStr =	data.toMatrixString(); */
	vector<vector<double> > dataDoub =	data.toMatrixDouble();
	/* vector<string> y =	data.toVectorString(19); */
	/* vector<double> y =	data.toVectorDouble(0); */

	/* for ( auto const& coutY : y ){ */
	/* 	cout << coutY << "\n"; */
	/* } */
	for( auto const& string_vec : dataDoub ){
		for( auto const& s : string_vec ){
        	cout << s << ' ';
        	/* cout << s << ' '; */
		}
        cout << endl;
	}

	return (0);
}
