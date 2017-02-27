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
		boost::shared_ptr<discretization>& disc)
		:StochasticProcess1D(disc), underlyingValue_(underlyingValue),
		riskFreeRate_(riskFree), dividendYield_(dividendYield), blackVolatility_(blackVol) {
		exerciceDate_ = exerciceDate;
		driftC_ = riskFreeRate_->zeroRate(exerciceDate_, riskFreeRate_->dayCounter(), Continuous,
			NoFrequency, true) - dividendYield_->zeroRate(exerciceDate_, riskFreeRate_->dayCounter(), Continuous,
				NoFrequency, true);
		diffusionC_ = blackVolatility_->blackVol(exerciceDate_, underlyingValue->value());

	}



	Real constantBlackScholesModel::drift(Time t, Real x) const {
		return driftC_*x;
	}

	Real constantBlackScholesModel::diffusion(Time t, Real x) const {
		return diffusionC_*x;
	}

	Real constantBlackScholesModel::variance(const StochasticProcess1D&,
		Time t0, Real x0, Time dt) const {
		return discretization_->variance(*this, t0, x0, dt);
	}

	Real constantBlackScholesModel::x0()const {
		return underlyingValue_->value();
	}










}