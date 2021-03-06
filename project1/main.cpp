#include "constantblackscholesprocess.hpp"
#include "mceuropeanengine.hpp"
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/quantlib.hpp>
#include <time.h>
using namespace QuantLib;
int main() {

	try {
		//Specify (1) STrike,(2) current stock price,(3)date count convention,(4) current date
		//		  (5) Maturity Dtae, (6) interest Rate, (7) dividend Yield, (8) Calendar for specific market
		//		  (9) Volatility, (10) Option Type
		Real strike = 100;
		Real underlying = 90;
		DayCounter dayCounter = Actual365Fixed();
		Date settlementDate(28, February, 2017);
		Date excerciceDate(28, February, 2018);
		Rate riskFreeRate = 0.05;
		Spread dividendYield = 0.00;
		Calendar calendar = TARGET();
		Volatility volatility = 0.20;
		Option::Type type(Option::Call);
	/*	std::cout << "Underlying Value = " << underlying << std::endl;
		std::cout << "Strike  =  " << strike << std::endl;
		std::cout << "Risk-free Rate = " << io::rate(riskFreeRate) << std::endl;
		std::cout << "Dividend yield = " << io::rate(dividendYield) << std::endl;
		std::cout << "Volatility = " << io::volatility(volatility) << std::endl;*/

		//handle for Object 
		// const Handle<Quote>& 

		Handle<Quote> underlyingV(
			boost::shared_ptr<Quote>(
				new SimpleQuote(underlying)
				));

		// Construct the Rate TS object, the pointer and the handle 

		Handle<YieldTermStructure> termStructure(
			boost::shared_ptr<YieldTermStructure>(
				new FlatForward(settlementDate, riskFreeRate, dayCounter)
				));

		// Construct the dividend TS Object ...,

		Handle<YieldTermStructure> dividend
			(boost::shared_ptr<YieldTermStructure>(
				new FlatForward(settlementDate, dividendYield, dayCounter)
				));


		// Construct the volatility TS object ...,
		Handle<BlackVolTermStructure> flatVolTS(
			boost::shared_ptr<BlackVolTermStructure>(
				new BlackConstantVol(settlementDate, calendar, volatility, dayCounter)
				));

		// add the constant stochastique process 
		//
		/*boost::shared_ptr<constantBlackScholesModel>
		ConstantProcess = boost::shared_ptr<constantBlackScholesModel>
		(new constantBlackScholesModel(
		underlyingV,excerciceDate, termStructure, flatVolTS, dividend));*/
		
		// add normal process
		boost::shared_ptr<GeneralizedBlackScholesProcess>
			nProcess = boost::shared_ptr<GeneralizedBlackScholesProcess>
			(new GeneralizedBlackScholesProcess(
				underlyingV, termStructure, dividend, flatVolTS));

		// Construct the Option excercice object ...,
		boost::shared_ptr<Exercise> exercise(
			new EuropeanExercise(excerciceDate));

		//Construct the Option payoff 

		boost::shared_ptr<StrikedTypePayoff> payoff(
			new PlainVanillaPayoff(type, strike));


		//Construct the Option,

		VanillaOption europeanOption(payoff, exercise);
		VanillaOption europeanOption_2(payoff, exercise);
		//Pricing ENgine

		europeanOption.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new AnalyticEuropeanEngine(nProcess)
				));
		europeanOption_2.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new AnalyticEuropeanEngine(nProcess)
				));
		std::cout << "--------------------------------------------------------------------" << std::endl;
		Real OptionPrice = europeanOption.NPV();
		std::cout << "OptionPrice = europeanOption.NPV()=" << OptionPrice << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "MCEuropeanEngine with GeneralizedBlackScholesProcess" <<std::endl ;

			
		europeanOption.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new MCEuropeanEngine<PseudoRandom>(
					nProcess, 10,
					Null<Size>(),
					true,
					false,
					10000,
					Null<Real>(),
					Null<Size>(), SeedGenerator::instance().get()
					))
			);
		clock_t tStart = clock();
		std::cout<<"Option Price " << europeanOption.NPV() << std::endl;
		printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
		std::cout <<"Error Estimation "<< europeanOption.errorEstimate() << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "--------------------------------------------------------------------" << std::endl;
		std::cout << "MCEuropeanEngine with constantBlackScholesModel" << std::endl;
		europeanOption_2.setPricingEngine(
			boost::shared_ptr<PricingEngine>(
				new MCEuropeanEngine_2<PseudoRandom>(
					nProcess, 10,
					Null<Size>(),
					true,
					false,
					10000,
					Null<Real>(),
					Null<Size>(), SeedGenerator::instance().get()
					))
			);
		clock_t tStart2 = clock();
		std::cout << "Option Price " << europeanOption_2.NPV() << std::endl;
		printf("Time taken: %.2fs\n", (double)(clock() - tStart2) / CLOCKS_PER_SEC);
		std::cout << "Error Estimation " << europeanOption_2.errorEstimate() << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
		system("pause");
		return 0;

	}
	catch (std::exception& e) {

		std::cerr << e.what() << std::endl;
		system("pause");
		return 1;
	}
	catch (...) {
		std::cerr << "unknown error" << std::endl;
		system("pause");
		return 1;
	}
}

