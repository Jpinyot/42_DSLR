/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:07 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/09 19:23:52 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "../includes/csvReader.h"
#include <Eigen/Dense>

#include <unistd.h>
/* #include "../includes/plot.h" */

#define CYCLES 5000
#define LEARNING_RATE 0.2
#define	THETA_FILE "files/theta.csv"
#define MEAN "Mean"
#define STD_DEVIATION "Standard Deviation"
#define THETA "Thetas"
#define DROPS "Drops"
#define DELIMETER ','
#define PREDETERMINATE_Y 1

using namespace std;

enum lineFlags
{
	noFlag = 0,
	thetaFlag = 2,
	meanFlag = 4,
	stdDeviationFlag = 8,
	dropsFlag = 16,
	unknowFlag = 32
};

class LogisticRegression
{
	private:
		bool				haveData_;
		int					cycles_;
		double				learningRate_;
		CsvData				dataTrain_;
		MatrixXd			X_;
		vector<VectorXd>	y_;
		vector<string>		yCol_;
		vector<VectorXd>	thetas_;
		vector<string>		yClasses_;
		MatrixXd			XNorm_;
		VectorXd			mean_;
		VectorXd			stdDeviation_;
		vector<int>			drops_;

		void			standarizeX();
		MatrixXd		standarize(const MatrixXd& X);
		void			yClasses(const int& id=PREDETERMINATE_Y);			//Need dataTrain
		void			getThetaFile(const string& thetaFile=THETA_FILE);
		lineFlags		setLineFlag(const string& str);
		VectorXd		vectorXdFromCsv(const string& str);
		vector<int>		vectorIntFromCsv(const string& str);

	public:
		LogisticRegression(const string& dataTrain, const int& cycles=CYCLES, const double& learningRate=LEARNING_RATE):
			haveData_(true), cycles_(cycles), learningRate_(learningRate), dataTrain_(dataTrain), X_(), y_(0), yCol_(0), thetas_(0), yClasses_(0), XNorm_(), mean_(), stdDeviation_(), drops_(0)
		{}
		LogisticRegression(const int& cycles=CYCLES, const double& learningRate=LEARNING_RATE):
			haveData_(true), cycles_(cycles), learningRate_(learningRate), dataTrain_(), X_(), y_(0), thetas_(0), yClasses_(0), yCol_(0), XNorm_(), mean_(), stdDeviation_(), drops_(0)
		{
			getThetaFile();
		}
		virtual	~LogisticRegression() {};
		void				train();
		void				predict(const string& dataPredict);
		void				setThetaFile(const string& thetaFile=THETA_FILE);	//CREATE FLAG FOR, NEED JUST ONE FILE NAME ALWAYS!!

		inline MatrixXd		X() {return X_;}
		inline bool			drop(const string& str) {return dataTrain_.drop(str);}
		inline bool			drop(const int& num) {return dataTrain_.drop(num);}
		inline string		dataLine(const int& lineNum) {return dataTrain_.line(lineNum);}	//create a case when no dataTrain_
		inline string		dataInfoLine() {return dataTrain_.infoLine();}
		inline void			setY(const string& id) {yCol_ = dataTrain_.y(id);}
		inline void			setY(const int& id) {yCol_ = dataTrain_.y(id);}
};
