

//#include <ql/stochasticprocess.hpp>
#include <ql\stochasticprocess.hpp>

#ifndef constant_blacksholes_process_hpp
#define constant_blacksholes_process_hpp
#include <ql/termstructures/volatility/equityfx/localvolsurface.hpp>
#include <ql/termstructures/volatility/equityfx/localvolcurve.hpp>
#include <ql/termstructures/volatility/equityfx/localconstantvol.hpp>
namespace QuantLib {
	//NEED help, idk, it seem so wrong
    class constantBlackScholesModel : public StochasticProcess1D {
		constantBlackScholesModel(
			const Real underlyingValue,
			const Handle<YieldTermStructure>& riskFree,
			const Handle<BlackVolTermStructure>& blackVol,
			const Handle<BlackVolTermStructure>& dividendYield,
			const boost::shared_ptr<discretization>& disc);
	
	protected:
		
		

	
        // your implementation goes here
        
    };

}

#endif