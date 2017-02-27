

//#include <ql/stochasticprocess.hpp>
#include <ql\stochasticprocess.hpp>

#ifndef constant_blacksholes_process_hpp
#define constant_blacksholes_process_hpp
#include <ql/termstructures/volatility/equityfx/localvolsurface.hpp>
#include <ql/termstructures/volatility/equityfx/localvolcurve.hpp>
#include <ql/termstructures/volatility/equityfx/localconstantvol.hpp>
namespace QuantLib {
	class constantBlackScholesModel : public StochasticProcess1D {
	private:
		Handle<Quote> underlyingValue_;
		Handle<YieldTermStructure> riskFreeRate_;
		Handle<YieldTermStructure> 	dividendYield_;
		Handle<BlackVolTermStructure> blackVolatility_;
		Real driftC_;
		Real diffusionC_;
		Date exerciceDate_;
	public:

		constantBlackScholesModel(
			const Handle <Quote>  underlyingValue,
			const Date exerciceDate,
			const Handle<YieldTermStructure>& riskFree,
			const Handle<BlackVolTermStructure>& blackVol,
			const Handle<YieldTermStructure>& dividendYield,
			boost::shared_ptr<discretization>& disc );

		Real drift(Time t, Real x) const;

		Real diffusion(Time t, Real x) const;


		Real variance(const StochasticProcess1D&,
			Time t0, Real x0, Time dt) const;

		Real x0() const;
	};
	//! \name 1-D stochastic process interface
	//@{
	//! returns the initial value of the state variable


	// your implementation goes here



}

#endif
