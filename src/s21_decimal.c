#include "s21_decimal.h"

/*---------------------------------------------------------TEST----------------------------------------------------------------*/

void normalize(s21_decimal *value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
}
void dnormalize(dec *dvalue) {
  dvalue->exponent = 0;
  dvalue->sign = 0;
  for (int i = 0; i < 29; i++) {
    dvalue->mantissa[i] = 0;
  }
}

int from_dec(s21_decimal *value, dec dvalue) {
  normalize(value);
  dec my_dvalue = dvalue;
  for (int i = 0; i <= 95; i++) {
    setbit((int *)&(value->bits[i / 32]), my_dvalue.mantissa[0] % 2, i % 32);
    divide_by2_dec(&my_dvalue);
  }
  value->bits[3] = my_dvalue.exponent << 16;
  setbit((int *)&(value->bits[3]), my_dvalue.sign, 31);
  return !(is_zero_dec(my_dvalue));
}

void set_val(s21_decimal *value, char *mantissa, int exponent, int sign) {
  dec dvalue;
  dnormalize(&dvalue);
  dvalue.exponent = exponent;
  dvalue.sign = sign;
  for (int i = 0; i <= 28; i++) {
    dvalue.mantissa[i] = mantissa[28 - i] - '0';
  }
  from_dec(value, dvalue);
}

void setbit(int *a, int bit, int i) {
  if (bit) {
    *a = *a | (bit << i);
  } else {
    *a = *a & ~((bit + 1) << i);
  }
}

int is_zero_dec(dec dvalue_1) {
  int ret = 1;
  for (int i = 0; i <= 28; i++) {
    if (dvalue_1.mantissa[i] != 0) {
      ret = 0;
    }
  }
  return ret;
}

void divide_by2_dec(dec *dvalue) {
  int counter = 0;
  for (int i = 28; i >= 0; i--) {
    if ((dvalue->mantissa[i] + counter) % 2 == 1) {
      dvalue->mantissa[i] = (dvalue->mantissa[i] + counter) / 2;
      counter = 10;
    } else {
      dvalue->mantissa[i] = (dvalue->mantissa[i] + counter) / 2;
      counter = 0;
    }
  }
}

/*---------------------------------------------------------TEST----------------------------------------------------------------*/

/**
 *@brief Функция преобразует из int в "Децимал"
 **/
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  unsigned int a = src;
  if (src == INT32_MIN) {
    a = ((unsigned int)INT32_MAX) + 1;
  } else if (src < 0) {
    a *= (-1);
  }
  dst->bits[0] = a;
  dst->bits[2] = dst->bits[1] = 0;
  _setPs(dst, 0, src < 0 ? 1 : 0);
  return 0;
}

/**
 *@brief Функция преобразует из float в "Децимал"
 **/
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  union {
    float floatView;
    uint32_t uint32tView;
  } fu = {.floatView = src};

  uint32_t pfloat = fu.uint32tView;
  int k;
  // вычисляем k, k - это индекс последнего значащего бита в мантисе
  {
    int i = 0;
    while (i < 23) {
      if (_getBitInt(&pfloat, i) == 1) {
        break;
      }
      i++;
    }
    k = 23 - i;
  }

  unsigned int exp = (pfloat >> 23) & 0b11111111;
  if (exp == 255 && (pfloat & 0b11111111111111111111111) == 0) {
    if ((_getBitInt(&pfloat, 31)) == 0) {
      // если exp 255 и мантиса 0, и знак 0 тогда это +бесконечность
      return 1;
    } else if ((_getBitInt(&pfloat, 31)) == 1) {
      // если exp 255 и мантиса 0, и знак 1 тогда это -бесконечность
      return 1;
    }
  } else if (exp == 255 && (pfloat & 0b11111111111111111111111) != 0) {
    if ((_getBitInt(&pfloat, 31)) == 0) {
      // если exp 255 и мантиса больше 0, и знак 0 тогда это +nan
      return 1;
    } else if ((_getBitInt(&pfloat, 31)) == 1) {
      // если exp 255 и мантиса больше 0, и знак 1 тогда это -nan
      return 1;
    }
  }
  int p = exp - 127;
  int flag = 0;
  if (k <= p) {
    int mantissaLength = p + 1;
    if (mantissaLength <= 96) {
      int j = 0;
      // начало заполнение нулями
      for (; j < p - k; j++) {
        _setBitMantissa(dst, j, 0);
      }
      // заполнение мантисы
      for (int e = 23 - k; e < 23; e++, j++) {
        _setBitMantissa(dst, j, _getBitInt(&pfloat, e));
      }
      // обязательно ставим 1,..........
      _setBitMantissa(dst, j, 1);
      j++;

      // заполняем оставшиеся нули
      for (; j < 96; j++) {
        _setBitMantissa(dst, j, 0);
      }
      _setPs(dst, 0, src < 0 ? 1 : 0);
    } else {
      // точное представление числа слишком большое (переполнение v).
      // так как p = 0, то сократить дробь нельзя
      flag = 1;
    }
  } else {
    int q = k - p;
    if (q <= 28) {
      int j = 0;
      // заполнение мантисы
      for (int i = 23 - k; i < 23; i++, j++) {
        _setBitMantissa(dst, j, _getBitInt(&pfloat, i));
      }
      // обязательно ставим 1,..........
      _setBitMantissa(dst, j, 1);
      j++;
      // заполняем оставшиеся нули
      for (; j < 96; j++) {
        _setBitMantissa(dst, j, 0);
      }

      // преобразование мантиссы
      for (int i = 0; i < q; i++) {
        // переполнение мантиссы невозможно, поскольку m * 5^q <= 90 bits
        _multiplyMantissa(dst, 5);
      }
      _setPs(dst, q, src < 0 ? 1 : 0);
    } else {
      // точное представление числа слишком маленькое, мантисса будет иметь
      // округлённое (неточное) значение
      int j = 0;
      // заполнение мантисы
      for (int i = 23 - k; i < 23; i++, j++) {
        _setBitMantissa(dst, j, _getBitInt(&pfloat, i));
      }
      // обязательно ставим 1,..........
      _setBitMantissa(dst, j, 1);
      j++;
      // заполняем оставшиеся нули
      for (; j < 96; j++) {
        _setBitMantissa(dst, j, 0);
      }

      // преобразование мантиссы
      for (int i = 0; i < 28; i++) {
        _multiplyMantissa(dst, 5);
      }
      s21_decimal pow2_28;
      _pow(&pow2_28, 2, q - 28);
      _modMantissa(dst, &pow2_28, NULL, 1);
      _setPs(dst, 28, src < 0 ? 1 : 0);
      if (dst->bits[2] == 0 && dst->bits[1] == 0 && dst->bits[0] == 0) {
        dst->bits[3] = 0;
        dst->bits[2] = 0;
        dst->bits[1] = 0;
        dst->bits[0] = 0;
        flag = 1;
      }
      // что бы округлить результат деления, нужно остаток сравнить с пловиной
      // делителя. если остаток меньше тогда оставляем как есть, а если остаток
      // больше или равен тогда прибавляем 1
    }
  }
  return flag;
}

