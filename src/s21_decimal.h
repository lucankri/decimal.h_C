#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 79228162514264337593543950335.0
#define MIN_INPUT -79228162514264337593543950335.0
#define POW_2_64 18446744073709551616.0
#define POW_2_32 4294967296.0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

/*--------------------------------TEST--------------------------------------*/
typedef struct {
  int mantissa[29];
  int exponent;
  int sign;
} dec;

void set_val(s21_decimal *value, char *mantissa, int exponent, int sign);
int from_dec(s21_decimal *value, dec dvalue);
void normalize(s21_decimal *value);
void dnormalize(dec *dvalue);
int is_zero_dec(dec dvalue_1);
void setbit(int *a, int bit, int i);
void divide_by2_dec(dec *dvalue);
/*--------------------------------TEST--------------------------------------*/

// Функции преобразования
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Функции сравнения
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

// Функции операции +, -, *, /
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Другие функции
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int _lengthMantissa(s21_decimal *a);
int _mul2Mantiss(s21_decimal *a, s21_decimal *b);
int _compareMantissa(s21_decimal *a, s21_decimal *b);
int _multiplyMantissa(s21_decimal *bits, unsigned int bits_to_multply);
int _addMantissa(s21_decimal *a, s21_decimal *b);
int _sbtMantissa(s21_decimal *bits, s21_decimal *bits_to_subtract);
int _getBitInt(unsigned int *src, int index);
void _setBitInt(unsigned int *target, int index, int value);
int _getBitMantissa(s21_decimal *a, int index);
void _setBitMantissa(s21_decimal *a, int index, int value);
void _setPs(s21_decimal *target, int p, int sign);
int _add(s21_decimal *s1, s21_decimal *s2);
int _getP(s21_decimal *d);
int _pow(s21_decimal *target, int base, int pow);
int _shiftLeftMantissa(s21_decimal *target, int index);
void _shiftRightMantissa(s21_decimal *target, int shift);
void _writeExpS(int exp, int signBit, unsigned int *target);
void _writeMantissa(s21_decimal *q, s21_decimal *t, unsigned int *target);
s21_decimal _createDecimal(int sign, unsigned int v2, unsigned int v1,
                           unsigned int v0);
int _modMantissa(s21_decimal *a, s21_decimal *b, s21_decimal *c, int flagRound);
void _commonDenominator(s21_decimal *a, s21_decimal *b);
int _mulMantissaS(s21_decimal *a, s21_decimal *b);

#endif  // SRC_S21_DECIMAL_H_
