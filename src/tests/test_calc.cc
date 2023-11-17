#include "../backend/model/modelCalc.h"
#include <gtest/gtest.h>

TEST(SmartCalc, calculate_test) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("(sin (cos tan x))", 0), "0.841471");
}

TEST(SmartCalc, calculate_test1) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("2 + 2", 0), "4.000000");
}

TEST(SmartCalc, calculate_test2) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("3 * 5", 0), "15.000000");
}

TEST(SmartCalc, calculate_test3) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("10 / 2", 0), "5.000000");
}

TEST(SmartCalc, calculate_test4) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("4 - 2", 0), "2.000000");
}

TEST(SmartCalc, calculate_test5) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("2 ^ 3", 0), "8.000000");
}

TEST(SmartCalc, calculate_test6) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("sqrt 25", 0), "5.000000");
}

TEST(SmartCalc, calculate_test7) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("log 100", 0), "2.000000");
}

TEST(SmartCalc, calculate_test8) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("sin 0", 0), "0.000000");
}

TEST(SmartCalc, calculate_test9) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("cos 0", 0), "1.000000");
}

TEST(SmartCalc, calculate_test10) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("tan 0", 0), "0.000000");
}

TEST(SmartCalc, calculate_test11) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("2 * (3 + 4)", 0), "14.000000");
}

TEST(SmartCalc, calculate_test12) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("8 / (2 + 2)", 0), "2.000000");
}

TEST(SmartCalc, calculate_test13) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("3 ^ (2 + 1)", 0), "27.000000");
}

TEST(SmartCalc, calculate_test14) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("sqrt (16 / 4)", 0), "2.000000");
}

TEST(SmartCalc, calculate_test15) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("log (10 ^ 2)", 0), "2.000000");
}

TEST(SmartCalc, calculate_test16) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("sin (3.141592653589793 / 2)", 0), "1.000000");
}

TEST(SmartCalc, calculate_test17) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("cos (3.141592653589793)", 0), "-1.000000");
}

TEST(SmartCalc, calculate_test18) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("tan (3.141592653589793 / 4)", 0), "1.000000");
}

TEST(SmartCalc, calculate_test19) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("2 ^ (3 ^ 2)", 0), "512.000000");
}

TEST(SmartCalc, calculate_test20) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("log (sqrt x)", 100), "1.000000");
}

TEST(Calc, toCalc0) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("-cos 5 --tan(4 mod 5)"), "0.874159");
}

TEST(Calc, toCalc1) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("-(-(-(-1)))"), "1.000000");
}

TEST(Calc, toCalc2) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("(-10)+5*(-3)"), "-25.000000");
}

TEST(Calc, toCalc3) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("cos x - tan log x/sin x", 0.33),
          "2.558486");
}

TEST(Calc, toCalc4) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("-cos(log(sqrt 25) + sin x)", 0.33),
          "-0.520796");
}

TEST(Calc, toCalc5) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("x/cos x", 0.33), "0.348822");
}

TEST(Calc, toCalc6) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("tan log x/cos x - tan log x/sin x", 0.33),
          "1.060142");
}

TEST(Calc, toCalc7) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate(
              "100000 * (0.07*(1 + 0.07)^12)/((1+0.07)^12 - 1)"),
          "12590.198866");
}

TEST(Calc, toCalc8) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("2 * tan(6) / (1 + tan(5)^2)"),
          "-0.046831");
}

TEST(Calc, toCalc9) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("0.07*(1 + 0.07)^12"), "0.157653");
}

TEST(Calc, toCalc10) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("64*-(62^2)--x", 0.33), "-246015.670000");
}

TEST(Calc, toCalc101) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("64*-62^2--x", 0.33), "246016.330000");
}

TEST(Calc, toCalc11) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("x mod1.33 ^ 4 + -5-(2^3)-sin1", 0.33),
          "-13.511471");
}

TEST(Calc, toCalc12) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("(sin (cos tan x))", 0.33), "0.808683");
}

TEST(Calc, toCalc13) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("-x mod-1.33", 0.33), "-0.330000");
}

TEST(Calc, toCalc14) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("log sqrt x", 100), "1.000000");
}

TEST(Calc, toCalc15) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("logsqrtx", 100), "1.000000");
}

TEST(Calc, toCalc16) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("sin1^2+cos1^2", 0), "1.000000");
}

TEST(Calc, toCalc17) {
s21::ModelCalc model;
EXPECT_EQ(model.Calculate("tan(90)", 0), "-1.995200");
}
