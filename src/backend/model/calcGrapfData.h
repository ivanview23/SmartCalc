#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCGRAPFDATA_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCGRAPFDATA_H_

#include <iostream>
#include <vector>

#include "calcData.h"

namespace s21 {
class CalcGrapfData {
 public:
  CalcGrapfData(std::string exprassion, CalcData::GrapfData data_value)
      : x_value_(), y_value_() {
    CalcVector(exprassion, data_value);
  };
  ~CalcGrapfData(){};

  std::pair<std::vector<double>, std::vector<double>> GetRes() const;

 private:
  void CalcVector(std::string exprassion, CalcData::GrapfData data);

  std::vector<double> x_value_;
  std::vector<double> y_value_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCGRAPFDATA_H_