/**
 *@brief Функция преобразует в float из "Децимал"
 **/
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag = 0;
  if (src.bits[2] == 0 && src.bits[1] == 0 && src.bits[0] == 0) {
    *dst = 0;
  } else {
    int p = _getP(&src);
    s21_decimal p10;
    if ((_pow(&p10, 10, p)) == 0) {
      if (_compareMantissa(&src, &p10) != -1) {
        int exp = 0;
        s21_decimal t;
        s21_decimal t1 = p10;
        // TODO обработать вариант когда старший бит мантиссы равен 1, и t не
        // может увеличиться на 2
        while (_compareMantissa(&src, &t1) != -1) {
          t = t1;
          exp++;
          if (_multiplyMantissa(&t1, 2) == 1) {
            break;
          }
        }
        exp--;

        if (exp <= 127) {
          s21_decimal q = src;
          _sbtMantissa(&q, &t);
          union {
            float floatView;
            uint32_t uint32tView;
          } fu = {.uint32tView = 0};
          _writeExpS(exp + 127, _getBitInt(&(src.bits[3]), 31),
                     &fu.uint32tView);
          _writeMantissa(&q, &t, &fu.uint32tView);

          *dst = fu.floatView;
        } else {
          flag = 1;
        }
      } else {
        int exp = 0;
        s21_decimal r = _createDecimal(0, 0, 0, 1);
        s21_decimal w = p10;
        _modMantissa(&w, &src, NULL, 0);
        while (_compareMantissa(&w, &r) == 1 || _compareMantissa(&w, &r) == 0) {
          if (_multiplyMantissa(&r, 2) == 1) {
            flag = 1;
          }
          exp++;
        }

        if (flag == 0 && exp > -128) {
          s21_decimal q = src;
          _shiftLeftMantissa(&q, exp);
          _sbtMantissa(&q, &p10);
          s21_decimal t = p10;
          union {
            float floatView;
            uint32_t uint32tView;
          } fu = {.uint32tView = 0};
          _writeExpS(-exp + 127, _getBitInt(&(src.bits[3]), 31),
                     &fu.uint32tView);
          _writeMantissa(&q, &t, &fu.uint32tView);
          *dst = fu.floatView;
        } else {
          flag = 1;
        }
      }
    } else {
      flag = 1;
    }
  }
  return flag;
}

/**
 *@brief Функция преобразует в int из "Децимал"
 **/
int s21_from_decimal_to_int(s21_decimal src, int *dst) {  //в int
  int flag = 0;
  int p = (src.bits[3] >> 16) & 0b11111111;
  s21_decimal p10;
  _pow(&p10, 10, p);
  s21_decimal v = src;
  _modMantissa(&v, &p10, NULL, 0);
  if (v.bits[2] == 0 && v.bits[1] == 0) {
    if (_getBitInt(&v.bits[0], 31) == 0 ||
        (v.bits[0] == (unsigned int)INT32_MIN &&
         _getBitInt(&v.bits[3], 31) == 1)) {
      if (_getBitInt(&v.bits[3], 31) == 1) {
        v.bits[0] *= (-1);
      }
      *dst = v.bits[0];
    } else {
      flag = 1;
    }
  } else {
    flag = 1;
  }
  return flag;
}

/**
 *@brief Функция сравнивает числа "Децимал" и проверяет: если а < b тогда
 *функция вернет 1, в остальных случаях 0
 **/
int s21_is_less(s21_decimal a, s21_decimal b) {
  int flag = 0;
  if ((a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) &&
      (b.bits[0] == 0 && b.bits[1] == 0 && b.bits[2] == 0)) {
    flag = 0;
  } else if ((_getBitInt(&a.bits[3], 31)) == 1 &&
             (_getBitInt(&b.bits[3], 31)) == 0) {
    flag = 1;
  } else if ((_getBitInt(&a.bits[3], 31)) == 0 &&
             (_getBitInt(&b.bits[3], 31)) == 1) {
    flag = 0;
  } else if ((_getBitInt(&a.bits[3], 31)) == 1 &&
             (_getBitInt(&b.bits[3], 31)) == 1) {
    _commonDenominator(&a, &b);
    if (_compareMantissa(&a, &b) == 1) {
      flag = 1;
    } else {
      flag = 0;
    }
  } else {
    _commonDenominator(&a, &b);
    if (_compareMantissa(&a, &b) != -1) {
      flag = 0;
    } else {
      flag = 1;
    }
  }
  return flag;
}

