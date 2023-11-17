#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCDATA_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCDATA_H_

#include <string>
#include <vector>

namespace s21 {
class CalcData {
 public:
  CalcData(double x_min, double x_max, double step)
      : ch(),
        grapfData(x_min, x_max, step),
        creditData(0, 0, 0, 0),
        debitData(0, 0, 0, 0, 0, ch){};
  CalcData(std::string cr_sum, std::string cr_proc, std::string cr_time,
           bool is_cr)
      : ch(),
        grapfData(0, 0, 0),
        creditData(cr_sum, cr_proc, cr_time, is_cr),
        debitData(0, 0, 0, 0, 0, ch){};
  CalcData(double sum_dep, double proc_dep, int time_dep, int period,
           bool is_cr, std::vector<std::string> change_dep)
      : ch(change_dep),
        grapfData(0, 0, 0),
        creditData(0, 0, 0, 0),
        debitData(sum_dep, proc_dep, time_dep, period, is_cr, ch){};
  ~CalcData(){};

  struct GrapfData {
    double x_min_;
    double x_max_;
    double step_;
    GrapfData(double x_min, double x_max, double step)
        : x_min_(x_min), x_max_(x_max), step_(step){};
  };

  struct CreditData {
    std::string cr_sum_;
    std::string cr_proc_;
    std::string cr_time_;
    bool is_cr_;
    CreditData(std::string cr_sum, std::string cr_proc, std::string cr_time,
               bool is_cr)
        : cr_sum_(cr_sum),
          cr_proc_(cr_proc),
          cr_time_(cr_time),
          is_cr_(is_cr) {}
  };

  struct DebitData {
    double sum_dep_;
    double proc_dep_;
    int time_dep_;
    int period_;
    bool is_cr_;
    std::vector<std::string> change_dep_;
    DebitData(double sum_dep, double proc_dep, int time_dep, int period,
              bool is_cr, std::vector<std::string> change_dep)
        : sum_dep_(sum_dep),
          proc_dep_(proc_dep),
          time_dep_(time_dep),
          period_(period),
          is_cr_(is_cr),
          change_dep_(change_dep) {}
  };

  std::vector<std::string> ch;
  GrapfData grapfData;
  CreditData creditData;
  DebitData debitData;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCDATA_H_