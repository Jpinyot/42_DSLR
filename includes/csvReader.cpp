/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:41:28 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/04 11:54:26 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csvReader.h"

inline vector<string>	CsvLine::toVecString(const vector<int>& desprecate)
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

inline vector<double>	CsvLine::toVecDouble(const vector<int>& desprecate)
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

inline ArrayXd			CsvLine::toArrayDouble(const int& size, const vector<int>& desprecate)
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

inline string	CsvLine::toString(const int& id)
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

inline double	CsvLine::toDouble(const int& id)
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

inline int		CsvSubsets::indexOf(int indx)
{
	for (int i = 0; i < subsetsIndex_.size(); i++){
		if (subsetsIndex_[i] == indx){
			return i;
		}
	}
	return -1;
}

inline void	CsvSubsets::indexing()
{
	subsetsIndex_.emplace_back(0);
	subsetsNum_ += 1;
	int	nextDelimeter = 0;
	while ((nextDelimeter = this->find(DELIMETER, nextDelimeter + 1)) != -1){
		subsetsIndex_.emplace_back(nextDelimeter + 1);
		subsetsNum_ += 1;
	}
}

inline bool	CsvSubsets::drop(const string& s)
{
	int pos = 0;
	if ((pos = this->find(s)) == -1){
		return false;
	}
	drops_.emplace_back(indexOf(pos));
	return true;
}

inline bool	CsvSubsets::drop(const int& num)
{
	if (num > subsetsNum_){
		return false;
	}
	else {
		drops_.emplace_back(num);
		return true;
	}
}

inline void	CsvData::getData()
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

inline MatrixXd	CsvData::toMatrixDouble()
{
	int rowSize = subsets_.subsetsNeeded();
	vector<int> drops = subsets_.drops();
	MatrixXd	ret(lines_.size(), rowSize);
	for (int i = 0; i < lines_.size(); i++){
		ret.row(i) = (lines_[i].toArrayDouble(rowSize, drops));
	}
	return ret;
}

inline vector<vector<string> >	CsvData::toVecVecString()
{
	vector<int> drops = subsets_.drops();
	vector<vector<string> > strVect;
	for (int i = 0; i < lines_.size(); i++){
		strVect.emplace_back(lines_[i].toVecString(drops));
	}
	return strVect;
}

inline vector<vector<double> >	CsvData::toVecVecDouble()
{
	vector<int> drops = subsets_.drops();
	vector<vector<double> > ret;
	for (int i = 0; i < lines_.size(); i++){
		ret.emplace_back(lines_[i].toVecDouble(drops));
	}
	return ret;
}

inline vector<string>	CsvData::toVectorString(const int& id)
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

inline vector<double>	CsvData::toVectorDouble(const int& id)
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
