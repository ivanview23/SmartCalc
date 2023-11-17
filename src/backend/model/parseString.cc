#include "parseString.h"

#include <regex>

namespace s21 {

void ParseString::StringToList() {
  IsCorrectSize();
  IsSymbolCorrect(pars_str_);
  RegexParse();
};

void ParseString::IsCorrectSize() {
  if (pars_str_.size() > kMaxSize) {
    throw std::invalid_argument("IsCorrectSize: too many symbols");
  }
};

void ParseString::IsSymbolCorrect(std::string &pars_str) {
  std::replace(pars_str.begin(), pars_str.end(), ',', '.');
  std::regex poss_lex(R"([Emcq stildragonex\d.+\+\-\*\(\)\^\/]+)");
  if (!std::regex_match(pars_str, poss_lex)) {
    throw std::invalid_argument("IsStringCorrect: invalid symbol");
  }
};

void ParseString::RegexParse() {
  std::regex reg_free(
      R"(mod|cos|sin|tan|acos|asin|atan|sqrt|ln|log|x|\d+(?:\.\d+)?(?:[Ee][-+]?\d+)?|\+|\-|\*|\(|\)|\^|\/)");
  std::string::const_iterator it_begin = pars_str_.begin();
  std::string::const_iterator it_end = pars_str_.end();
  std::smatch sm;
  int count_bracket = 0;
  int size_str = pars_str_.size() - CountSpace(), count_size_lex = 0;

  while (std::regex_search(it_begin, it_end, sm, reg_free)) {
    count_size_lex += sm[0].str().size();
    CountBracket(sm[0].str(), count_bracket);
    TokenToList(StringToToken(sm[0].str()));
    it_begin = sm.suffix().first;
  }
  IsTokenCorrect(size_str, count_size_lex);
  CheckCountBracket(count_bracket);
  IsCorrectLastToken();
}

int ParseString::CountSpace() {
  int count = 0;
  for (auto it = pars_str_.begin(); it != pars_str_.end(); it++)
    if (*it == ' ') count++;
  return count;
};

void ParseString::IsTokenCorrect(int size_str, int count_size_lex) {
  if (size_str != count_size_lex) {
    throw std::invalid_argument("IsTokenCorrect: invalid size");
  }
};

Tokens ParseString::StringToToken(std::string match) {
  Tokens token;
  if (match[0] >= 48 && match[0] <= 57) {
    token.setType((*token.mapTokenType_.find("num")).second);
    token.setGroup((*token.mapTokenGroup_.find(token.getType())).second);
    token.setNum(std::stod(match));
    token.setPreority(OperatorPriority(token.getType()));
  } else {
    token.setType((*token.mapTokenType_.find(match)).second);
    token.setGroup((*token.mapTokenGroup_.find(token.getType())).second);
    token.setPreority(OperatorPriority(token.getType()));
  }
  UnarCreate(token);
  return token;
};

void ParseString::TokenToList(Tokens token) {
  if (!(list_tokens_.size() > 0)) {
    IsCorrectFirstToken(token.getGroup());
    list_tokens_.push_back(token);
  } else {
    auto it_prev = std::prev(list_tokens_.end(), 1);
    list_tokens_.push_back(token);

    bool matrix_match[5][5] = {{0, 1, 1, 1, 0},
                               {1, 0, 0, 0, 1},
                               {0, 1, 1, 1, 0},
                               {0, 1, 1, 1, 0},
                               {1, 0, 0, 0, 1}};

    if (!matrix_match[static_cast<int>(token.getGroup())]
                     [static_cast<int>((*it_prev).getGroup())]) {
      throw std::invalid_argument("TokenToList: invalid token");
    }
  }
};

int ParseString::OperatorPriority(TokenType t) {
  switch (t) {
    case TokenType::kAdd:
    case TokenType::kSub:
      return 1;
    case TokenType::kMul:
    case TokenType::kDiv:
    case TokenType::kMod:
      return 2;
    case TokenType::kCos:
    case TokenType::kSin:
    case TokenType::kTan:
    case TokenType::kAcos:
    case TokenType::kAsin:
    case TokenType::kAtan:
    case TokenType::kSqrt:
    case TokenType::kLn:
    case TokenType::kLog:
    case TokenType::kPow:
      return 3;
    case TokenType::kUnPlus:
    case TokenType::kUnMinus:
      return 4;
    default:
      return 0;
  }
};

void ParseString::UnarCreate(Tokens &token) {
  if (!(list_tokens_.size() > 0)) {
    UnarRemaster(token, (*token.mapTokenGroup_.find(TokenType::kAdd)).second);
  } else {
    auto it_prev = std::prev(list_tokens_.end(), 1);
    UnarRemaster(token, (*it_prev).getGroup());
  }
};

void ParseString::UnarRemaster(Tokens &token, TokenGroup prev_token) {
  if (token.getType() == TokenType::kAdd ||
      token.getType() == TokenType::kSub) {
    //          num  oper  fun  opbr clbr
    // add/sub   0    1    1    1    0
    bool matrix_unar_make[1][5] = {0, 1, 1, 1, 0};

    if (matrix_unar_make[0][static_cast<int>(prev_token)]) {
      if (token.getType() == TokenType::kAdd) {
        token.setType(TokenType::kUnPlus);
        token.setGroup(TokenGroup::kFunction);
      } else {
        token.setType(TokenType::kUnMinus);
        token.setGroup(TokenGroup::kFunction);
      }
    }
    token.setPreority(OperatorPriority(token.getType()));
  }
};

void ParseString::IsCorrectFirstToken(TokenGroup group) {
  if (group == TokenGroup::kOperator) {
    throw std::invalid_argument("IsCorrectFirstToken: invalid token");
  }
};

void ParseString::IsCorrectLastToken() {
  if (!(list_tokens_.back().getGroup() == TokenGroup::kNumber) &&
      !(list_tokens_.back().getGroup() == TokenGroup::kCloseBracket))
    throw std::invalid_argument("IsCorrectLastToken: invalid token");
};

void ParseString::CountBracket(std::string pars_str, int &count_bracket) {
  if (pars_str[0] == '(') {
    count_bracket++;
  } else if (pars_str[0] == ')') {
    count_bracket--;
  }

  if (count_bracket < 0) {
    throw std::invalid_argument("CountBracket: invalid token");
  }
};

void ParseString::CheckCountBracket(int count_bracket) {
  if (count_bracket != 0) {
    throw std::invalid_argument("CountBracket: invalid token");
  }
};

std::list<Tokens> ParseString::GetList() const { return list_tokens_; };

}  // namespace s21