/**
 *@brief Функция сравнивает числа "Децимал" и проверяет: если а == b тогда
 *функция вернет 1, в остальных случаях 0
 **/
int s21_is_equal(s21_decimal a, s21_decimal b) {
  int flag = 0;
  if ((a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) &&
      (b.bits[0] == 0 && b.bits[1] == 0 && b.bits[2] == 0)) {
    flag = 1;
  } else if (((_getBitInt(&a.bits[3], 31)) == 1 &&
              (_getBitInt(&b.bits[3], 31)) == 1) ||
             ((_getBitInt(&a.bits[3], 31)) == 0 &&
              (_getBitInt(&b.bits[3], 31)) == 0)) {
    _commonDenominator(&a, &b);
    if (_compareMantissa(&a, &b) == 0) {
      flag = 1;
    } else {
      flag = 0;
    }
  } else {
    flag = 0;
  }
  return flag;
}

/**
 *@brief Функция сравнивает числа "Децимал" и проверяет: если а <= b тогда
 *функция вернет 1, в остальных случаях 0
 **/
int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int flag = 0;
  if ((s21_is_less(a, b)) == 1 || (s21_is_equal(a, b)) == 1) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}

/**
 *@brief Функция сравнивает числа "Децимал" и проверяет: если а > b тогда
 *функция вернет 1, в остальных случаях 0
 **/
int s21_is_greater(s21_decimal a, s21_decimal b) {
  int flag = 0;
  if ((a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) &&
      (b.bits[0] == 0 && b.bits[1] == 0 && b.bits[2] == 0)) {
    flag = 0;
  } else if (((_getBitInt(&a.bits[3], 31)) == 1 &&
              (_getBitInt(&b.bits[3], 31)) == 1) ||
             ((_getBitInt(&a.bits[3], 31)) == 0 &&
              (_getBitInt(&b.bits[3], 31)) == 0)) {
    if ((s21_is_less(a, b)) == 1 || (s21_is_equal(a, b)) == 1) {
      flag = 0;
    } else {
      flag = 1;
    }
  } else if ((_getBitInt(&a.bits[3], 31)) == 0 &&
             (_getBitInt(&b.bits[3], 31)) == 1) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}

/**
 *@brief Функция сравнивает числа "Децимал" и проверяет: если а >= b тогда
 *функция вернет 1, в остальных случаях 0
 **/
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int flag = 0;
  if ((s21_is_greater(a, b)) == 1 || (s21_is_equal(a, b)) == 1) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}

/**
 *@brief Функция сравнивает числа "Децимал" и проверяет: если а != b тогда
 *функция вернет 1, в остальных случаях 0
 **/
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int flag = 0;
  if ((s21_is_equal(a, b)) == 1) {
    flag = 0;
  } else {
    flag = 1;
  }
  return flag;
}

/**
 *@brief Функция сложения чисел Децимал
 **/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_decimal a = value_1;
  s21_decimal b = value_2;
  _commonDenominator(&a, &b);
  int p = _add(&a, &b);
  if (p > 0) {
    if (_getP(&a) > 0) {
      int pa = _getP(&a);
      int pb = _getP(&b);
      pa--;
      pb--;
      a = value_1;
      b = value_2;
      s21_decimal p10 = _createDecimal(0, 0, 0, 10);
      _modMantissa(&a, &p10, NULL, 1);
      _modMantissa(&b, &p10, NULL, 1);
      _setPs(&a, pa, _getBitInt(&(a.bits[3]), 31));
      _setPs(&b, pb, _getBitInt(&(b.bits[3]), 31));
      _add(&a, &b);
    } else {
      if (p == 1) {
        flag = 1;
      } else {
        flag = 2;
      }
    }
  }
  if (flag == 0) {
    *result = a;
  }
  return flag;
}

/**
 *@brief Функция вычитания чисел Децимал
 **/
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_decimal result_value;
  s21_negate(value_2, &result_value);
  int p = s21_add(value_1, result_value, result);
  if (p == 1) {
    flag = 1;
  } else if (p == 2) {
    flag = 2;
  }
  return flag;
}

/**
 * @brief Функция умножения двух чисел "Децимал"
 **/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_decimal a = value_1;
  s21_decimal b = value_2;

  s21_decimal a1 = a;
  s21_decimal b1 = b;
  s21_decimal p10 = _createDecimal(0, 0, 0, 10);
  int x = _mulMantissaS(&a1, &b1);

  int pa = _getP(&a);
  int pb = _getP(&b);
  int pa_pb_res = pa + pb - x;

  if (pa_pb_res < 0) {
    if ((_getBitInt(&(value_1.bits[3]), 31) == 1 &&
         _getBitInt(&(value_2.bits[3]), 31) == 1) ||
        (_getBitInt(&(value_1.bits[3]), 31) == 0 &&
         _getBitInt(&(value_2.bits[3]), 31) == 0)) {
      flag = 1;
    } else {
      flag = 2;
    }
  }
  if (flag == 0) {
    if (x == 0) {
      _mul2Mantiss(&a1, &b1);
    }

    s21_decimal mod;
    int flagRound = 0;
    while (pa_pb_res > 28) {
      _modMantissa(&a1, &p10, &mod, 0);
      pa_pb_res--;
      flagRound = 1;
    }

    // pa_pb_res <= 28
    if (flagRound == 1) {
      _shiftRightMantissa(&p10, 1);
      if ((_compareMantissa(&mod, &p10)) != -1) {
        s21_decimal add1 = _createDecimal(0, 0, 0, 1);
        _addMantissa(&a1, &add1);
      }
    }

    int resultSign = ((_getBitInt(&(value_1.bits[3]), 31) == 1 &&
                       _getBitInt(&(value_2.bits[3]), 31) == 1) ||
                      (_getBitInt(&(value_1.bits[3]), 31) == 0 &&
                       _getBitInt(&(value_2.bits[3]), 31) == 0))
                         ? 0
                         : 1;
    _setPs(&a1, pa_pb_res, resultSign);
    *result = a1;
  }

  return flag;
}

