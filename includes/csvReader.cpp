/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csvReader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:41:28 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/25 11:10:21 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "csvReader.h"

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
	subsets_.deprecate("Flying");
	/* cout << subsets_ << "\n\n"; */
	CsvLine line;
	while (getline(file,line)){
		lines_.emplace_back(line);
		/* cout << lines_.back(); */
	}
}

int	main()
{
	CsvData data("files/dataset_train.csv");

	return (0);
}

/* int main() { */
/*     for (int i=0; i<1800; i++) { */
/*         for (int j=0; j<1800; j++) */
/*             std::cout<<rand()/double(RAND_MAX)<<","; */
/*         std::cout << "\n"; */
/*     } */
/* } */
