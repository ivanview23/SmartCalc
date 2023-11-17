#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCCREDITDATA_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCCREDITDATA_H_

#include <iostream>
#include <list>

#include "calcData.h"

namespace s21 {
class CalcCreditData {
 public:
  CalcCreditData(CalcData::CreditData data_value) {
    if (data_value.is_cr_)
      CalcAnnuity(data_value);
    else
      CalcDifferen(data_value);
  };
  ~CalcCreditData(){};

  std::pair<std::string,
            std::pair<std::pair<std::list<double>, std::list<double>>,
                      std::pair<std::list<double>, std::list<double>>>>
  GetRes() const;

 private:
  void CalcAnnuity(CalcData::CreditData data_value);
  void CalcDifferen(CalcData::CreditData data);
  void PushListData(CalcData::CreditData data, std::string proc_plat);
  std::pair<double, std::string> Calcus(std::string exp);

  std::string str_;
  std::list<double> ost_plat_;
  std::list<double> proc_plat_;
  std::list<double> cred_plat_;
  std::list<double> mount_plat_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCCREDITDATA_H_
