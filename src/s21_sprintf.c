#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  s21_size_t i_format = 0;
  s21_size_t i_str = 0;
  va_list args;
  va_start(args, format);

  while (i_format < s21_strlen(format)) {
    if (format[i_format] == '%') {
      switch_flags(&args, str, &i_str, &i_format, format);
    } else {
      str[i_str] = format[i_format];
      i_format++;
      i_str++;
    }
  }
  str[i_str] = 0;
  va_end(args);
  return i_str;
}

void switch_flags(va_list *args, char *str, s21_size_t *i_str,
                  s21_size_t *i_format, const char *format) {
  Flags flag = {false, false, false, false, false, false, false, false};

  int counter_switch = 1;
  add_flags(i_format, format, &flag, &counter_switch);

  if (!flag.sprint_null && format[*i_format + counter_switch] >= '1' &&
      format[*i_format + counter_switch] <= '9' && !flag.point) {
    flag.width = true;
  }
  if (format[*i_format + counter_switch - 1] == '0' &&
      !(format[*i_format + counter_switch] >= '1' &&
        format[*i_format + counter_switch] <= '9')) {
    flag.sprint_null = false;
    flag.width = true;
    counter_switch--;
  }

  if (format[*i_format + counter_switch +
             counter_null_width(i_format, format, &counter_switch)] == '.') {
    flag.point = true;
  }

  switch_spec(args, str, i_str, i_format, format, flag, &counter_switch);
  counter_switch++;
  *i_format += counter_switch;
}

void add_flags(const s21_size_t *i_format, const char *format, Flags *flag,
               int *counter_switch) {
  while (format[*i_format + *counter_switch] == ' ' ||
         format[*i_format + *counter_switch] == '+' ||
         format[*i_format + *counter_switch] == '0' ||
         format[*i_format + *counter_switch] == '.' ||
         format[*i_format + *counter_switch] == '-' ||
         format[*i_format + *counter_switch] == 'h' ||
         format[*i_format + *counter_switch] == 'l') {
    switch (format[*i_format + *counter_switch]) {
      case ' ':
        flag->space = true;
        (*counter_switch)++;
        break;
      case '+':
        flag->sign = true;
        (*counter_switch)++;
        break;
      case '0':
        flag->sprint_null = true;
        (*counter_switch)++;
        break;
      case '-':
        flag->minus = true;
        (*counter_switch)++;
        break;
      case '.':
        flag->point = true;
        (*counter_switch)++;
        break;
      case 'h':
        flag->h = true;
        (*counter_switch)++;
        break;
      case 'l':
        flag->l = true;
        (*counter_switch)++;
        break;
    }
  }
}

void switch_spec(va_list *args, char *str, s21_size_t *i_str,
                 s21_size_t *i_format, const char *format, Flags flag,
                 int *counter_switch) {
  int counter_null_width_tmp = 0;
  if (flag.sprint_null || flag.width || flag.point) {
    counter_null_width_tmp =
        counter_null_width(i_format, format, counter_switch);
    *i_format += counter_null_width_tmp;
  }
  add_spec(args, str, i_str, i_format, format, flag, counter_switch,
           &counter_null_width_tmp);
}

void space(char *str, s21_size_t *i_str) {
  str[*i_str] = ' ';
  (*i_str)++;
}

void sign(char *str, s21_size_t *i_str) {
  str[*i_str] = '+';
  (*i_str)++;
}

