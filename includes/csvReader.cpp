/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:41:28 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/25 12:17:18 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csvReader.h"

vector<string>	CsvLine::toStrings(vector<int> desprecate)
{
	/* cout << *this << "\n\n"; */
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

int		CsvSubsets::indexOf(int indx)
{
	for (int i = 0; i < subsetsIndex_.size(); i++){
		if (subsetsIndex_[i] == indx){
			cout << i << "\n\n";
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
		size_ += 1;
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
	/* cout << subsets_ << "\n\n"; */
	CsvLine line;
	while (getline(file,line)){
		lines_.emplace_back(line);
		/* cout << lines_.back(); */
	}
}

vector<vector<string> >	CsvData::strVect()
{
	deprecate("Index");
	deprecate("Flying");
	vector<int> deprecates = subsets_.deprecates();
	vector<vector<string> > strVect;
	/* for (int i = 0; i < lines_.size(); i++){ */
	/* 	strVect.emplace_back(lines_[i].toStrings()); */
	/* } */
		strVect.emplace_back(lines_[0].toStrings(deprecates));
	return strVect;
}


int	main()
{
	CsvData data("files/dataset_train.csv");
	vector<vector<string> > dataStr =	data.strVect();

	for( auto const& string_vec : dataStr ){
    for( auto const& s : string_vec )
        cout << s << endl;
	}
	/* cout << dataStr[0];d */

	return (0);
}

/* int main() { */
/*     for (int i=0; i<1800; i++) { */
/*         for (int j=0; j<1800; j++) */
/*             std::cout<<rand()/double(RAND_MAX)<<","; */
/*         std::cout << "\n"; */
/*     } */
/* } */
