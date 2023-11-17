#include "calculatePostfix.h"

namespace s21 {

void CalculatePostfix::CalcilatePostfixNotation() {
  while (!current_list_.empty()) {
    Separation();
  }
  res_num_ = st_num_.top();
  res_str_ = std::to_string(st_num_.top());
};

void CalculatePostfix::Separation() {
  auto it = operations_.find(current_list_.front().getType());
  if (it != operations_.end()) {
    it->second();
  }
};

void CalculatePostfix::NumAdding(double num) {
  st_num_.push(num);
  current_list_.pop_front();
}

void CalculatePostfix::Binar() {
  auto it = binar_oper_.find(current_list_.front().getType());
  double num = st_num_.top();
  st_num_.pop();
  it->second(num);
  current_list_.pop_front();
};

void CalculatePostfix::Unar() {
  auto it = unar_oper_.find(current_list_.front().getType());
  st_num_.top() = it->second();
  current_list_.pop_front();
};

std::pair<double, std::string> CalculatePostfix::GetRes() const {
  return std::make_pair(res_num_, res_str_);
};

}  // namespace s21
