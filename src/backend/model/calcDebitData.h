#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCDEBITDATA_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCDEBITDATA_H_

#include <iostream>
#include <list>

#include "calcData.h"

namespace s21 {
class CalcDebitData {
 public:
  CalcDebitData(CalcData::DebitData data_value) {
    CalcNonCapitalization(data_value);
  };
  ~CalcDebitData(){};

  std::pair<std::pair<std::string, std::list<double>>,
            std::pair<std::list<double>, std::list<double>>>
  GetRes() const;

 private:
  void CalcNonCapitalization(CalcData::DebitData data);
  void ParsChangeDep(std::vector<std::string> change_dep);

  int time_change_dep_;
  double sum_change_dep_;
  std::list<double> proc_dep_;
  std::list<double> sum_dep_;
  std::list<double> add_dep_;
  std::vector<std::pair<int, double>> change_dep_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCDEBITDATA_H_