/**
 * @brief Функция деление двух чисел "Децимал"
 **/
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  if (value_2.bits[2] == 0 && value_2.bits[1] == 0 && value_2.bits[0] == 0) {
    flag = 3;
  } else if (value_1.bits[2] == 0 && value_1.bits[1] == 0 &&
             value_1.bits[0] == 0) {
    result->bits[3] = 0;
    result->bits[2] = 0;
    result->bits[1] = 0;
    result->bits[0] = 0;
  } else {
    s21_decimal a = value_1;
    s21_decimal b = value_2;
    int pa = _getP(&a);
    int pb = _getP(&b);

    s21_decimal p10 = _createDecimal(0, 0, 0, 10);
    s21_decimal res = _createDecimal(0, 0, 0, 0);

    int pa_pb_res = pa - pb;
    s21_decimal mod;
    _modMantissa(&a, &b, &mod, 0);
    _addMantissa(&res, &a);
    int flagPb = 0;
    if (pa_pb_res < 0) {
      flagPb = 1;
    }

    while (((mod.bits[0] != 0 || mod.bits[1] != 0 || mod.bits[2] != 0) &&
            pa_pb_res < 28) ||
           flagPb == 1) {
      if (_mul2Mantiss(&res, &p10) == 1) {
        break;
      }
      pa_pb_res++;
      if (pa_pb_res == 0) {
        flagPb = 0;
      }
      a = mod;
      _mul2Mantiss(&a, &p10);
      _modMantissa(&a, &b, &mod, 0);

      _addMantissa(&res, &a);
    }

    if (pa_pb_res < 0) {
      if ((_getBitInt(&(value_1.bits[3]), 31) == 1 &&
           _getBitInt(&(value_2.bits[3]), 31) == 1) ||
          (_getBitInt(&(value_1.bits[3]), 31) == 0 &&
           _getBitInt(&(value_2.bits[3]), 31) == 0)) {
        flag = 1;
      } else {
        flag = 2;
      }
    }
    if (flag == 0) {
      _shiftRightMantissa(&b, 1);
      if ((_compareMantissa(&mod, &b)) != -1) {
        s21_decimal add1 = _createDecimal(0, 0, 0, 1);
        _addMantissa(&res, &add1);
      }

      int resultSign = ((_getBitInt(&(value_1.bits[3]), 31) == 1 &&
                         _getBitInt(&(value_2.bits[3]), 31) == 1) ||
                        (_getBitInt(&(value_1.bits[3]), 31) == 0 &&
                         _getBitInt(&(value_2.bits[3]), 31) == 0))
                           ? 0
                           : 1;

      _setPs(&res, pa_pb_res, resultSign);
      *result = res;
    }
  }
  return flag;
}

/**
 * @brief Функция записывает остаток от деления
 **/
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  if (value_2.bits[2] == 0 && value_2.bits[1] == 0 && value_2.bits[0] == 0) {
    flag = 3;
  } else if (value_1.bits[2] == 0 && value_1.bits[1] == 0 &&
             value_1.bits[0] == 0) {
    result->bits[3] = 0;
    result->bits[2] = 0;
    result->bits[1] = 0;
    result->bits[0] = 0;
  } else {
    s21_decimal a = value_1;
    s21_decimal b = value_2;
    s21_decimal res;
    _commonDenominator(&a, &b);
    if (b.bits[0] == 0 && b.bits[1] == 0 && b.bits[2] == 0) {
      res = _createDecimal(0, 0, 0, 0);
    } else {
      _modMantissa(&a, &b, &res, 0);
      _setPs(&res, _getP(&a), _getBitInt(&(value_1.bits[3]), 31));
    }
    *result = res;
  }
  return flag;
}

/**
 * @brief Округляет указанное Decimal число до ближайшего целого числа в сторону
 *отрицательной бесконечности.
 **/
int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  s21_decimal p10 = _createDecimal(0, 0, 0, 10);
  s21_decimal a = value;
  int pa = _getP(&a);
  int flagSign = 1;

  if (value.bits[0] != 0 || value.bits[1] != 0 || value.bits[2] != 0) {
    while (pa > 0) {
      _modMantissa(&a, &p10, NULL, 0);
      pa--;
    }

    if (a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) {
      flagSign = 0;
    }

    if (_getBitInt(&(a.bits[3]), 31) == 1) {
      s21_decimal add1 = _createDecimal(0, 0, 0, 1);
      if (_addMantissa(&a, &add1) > 0) {
        flag = 1;
      }
    }
    if (flag == 0) {
      _setPs(&a, pa, flagSign == 1 ? _getBitInt(&(a.bits[3]), 31) : 0);
      *result = a;
    }
  } else {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;
  }
  return flag;
}

/**
 * @brief Округляет Decimal до ближайшего целого числа.
 **/
