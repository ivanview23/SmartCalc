#include "calcDebitData.h"

#include <sstream>
#include <string>

#include "calculatePostfix.h"

namespace s21 {

void CalcDebitData::CalcNonCapitalization(CalcData::DebitData data) {
  ParsChangeDep(data.change_dep_);
  proc_dep_.push_back(0);
  sum_dep_.push_back(data.sum_dep_);
  add_dep_.push_back(data.sum_dep_);

  for (int i = 1; i <= data.time_dep_; i++) {
    double popolnenia = 0;
    double proc_dep = (data.sum_dep_ * data.proc_dep_ * 30.4175 / 365) / 100;

    if (data.is_cr_) {
      data.sum_dep_ += proc_dep;
    }

    proc_dep_.push_back(proc_dep);
    sum_dep_.push_back(data.sum_dep_);

    if (!change_dep_.empty()) {
      for (auto it = change_dep_.begin(); it != change_dep_.end();) {
        if (it->first == i) {
          popolnenia += it->second;
          data.sum_dep_ += it->second;
          change_dep_.erase(it);
        } else
          it++;

        if (data.sum_dep_ < 0) {
          throw std::invalid_argument("Error: limit deposit is less than 0");
        }
      }
    }
    add_dep_.push_back(popolnenia);
  }
};

std::pair<std::pair<std::string, std::list<double>>,
          std::pair<std::list<double>, std::list<double>>>
CalcDebitData::GetRes() const {
  return std::make_pair(std::make_pair("all correct", add_dep_),
                        std::make_pair(sum_dep_, proc_dep_));
};

void CalcDebitData::ParsChangeDep(std::vector<std::string> change_dep) {
  int time_change = 0;
  double sum_change = 0;

  for (auto it = change_dep.begin(); it != change_dep.end(); it++) {
    bool is_change = false;

    std::stringstream ss(*it);
    std::string token;
    std::string delimiter = "|";

    for (int i = 0; i <= 3; i++) {
      std::getline(ss, token, '|');

      size_t start = token.find_first_not_of(' ');
      size_t end = token.find_last_not_of(' ');
      token = token.substr(start, end - start + 1);

      if (token[0] == '-') {
        is_change = true;
      }
      if (i == 1) {
        time_change = std::stoi(token);
      }
      if (i == 2) {
        sum_change = std::stod(token);
      }
    }

    if (is_change) {
      sum_change *= -1;
    }

    change_dep_.push_back(std::make_pair(time_change, sum_change));
  }
};

}  // namespace s21
