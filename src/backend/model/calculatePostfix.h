#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCULATEPOSTFIX_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCULATEPOSTFIX_H_

#include <cmath>
#include <functional>
#include <string>

#include "postfixNotation.h"

namespace s21 {
class CalculatePostfix {
 public:
  CalculatePostfix(std::list<Tokens> token, double x)
      : x_num_(x), current_list_(token) {
    CalcilatePostfixNotation();
  };
  ~CalculatePostfix(){};

  std::pair<double, std::string> GetRes() const;

  const std::map<TokenType, std::function<void()>> operations_ = {
      {TokenType::kNum, [&]() { NumAdding(current_list_.front().getNum()); }},
      {TokenType::kX, [&]() { NumAdding(x_num_); }},
      {TokenType::kAdd, [&]() { Binar(); }},
      {TokenType::kSub, [&]() { Binar(); }},
      {TokenType::kMul, [&]() { Binar(); }},
      {TokenType::kDiv, [&]() { Binar(); }},
      {TokenType::kMod, [&]() { Binar(); }},
      {TokenType::kPow, [&]() { Binar(); }},
      {TokenType::kUnPlus, [&]() { Unar(); }},
      {TokenType::kUnMinus, [&]() { Unar(); }},
      {TokenType::kCos, [&]() { Unar(); }},
      {TokenType::kSin, [&]() { Unar(); }},
      {TokenType::kTan, [&]() { Unar(); }},
      {TokenType::kAcos, [&]() { Unar(); }},
      {TokenType::kAsin, [&]() { Unar(); }},
      {TokenType::kAtan, [&]() { Unar(); }},
      {TokenType::kSqrt, [&]() { Unar(); }},
      {TokenType::kLn, [&]() { Unar(); }},
      {TokenType::kLog, [&]() { Unar(); }},
  };

  const std::map<TokenType, std::function<void(double num)>> binar_oper_ = {
      {TokenType::kAdd, [&](double num) { st_num_.top() += num; }},
      {TokenType::kSub, [&](double num) { st_num_.top() -= num; }},
      {TokenType::kMul, [&](double num) { st_num_.top() *= num; }},
      {TokenType::kDiv, [&](double num) { st_num_.top() /= num; }},
      {TokenType::kMod,
       [&](double num) { st_num_.top() = std::fmod(st_num_.top(), num); }},
      {TokenType::kPow,
       [&](double num) { st_num_.top() = std::pow(st_num_.top(), num); }},
  };

  const std::map<TokenType, std::function<double()>> unar_oper_ = {
      {TokenType::kUnPlus, [&]() { return st_num_.top(); }},
      {TokenType::kUnMinus, [&]() { return -st_num_.top(); }},
      {TokenType::kCos, [&]() { return std::cos(st_num_.top()); }},
      {TokenType::kSin, [&]() { return std::sin(st_num_.top()); }},
      {TokenType::kTan, [&]() { return std::tan(st_num_.top()); }},
      {TokenType::kAcos, [&]() { return std::acos(st_num_.top()); }},
      {TokenType::kAsin, [&]() { return std::asin(st_num_.top()); }},
      {TokenType::kAtan, [&]() { return std::atan(st_num_.top()); }},
      {TokenType::kSqrt, [&]() { return std::sqrt(st_num_.top()); }},
      {TokenType::kLn, [&]() { return std::log(st_num_.top()); }},
      {TokenType::kLog, [&]() { return std::log10(st_num_.top()); }},
  };

 private:
  void CalcilatePostfixNotation();
  void Separation();
  void NumAdding(double num);
  void Binar();
  void Unar();

  std::string res_str_;
  double res_num_;
  double x_num_;
  std::list<Tokens> current_list_;
  std::stack<double> st_num_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_CALCULATEPOSTFIX_H_