int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal a = value;
  s21_decimal p10 = _createDecimal(0, 0, 0, 10);
  int flagRound = 0;
  int flagSign = 1;

  int pa = _getP(&a);
  while (pa > 0) {
    if (pa == 1) {
      flagRound = 1;
    }
    _modMantissa(&a, &p10, NULL, flagRound);
    pa--;
  }

  if (a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) {
    flagSign = 0;
  }

  _setPs(&a, pa, flagSign == 1 ? _getBitInt(&(a.bits[3]), 31) : 0);
  *result = a;
  return 0;
}

/**
 * @brief Возвращает целые цифры указанного Decimal числа; любые дробные цифры
 *отбрасываются, включая конечные нули.
 **/
int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal a = value;
  s21_decimal p10 = _createDecimal(0, 0, 0, 10);
  int flagSign = 1;
  int pa = _getP(&a);
  while (pa > 0) {
    _modMantissa(&a, &p10, NULL, 0);
    pa--;
  }
  if (a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) {
    flagSign = 0;
  }

  _setPs(&a, pa, flagSign == 1 ? _getBitInt(&(a.bits[3]), 31) : 0);
  *result = a;
  return 0;
}

/**
 *@brief Возвращает результат умножения указанного Decimal на -1.
 **/
int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_decimal val = value;
  _setBitInt(&(val.bits[3]), 31, !(_getBitInt(&(val.bits[3]), 31)));
  result->bits[3] = val.bits[3];
  result->bits[2] = val.bits[2];
  result->bits[1] = val.bits[1];
  result->bits[0] = val.bits[0];
  return 0;
}

/**
 *@brief Функция выводит сколько бит занято в мантиссе
 **/
int _lengthMantissa(s21_decimal *a) {
  int i = 95;
  while ((_getBitMantissa(a, i)) == 0 && i != -1) {
    i--;
  }
  i += 1;
  return i;
}

int _mul2Mantiss(s21_decimal *a, s21_decimal *b) {
  int flag = 0;
  if ((a->bits[2] == 0 && a->bits[1] == 0 && a->bits[0] == 0) ||
      (b->bits[2] == 0 && b->bits[1] == 0 && b->bits[0] == 1)) {
    // число остаётся тем же
  } else if (b->bits[2] == 0 && b->bits[1] == 0 && b->bits[0] == 0) {
    a->bits[0] = 0;
    a->bits[1] = 0;
    a->bits[2] = 0;
  } else {
    s21_decimal a1 = *a;
    s21_decimal b1 = *b;
    while (_getBitMantissa(&b1, 0) == 0) {
      _shiftRightMantissa(&b1, 1);
      if (_shiftLeftMantissa(&a1, 1) == 1) {
        // переполнение
        flag = 1;
        break;
      }
    }
    s21_decimal t;
    s21_decimal c = _createDecimal(0, 0, 0, 0);
    if (flag == 0) {
      for (int i = 0; i < 96; i++) {
        if ((_getBitMantissa(&a1, i)) == 1) {
          t = b1;
          if ((_shiftLeftMantissa(&t, i)) == 1) {
            flag = 1;
            break;
          }
          if ((_addMantissa(&c, &t)) == 1) {
            flag = 1;
            break;
          }
        }
      }
    }

    if (flag == 0) {
      a->bits[0] = c.bits[0];
      a->bits[1] = c.bits[1];
      a->bits[2] = c.bits[2];
    }
  }
  return flag;
}

/**
 * @brief доп. функция умножения, помогает сохранить точность при сокращении
 **/
int _mulMantissaS(s21_decimal *a, s21_decimal *b) {
  int x;
  if (a->bits[0] == 0 && a->bits[1] == 0 && a->bits[2] == 0) {
    x = 0;
  } else if (b->bits[0] == 0 && b->bits[1] == 0 && b->bits[2] == 0) {
    a->bits[0] = 0;
    a->bits[1] = 0;
    a->bits[2] = 0;
    x = 0;
  } else {
    s21_decimal p10 = _createDecimal(0, 0, 0, 10);

    // подбор min х: _lengthMantissa(a*b/10^x) <= 96
    {
      x = 0;
      s21_decimal a1 = *a;
      s21_decimal b1 = *b;
      s21_decimal moda;
      s21_decimal modb;
      while ((_lengthMantissa(&a1) + _lengthMantissa(&b1)) > 96) {
        if (_compareMantissa(&a1, &p10) == 1) {
          _modMantissa(&a1, &p10, &moda, 0);
        } else {
          _modMantissa(&b1, &p10, &modb, 0);
        }
        x++;
      }
    }

    // ищем произведение a и b в виде
    // a*b = (m*n*10^x + m*q + p*n + p*q/10^x) * 10^x,
    // где a = m*10^x + p; b = n*10^x + q; x >= 0
    {
      s21_decimal a1 = *a;
      s21_decimal b1 = *b;
      s21_decimal px10;
      _pow(&px10, 10, x);
      s21_decimal m, p, n, q;
      m = a1;
      n = b1;
      _modMantissa(&m, &px10, &p, 0);
      _modMantissa(&n, &px10, &q, 0);
      s21_decimal s1 = m;
      _mul2Mantiss(&s1, &n);
      _mul2Mantiss(&s1, &px10);

      s21_decimal s2 = m;
      _mul2Mantiss(&s2, &q);

      s21_decimal s3 = p;
      _mul2Mantiss(&s3, &n);

      s21_decimal s4 = p;
      int x1 = _mulMantissaS(&s4, &q);
      s21_decimal px10_1;
      _pow(&px10_1, 10, x - x1);
      _modMantissa(&s4, &px10_1, NULL, 1);
      _addMantissa(&s1, &s2);
      _addMantissa(&s1, &s3);
      _addMantissa(&s1, &s4);
      a->bits[0] = s1.bits[0];
      a->bits[1] = s1.bits[1];
      a->bits[2] = s1.bits[2];
    }
  }

  return x;
}

