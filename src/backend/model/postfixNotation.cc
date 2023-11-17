#include "postfixNotation.h"

namespace s21 {

void PostfixNotation::CreatePostfixNotation() {
  for (auto token : notation_->GetList()) {
    ParseGroup(token);
  }
  EmptyExtrusion();
};

void PostfixNotation::ParseGroup(Tokens token) {
  if (token.getGroup() == TokenGroup::kNumber)
    postfix_notation_.push_back(token);
  else if (token.getGroup() == TokenGroup::kOperator)
    WaitingStack(token);
  else if (token.getGroup() == TokenGroup::kFunction ||
           token.getGroup() == TokenGroup::kOpenBracket)
    stack_operator_.push(token);
  else if (token.getGroup() == TokenGroup::kCloseBracket)
    BrackExtrusion();
};

void PostfixNotation::WaitingStack(Tokens token) {
  if (stack_operator_.empty())
    stack_operator_.push(token);
  else {
    while (!stack_operator_.empty() &&
           token.getPreority() <= stack_operator_.top().getPreority()) {
      Extrusion();
    }
    stack_operator_.push(token);
  };
};

void PostfixNotation::BrackExtrusion() {
  while (stack_operator_.top().getGroup() != TokenGroup::kOpenBracket) {
    Extrusion();
  }
  stack_operator_.pop();
};

void PostfixNotation::EmptyExtrusion() {
  while (!stack_operator_.empty()) {
    Extrusion();
  }
};

void PostfixNotation::Extrusion() {
  postfix_notation_.push_back(stack_operator_.top());
  stack_operator_.pop();
};

std::list<Tokens> PostfixNotation::GetList() const {
  return postfix_notation_;
};

}  // namespace s21