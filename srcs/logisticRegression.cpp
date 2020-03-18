/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:53 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/09 19:24:30 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logisticRegression.h"

inline void	LogisticRegression::standarizeX()
{
	mean_ = X_.colwise().mean();
	stdDeviation_ = (X_.rowwise() - mean_.transpose()).array().pow(2).colwise().sum() / X_.rows();

	XNorm_ = MatrixXd(X_.cols(), X_.rows());
	XNorm_ = (X_.rowwise() - mean_.transpose()).array().rowwise() / stdDeviation_.transpose().array();
}

inline MatrixXd	LogisticRegression::standarize(const MatrixXd& X)
{
	MatrixXd ret(X.cols(), X.rows());
	ret = (X.rowwise() - mean_.transpose()).array().rowwise() / stdDeviation_.transpose().array();
	return ret;
}

inline void	LogisticRegression::yClasses(const int& id)
{
	if (!yCol_.size()){
		yCol_ = dataTrain_.y(id);
	}
	int rows = yCol_.size();
	int cols = X_.cols();
	vector<string>::iterator it;

	for(int i = 0; i < rows; i++){
		if ((it = find(yClasses_.begin(), yClasses_.end(), yCol_[i])) == yClasses_.end()){
			yClasses_.emplace_back(yCol_[i]);
			y_.emplace_back(VectorXd::Zero(rows, 1));
			y_.back()(i, 0) = 1;
			thetas_.emplace_back(VectorXd::Zero(cols, 1));
		}
		else {
			y_[it - yClasses_.begin()](i, 0) = 1;
		}
	}
}

inline void LogisticRegression::getThetaFile(const string& thetaFile)
{
	ifstream file(thetaFile);
	if (!file){
		cout << "NO FILE!!"; //When there is no file!!
	}
	else{
		string		line = "";
		lineFlags	lineFlag = noFlag;
		bool		lineIsClass = true;
		while (getline(file,line)){
			if (lineFlag == noFlag){
				lineFlag = setLineFlag(line);
			}
			else {
				switch (lineFlag){
					case thetaFlag:
						if (lineIsClass) yClasses_.emplace_back(line);
						else thetas_.emplace_back(vectorFromCsv(line));
						lineIsClass = !lineIsClass;
						break;
					case meanFlag:
						mean_ = vectorFromCsv(line);
						lineFlag = noFlag;
						break;
					case stdDeviationFlag:
						stdDeviation_ = vectorFromCsv(line);
						lineFlag = noFlag;
						break;
					default :
						lineFlag = noFlag;
						break;
				}
			}
		}
	}
}

inline lineFlags	LogisticRegression::setLineFlag(const string& str)
{
	if (str == MEAN){
		return meanFlag;
	}
	else if (str == STD_DEVIATION){
		return stdDeviationFlag;
	}
	else if (str == THETA){
		return thetaFlag;
	}
	else {
		return unknowFlag;
	}
}

inline VectorXd	LogisticRegression::vectorFromCsv(const string& str)
{
	VectorXd		ret(count(str.begin(), str.end(), DELIMETER) + 1, 1);
	int				nextDelimeter = 0;
	int				passDelimeter = 0;
	int				i = 0;
	while ((nextDelimeter = str.find(DELIMETER, nextDelimeter + 1)) != -1){
		ret(i, 0) = (atof(&str[passDelimeter]));
		i ++;
		passDelimeter = nextDelimeter + 1;
	}
	ret(i, 0) = (atof(&str[passDelimeter]));
	return ret;
}

inline void	LogisticRegression::train()
{
	if (!X_.size()){
		X_ = dataTrain_.toMatrixDouble();
		standarizeX();
	}
	if (!y_.size()){
		yClasses();
	}

	for (int i = 0; i < yClasses_.size(); i++){
		for (int j = 0; j < cycles_; j++){
			VectorXd sigmoid = 1 / (1 + ((-XNorm_ * thetas_[i]).array()).exp());
			VectorXd sum = (sigmoid.array() - y_[i].array()).array();
			VectorXd dot = (sum.transpose() * XNorm_) / XNorm_.rows();
			thetas_[i] -= learningRate_ * dot;
		}
	}

		VectorXd tmp = 1 / (1 + ((-XNorm_ * thetas_[0]).array()).exp());
	for (int i = 0; i < 4; i++){
		cout << tmp[i] << "\t" << y_[0][i] << "\n";
	}
}

inline void	LogisticRegression::predict(const string& dataPredict)
{
	CsvData	file(dataPredict);
	file.drop("Index");
	file.drop("Hogwarts House");
	file.drop("First Name");
	file.drop("Last Name");
	file.drop("Best Hand");
	file.drop("Birthday");

	file.drop("Defense Against the Dark Arts");
	file.drop("Care of Magical Creatures");
	file.drop("Arithmancy");						//NEED TO PASS IN THETA FILE

	MatrixXd XNorm = standarize(file.toMatrixDouble());
	vector<VectorXd> ret;

	for (int i = 0; i < thetas_.size(); i++){
		VectorXd sigmoid = 1 / (1 + ((-XNorm * thetas_[i]).array()).exp());
		ret.emplace_back(sigmoid);
	}
}

inline void	LogisticRegression::setThetaFile(const string& thetaFile)
{
	ofstream file(thetaFile);
	if (!file){
		cout << "Error opening file.\n";//When haven't open the file
	}
	file << MEAN << '\n';
	for (int i = 0; i < mean_.size(); i++){
		file << mean_(i, 0);
		if (i + 1 < mean_.size())
			file << ',';
	}
	file << '\n' << STD_DEVIATION << '\n';
	for (int i = 0; i < stdDeviation_.size(); i++){
		file << stdDeviation_(i, 0);
		if (i + 1 < stdDeviation_.size())
			file << ',';
	}
	file << '\n' << THETA;
	for (int i = 0; i < thetas_.size(); i++){
		file << "\n" << yClasses_[i] << "\n";
		for (int j = 0; j < thetas_[i].size(); j++){
			file << thetas_[i](j, 0);
			if (j + 1 < thetas_[i].size())
				file << ',';
		}
	}
	file.close();
}

int main()
{
	/* LogisticRegression	logReg; */
	/* logReg.predict("files/dataset_train.csv"); */


	LogisticRegression logReg("files/dataset_train.csv");
	logReg.setY("Hogwarts House");
	/* logReg.drop("Hogwarts House"); */
	logReg.drop("Index");
	logReg.drop("First Name");
	logReg.drop("Last Name");
	logReg.drop("Best Hand");
	logReg.drop("Birthday");
	logReg.drop("Defense Against the Dark Arts");
	logReg.drop("Care of Magical Creatures");
	logReg.drop("Arithmancy");
	logReg.train();
	/* logReg.setThetaFile(); */
	/* logReg.predict("files/dataset_test.csv"); */
	return 0;
}
