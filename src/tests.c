#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

START_TEST(operators_1) {
  char mantissa_1[] = "00000000000000000000999999999";
  char mantissa_2[] = "00000000000000000000999999999";
  int exponent_1 = 4;
  int exponent_2 = 4;
  int sign_1 = 1;
  int sign_2 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_is_less(test_1, test_2);
  int r_2 = s21_is_less_or_equal(test_1, test_2);
  int r_3 = s21_is_greater(test_1, test_2);
  int r_4 = s21_is_greater_or_equal(test_1, test_2);
  int r_5 = s21_is_equal(test_1, test_2);
  int r_6 = s21_is_not_equal(test_1, test_2);

  int all_1 = (r_1 == 0) && (r_2 == 1) && (r_3 == 0) && (r_4 == 1) &&
              (r_5 == 1) && (r_6 == 0);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_1) {
  char mantissa_1[] = "00000000000000000000000000000";
  char mantissa_2[] = "00000000000000000000000000000";
  char mantissa_3[] = "00000000000000000000000000000";
  int exponent_1 = 28;
  int exponent_2 = 5;
  int exponent_3 = 1;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_2) {
  char mantissa_1[] = "00052345234523452349765847513";
  char mantissa_2[] = "00000000000000000009999999999";
  char mantissa_3[] = "10000000522452345234523497658";
  int exponent_1 = 28;
  int exponent_2 = 5;
  int exponent_3 = 23;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_3) {
  char mantissa_1[] = "00052345234523452349765847513";
  char mantissa_2[] = "00000000000000000009999999999";
  char mantissa_3[] = "52345234523452349765947513000";
  int exponent_1 = 0;
  int exponent_2 = 5;
  int exponent_3 = 3;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_4) {
  char mantissa_1[] = "00052345234523452349765847513";
  char mantissa_2[] = "00000000000000000009999999999";
  char mantissa_3[] = "52345234523452349765747513000";
  int exponent_1 = 0;
  int exponent_2 = 5;
  int exponent_3 = 3;
  int sign_1 = 0;
  int sign_2 = 1;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_5) {
  char mantissa_1[] = "00052345234523452349765847513";
  char mantissa_2[] = "00000000000000000000000000000";
  char mantissa_3[] = "00052345234523452349765847513";
  int exponent_1 = 0;
  int exponent_2 = 5;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_6) {
  char mantissa_1[] = "00052345234523452349765847513";
  char mantissa_2[] = "00000000000000000099999999999";
  char mantissa_3[] = "09999999947554765476547650234";
  int exponent_1 = 28;
  int exponent_2 = 5;
  int exponent_3 = 22;
  int sign_1 = 1;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_7) {
  char mantissa_1[] = "52345234523452349765847513000";
  char mantissa_2[] = "30000000000000000099999999999";
  char mantissa_3[] = "10000000052245234523452349766";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 22;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 1);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_8) {
  char mantissa_1[] = "52345234523452349765847513000";
  char mantissa_2[] = "30000000000000000099999999999";
  char mantissa_3[] = "10000000052245234523452349766";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 22;
  int sign_1 = 1;
  int sign_2 = 1;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_9) {
  char mantissa_1[] = "55555555555555555555555555555";
  char mantissa_2[] = "30000000000000000000000000000";
  char mantissa_3[] = "08555555555555555555555555556";
  int exponent_1 = 28;
  int exponent_2 = 28;
  int exponent_3 = 27;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_10) {
  char mantissa_1[] = "55555555555555555555555555555";
  char mantissa_2[] = "70000000000000000000000000000";
  char mantissa_3[] = "08555555555555555555555555556";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 1);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(sub_1) {
  char mantissa_1[] = "00000000000000000006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "00023413241234123405766219860";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(sub_2) {
  char mantissa_1[] = "00000000000000000006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "65781347829976586758765876588";
  int exponent_1 = 0;
  int exponent_2 = 28;
  int exponent_3 = 19;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(sub_3) {
  char mantissa_1[] = "41234123434322657813478345134";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "41210710193088534401133990491";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(sub_4) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "41234123434322657813478345134";
  char mantissa_3[] = "41210710193088534401133990491";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(sub_5) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "41234123434322657813478345134";
  char mantissa_3[] = "41210710193088534401133990491";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 1;
  int sign_2 = 1;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(sub_6) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "41234123434322657813478345134";
  char mantissa_3[] = "41257536675556781225822699777";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 1;
  int sign_2 = 0;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(sub_7) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "00000000000000000000000000001";
  char mantissa_3[] = "00023413241234123412344254643";
  int exponent_1 = 5;
  int exponent_2 = 0;
  int exponent_3 = 5;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(sub_8) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "00000000000000000000999999999";
  char mantissa_3[] = "00023413241234023412344454643";
  int exponent_1 = 5;
  int exponent_2 = 0;
  int exponent_3 = 5;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_1) {
  char mantissa_1[] = "00000000000000000006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "15401545654495706525705085081";
  int exponent_1 = 0;
  int exponent_2 = 28;
  int exponent_3 = 21;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_2) {
  char mantissa_1[] = "00000053163426435536578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "12447281279677916771908993163";
  int exponent_1 = 15;
  int exponent_2 = 10;
  int exponent_3 = 5;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_3) {
  char mantissa_1[] = "00000053163426435536578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "12447281279677916771908993163";
  int exponent_1 = 15;
  int exponent_2 = 10;
  int exponent_3 = 5;
  int sign_1 = 1;
  int sign_2 = 0;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_4) {
  char mantissa_1[] = "00000053163426435536578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "12447281279677916771908993163";
  int exponent_1 = 15;
  int exponent_2 = 10;
  int exponent_3 = 5;
  int sign_1 = 0;
  int sign_2 = 1;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_5) {
  char mantissa_1[] = "00000053163426435536578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "12447281279677916771908993163";
  int exponent_1 = 15;
  int exponent_2 = 10;
  int exponent_3 = 5;
  int sign_1 = 1;
  int sign_2 = 1;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_6) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "00000053163426435536578134783";
  char mantissa_3[] = "12447281279677916771908993163";
  int exponent_1 = 15;
  int exponent_2 = 10;
  int exponent_3 = 5;
  int sign_1 = 1;
  int sign_2 = 1;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_7) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "00000053163426435536578134783";
  char mantissa_3[] = "12447281279677916771908993163";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 5;
  int sign_1 = 1;
  int sign_2 = 1;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 1);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_8) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "00000053163426435536578134783";
  char mantissa_3[] = "12447281279677916771908993163";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 5;
  int sign_1 = 1;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mul_9) {
  char mantissa_1[] = "09999999999999999999999999999";
  char mantissa_2[] = "00000000000000000000000000010";
  char mantissa_3[] = "09999999999999999999999999999";
  int exponent_1 = 28;
  int exponent_2 = 0;
  int exponent_3 = 27;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(div_1) {
  char mantissa_1[] = "00000000000000000006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "28095788691626164827438934124";
  int exponent_1 = 0;
  int exponent_2 = 28;
  int exponent_3 = 16;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_2) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "00421835795191209536611678248";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_3) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "00000004218357951912095366117";
  int exponent_1 = 5;
  int exponent_2 = 0;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_4) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "04218357951912095366116782475";
  int exponent_1 = 5;
  int exponent_2 = 6;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_5) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "04218357951912095366116782475";
  int exponent_1 = 5;
  int exponent_2 = 6;
  int exponent_3 = 28;
  int sign_1 = 1;
  int sign_2 = 0;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_6) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "04218357951912095366116782475";
  int exponent_1 = 5;
  int exponent_2 = 6;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 1;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_7) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00000000000004123412344354643";
  char mantissa_3[] = "04218357951912095366116782475";
  int exponent_1 = 0;
  int exponent_2 = 28;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 1;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_8) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00000000000004123412344354643";
  char mantissa_3[] = "04218357951912095366116782475";
  int exponent_1 = 0;
  int exponent_2 = 28;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 1);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_9) {
  char mantissa_1[] = "00000987654323400006578134783";
  char mantissa_2[] = "00000000000000000000000000000";
  char mantissa_3[] = "04218357951912095366116782475";
  int exponent_1 = 0;
  int exponent_2 = 28;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 3);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(div_10) {
  char mantissa_1[] = "09876543234000065781347830000";
  char mantissa_2[] = "01000000000000000000000000000";
  char mantissa_3[] = "09876543234000065781347830000";
  int exponent_1 = 28;
  int exponent_2 = 28;
  int exponent_3 = 27;
  int sign_1 = 0;
  int sign_2 = 1;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_div(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mod_1) {
  char mantissa_1[] = "00000000000000000004523452345";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "00000000000000000004523452345";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mod(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mod_2) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "00000000000000000004523452345";
  char mantissa_3[] = "00000000000000000000430734324";
  int exponent_1 = 0;
  int exponent_2 = 1;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mod(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mod_3) {
  char mantissa_1[] = "00023413241234123412344354643";
  char mantissa_2[] = "00000000000000000004523452345";
  char mantissa_3[] = "00000000000000000000000000000";
  int exponent_1 = 0;
  int exponent_2 = 28;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mod(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(mod_4) {
  char mantissa_1[] = "00000000000000123412344354643";
  char mantissa_2[] = "00000000000000000004523452345";
  char mantissa_3[] = "00000000000000000003510617115";
  int exponent_1 = 0;
  int exponent_2 = 1;
  int exponent_3 = 1;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mod(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(from_int_1) {
  char mantissa_3[] = "00000000000000000000412412341";
  int exponent_3 = 0;
  int sign_3 = 0;
  s21_decimal result_1;
  s21_decimal result_2;
  int src = 412412341;
  int r_1 = s21_from_int_to_decimal(src, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(from_float_1) {
  char mantissa_3[] = "00000000000000000000000412341";
  int exponent_3 = 0;
  int sign_3 = 0;
  s21_decimal result_1;
  s21_decimal result_2;
  float src = 412341;
  int r_1 = s21_from_float_to_decimal(src, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}

END_TEST
START_TEST(to_int_1) {
  char mantissa_3[] = "00000000000000000000412412341";
  int exponent_3 = 0;
  int sign_3 = 0;
  s21_decimal result_1;
  s21_decimal result_2;
  int src = 412412341;
  set_val(&result_1, mantissa_3, exponent_3, sign_3);
  int r_1 = s21_from_decimal_to_int(result_1, &src);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(to_int_2) {
  char mantissa_3[] = "00000000999999999999412412341";
  int exponent_3 = 0;
  int sign_3 = 0;
  s21_decimal result_1;
  s21_decimal result_2;
  int src = 412412341;
  set_val(&result_1, mantissa_3, exponent_3, sign_3);
  int r_1 = s21_from_decimal_to_int(result_1, &src);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 1);
  ck_assert_int_eq(all_1, 1);
}
END_TEST
START_TEST(to_float_1) {
  char mantissa_3[] = "00000000000000000000000412341";
  int exponent_3 = 0;
  int sign_3 = 0;
  s21_decimal result_1;
  s21_decimal result_2;
  float src = 412341;
  set_val(&result_1, mantissa_3, exponent_3, sign_3);
  int r_1 = s21_from_decimal_to_float(result_1, &src);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(truncate_1) {
  char mantissa_1[] = "59999999999991234123411423420";
  char mantissa_3[] = "00000000000000000000000000005";
  int exponent_1 = 28;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  int r_1 = s21_truncate(test_1, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(floor_1) {
  char mantissa_1[] = "59999999999991234123411423420";
  char mantissa_3[] = "00000000000000000000000000005";
  int exponent_1 = 28;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  int r_1 = s21_floor(test_1, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(round_1) {
  char mantissa_1[] = "59999999999991234123411423420";
  char mantissa_3[] = "00000000000000000000000000006";
  int exponent_1 = 28;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  int r_1 = s21_round(test_1, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(negate_1) {
  char mantissa_1[] = "59999999999991234123411423420";
  char mantissa_3[] = "59999999999991234123411423420";
  int exponent_1 = 28;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_3 = -1;
  s21_decimal test_1;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  int r_1 = s21_negate(test_1, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(add_dop) {
  char mantissa_1[] = "39614081257132168796771975168";
  char mantissa_2[] = "39614081257132168796771975167";
  char mantissa_3[] = "79228162514264337593543950335";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_add(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(floor_dop) {
  char mantissa_1[] = "59999999999991234123411423420";
  char mantissa_3[] = "00000000000000000000000000006";
  int exponent_1 = 28;
  int exponent_3 = 0;
  int sign_1 = 1;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  int r_1 = s21_floor(test_1, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(mod_dop) {
  char mantissa_1[] = "00000000000000000000000000000";
  char mantissa_2[] = "00023413241234123412344354643";
  char mantissa_3[] = "00000000000000000000000000000";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mod(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(mul_dop) {
  char mantissa_1[] = "00000000000000000194935521279";
  char mantissa_2[] = "00000000000011111244341000000";
  char mantissa_3[] = "00021659762076711738321390000";
  int exponent_1 = 15;
  int exponent_2 = 15;
  int exponent_3 = 28;
  int sign_1 = 0;
  int sign_2 = 0;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_mul(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(sub_dop) {
  char mantissa_1[] = "59999999999991234123411423420";
  char mantissa_2[] = "59999999999991234123411423420";
  char mantissa_3[] = "10000000052245234523452349766";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int exponent_3 = 0;
  int sign_1 = 0;
  int sign_2 = 1;
  int sign_3 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_sub(test_1, test_2, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 1);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(operators_dop) {
  char mantissa_1[] = "00000000000000000000999999999";
  char mantissa_2[] = "00000000000000000000999999999";
  int exponent_1 = 4;
  int exponent_2 = 4;
  int sign_1 = 0;
  int sign_2 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_is_less(test_1, test_2);
  int r_2 = s21_is_less_or_equal(test_1, test_2);
  int r_3 = s21_is_greater(test_1, test_2);
  int r_4 = s21_is_greater_or_equal(test_1, test_2);
  int r_5 = s21_is_equal(test_1, test_2);
  int r_6 = s21_is_not_equal(test_1, test_2);

  int all_1 = (r_1 == 0) && (r_2 == 1) && (r_3 == 0) && (r_4 == 1) &&
              (r_5 == 1) && (r_6 == 0);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(operators_dop2) {
  char mantissa_1[] = "00000000000000000000999999999";
  char mantissa_2[] = "00000000000000000000999999999";
  int exponent_1 = 4;
  int exponent_2 = 4;
  int sign_1 = 0;
  int sign_2 = 1;
  s21_decimal test_1;
  s21_decimal test_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_is_less(test_1, test_2);
  int r_2 = s21_is_less_or_equal(test_1, test_2);
  int r_3 = s21_is_greater(test_1, test_2);
  int r_4 = s21_is_greater_or_equal(test_1, test_2);
  int r_5 = s21_is_equal(test_1, test_2);
  int r_6 = s21_is_not_equal(test_1, test_2);

  int all_1 = (r_1 == 0) && (r_2 == 0) && (r_3 == 1) && (r_4 == 1) &&
              (r_5 == 0) && (r_6 == 1);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(from_float_dop) {
  s21_decimal result_1;
  s21_decimal result_2;
  float src = 0.00840044952929019927978515625;
  int r_1 = s21_from_float_to_decimal(src, &result_1);
  result_2.bits[0] = 0b01111011100101000100111110101011;
  result_2.bits[1] = 0b11010000100100111101001101000000;
  result_2.bits[2] = 0b00000000010001010111110010100100;
  result_2.bits[3] = 0b00000000000111000000000000000000;
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(from_float_dop2) {
  s21_decimal result_1;
  s21_decimal result_2;
  float src =
      0.0000000000000000000000000000000440316615156294913620553933675881924885031853322410705202372138700184223125688731670379638671875;
  int r_1 = s21_from_float_to_decimal(src, &result_1);
  result_2.bits[0] = 0;
  result_2.bits[1] = 0;
  result_2.bits[2] = 0;
  result_2.bits[3] = 0;
  int all_1 = (r_1 == 1) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(from_float_dop3) {
  s21_decimal result_1;
  s21_decimal result_2;
  float src = 305557.625;
  int r_1 = s21_from_float_to_decimal(src, &result_1);
  result_2.bits[0] = 0b00010010001101100111000001111001;
  result_2.bits[1] = 0b00000000000000000000000000000000;
  result_2.bits[2] = 0b00000000000000000000000000000000;
  result_2.bits[3] = 0b00000000000000110000000000000000;
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(to_float_dop) {
  s21_decimal result_2;
  float src;
  float srcfact = 0.993952810764312744140625;
  s21_decimal result_1;
  s21_from_float_to_decimal(srcfact, &result_1);
  result_2.bits[0] = 0b11010000001011011001111101010001;
  result_2.bits[1] = 0b01001010001100101110001001110011;
  result_2.bits[2] = 0b00000000000000001101001001111010;
  result_2.bits[3] = 0b00000000000110000000000000000000;
  int r_1 = s21_from_decimal_to_float(result_2, &src);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(operators_dop3) {
  char mantissa_1[] = "00000000000000000000000000000";
  char mantissa_2[] = "00000000000000000000000000000";
  int exponent_1 = 0;
  int exponent_2 = 0;
  int sign_1 = 0;
  int sign_2 = 0;
  s21_decimal test_1;
  s21_decimal test_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  set_val(&test_2, mantissa_2, exponent_2, sign_2);
  int r_1 = s21_is_less(test_1, test_2);
  int r_2 = s21_is_less_or_equal(test_1, test_2);
  int r_3 = s21_is_greater(test_1, test_2);
  int r_4 = s21_is_greater_or_equal(test_1, test_2);
  int r_5 = s21_is_equal(test_1, test_2);
  int r_6 = s21_is_not_equal(test_1, test_2);

  int all_1 = (r_1 == 0) && (r_2 == 1) && (r_3 == 0) && (r_4 == 1) &&
              (r_5 == 1) && (r_6 == 0);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(floor_dop2) {
  char mantissa_1[] = "00000000000000000000000000000";
  char mantissa_3[] = "00000000000000000000000000000";
  int exponent_1 = 25;
  int exponent_3 = 0;
  int sign_1 = 1;
  int sign_3 = 1;
  s21_decimal test_1;
  s21_decimal result_1;
  s21_decimal result_2;
  set_val(&test_1, mantissa_1, exponent_1, sign_1);
  int r_1 = s21_floor(test_1, &result_1);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

START_TEST(to_int_dop) {
  char mantissa_3[] = "00000000000000000002147483648";
  int exponent_3 = 0;
  int sign_3 = 1;
  s21_decimal result_1;
  s21_decimal result_2;
  int src = -2147483648;
  set_val(&result_1, mantissa_3, exponent_3, sign_3);
  int r_1 = s21_from_decimal_to_int(result_1, &src);
  set_val(&result_2, mantissa_3, exponent_3, sign_3);
  int all_1 = (r_1 == 0) && s21_is_equal(result_1, result_2);
  ck_assert_int_eq(all_1, 1);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, to_int_dop);
  tcase_add_test(tc1_1, to_float_dop);
  tcase_add_test(tc1_1, from_float_dop3);
  tcase_add_test(tc1_1, from_float_dop2);
  tcase_add_test(tc1_1, from_float_dop);
  tcase_add_test(tc1_1, operators_dop3);
  tcase_add_test(tc1_1, operators_dop2);
  tcase_add_test(tc1_1, operators_dop);
  tcase_add_test(tc1_1, sub_dop);
  tcase_add_test(tc1_1, mul_dop);
  tcase_add_test(tc1_1, mod_dop);
  tcase_add_test(tc1_1, floor_dop2);
  tcase_add_test(tc1_1, floor_dop);
  tcase_add_test(tc1_1, add_dop);
  tcase_add_test(tc1_1, operators_1);
  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_3);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_3);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);
  tcase_add_test(tc1_1, mul_6);
  tcase_add_test(tc1_1, mul_7);
  tcase_add_test(tc1_1, mul_8);
  tcase_add_test(tc1_1, mul_9);
  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  tcase_add_test(tc1_1, div_6);
  tcase_add_test(tc1_1, div_7);
  tcase_add_test(tc1_1, div_8);
  tcase_add_test(tc1_1, div_9);
  tcase_add_test(tc1_1, div_10);
  tcase_add_test(tc1_1, mod_1);
  tcase_add_test(tc1_1, mod_2);
  tcase_add_test(tc1_1, mod_3);
  tcase_add_test(tc1_1, mod_4);
  tcase_add_test(tc1_1, from_int_1);
  tcase_add_test(tc1_1, from_float_1);
  tcase_add_test(tc1_1, to_int_1);
  tcase_add_test(tc1_1, to_int_2);
  tcase_add_test(tc1_1, to_float_1);
  tcase_add_test(tc1_1, truncate_1);
  tcase_add_test(tc1_1, floor_1);
  tcase_add_test(tc1_1, round_1);
  tcase_add_test(tc1_1, negate_1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