void add_spec(va_list *args, char *str, s21_size_t *i_str, s21_size_t *i_format,
              const char *format, Flags flag, int *counter_switch,
              int *counter_null_width_tmp) {
  if (format[*i_format + *counter_switch] == 'd')
    s21_sprintf_d(args, str, i_str, 0, false, flag, counter_switch, i_format,
                  format, counter_null_width_tmp);
  else if (format[*i_format + *counter_switch] == 'c')
    s21_sprintf_c(args, str, i_str, i_format, format, counter_switch,
                  counter_null_width_tmp, flag);
  else if (format[*i_format + *counter_switch] == 's')
    s21_sprintf_s(args, str, i_str, i_format, format, counter_switch,
                  counter_null_width_tmp, flag);
  else if (format[*i_format + *counter_switch] == 'u')
    s21_sprintf_u(args, str, i_str, flag, i_format, format, counter_switch,
                  counter_null_width_tmp);
  else if (format[*i_format + *counter_switch] == 'f')
    s21_sprintf_f(args, str, i_str, 0, false, flag, i_format, format,
                  counter_switch, counter_null_width_tmp, false);
  else if (format[*i_format + *counter_switch] == 'o')
    s21_sprintf_o(args, str, i_str, flag, i_format, format, counter_switch,
                  counter_null_width_tmp);
  else if (format[*i_format + *counter_switch] == 'x' ||
           format[*i_format + *counter_switch] == 'X')
    s21_sprintf_x(args, str, i_str,
                  (format[*i_format + *counter_switch] == 'x' ? false : true),
                  flag, i_format, format, counter_switch,
                  counter_null_width_tmp);
  else if (format[*i_format + *counter_switch] == 'e' ||
           format[*i_format + *counter_switch] == 'E')
    s21_sprintf_e(args, str, i_str,
                  (format[*i_format + *counter_switch] == 'e' ? false : true),
                  flag, counter_switch, i_format, format,
                  counter_null_width_tmp, false, 0.0);
  else if (format[*i_format + *counter_switch] == 'g' ||
           format[*i_format + *counter_switch] == 'G')
    s21_sprintf_g(args, str, i_str,
                  (format[*i_format + *counter_switch] == 'g' ? false : true),
                  flag, counter_switch, i_format, format,
                  counter_null_width_tmp);
}

int counter_null_width(const s21_size_t *i_format, const char *format,
                       const int *counter_switch) {
  int result = 1;
  while (format[*i_format + *counter_switch + result] >= '0' &&
         format[*i_format + *counter_switch + result] <= '9') {
    result++;
  }
  return result;
}

int read_null_width(const s21_size_t *i_format, const char *format,
                    int *counter_switch) {
  int result = 0;
  int multiplier = 1;
  char digitals[100] = {0};
  int i_digitals = -1;
  while (format[*i_format + *counter_switch] >= '0' &&
         format[*i_format + *counter_switch] <= '9') {
    i_digitals++;
    digitals[i_digitals] = format[*i_format + *counter_switch];
    (*counter_switch)++;
  }
  while (i_digitals != -1) {
    result += ((int)(digitals[i_digitals] - '0')) * multiplier;
    multiplier *= 10;
    i_digitals--;
  }
  return result;
}

void add_nulls_width(char *str, s21_size_t *i_str, int *digitals,
                     const s21_size_t *container, Flags flag) {
  while ((s21_size_t)*digitals > *container) {
    if (flag.sprint_null || flag.point) str[*i_str] = '0';
    if (flag.width) str[*i_str] = ' ';
    (*i_str)++;
    (*digitals)--;
  }
}

void s21_sprintf_d(va_list *args, char *str, s21_size_t *i_str,
                   const int *num_e, bool spec_e, Flags flag,
                   int *counter_switch, s21_size_t *i_format,
                   const char *format, const int *counter_null_width_tmp) {
  if (flag.sprint_null || flag.width || flag.point)
    *i_format -= *counter_null_width_tmp;

  long int num = 0;
  int digitals = -1;
  s21_size_t container = 0;
  bool minus = false;

  if (flag.sign && flag.width && !spec_e) container++;
  if (!spec_e)
    num = va_arg(*args, long int);
  else {
    if (num_e != s21_NULL) num = *num_e;
  }
  if (!flag.l) num = (int)num;
  if (flag.h) num = (short int)num;

  if (flag.space && num >= 0 && !flag.width && !spec_e) space(str, i_str);
  if (flag.sprint_null || flag.width || flag.point) {
    digitals = read_null_width(i_format, format, counter_switch);
  }
  if (num == 0 && ((digitals != 0 && flag.point) || !flag.point)) {
    s21_sprintf_d_null(str, i_str, spec_e, flag, &digitals);
  } else {
    s21_sprintf_d_not_null(str, i_str, spec_e, flag, &num, &digitals,
                           &container, &minus);
  }
  if (flag.point && flag.width) (*counter_switch)++;
}

