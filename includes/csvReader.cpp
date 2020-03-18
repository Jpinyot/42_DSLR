/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:41:28 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/05 10:45:11 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csvReader.h"

vector<string>	CsvLine::toVecString(const vector<int>& desprecate)
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

vector<double>	CsvLine::toVecDouble(const vector<int>& desprecate)
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

ArrayXd			CsvLine::toArrayDouble(const int& size, const vector<int>& desprecate)
{
	ArrayXd			ret(size, 1);
	int				nextDelimeter = 0;
	int				passDelimeter = 0;
	int				despCnt = 0;
	int				i = 0;
	while (i < size && (nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		if (!desprecate.size() || desprecate[despCnt] != i + despCnt){
			ret(i, 0) = (atof(this->substr(passDelimeter, nextDelimeter - passDelimeter).c_str()));
			i ++;
		}
		else {
			despCnt ++;
		}
		passDelimeter = nextDelimeter + 1;
	}
	if (i < size && (!desprecate.size() || desprecate[despCnt] != i + despCnt)){
		ret(i, 0) = (atof(this->substr(passDelimeter, nextDelimeter - passDelimeter).c_str()));
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
	subsetsNum_ += 1;
	int	nextDelimeter = 0;
	while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		subsetsIndex_.emplace_back(nextDelimeter + 1);
		subsetsNum_ += 1;
	}
}

int	CsvSubsets::drop(const string& s)
{
	int pos = 0;
	if ((pos = this->find(s)) == -1){
		return -1;
	}
	int index = indexOf(pos);
	drops_.emplace_back(index);
	return index;
}

int	CsvSubsets::drop(const int& num)
{
	if (num > subsetsNum_ || num < 0){
		return -1;
	}
	else {
		drops_.emplace_back(num);
		return num;
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

MatrixXd	CsvData::toMatrixDouble()
{
	int rowSize = subsets_.subsetsNeeded();
	vector<int> drops = subsets_.drops();
	sort(drops.begin(), drops.end());
	MatrixXd	ret(lines_.size(), rowSize);
	for (int i = 0; i < lines_.size(); i++){
		ret.row(i) = (lines_[i].toArrayDouble(rowSize, drops));
	}
	return ret;
}

vector<vector<string> >	CsvData::toVecVecString()
{
	vector<int> drops = subsets_.drops();
	sort(drops.begin(), drops.end());
	vector<vector<string> > strVect;
	for (int i = 0; i < lines_.size(); i++){
		strVect.emplace_back(lines_[i].toVecString(drops));
	}
	return strVect;
}

vector<vector<double> >	CsvData::toVecVecDouble()
{
	vector<int> drops = subsets_.drops();
	sort(drops.begin(), drops.end());
	vector<vector<double> > ret;
	for (int i = 0; i < lines_.size(); i++){
		ret.emplace_back(lines_[i].toVecDouble(drops));
	}
	return ret;
}

vector<string>	CsvData::toVectorString(const int& id)
{
	if (id > subsets_.subsetsNum() || id < 0){
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
	if (id > subsets_.subsetsNum() || id < 0){
		return {};
	}
	vector<double> ret;
	for (int i = 0; i < lines_.size(); i++){
		ret.emplace_back(lines_[i].toDouble(id));
	}
	return ret;
}

vector<string>	CsvData::y(const int& id)
{
	if (id > subsets_.subsetsNum() || id < 0){
		return {};
	}
	subsets_.drop(id);
	vector<string> ret;
	for (int i = 0; i < lines_.size(); i++){
		ret.emplace_back(lines_[i].toString(id));
	}
	return ret;
}

vector<string>	CsvData::y(const string& str)
{
	int id = subsets_.drop(str);
	if (id > subsets_.subsetsNum() || id < 0){
		return {};
	}
	vector<string> ret;
	for (int i = 0; i < lines_.size(); i++){
		ret.emplace_back(lines_[i].toString(id));
	}
	return ret;
}
