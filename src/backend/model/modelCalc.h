#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_MODELCALC_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_MODELCALC_H_

#include <iostream>

#include "calcCreditData.h"
#include "calcDebitData.h"
#include "calcGrapfData.h"
#include "calculatePostfix.h"

namespace s21 {
class ModelCalc {
 public:
  ModelCalc(){};

  std::string Calculate(std::string exprassion, double x = 0) {
    try {
      ParseString parse(exprassion);
      PostfixNotation notation(&parse);
      CalculatePostfix calculate(notation.GetList(), x);
      return calculate.GetRes().second;
    } catch (std::invalid_argument &e) {
      return e.what();
    }
  };

  std::pair<std::string, std::pair<std::vector<double>, std::vector<double>>>
  СalculateGraphData(std::string exprassion, CalcData::GrapfData data) {
    std::pair<std::vector<double>, std::vector<double>> buff;
    try {
      CalcGrapfData calcGrapf(exprassion, data);
      buff = calcGrapf.GetRes();
      return std::make_pair("all correct", buff);
    } catch (std::invalid_argument &e) {
      return std::make_pair(e.what(), buff);
    }
  };

  std::pair<std::string,
            std::pair<std::pair<std::list<double>, std::list<double>>,
                      std::pair<std::list<double>, std::list<double>>>>
  CalculateCreditData(CalcData::CreditData data) {
    std::pair<std::pair<std::list<double>, std::list<double>>,
              std::pair<std::list<double>, std::list<double>>>
        buff;
    try {
      CalcCreditData calcCredit(data);
      buff = calcCredit.GetRes().second;
      return std::make_pair("all correct", buff);
    } catch (std::invalid_argument &e) {
      return std::make_pair(e.what(), buff);
    }
  };

  std::pair<std::pair<std::string, std::list<double>>,
            std::pair<std::list<double>, std::list<double>>>
  CalculateDebitData(CalcData::DebitData data) {
    std::pair<std::list<double>, std::list<double>> buff;
    std::list<double> buff_2;
    try {
      CalcDebitData calcDebit(data);
      buff = calcDebit.GetRes().second;
      buff_2 = calcDebit.GetRes().first.second;
      return std::make_pair(std::make_pair("q", buff_2), buff);
    } catch (std::invalid_argument &e) {
      return std::make_pair(std::make_pair(e.what(), buff_2), buff);
    }
  };
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_MODELCALC_H_
