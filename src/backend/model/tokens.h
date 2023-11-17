#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_TOKENS_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_TOKENS_H_

#include <iostream>
#include <map>

namespace s21 {

enum class TokenType {
  kNull,
  kNum,
  kX,
  kAdd,
  kSub,
  kMul,
  kDiv,
  kPow,
  kMod,
  kUnPlus,
  kUnMinus,
  kCos,
  kSin,
  kTan,
  kAcos,
  kAsin,
  kAtan,
  kSqrt,
  kLn,
  kLog,
  KOpenBrack,
  kCloseBrack
};

enum class TokenGroup {
  kNumber,
  kOperator,
  kFunction,
  kOpenBracket,
  kCloseBracket,
  kNull
};

class Tokens {
 public:
  Tokens()
      : type_(TokenType::kNull),
        group_(TokenGroup::kNull),
        num_(0),
        preority_(0){};
  ~Tokens(){};

  void setType(TokenType t) { type_ = t; };
  void setGroup(TokenGroup g) { group_ = g; };
  void setNum(double n) { num_ = n; };
  void setPreority(int p) { preority_ = p; };

  TokenType getType() const { return type_; };
  TokenGroup getGroup() const { return group_; };
  double getNum() const { return num_; }
  int getPreority() const { return preority_; };

  const std::map<std::string, TokenType> mapTokenType_ = {
      {"num", TokenType::kNum},      {"x", TokenType::kX},
      {"+", TokenType::kAdd},        {"-", TokenType::kSub},
      {"cos", TokenType::kCos},      {"sin", TokenType::kSin},
      {"tan", TokenType::kTan},      {"acos", TokenType::kAcos},
      {"asin", TokenType::kAsin},    {"atan", TokenType::kAtan},
      {"sqrt", TokenType::kSqrt},    {"ln", TokenType::kLn},
      {"log", TokenType::kLog},      {"*", TokenType::kMul},
      {"/", TokenType::kDiv},        {"^", TokenType::kPow},
      {"mod", TokenType::kMod},      {"(", TokenType::KOpenBrack},
      {")", TokenType::kCloseBrack}, {"u-", TokenType::kUnMinus},
      {"u+", TokenType::kUnPlus}};

  const std::map<TokenType, TokenGroup> mapTokenGroup_ = {
      {TokenType::kNum, TokenGroup::kNumber},
      {TokenType::kX, TokenGroup::kNumber},
      {TokenType::kAdd, TokenGroup::kOperator},
      {TokenType::kSub, TokenGroup::kOperator},
      {TokenType::kMul, TokenGroup::kOperator},
      {TokenType::kDiv, TokenGroup::kOperator},
      {TokenType::kPow, TokenGroup::kOperator},
      {TokenType::kMod, TokenGroup::kOperator},
      {TokenType::kUnPlus, TokenGroup::kFunction},
      {TokenType::kUnMinus, TokenGroup::kFunction},
      {TokenType::kCos, TokenGroup::kFunction},
      {TokenType::kSin, TokenGroup::kFunction},
      {TokenType::kTan, TokenGroup::kFunction},
      {TokenType::kAcos, TokenGroup::kFunction},
      {TokenType::kAsin, TokenGroup::kFunction},
      {TokenType::kAtan, TokenGroup::kFunction},
      {TokenType::kSqrt, TokenGroup::kFunction},
      {TokenType::kLn, TokenGroup::kFunction},
      {TokenType::kLog, TokenGroup::kFunction},
      {TokenType::KOpenBrack, TokenGroup::kOpenBracket},
      {TokenType::kCloseBrack, TokenGroup::kCloseBracket}};

 private:
  TokenType type_;
  TokenGroup group_;
  double num_;
  int preority_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_TOKENS_H_