void s21_sprintf_d_null(char *str, s21_size_t *i_str, bool spec_e, Flags flag,
                        int *digitals) {
  s21_size_t container = 1;
  if (((flag.sprint_null || flag.width) && !flag.minus) || flag.point)
    add_nulls_width(str, i_str, digitals, &container, flag);
  if (flag.sign && !spec_e) sign(str, i_str);
  str[*i_str] = '0';
  (*i_str)++;
  if ((flag.sprint_null || flag.width) && flag.minus)
    add_nulls_width(str, i_str, digitals, &container, flag);
}

void s21_sprintf_d_not_null(char *str, s21_size_t *i_str, bool spec_e,
                            Flags flag, long int *num, int *digitals,
                            s21_size_t *container, bool *minus) {
  if (*num < 0) {
    *minus = true;
    *num = labs(*num);
    if (flag.sprint_null || flag.width) (*container)++;
  }
  char change_num[1000] = {0};
  int counter = -1;
  while (*num > 0) {
    counter++;
    change_num[counter] = *num % 10 + '0';
    *num = *num / 10;
    if (flag.sprint_null || flag.width || flag.point) (*container)++;
  }
  if (flag.width && !flag.minus && !flag.point)
    add_nulls_width(str, i_str, digitals, container, flag);
  if (flag.sign && !(*minus) && !spec_e) sign(str, i_str);
  if (*minus) {
    str[*i_str] = '-';
    (*i_str)++;
  }
  if ((flag.point || flag.sprint_null) && !flag.width)
    add_nulls_width(str, i_str, digitals, container, flag);
  while (counter != -1) {
    str[*i_str] = change_num[counter];
    counter--;
    (*i_str)++;
  }
  if ((flag.sprint_null || flag.width) && flag.minus && !flag.point)
    add_nulls_width(str, i_str, digitals, container, flag);
}

void width_char(s21_size_t *i_format, const char *format, int *counter_switch,
                const int *counter_null_width_tmp, Flags flag, char *str,
                s21_size_t *i_str, s21_size_t container) {
  int digitals = 0;
  *i_format -= *counter_null_width_tmp;
  digitals = read_null_width(i_format, format, counter_switch);
  add_nulls_width(str, i_str, &digitals, &container, flag);
}

void s21_sprintf_c(va_list *args, char *str, s21_size_t *i_str,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp,
                   Flags flag) {
  if (!flag.minus && flag.width)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, 1);
  char symbol;
  wchar_t big_symbol;
  if (flag.l) {
    big_symbol = va_arg(*args, wchar_t);
    mbstowcs(&big_symbol, &symbol, 1);
    str[*i_str] = big_symbol;
  } else {
    symbol = (char)va_arg(*args, int);
    str[*i_str] = symbol;
  }
  (*i_str)++;
  if (flag.minus && flag.width)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, 1);
}

void s21_sprintf_s(va_list *args, char *str, s21_size_t *i_str,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp,
                   Flags flag) {
  char *s = va_arg(*args, char *);
  s21_size_t length = s21_strlen(s);
  s21_sprintf_save_s(str, i_str, i_format, format, counter_switch,
                     counter_null_width_tmp, flag, s, false);

  if (flag.width && flag.minus)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, length);
}

void s21_sprintf_save_s(char *str, s21_size_t *i_str, s21_size_t *i_format,
                        const char *format, int *counter_switch,
                        int *counter_null_width_tmp, Flags flag, char *s,
                        bool spec_e) {
  s21_size_t length = s21_strlen(s);
  int counter_string = -1;
  if (flag.width && !flag.minus && !spec_e)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, length);
  if (flag.point && !spec_e) {
    *i_format -= *counter_null_width_tmp;
    counter_string = read_null_width(i_format, format, counter_switch);
  }
  while (*s && counter_string != 0) {
    str[*i_str] = *s;
    (*i_str)++;
    s++;
    counter_string--;
  }
}

