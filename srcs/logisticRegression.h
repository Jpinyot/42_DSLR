/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logisticRegression.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:11:07 by jpinyot           #+#    #+#             */
/*   Updated: 2020/02/28 09:48:25 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/csvReader.h"
#include <Eigen/Dense>

using namespace std;

class LogisticRegression
{
	private:
		CsvData		dataTrain_;
		/* CsvData		dataTest_; */
		MatrixXd	X_;
		ArrayXd		y_;

	public:
		LogisticRegression(const string& dataTrain):
			dataTrain_(dataTrain), X_(), y_()
		{}
		virtual	~LogisticRegression() {};
		void		train();


		inline MatrixXd		X() {return dataTrain_.toMatrixDouble();}
		/* inline ArrayXd		y() {return y_;}				//need information about the y line of data */
		inline bool			dataDeprecate(const string& str) {return dataTrain_.deprecate(str);}		//drop
		inline bool			dataDeprecate(const int& num) {return dataTrain_.deprecate(num);}
		inline string		dataLine(const int& lineNum) {return dataTrain_.line(lineNum);}
		inline string		dataInfoLine() {return dataTrain_.infoLine();}
};
