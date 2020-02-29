/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:53 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/29 14:59:29 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logisticRegression.h"

inline void	LogisticRegression::standarizeX()
{
	VectorXd mean(X_.cols(), 1);
	mean = X_.colwise().mean();
	VectorXd	stdDeviation(X_.cols(), 1);
	stdDeviation = (X_.rowwise() - mean.transpose()).array().pow(2).colwise().sum() / X_.rows();

	XNorm_ = MatrixXd(X_.cols(), X_.rows());
	XNorm_ = (X_.rowwise() - mean.transpose()).array().rowwise() / stdDeviation.transpose().array();
	cout << XNorm_ << "\n\n" ;
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
