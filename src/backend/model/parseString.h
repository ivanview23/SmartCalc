#ifndef CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_PARSESTRING_H_
#define CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_PARSESTRING_H_

#include <list>

#include "tokens.h"

namespace s21 {
class ParseString {
 public:
  ParseString(std::string pars_str) : list_tokens_(), pars_str_(pars_str) {
    StringToList();
  };
  ~ParseString(){};

  std::list<Tokens> GetList() const;

 private:
  void StringToList();
  void IsCorrectSize();
  void IsSymbolCorrect(std::string &pars_str);
  void RegexParse();
  int CountSpace();
  void IsTokenCorrect(int size_str, int count_size_lex);
  Tokens StringToToken(std::string match);
  void TokenToList(Tokens token);
  int OperatorPriority(TokenType t);
  void UnarCreate(Tokens &token);
  void UnarRemaster(Tokens &token, TokenGroup prev_token);
  void IsCorrectFirstToken(TokenGroup group);
  void IsCorrectLastToken();
  void CountBracket(std::string pars_str, int &count_bracket);
  void CheckCountBracket(int count_bracket);

  std::list<Tokens> list_tokens_;
  std::string pars_str_;
  const unsigned int kMaxSize = 255;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BACKEND_MODEL_PARSESTRING_H_