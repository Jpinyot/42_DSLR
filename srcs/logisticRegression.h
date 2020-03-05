/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:07 by jpinyot           #+#    #+#             */
/*   Updated: 2020/03/05 11:53:58 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include <cmath>
#include "../includes/csvReader.h"
#include <Eigen/Dense>

#include <unistd.h>
/* #include "../includes/plot.h" */

#define CYCLES 5000
#define LEARNING_RATE 0.2

using namespace std;

class LogisticRegression
{
	private:
		CsvData				dataTrain_;
		MatrixXd			X_;
		vector<VectorXd>	y_;
		vector<VectorXd>	thetas_;
		vector<string>		yClasses_;
		MatrixXd			XNorm_;

		void			standarizeX();
		void			yClasses();

	public:
		LogisticRegression(const string& dataTrain):
			dataTrain_(dataTrain), X_(), y_(0), thetas_(0), yClasses_(0), XNorm_()
		{}
		virtual	~LogisticRegression() {};
		void		train();


		inline MatrixXd		X() {return dataTrain_.toMatrixDouble();}
		inline bool			drop(const string& str) {return dataTrain_.drop(str);}
		inline bool			drop(const int& num) {return dataTrain_.drop(num);}
		inline string		dataLine(const int& lineNum) {return dataTrain_.line(lineNum);}
		inline string		dataInfoLine() {return dataTrain_.infoLine();}
};
