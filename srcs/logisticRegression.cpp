/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:53 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/05 11:55:15 by jpinyot          ###   ########.fr       */
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
	int rows = y.size();
	int cols = X_.cols();
	vector<string>::iterator it;

	for(int i = 0; i < rows; i++){
		if ((it = find(yClasses_.begin(), yClasses_.end(), y[i])) == yClasses_.end()){
			yClasses_.emplace_back(y[i]);
			y_.emplace_back(VectorXd::Zero(rows, 1));
			y_.back()(i, 0) = 1;
			thetas_.emplace_back(VectorXd::Zero(cols, 1));
		}
		else {
			y_[it - yClasses_.begin()](i, 0) = 1;
		}
	}
}

inline void	LogisticRegression::train()
{

	vector<double>	plotVec;

	if (!X_.size()){
		X_ = dataTrain_.toMatrixDouble();
		standarizeX();
	}
	if (!y_.size()){
		yClasses();
	}

	for (int i = 0; i < yClasses_.size(); i++){
		for (int j = 0; j < CYCLES; j++){
			VectorXd sigmoid = 1 / (1 + ((-XNorm_ * thetas_[i]).array()).exp());
			VectorXd sum = (sigmoid.array() - y_[i].array()).array();
			VectorXd dot = (sum.transpose() * XNorm_) / XNorm_.rows();
			thetas_[i] -= LEARNING_RATE * dot;

			if (i == 0){
				plotVec.emplace_back(sum.sum());		//change for signal
			}
		}
	}
}


int main()
{
	LogisticRegression logReg("files/dataset_train.csv");
	logReg.drop("Index");
	logReg.drop("Hogwarts House");
	logReg.drop("First Name");
	logReg.drop("Last Name");
	logReg.drop("Best Hand");
	logReg.drop("Birthday");

	logReg.drop("Defense Against the Dark Arts");
	logReg.drop("Care of Magical Creatures");
	logReg.drop("Arithmancy");
	logReg.train();
	return 0;
}
