#include "calcCreditData.h"

#include "calculatePostfix.h"

namespace s21 {

void CalcCreditData::CalcAnnuity(CalcData::CreditData data) {
  std::string str(data.cr_sum_ + "*((" + data.cr_proc_ + "/1200)*(1+(" +
                  data.cr_proc_ + "/1200))^" + data.cr_time_ + "/((1+(" +
                  data.cr_proc_ + "/1200))^" + data.cr_time_ + "-1))");
  str_ = Calcus(str).second;
  data.cr_proc_ =
      Calcus(data.cr_proc_ + "-(" + data.cr_proc_ + "*0.16666665)").second;
  std::string proc_plat;
  std::string cred_plat;
  for (auto i = 0; i < std::stod(data.cr_time_); i++) {
    proc_plat = Calcus(data.cr_sum_ + "*(" + data.cr_proc_ + "/1000)").second;
    cred_plat = Calcus(str_ + "-" + proc_plat).second;
    PushListData(data, proc_plat);
    data.cr_sum_ = Calcus(data.cr_sum_ + "-" + cred_plat).second;
  }
};

void CalcCreditData::CalcDifferen(CalcData::CreditData data) {
  std::string proc_plat;
  std::string cred_plat;
  std::string mount_plat;
  std::string ost_plat(data.cr_sum_);
  for (auto i = 0; i < std::stod(data.cr_time_); i++) {
    proc_plat = Calcus(data.cr_sum_ + "/" + data.cr_time_).second;
    cred_plat_.push_back(Calcus(data.cr_sum_ + "/" + data.cr_time_).first);
    cred_plat = Calcus("(" + data.cr_sum_ + "-" + proc_plat + "*" +
                       std::to_string(i) + ")*(" + data.cr_proc_ + "/1200)")
                    .second;
    proc_plat_.push_back(Calcus("(" + data.cr_sum_ + "-" + proc_plat + "*" +
                                std::to_string(i) + ")*(" + data.cr_proc_ +
                                "/1200)")
                             .first);
    mount_plat_.push_back(Calcus(proc_plat + "+" + cred_plat).first);
    ost_plat = Calcus(ost_plat + "-" + proc_plat).second;
    ost_plat_.push_back(Calcus(ost_plat).first);
  }
};

void CalcCreditData::PushListData(CalcData::CreditData data,
                                  std::string proc_plat) {
  proc_plat_.push_back(
      Calcus(data.cr_sum_ + "*(" + data.cr_proc_ + "/1000)").first);
  cred_plat_.push_back(Calcus(str_ + "-" + proc_plat).first);
  if (Calcus(data.cr_sum_ + "-" + str_).first < 0)
    ost_plat_.push_back(0);
  else
    ost_plat_.push_back(Calcus(data.cr_sum_ + "-" + str_).first);
  mount_plat_.push_back(std::stod(str_));
};

std::pair<double, std::string> CalcCreditData::Calcus(std::string exp) {
  ParseString parse(exp);
  PostfixNotation notation(&parse);
  CalculatePostfix calculate(notation.GetList(), 0);
  return calculate.GetRes();
};

std::pair<std::string,
          std::pair<std::pair<std::list<double>, std::list<double>>,
                    std::pair<std::list<double>, std::list<double>>>>
CalcCreditData::GetRes() const {
  return std::make_pair(str_,
                        std::make_pair(std::make_pair(mount_plat_, cred_plat_),
                                       std::make_pair(proc_plat_, ost_plat_)));
};

}  // namespace s21