#include <ql/processes/blackscholesprocess.hpp>
#include "constantblackscholesprocess.hpp"
#include <ql/termstructures/volatility/equityfx/localvolsurface.hpp>
#include <ql/termstructures/volatility/equityfx/localvolcurve.hpp>
#include <ql/termstructures/volatility/equityfx/localconstantvol.hpp>
using namespace std;

namespace QuantLib {
	/*! This class describes the stochastic process \f$ S \f$ governed by
	\f[
	d\ln S(t) = (r(t) - q(t) ) dt	+ \sigma dW_t.
	\f]
	*/

	class blackScholesModel : public StochasticProcess1D
	{
	public:

		BlackScholesModel(
			const Real underlyingValue,
			const Handle<YieldTermStructure>& riskFree,
			const Handle<BlackVolTermStructure>& blackVol,
			const Handle<BlackVolTermStructure>& dividendYield,
			const boost::shared_ptr<discretization>& disc)
			:StochasticProcess1D(disc), underlyingValue_(underlyingValue), 
			riskFreeRate_(riskFree), dividendYield_(dividend), blackVolatility_(blackVol) {
				registerWith(underlyingValue_);
				registerWith(riskFreeRate_);
				registerWith(dividendYield_);
				registerWith(blackVolatility_);
			}
		~blackScholesModel();

	private:
		Real underlyingValue_;
		Handle<YieldTermStructure> riskFreeRate_;
		Handle<YieldTermStructure> 	dividendYield_;
		Handle<BlackVolTermStructure> blackVolatility_;
		Real driftC;
		Real diffusionC;

	private:
		Real BlackScholesModel::drift() const {
			return riskFreeRate_ - dividendYield_;
		}

		Real BlackScholesModel::diffusion() const {
			return blackVolatility_;
		}


		/*
	private:
		double underlyingValue;
		double riskFreeRate;
		double dividendYield;
		double volatility;
		double exercicePrice;
		double exerciceDate;
		char callputchoice; //callputchoice='c' pour call et callputchoice='p' pour put
		*/

	};

	
	blackScholesModel::blackScholesModel()
	{
	}
	/*
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
	*/
	


}