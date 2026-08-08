#include "s21_string.h"

void skip_whitespace(const char **str) {
  while (isspace(**str)) {
    (*str)++;
  }
}
void s21_sscanf_width(const char **format, Arguments *arg) {
  if (isdigit(**format)) {
    arg->is_width_set = true;
    while (isdigit(**format)) {
      arg->width = arg->width * 10 + (**format - '0');
      (*format)++;
    }
  }
}
void s21_sscanf_length(const char **format, Arguments *arg) {
  if (**format == 'l') {
    arg->is_long = true;
    (*format)++;
  } else if (**format == 'h') {
    arg->is_short = true;
    (*format)++;
  } else if (**format == 'L') {
    arg->is_long_double = true;
    (*format)++;
  }
}
int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count = 0;

  while (*format != '\0') {
    skip_whitespace(&str);

    if (*format == '%') {
      format++;
      Arguments arg = {0, false, false, false, false};

      s21_sscanf_width(&format, &arg);

      s21_sscanf_length(&format, &arg);

      switch (*format) {
        case 'd':
        case 'u':
        case 'c':
        case 's':
        case 'f':
        case 'x':
        case 'X':
        case 'o':
        case 'g':
        case 'G':
        case 'p':
          process_format_specifier(&str, &format, &args, arg);
          count++;
          break;
        case '*':
          skip_value(&str, &format);
          break;
      }
    }
    format++;
  }

  va_end(args);
  return count;
}

void skip_value(const char **str, const char **format) {
  while (**format != '\0' && **format != '%') {
    (*str)++;
    (*format)++;
  }
}

void process_format_specifier(const char **str, const char **format,
                              va_list *args, Arguments arg) {
  switch (**format) {
    case 'd':
      s21_sscanf_d(str, args, arg);
      break;
    case 'u':
      s21_sscanf_u(str, args, arg);
      break;
    case 'c':
      s21_sscanf_c(str, args);
      break;
    case 's':
      s21_sscanf_s(str, args, arg);
      break;
    case 'f':
      s21_sscanf_f(str, args, arg);
      break;
    case 'x':
    case 'X':
      s21_sscanf_x(str, args, arg);
      break;
    case 'o':
      s21_sscanf_o(str, args, arg);
      break;
    case 'p':
      s21_sscanf_p(str, args);
      break;
  }
}

void s21_sscanf_d(const char **str, va_list *args, Arguments arg) {
  int value = 0;
  int len = 0;
  int sign = 1;

  skip_whitespace(str);
  if (**str == '-') {
    sign = -1;
    (*str)++;
  }

  while (isdigit(**str) && (arg.is_width_set ? len < arg.width : true)) {
    value = value * 10 + (**str - '0');
    (*str)++;
    len++;
  }

  if (len > 0) {
    int *num = va_arg(*args, int *);
    *num = value * sign;
  }
}

void s21_sscanf_c(const char **str, va_list *args) {
  char c = '\0';
  if (**str != '\0' && !isspace(**str)) {
    c = **str;
    (*str)++;
  }

  char *ch = va_arg(*args, char *);
  *ch = c;
}

void s21_sscanf_s(const char **str, va_list *args, Arguments arg) {
  char *str_ptr = va_arg(*args, char *);
  int len = 0;

  skip_whitespace(str);

  while (**str && (arg.is_width_set ? len < arg.width : true) &&
         !isspace(**str)) {
    str_ptr[len++] = **str;
    (*str)++;
  }
  str_ptr[len] = '\0';
}

void s21_sscanf_f(const char **str, va_list *args, Arguments arg) {
  double value = 0.0;
  int sign = 1;
  if (**str == '-') {
    sign = -1;
    (*str)++;
  }

  int len = 0;
  while (isdigit(**str) && (arg.is_width_set ? len < arg.width : true)) {
    value = value * 10 + (**str - '0');
    (*str)++;
    len++;
  }

  if (**str == '.') {
    (*str)++;
    double factor = 0.1;
    while (isdigit(**str) && (arg.is_width_set ? len < arg.width : true)) {
      value += (**str - '0') * factor;
      factor /= 10.0;
      (*str)++;
      len++;
    }
  }

  value *= sign;
  double *num = va_arg(*args, double *);
  *num = value;
}

void s21_sscanf_u(const char **str, va_list *args, Arguments arg) {
  unsigned int value = 0;
  int len = 0;
  int sign = 1;

  skip_whitespace(str);
  if (**str == '-') {
    sign = -1;
    (*str)++;
  }

  while (isdigit(**str) && (arg.is_width_set ? len < arg.width : true)) {
    value = value * 10 + (**str - '0');
    (*str)++;
    len++;
  }

  if (len > 0) {
    unsigned int *num = va_arg(*args, unsigned int *);
    *num = value * sign;
  }
}

void s21_sscanf_x(const char **str, va_list *args, Arguments arg) {
  unsigned int value = 0;
  int len = 0;

  skip_whitespace(str);
  if (**str == '0') {
    (*str)++;
    if (**str == 'x' || **str == 'X') {
      (*str)++;
    }
  }
  while (isxdigit(**str) && (arg.is_width_set ? len < arg.width : true)) {
    char c = **str;
    if (isdigit(c)) {
      value = value * 16 + (c - '0');
    } else if (c >= 'a' && c <= 'f') {
      value = value * 16 + (c - 'a' + 10);
    } else if (c >= 'A' && c <= 'F') {
      value = value * 16 + (c - 'A' + 10);
    }
    (*str)++;
    len++;
  }

  unsigned int *num = va_arg(*args, unsigned int *);
  *num = value;
}

void s21_sscanf_o(const char **str, va_list *args, Arguments arg) {
  unsigned int value = 0;
  int len = 0;

  skip_whitespace(str);

  while (**str >= '0' && **str <= '7' &&
         (arg.is_width_set ? len < arg.width : true)) {
    value = value * 8 + (**str - '0');
    (*str)++;
    len++;
  }

  unsigned int *num = va_arg(*args, unsigned int *);
  *num = value;
}

void s21_sscanf_p(const char **str, va_list *args) {
  unsigned long num = 0;
  int len = 0;
  int base = 16;

  skip_whitespace(str);

  if (**str == '0') {
    (*str)++;
    if (**str == 'x' || **str == 'X') {
      (*str)++;
    }
  }

  while (isxdigit(**str)) {
    char c = **str;
    if (isdigit(c)) {
      num = num * base + (c - '0');
    } else if (c >= 'a' && c <= 'f') {
      num = num * base + (c - 'a' + 10);
    } else if (c >= 'A' && c <= 'F') {
      num = num * base + (c - 'A' + 10);
    }
    (*str)++;
    len++;
  }

  void **ptr = va_arg(*args, void **);
  *ptr = (void *)num;
}
