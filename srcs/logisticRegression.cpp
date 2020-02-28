/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:53 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/28 12:17:09 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logisticRegression.h"

https://stats.stackexchange.com/questions/289215/how-to-standardize-the-data-matrix-before-applying-svd-for-pca
https://gist.github.com/kevinhughes27/6356673

inline void	LogisticRegression::standarizeX()
{
	ArrayXd	mean(X_.cols(), 1);
	mean = X_.colwise().mean();//colwise aplies individualy to each colum
	/* cout << mean << "\n"; */

	ArrayXd	stdDeviation(X_.cols(), 1);
	stdDeviation = X_.rowwise() - mean;
	/* stdDeviation = (X_.colwise() - mean.transpose()).array().pow(2).rowwise().sum() / X_.cols(); */
	/* cout << X_.colwise() << "\n"; */
	cout << stdDeviation << "\n";
}

inline void	LogisticRegression::train()			//inlin can give error
{
	if (!X_.size()){
		X_ = dataTrain_.toMatrixDouble();
		standarizeX();
	}
}


int main()
{
	LogisticRegression logReg("files/dataset_train.csv");
	/* CsvData data("files/dataset_train.csv"); */
	logReg.dataDeprecate("Index");
	logReg.dataDeprecate("Hogwarts House");
	logReg.dataDeprecate("First Name");
	logReg.dataDeprecate("Last Name");
	logReg.dataDeprecate("Best Hand");
	logReg.train();

	/* vector<vector<double> > dataDoub =	logReg.toMatrixDouble(); */
	/* for( auto const& string_vec : dataDoub ){ */
	/* 	for( auto const& s : string_vec ){ */
        	/* cout << s << ' '; */
        	/* /1* cout << s << ' '; *1/ */
	/* 	} */
        /* cout << endl; */
	/* } */
	return 0;
}