void s21_sprintf_f(va_list *args, char *str, s21_size_t *i_str,
                   const double *num_e, bool spec_e, Flags flag,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp,
                   bool spec_g) {
  double num;
  bool minus = false;
  bool num_null = false;
  bool first_null = false;
  if (!spec_e)
    num = va_arg(*args, double);
  else
    num = *num_e;
  s21_size_t container = 0;
  if (flag.space && num >= 0 && !flag.width && !spec_e) space(str, i_str);
  if (flag.sign && num >= 0 && flag.width && !spec_g) container++;
  if (num == 0) {
    container++;
    num_null = true;
  }
  if (num < 0) {
    num = fabs(num);
    minus = true;
    if (flag.width) container++;
  }
  double i_num = (int)num;
  if (!i_num) first_null = true;
  double d_num = num - i_num;
  char change_num[1000] = {0};
  int counter = -1;
  int counter_double = 6;

  if (flag.point) {
    *i_format -= *counter_null_width_tmp;
    counter_double = read_null_width(i_format, format, counter_switch);
  }
  while ((int)i_num > 0) {
    counter++;
    change_num[counter] = (int)i_num % 10 + '0';
    i_num = (int)i_num / 10;
    container++;
  }
  if (spec_e && spec_g) counter_double -= 1;
  s21_sprintf_f_save(str, i_str, flag, i_format, format, counter_switch,
                     counter_null_width_tmp, &counter_double, minus, num_null,
                     first_null, &counter, &d_num, change_num, &container,
                     spec_g);
}

void s21_sprintf_f_save(char *str, s21_size_t *i_str, Flags flag,
                        s21_size_t *i_format, const char *format,
                        int *counter_switch, int *counter_null_width_tmp,
                        int *counter_double, bool minus, bool num_null,
                        bool first_null, int *counter, double *d_num,
                        const char *change_num, const s21_size_t *container,
                        bool spec_g) {
  int container_g = 6;
  if (flag.point && spec_g) {
    *i_format -= *counter_null_width_tmp;
    container_g = read_null_width(i_format, format, counter_switch);
  }

  if (flag.width && !flag.minus)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, *container + *counter_double + 1);
  int counter_double_minus = *counter_double;
  bool null_g = false;
  if (num_null && spec_g) null_g = true;
  if (minus) {
    str[*i_str] = '-';
    (*i_str)++;
  }
  if (!minus && flag.sign) sign(str, i_str);
  if (num_null || first_null) {
    str[*i_str] = '0';
    (*i_str)++;
  }
  while (*counter != -1) {
    str[*i_str] = change_num[*counter];
    (*counter)--;
    (*i_str)++;
    if (spec_g) container_g--;
  }

  if (*counter_double > 0 && container_g > 0 && !null_g &&
      !(spec_g && !(*d_num > 0))) {
    str[*i_str] = '.';
    (*i_str)++;
  }

  while (*d_num > 0 && *counter_double != 0 && container_g && !null_g) {
    s21_sprintf_f_point(d_num, counter_double, str, i_str, &container_g,
                        spec_g);
  }

  while (*counter_double && !spec_g) {
    str[*i_str] = '0';
    (*i_str)++;
    if (!spec_g) (*counter_double)--;
  }

  if (flag.width && flag.minus)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, *container + counter_double_minus + 1);
}

void s21_sprintf_f_point(double *d_num, int *counter_double, char *str,
                         s21_size_t *i_str, int *container_g, bool spec_g) {
  *d_num *= 10;
  double check_num = fmod(*d_num, 1.0);
  if (check_num >= 0.5 && check_num < 0.999 && *counter_double != 1) {
    str[*i_str] = (int)floor(*d_num) + '0';
    *d_num = *d_num - (int)floor(*d_num);
  } else {
    str[*i_str] = (int)round(*d_num) + '0';
    *d_num = *d_num - (int)round(*d_num);
  }
  (*i_str)++;
  if (!spec_g) (*counter_double)--;
  if (spec_g) (*container_g)--;
}

