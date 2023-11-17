#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_POSTFIXNOTATION_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_POSTFIXNOTATION_H_

#include <stack>

#include "parseString.h"

namespace s21 {
class PostfixNotation {
 public:
  PostfixNotation(ParseString *n)
      : notation_(n), stack_operator_(), postfix_notation_() {
    CreatePostfixNotation();
  };
  ~PostfixNotation(){};

  std::list<Tokens> GetList() const;

 private:
  void CreatePostfixNotation();
  void ParseGroup(Tokens token);
  void WaitingStack(Tokens token);
  void BrackExtrusion();
  void EmptyExtrusion();
  void Extrusion();

  ParseString *notation_;
  std::stack<Tokens> stack_operator_;
  std::list<Tokens> postfix_notation_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_POSTFIXNOTATION_H_