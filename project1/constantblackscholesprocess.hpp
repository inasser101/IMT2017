
#include <ql/stochasticprocess.hpp>
#ifndef constant_blacksholes_process_hpp
#define constant_blacksholes_process_hpp
#include <boost/math/distributions/normal.hpp>

namespace QuantLib {
	//NEED help, idk, it seem so wrong
    class ConstantBlackScholesProcess : public StochasticProcess1D {
	public :
		double calculd1();
		double calculd2();
		double optionPrice();
	protected:
		blackScholesModel();
		blackScholesModel(char callputchoice, double S, double rate, double dy, double strike, double vol, double maturity);
	private:
		double underlyingValue;
		double riskFreeRate;
		double dividendYield;
		double volatility;
		double exercicePrice;
		double exerciceDate;
		char callputchoice;

	
        // your implementation goes here
        
    };

}

#endif