void s21_sprintf_u(va_list *args, char *str, s21_size_t *i_str, Flags flag,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp) {
  unsigned long int num = va_arg(*args, unsigned long int);
  if (!flag.l) num = (unsigned int)num;
  if (flag.h) num = (unsigned short int)num;
  if (flag.space && !flag.width) space(str, i_str);
  if (num == 0 &&
      ((read_null_width(i_format, format, counter_switch) != 0 && flag.point) ||
       !flag.point)) {
    if ((flag.width && !flag.minus) || flag.point)
      width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
                 str, i_str, 1);
    str[*i_str] = '0';
    (*i_str)++;
    if (flag.width && flag.minus)
      width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
                 str, i_str, 1);
  } else {
    s21_sprintf_u_not_null(str, i_str, flag, i_format, format, counter_switch,
                           counter_null_width_tmp, &num);
  }
}

void s21_sprintf_u_not_null(char *str, s21_size_t *i_str, Flags flag,
                            s21_size_t *i_format, const char *format,
                            int *counter_switch, int *counter_null_width_tmp,
                            unsigned long int *num) {
  char change_num[1000] = {0};
  int counter = -1;
  int container = 0;
  while (*num > 0) {
    counter++;
    change_num[counter] = *num % 10 + '0';
    *num = *num / 10;
    container++;
  }
  if ((flag.width && !flag.minus) || flag.point)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, container);
  while (counter != -1) {
    str[*i_str] = change_num[counter];
    counter--;
    (*i_str)++;
  }
  if (flag.width && flag.minus)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, container);
}

void s21_sprintf_x(va_list *args, char *str, s21_size_t *i_str, bool upper,
                   Flags flag, s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp) {
  unsigned long int num = va_arg(*args, unsigned long int);
  if (!flag.l) num = (unsigned int)num;
  if (flag.h) num = (unsigned short int)num;
  if (num == 0 &&
      ((read_null_width(i_format, format, counter_switch) != 0 && flag.point) ||
       !flag.point)) {
    if ((flag.width && !flag.minus) || flag.point)
      width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
                 str, i_str, 1);
    str[*i_str] = '0';
    (*i_str)++;
    if (flag.width && flag.minus)
      width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
                 str, i_str, 1);
  } else {
    s21_sprintf_x_not_null(str, i_str, upper, flag, i_format, format,
                           counter_switch, counter_null_width_tmp, &num);
  }
}

void s21_sprintf_x_not_null(char *str, s21_size_t *i_str, bool upper,
                            Flags flag, s21_size_t *i_format,
                            const char *format, int *counter_switch,
                            int *counter_null_width_tmp,
                            unsigned long int *num) {
  char change_num[1000] = {0};
  int counter = -1;
  int x = 87;
  int container = 0;
  if (upper) x = 55;
  while (*num > 0) {
    counter++;
    if (*num % 16 < 10)
      change_num[counter] = *num % 16 + '0';
    else
      change_num[counter] = *num % 16 + x;
    *num /= 16;
    container++;
  }
  if ((flag.width && !flag.minus) || flag.point)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, container);
  while (counter != -1) {
    str[*i_str] = change_num[counter];
    counter--;
    (*i_str)++;
  }
  if (flag.width && flag.minus)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, container);
}

void s21_sprintf_e(va_list *args, char *str, s21_size_t *i_str, bool upper,
                   Flags flag, int *counter_switch, s21_size_t *i_format,
                   const char *format, int *counter_null_width_tmp, bool spec_g,
                   double num_g) {
  double num;
  if (!spec_g)
    num = va_arg(*args, double);
  else
    num = num_g;
  int container = 0;

  if (flag.space && num >= 0) space(str, i_str);
  if (flag.sign && num >= 0 && !spec_g) container++;
  if (num == 0) {
    char null_e[] = {'0', '.', '0', '0', '0', '0', '0',
                     '0', 'E', '+', '0', '0', '\0'};
    if (!upper) null_e[8] = 'e';
    if (flag.width)
      width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
                 str, i_str, container + 12);

    if (flag.sign) sign(str, i_str);
    s21_sprintf_save_s(str, i_str, i_format, format, counter_switch,
                       counter_null_width_tmp, flag, null_e, true);

  } else {
    s21_sprintf_e_not_null(args, str, i_str, upper, flag, counter_switch,
                           i_format, format, counter_null_width_tmp, &num,
                           spec_g);
  }
}

