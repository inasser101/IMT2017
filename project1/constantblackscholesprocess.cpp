#include <ql/stochasticprocess.hpp>
#include "constantblackscholesprocess.hpp"
#include <ql/termstructures/volatility/equityfx/localvolsurface.hpp>
#include <ql/termstructures/volatility/equityfx/localvolcurve.hpp>
#include <ql/termstructures/volatility/equityfx/localconstantvol.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
using namespace std;

namespace QuantLib {
	/*! This class describes the stochastic process \f$ S \f$ governed by
	\f[
	d\ln S(t) = (r(t) - q(t) ) dt	+ \sigma dW_t.
	\f]
	*/
	
		constantBlackScholesModel::constantBlackScholesModel(
			const Handle<Quote> underlyingValue,
			const Date exerciceDate,
			const Handle<YieldTermStructure>& riskFree,
			const Handle<BlackVolTermStructure>& blackVol,
			const Handle<YieldTermStructure>& dividendYield,
			const boost::shared_ptr<discretization>& disc)
			:StochasticProcess1D(disc), underlyingValue_(underlyingValue), 
			riskFreeRate_(riskFree), dividendYield_(dividendYield), blackVolatility_(blackVol) {
				exerciceDate_ = exerciceDate;
				driftC_ = riskFreeRate_->zeroRate(exerciceDate_, riskFreeRate_->dayCounter(),Continuous,
					NoFrequency, true)- dividendYield_->zeroRate(exerciceDate_,riskFreeRate_->dayCounter(), Continuous,
						NoFrequency, true);
				diffusionC_ = blackVolatility_->blackVol(exerciceDate_, underlyingValue->value());

		}

	

		// this will be removed
		
		Real constantBlackScholesModel::drift(Time t, Real x) const {
			return driftC_*x;
		}

		Real constantBlackScholesModel::diffusion(Time t,Real x) const {
			return diffusionC_*x;
		}
		

		//// this code will be added in Stochasticprocess.hpp
		/*
		inline Real StochasticProcess1D::drift(Time t, Real x) const {;
        return this.driftC_*x;
    }

    inline Real StochasticProcess1D::diffusion(Time t, Real x) const {
        return this.diffusionC_*x;
    }

		*/
		
	

	

	
	


}