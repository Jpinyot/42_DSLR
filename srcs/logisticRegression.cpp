/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:53 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/03 08:30:32 by jpinyot          ###   ########.fr       */
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
}

inline void	LogisticRegression::yClasses()
{
	vector<string> y = dataTrain_.toVectorString(1);
	int size = y.size();
	vector<string>::iterator it;

	for(int i = 0; i < size; i++){
		if ((it = find(yClasses_.begin(), yClasses_.end(), y[i])) == yClasses_.end()){
			yClasses_.emplace_back(y[i]);
			y_.emplace_back(VectorXd::Zero(size, 1));
		}
		else {
			y_[it - yClasses_.begin()](i, 0) = 1;
		}
	}
	/* cout << y_[0] << "\n" << y_.size();; */
}

inline double	LogisticRegression::sigmoid(const double& x)
{
	return 1.0 / (1.0 + exp(x * -1));
	/* return x / (1 + abs(x));	//approximateVersion */
}

inline void	LogisticRegression::train()			//inlin can give error
{
	if (!X_.size()){
		X_ = dataTrain_.toMatrixDouble();
		standarizeX();
	}
	if (!y_.size()){
		/* y_ = dataTrain_.toVectorString(1); */
		yClasses();
	}
	for (int i = 0; i < yClasses_.size(); i++){
		for (int j = 0; j < CYCLES; j++){
			/* int y = (yClasses_[i] == y_[j]) ? 1 : 0; */
			/* (X_ * -1).exp(); */
		}
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