void s21_sprintf_e_not_null(va_list *args, char *str, s21_size_t *i_str,
                            bool upper, Flags flag, int *counter_switch,
                            s21_size_t *i_format, const char *format,
                            int *counter_null_width_tmp, double *num,
                            bool spec_g) {
  double c = fabs(*num);
  int counter_to_min = 0;
  int counter_to_max = 0;
  while (c > 9 || c < 1) {
    if (c < 1) {
      c *= 10;
      *num *= 10;
      counter_to_max++;
    } else {
      c /= 10;
      *num /= 10;
      counter_to_min++;
    }
  }
  if (counter_to_max == 0) {
    double control_num = 1.0;
    control_num = control_num * pow(10, 6);
    if (*num > 0) *num = (int)((*num * control_num) + 0.5);
    if (*num < 0) *num = (int)((*num * control_num) - 0.5);
    *num = *num / control_num;
  }
  s21_sprintf_f(args, str, i_str, num, true, flag, i_format, format,
                counter_switch, counter_null_width_tmp, spec_g);
  if (upper)
    str[*i_str] = 'E';
  else
    str[*i_str] = 'e';
  if (counter_to_max == 0)
    str[*i_str + 1] = '+';
  else
    str[*i_str + 1] = '-';
  *i_str += 2;
  if (counter_to_min < 10) {
    str[*i_str] = '0';
    (*i_str)++;
  }
  if (counter_to_max == 0)
    s21_sprintf_d(args, str, i_str, &counter_to_min, true, flag, counter_switch,
                  i_format, format, 0);
  else
    s21_sprintf_d(args, str, i_str, &counter_to_max, true, flag, counter_switch,
                  i_format, format, 0);
}

void s21_sprintf_o(va_list *args, char *str, s21_size_t *i_str, Flags flag,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp) {
  unsigned long int num = va_arg(*args, unsigned long int);

  if (!flag.l) num = (unsigned int)num;
  if (flag.h) num = (unsigned short int)num;

  if (num == 0 &&
      ((read_null_width(i_format, format, counter_switch) != 0 && flag.point) ||
       !flag.point)) {
    if ((flag.width || flag.point) && !flag.minus)
      width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
                 str, i_str, 1);
    str[*i_str] = '0';
    (*i_str)++;
    if (flag.width && flag.minus)
      width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
                 str, i_str, 1);
  } else {
    s21_sprintf_o_not_null(str, i_str, flag, i_format, format, counter_switch,
                           counter_null_width_tmp, &num);
  }
}

void s21_sprintf_o_not_null(char *str, s21_size_t *i_str, Flags flag,
                            s21_size_t *i_format, const char *format,
                            int *counter_switch, int *counter_null_width_tmp,
                            unsigned long int *num) {
  char change_num[1000] = {0};
  int counter = -1;
  int container = 0;
  while (*num > 0) {
    counter++;
    change_num[counter] = *num % 8 + '0';
    *num /= 8;
    container++;
  }
  if ((flag.width || flag.point) && !flag.minus)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, container);
  while (counter != -1) {
    str[*i_str] = change_num[counter];
    counter--;
    (*i_str)++;
  }
  if (flag.width && flag.minus)
    width_char(i_format, format, counter_switch, counter_null_width_tmp, flag,
               str, i_str, container);
}

void s21_sprintf_g(va_list *args, char *str, s21_size_t *i_str, bool upper,
                   Flags flag, int *counter_switch, s21_size_t *i_format,
                   const char *format, int *counter_null_width_tmp) {
  double num = va_arg(*args, double);
  if ((fabs(num) < 0.0001 || fabs(num) >= 1000000) && num != 0)
    s21_sprintf_e(args, str, i_str, upper, flag, counter_switch, i_format,
                  format, counter_null_width_tmp, true, num);

  else
    s21_sprintf_f(args, str, i_str, &num, true, flag, i_format, format,
                  counter_switch, counter_null_width_tmp, true);
}