/**
 *@brief Функция приводит к общему знаменателю "Децимал"
 **/
void _commonDenominator(s21_decimal *a, s21_decimal *b) {
  int ap = _getP(a);
  int bp = _getP(b);
  if (ap >= bp) {
    while (bp < ap) {
      if ((_multiplyMantissa(b, 10)) == 1) {
        break;
      }
      bp++;
    }
    if (bp != ap) {
      s21_decimal k;
      _pow(&k, 10, ap - bp);
      _modMantissa(a, &k, NULL, 1);
      _setPs(a, bp, _getBitInt(&(a->bits[3]), 31));
      _setPs(b, bp, _getBitInt(&(b->bits[3]), 31));
    } else {
      _setPs(b, bp, _getBitInt(&(b->bits[3]), 31));
    }
  } else {
    _commonDenominator(b, a);
  }
}

/**
 *@brief Функция целочисленного деления мантисс чисел "Децимал" с остатком
 * функция вернет 1 если b = 0;
 * @param flagRound если передать 1,  функция будет делить с округлением,
 * если 0, функция не будет округлять
 **/
int _modMantissa(s21_decimal *a, s21_decimal *b, s21_decimal *c,
                 int flagRound) {
  int flag = 0;
  if (b->bits[2] != 0 || b->bits[1] != 0 || b->bits[0] != 0) {
    if (a->bits[2] != 0 || a->bits[1] != 0 || a->bits[0] != 0) {
      if (b->bits[2] != 0 || b->bits[1] != 0 || b->bits[0] != 1) {
        // сокращаем нули
        s21_decimal a1 = *a;
        s21_decimal b2 = *b;
        int c_shift = 0;
        while ((_getBitMantissa(&a1, 0)) == 0 &&
               (_getBitMantissa(&b2, 0)) == 0) {
          _shiftRightMantissa(&a1, 1);
          _shiftRightMantissa(&b2, 1);
          c_shift++;
        }

        int q = 0;
        s21_decimal t = b2;
        s21_decimal spow;
        s21_decimal s = _createDecimal(0, 0, 0, 0);
        while (_compareMantissa(&a1, &b2) != -1) {
          t = b2;
          q = _lengthMantissa(&a1) - _lengthMantissa(&t);
          _shiftLeftMantissa(&t, q);
          if (_compareMantissa(&a1, &t) == -1) {
            _shiftRightMantissa(&t, 1);
            q--;
          }
          _pow(&spow, 2, q);
          _addMantissa(&s, &spow);
          _sbtMantissa(&a1, &t);
        }

        if (flagRound == 1) {
          b2 = *b;
          _shiftRightMantissa(&b2, 1);
          _shiftLeftMantissa(&a1, c_shift);
          if ((_compareMantissa(&a1, &b2)) != -1) {
            s21_decimal add1 = _createDecimal(0, 0, 0, 1);
            _addMantissa(&s, &add1);
          }
        }
        a->bits[0] = s.bits[0];
        a->bits[1] = s.bits[1];
        a->bits[2] = s.bits[2];

        if (c != NULL) {
          c->bits[0] = a1.bits[0];
          c->bits[1] = a1.bits[1];
          c->bits[2] = a1.bits[2];
          c->bits[3] = 0;
          if (flagRound == 0) {
            _shiftLeftMantissa(c, c_shift);
          }
        }
      } else {
        if (c != NULL) {
          c->bits[3] = 0;
          c->bits[2] = 0;
          c->bits[1] = 0;
          c->bits[0] = 0;
        }
      }
    } else {
      if (c != NULL) {
        c->bits[3] = 0;
        c->bits[2] = 0;
        c->bits[1] = 0;
        c->bits[0] = 0;
      }
    }
  } else {
    flag = 1;
  }
  return flag;
}

/**
 *
 * @param sign < 0 for negative
 * @return s21_decimal
 **/
s21_decimal _createDecimal(int sign, unsigned int v2, unsigned int v1,
                           unsigned int v0) {
  s21_decimal d;
  d.bits[0] = v0;
  d.bits[1] = v1;
  d.bits[2] = v2;
  d.bits[3] = sign == 1 ? ((unsigned int)1 << 31) : 0;
  return d;
}

/**
 *@brief Записывает signBit и exp в uint32_t-представление числа float
 */
void _writeExpS(int exp, int signBit, unsigned int *target) {
  *target |= (exp << 23);
  _setBitInt(target, 31, signBit);
}

/**
 *@brief Записывает побитово дробную часть дроби q/t в uint32_t-представление
 *числа float
 **/
void _writeMantissa(s21_decimal *q, s21_decimal *t, unsigned int *target) {
  s21_decimal x = *q;
  for (int index = 22; index >= 0; index--) {
    _multiplyMantissa(&x, 2);
    if ((_compareMantissa(&x, t)) == 1 || (_compareMantissa(&x, t)) == 0) {
      _setBitInt(target, index, 1);
      _sbtMantissa(&x, t);
    } else {
      _setBitInt(target, index, 0);
    }
  }
}

/**
 *@brief Функция производит сдвиг влево числа "Децимал"
 * @param target - число "Децимал"
 * @param shift - на сколько сдвинуть число
 **/
