#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_CONTROLLERCALC_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_CONTROLLERCALC_H_

#include "model/modelCalc.h"

namespace s21 {
class ControllerCalc {
 public:
  ControllerCalc(){};

  std::string Calculate(std::string exprassion, double x) {
    return model_calc_.Calculate(exprassion, x);
  };

  std::pair<std::string, std::pair<std::vector<double>, std::vector<double>>>
  CalculateGraphData(std::string exprassion, CalcData::GrapfData data) {
    return model_calc_.СalculateGraphData(exprassion, data);
  };

  std::pair<std::string,
            std::pair<std::pair<std::list<double>, std::list<double>>,
                      std::pair<std::list<double>, std::list<double>>>>
  CalculateCreditData(CalcData::CreditData data) {
    return model_calc_.CalculateCreditData(data);
  };

  std::pair<std::pair<std::string, std::list<double>>,
            std::pair<std::list<double>, std::list<double>>>
  CalculateDebitData(CalcData::DebitData data) {
    return model_calc_.CalculateDebitData(data);
  };

 private:
  ModelCalc model_calc_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_CONTROLLERCALC_H_