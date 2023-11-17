#include "calcGrapfData.h"

#include "calculatePostfix.h"

namespace s21 {

void CalcGrapfData::CalcVector(std::string exprassion,
                               CalcData::GrapfData data) {
  ParseString parse(exprassion);
  PostfixNotation notation(&parse);
  for (double i = data.x_min_; i <= data.x_max_; i += data.step_) {
    CalculatePostfix calculate(notation.GetList(), i);
    y_value_.push_back(calculate.GetRes().first);
    x_value_.push_back(i);
  }
};

std::pair<std::vector<double>, std::vector<double>> CalcGrapfData::GetRes()
    const {
  return std::make_pair(x_value_, y_value_);
};

}  // namespace s21