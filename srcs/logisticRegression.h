/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:07 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/09 09:56:30 by jpinyot          ###   ########.fr       */
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
#define DELIMETER ','

using namespace std;

enum lineFlags
{
	noFlag = 0,
	meanFlag = 2,
	stdDeviationFlag = 4,
	thetaFlag = 8,
	unknowFlag = 16
};

class LogisticRegression
{
	private:
		bool				haveData_;
		CsvData				dataTrain_;
		MatrixXd			X_;
		vector<VectorXd>	y_;
		vector<VectorXd>	thetas_;
		vector<string>		yClasses_;
		MatrixXd			XNorm_;
		VectorXd			mean_;
		VectorXd			stdDeviation_;

		void			standarizeX();
		void			yClasses();			//Need dataTrain
		void			setThetaFile(const string& thetaFile=THETA_FILE);
		lineFlags		setLineFlag(const string& str);
		VectorXd		vectorFromCsv(const string& str);

	public:
		LogisticRegression(const string& dataTrain):
			haveData_(true), dataTrain_(dataTrain), X_(), y_(0), thetas_(0), yClasses_(0), XNorm_(), mean_(), stdDeviation_()
		{}
		/* LogisticRegression(const string& thetaFile=THETA_FILE): */
		LogisticRegression():
			haveData_(false), dataTrain_(), X_(), y_(0), thetas_(0), yClasses_(0), XNorm_(), mean_(), stdDeviation_()
		{
			setThetaFile();
		}
		virtual	~LogisticRegression() {};
		void				train();
		void				predict(const string& dataPredict);
		void				thetaFile(const string& thetaFile=THETA_FILE);	//CREATE FLAG FOR, NEED JUST ONE FILE NAME ALWAYS!!

		inline MatrixXd		X() {return X_;}
		inline bool			drop(const string& str) {return dataTrain_.drop(str);}
		inline bool			drop(const int& num) {return dataTrain_.drop(num);}
		inline string		dataLine(const int& lineNum) {return dataTrain_.line(lineNum);}	//create a case when no dataTrain_
		inline string		dataInfoLine() {return dataTrain_.infoLine();}
};