int _shiftLeftMantissa(s21_decimal *target, int shift) {
  int flag = 0;
  // проверяем, что первые shift бит мантиссы нули
  for (int i = 95; i > 95 - shift; i--) {
    if (_getBitMantissa(target, i) == 1) {
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    if (shift < 32) {
      target->bits[2] <<= shift;
      for (int i = 0; i < shift; i++) {
        _setBitInt(&(target->bits[2]), i,
                   _getBitInt(&(target->bits[1]), 32 - shift + i));
      }
      target->bits[1] <<= shift;
      for (int i = 0; i < shift; i++) {
        _setBitInt(&(target->bits[1]), i,
                   _getBitInt(&(target->bits[0]), 32 - shift + i));
      }
      target->bits[0] <<= shift;
    } else {
      shift -= 31;
      _shiftLeftMantissa(target, 31);
      _shiftLeftMantissa(target, shift);
    }
  }
  return flag;
}

/**
 *@brief Функция производит сдвиг вправо числа "Децимал"
 * @param target - число "Децимал"
 * @param shift - на сколько сдвинуть число
 **/
void _shiftRightMantissa(s21_decimal *target, int shift) {
  if (shift < 32) {
    target->bits[0] >>= shift;
    for (int i = 0; i < shift; i++) {
      _setBitInt(&(target->bits[0]), 31 - i,
                 _getBitInt(&(target->bits[1]), shift - i - 1));
    }
    target->bits[1] >>= shift;
    for (int i = 0; i < shift; i++) {
      _setBitInt(&(target->bits[1]), 31 - i,
                 _getBitInt(&(target->bits[2]), shift - i - 1));
    }
    target->bits[2] >>= shift;
  } else {
    shift -= 31;
    _shiftRightMantissa(target, 31);
    _shiftRightMantissa(target, shift);
  }
}

/**
 *@brief Функция кладет в target - base в степени pow
 * если функция вернула 1 - массив переполнился
 * если функция вернула 0 - все хорошо
 **/
int _pow(s21_decimal *target, int base, int pow) {
  int flag = 0;
  // TODO сейчас функция работает только с модулем числа. Реализовать обработку
  // знака
  if (pow == 0) {
    s21_from_int_to_decimal(1, target);
  } else {
    s21_from_int_to_decimal(base, target);
    for (int i = 1; i < pow; i++) {
      if (_multiplyMantissa(target, base) == 1) {
        flag = 1;
        break;
      }
    }
  }

  return flag;
}

/**
 *@brief Функция сравнения двух модулей "Децимал",
 * функция выводит 3 значения:
 * 1 - |a| > |b|.
 * -1 - |a| < |b|.
 * 0 - |a| = |b|.
 **/
int _compareMantissa(s21_decimal *a, s21_decimal *b) {
  int flag = 0;
  if (a->bits[2] == b->bits[2]) {
    if (a->bits[1] == b->bits[1]) {
      if (a->bits[0] == b->bits[0]) {
        flag = 0;
      } else if ((a->bits[0]) > (b->bits[0])) {
        flag = 1;
      } else {
        flag = -1;
      }
    } else if ((a->bits[1]) > (b->bits[1])) {
      flag = 1;
    } else {
      flag = -1;
    }
  } else if ((a->bits[2]) > (b->bits[2])) {
    flag = 1;
  } else {
    flag = -1;
  }
  return flag;
}

/**
 *@brief Функция setPs работает с массивом bits[3], записывает степень и знак
 **/
void _setPs(s21_decimal *target, int p, int sign) {
  target->bits[3] = p;
  target->bits[3] <<= 16;
  _setBitInt(&(target->bits[3]), 31, sign);
}

/**
 * Функция выводит степень числа "Децимал"
 **/
int _getP(s21_decimal *d) {
  int p = (d->bits[3] >> 16) & 0b11111111;
  return p;
}

/**
 *@brief Функция сложения чисел "Децимал", если функция вернула 1 - массив
 *переполнился, а если 0 - функци отработала успешно.
 **/
int _addMantissa(s21_decimal *a, s21_decimal *b) {
  int flag = 0;
  s21_decimal res;
  int m = 0;
  for (int i = 0; i < 96; i++) {
    int s1, s2;
    s1 = _getBitMantissa(a, i);
    s2 = _getBitMantissa(b, i);
    int sum = s1 + s2 + m;
    if (sum >= 2) {
      if (i == 95) {
        // TODO исправить
        flag = 1;
        break;
      }
      m = 1;
    } else {
      m = 0;
    }
    if (sum == 0 || sum == 2) {
      _setBitMantissa(&res, i, 0);
    } else {
      _setBitMantissa(&res, i, 1);
    }
  }
  if (flag == 0) {
    a->bits[0] = res.bits[0];
    a->bits[1] = res.bits[1];
    a->bits[2] = res.bits[2];
  }
  return flag;
}

/**
 *@brief Функция вычитания модулей "Децимал".
 * |a| должен быть >= |b|
 **/
int _sbtMantissa(s21_decimal *a, s21_decimal *b) {
  int flag = 0;
  if ((_compareMantissa(a, b)) == 1) {
    for (int i = 0; i < 96; i++) {
      int b1 = _getBitMantissa(a, i);
      int b2 = _getBitMantissa(b, i);
      int raz = b1 - b2;
      if (raz == -1) {
        int j = i + 1;
        while ((_getBitMantissa(a, j)) != 1 && j < 96) {
          _setBitMantissa(a, j, 1);
          j++;
        }
        _setBitMantissa(a, j, 0);
        _setBitMantissa(a, i, 1);
      } else {
        _setBitMantissa(a, i, raz);
      }
    }
  } else if ((_compareMantissa(a, b)) == 0) {
    a->bits[0] = 0;
    a->bits[1] = 0;
    a->bits[2] = 0;
    a->bits[3] = 0;
  } else {
    flag = 1;
  }
  return flag;
}

/**
 *@brief Функция умножение чисел "Децимал", если функция вернула 1 - массив
 *переполнился, а если 0 - функци отработала успешно.
 **/
int _multiplyMantissa(s21_decimal *a, unsigned int b) {
  s21_decimal bDec = _createDecimal(0, 0, 0, b);
  return _mul2Mantiss(a, &bDec);
}

/**
 *@brief Функция выводит нужный бит по индексу внутри integer.
 * index from 0 to 31, from right to left
 **/
int _getBitInt(unsigned int *src, int index) {
  unsigned int MASK = 1 << index;
  return ((*src) & MASK) >> index;
}

/**
 *@brief Функция меняет бит по индексу внутри integer, на который нам нужен
 * index from 0 to 31, from right to left
 **/
void _setBitInt(unsigned int *target, int index, int value) {
  if (value == 0) {
    unsigned int MASK = ~(1 << index);
    *target &= MASK;
  } else {
    unsigned int MASK = 1 << index;
    *target |= MASK;
  }
}

/**
 *@brief Функция выводит нужный бит по индексу внутри массива из трёх integer.
 * index from 0 to 95, from right to left
 **/
int _getBitMantissa(s21_decimal *a, int index) {
  int res;
  if (index < 32) {
    res = _getBitInt(&(a->bits[0]), index);
  } else if (index < 64) {
    res = _getBitInt(&(a->bits[1]), index - 32);
  } else {
    res = _getBitInt(&(a->bits[2]), index - 64);
  }
  return res;
}

/**
 *@brief Функция меняет бит по индексу внутри v-числа decimal
 * index from 0 to 95, from right to left
 **/
void _setBitMantissa(s21_decimal *a, int index, int value) {
  if (value == 0) {
    if (index < 32) {
      _setBitInt(&(a->bits[0]), index, 0);
    } else if (index < 64) {
      _setBitInt(&(a->bits[1]), index - 32, 0);
    } else {
      _setBitInt(&(a->bits[2]), index - 64, 0);
    }
  } else {
    if (index < 32) {
      _setBitInt(&(a->bits[0]), index, 1);
    } else if (index < 64) {
      _setBitInt(&(a->bits[1]), index - 32, 1);
    } else {
      _setBitInt(&(a->bits[2]), index - 64, 1);
    }
  }
}

/**
 *@brief Функция складывает и вычитает 2 числа модуля "Децимал" в зависимости от
 *знака
 **/
int _add(s21_decimal *s1, s21_decimal *s2) {
  int flag = 0;
  if (s2->bits[2] != 0 || s2->bits[1] != 0 || s2->bits[0] != 0) {
    if (s1->bits[2] != 0 || s1->bits[1] != 0 || s1->bits[0] != 0) {
      if ((_getBitInt(&(s1->bits[3]), 31)) == 0 &&
          (_getBitInt(&(s2->bits[3]), 31)) == 0) {
        if ((_addMantissa(s1, s2)) == 1) {
          flag = 1;
        }
      } else if ((_getBitInt(&(s1->bits[3]), 31)) == 0 &&
                 (_getBitInt(&(s2->bits[3]), 31)) == 1) {
        if ((_compareMantissa(s1, s2)) != -1) {
          _sbtMantissa(s1, s2);
          _setBitInt(&(s1->bits[3]), 31, 0);
        } else if ((_compareMantissa(s1, s2)) == -1) {
          s21_decimal res;
          res.bits[3] = s2->bits[3];
          res.bits[2] = s2->bits[2];
          res.bits[1] = s2->bits[1];
          res.bits[0] = s2->bits[0];
          _sbtMantissa(&res, s1);
          _setBitInt(&(res.bits[3]), 31, 1);
          s1->bits[3] = res.bits[3];
          s1->bits[2] = res.bits[2];
          s1->bits[1] = res.bits[1];
          s1->bits[0] = res.bits[0];
        }
      } else if ((_getBitInt(&(s1->bits[3]), 31)) == 1 &&
                 (_getBitInt(&(s2->bits[3]), 31)) == 0) {
        if ((_compareMantissa(s1, s2)) == 1) {
          _sbtMantissa(s1, s2);
          _setBitInt(&(s1->bits[3]), 31, 1);
        } else if ((_compareMantissa(s1, s2)) == -1) {
          s21_decimal res;
          res.bits[3] = s2->bits[3];
          res.bits[2] = s2->bits[2];
          res.bits[1] = s2->bits[1];
          res.bits[0] = s2->bits[0];
          _sbtMantissa(&res, s1);
          _setBitInt(&(res.bits[3]), 31, 0);
          s1->bits[3] = res.bits[3];
          s1->bits[2] = res.bits[2];
          s1->bits[1] = res.bits[1];
          s1->bits[0] = res.bits[0];
        } else {
          s1->bits[3] = 0;
          s1->bits[2] = 0;
          s1->bits[1] = 0;
          s1->bits[0] = 0;
        }
      } else if ((_getBitInt(&(s1->bits[3]), 31)) == 1 &&
                 (_getBitInt(&(s2->bits[3]), 31)) == 1) {
        if ((_addMantissa(s1, s2)) == 1) {
          flag = 2;
        }
        if (flag == 0) {
          _setBitInt(&(s1->bits[3]), 31, 1);
        }
      }
    } else {
      s1->bits[3] = s2->bits[3];
      s1->bits[2] = s2->bits[2];
      s1->bits[1] = s2->bits[1];
      s1->bits[0] = s2->bits[0];
    }
  }
  return flag;
}
