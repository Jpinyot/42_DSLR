/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:53 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/04 11:38:32 by jpinyot          ###   ########.fr       */
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
			y_[it - yClasses_.begin()](i, 0) = 1;			//need to pass to 1 when find new class
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

	vector<double>	plotVec;

	if (!X_.size()){
		X_ = dataTrain_.toMatrixDouble();
		standarizeX();
	}
	if (!y_.size()){
		yClasses();
	}
	/* cout << "<<<<" << XNorm_ << ">>>>\n\n"; */

	for (int i = 0; i < yClasses_.size(); i++){
		for (int j = 0; j < CYCLES; j++){
			VectorXd sigmoid = 1 / (1 + ((-XNorm_ * thetas_[i]).array()).exp());
			VectorXd sum = (sigmoid.array() - y_[i].array()).array();
			VectorXd dot = (sum.transpose() * XNorm_) / XNorm_.rows();
			thetas_[i] -= LEARNING_RATE * dot;

			if (i == 0){
				plotVec.emplace_back(sum.sum());
			}
		}
	}

	Plot plotData;

	plotData.initialize();
	plotData.plot(plotVec);
	plotData.show();

		/* cout << thetas_[0] << "\n\n" << XNorm_.row(0) << "\n\n"; */
	for (int i = 0; i < 100; i++){
		cout << 1 / (1 + ((-XNorm_.row(i) * thetas_[0]).array()).exp()) << " " << y_[0].row(i) << "\n";
		/* return ((1 / (1 + ((-inputs*this->w).array() - b).exp())).array() > 0.5).cast<double>(); */
		/* cout << ((-XNorm_.row(i) * thetas_[0]).array()) << "\n\n"; */
		/* auto res = 1 / (1 + ((-XNorm_.row(i) * thetas_[0]).array()).exp()); */
		/* auto y = y_[0].row(i); */
		/* if (res.isEqual()){ */
		/* 	cout << "---" << i << "---\n"; */
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
	logReg.dataDeprecate("Birthday");

	logReg.dataDeprecate("Defense Against the Dark Arts");
	logReg.dataDeprecate("Care of Magical Creatures");
	logReg.dataDeprecate("Arithmancy");
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
