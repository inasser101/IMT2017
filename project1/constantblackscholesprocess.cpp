
#include "constantblackscholesprocess.hpp"
#include <iostream>
#include <boost/math/distributions/normal.hpp>
#include <cmath>

using namespace std;
//this is far from being the last Class we ll provide, attributes and methods are defined as simple as it can be


// Returns the probability of x, given the distribution described by mu and sigma.

double cdf(double value)
{
	cout << "erf0     " << std::erf(0.) << endl;
	return 0.5 *(1. + std::erf(value / sqrt(2.)));
}




class blackScholesModel
{
public:
	blackScholesModel();
	blackScholesModel(char callputchoice, double S, double rate, double dy, double strike, double vol, double maturity);
	double calculd1();
	double calculd2();
	double optionPrice();
	~blackScholesModel();

private:
	double underlyingValue;
	double riskFreeRate;
	double dividendYield;
	double volatility;
	double exercicePrice;
	double exerciceDate;
	char callputchoice; //callputchoice='c' pour call et callputchoice='p' pour put


};

blackScholesModel::blackScholesModel(char choice, double S, double rate, double dy, double strike, double vol, double maturity)
{
	callputchoice = choice;
	underlyingValue = S;
	riskFreeRate = rate / 100.0;
	dividendYield = dy / 100.0;
	exercicePrice = strike;
	volatility = vol;
	exerciceDate = maturity / 365.0;
}

blackScholesModel::blackScholesModel()
{
}

double blackScholesModel::calculd1()
{


	return (log(underlyingValue / exercicePrice) +
		(riskFreeRate - dividendYield + pow(volatility, 2) / 2.0)*
		exerciceDate) / (volatility*sqrt(exerciceDate));
}

double blackScholesModel::calculd2()
{
	return (log(underlyingValue / exercicePrice) +
		(riskFreeRate - dividendYield - pow(volatility, 2) / 2)
		*exerciceDate) / (volatility*sqrt(exerciceDate));
}
double blackScholesModel::optionPrice()
{
	if (callputchoice == 'c')
	{
		cout << "call price: " << underlyingValue*exp(-1.0 * dividendYield*exerciceDate)*cdf(calculd1())
			- exercicePrice*exp(-1 * riskFreeRate*exerciceDate)*cdf(calculd2()) << endl;
		cout << cdf(calculd1()) << endl;
		cout << exp(-1.0 * dividendYield*exerciceDate)*cdf(calculd1()) << endl;

		return underlyingValue*exp(-1 * dividendYield*exerciceDate)*
			cdf(calculd1()) - exercicePrice*exp(-1 * riskFreeRate*exerciceDate)*
			cdf(calculd2());
	}
	if (callputchoice == 'p')
	{
		cout << "put price " << -underlyingValue*exp(-1.0 *
			dividendYield*exerciceDate)*cdf(-calculd1()) +
			exercicePrice*exp(-1 * riskFreeRate*exerciceDate)*cdf(-calculd1()) << endl;
		return -underlyingValue*exp(-1 * dividendYield*exerciceDate)*
			cdf(-calculd1()) + exercicePrice*exp(-1 * riskFreeRate*exerciceDate)*
			cdf(-calculd1());
	}
}

blackScholesModel::~blackScholesModel()
{
}


