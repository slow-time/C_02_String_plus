#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_memchr_test) {
  char *src = "check! some str";
  ck_assert_str_eq(memchr(src, '!', 10), s21_memchr(src, '!', 10));
  ck_assert_ptr_eq(memchr(src, 'l', 1), s21_memchr(src, 'l', 1));
  ck_assert_ptr_eq(memchr(src, 'l', 16), s21_memchr(src, 'l', 16));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char *str1 = "equals str";
  char *str2 = "equals str";
  ck_assert(memcmp(str1, str2, 6) == s21_memcmp(str1, str2, 6));
  ck_assert(s21_memcmp("NOT EQUALS", "EQUALS", 5) != 0);
}
END_TEST

START_TEST(s21_memcpy_test) {
  const char *src = "Copies n characters from src to dest";
  size_t l = strlen(src);
  char dest[50] = "";
  ck_assert_str_eq(memcpy(dest, src, l), s21_memcpy(dest, src, l));
  ck_assert_str_eq(memcpy(dest, src, l - 5), s21_memcpy(dest, src, l - 5));
  ck_assert_str_eq(memcpy(dest, src, 0), s21_memcpy(dest, src, 0));
}
END_TEST

START_TEST(s21_memset_test) {
  size_t l1 = 0;
  s21_size_t l2 = 0;
  char str[20] = "add n c";
  ck_assert_str_eq(s21_memset(str, 's', l1), memset(str, 's', l2));
  l1 = 1;
  l2 = 1;
  ck_assert_str_eq(s21_memset(str, 's', l1), memset(str, 's', l2));
}

START_TEST(s21_strncat_test) {
  char dest1[40] = "dest str + ";
  char dest2[40] = "dest str + ";
  const char *src = "const src";
  size_t l = strlen(src);
  ck_assert_str_eq(strncat(dest1, src, 5), s21_strncat(dest2, src, 5));
  ck_assert_str_eq(strncat(dest1, "", 2), s21_strncat(dest2, "", 2));
  ck_assert_str_eq(strncat(dest1, src, l), s21_strncat(dest2, src, l));
}
END_TEST

START_TEST(s21_strchr_test) {
  char *str = "Searches for the first occurrence of the character c";
  ck_assert_ptr_null(s21_strchr(str, '!'));
  ck_assert_str_eq(strchr(str, 'f'), s21_strchr(str, 'f'));
}
END_TEST

START_TEST(s21_strncmp_test) {
  ck_assert_int_eq(strncmp("str", "str", 2), s21_strncmp("str", "str", 2));
  ck_assert_int_eq(strncmp("abc", "cbc", 4), s21_strncmp("abc", "cbc", 4));
  ck_assert_int_eq(strncmp("123", "321", 4), s21_strncmp("123", "321", 4));
}
END_TEST

START_TEST(s21_strncpy_test) {
  char dest1[20] = "abc";
  char dest2[20] = "abc";
  const char src1[20] = "111";
  const char src2[20] = "111";
  strncpy(dest1, "", 2);
  s21_strncpy(dest2, "", 2);
  ck_assert_str_eq(dest1, dest2);
  strncpy(dest1, src1, 2);
  s21_strncpy(dest2, src2, 2);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21_strcspn_test) {
  ck_assert_int_eq(s21_strcspn("123gg", "123"), strcspn("123gg", "123"));
  ck_assert_int_eq(s21_strcspn("456", "123"), strcspn("456", "123"));
}
END_TEST

START_TEST(s21_strlen_test) {
  char *str = "length of the string    ";
  ck_assert_uint_eq(strlen(str), s21_strlen(str));
  ck_assert_uint_eq(strlen(""), s21_strlen(""));
  ck_assert_uint_eq(strlen("\0"), s21_strlen("\0"));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char *str = "Finds the first character in the string str1";
  ck_assert_str_eq(strpbrk(str, "abc"), s21_strpbrk(str, "abc"));
  ck_assert_ptr_null(s21_strpbrk(str, "!"));
  ck_assert_ptr_null(s21_strpbrk(str, ""));
}
END_TEST

START_TEST(s21_strrchr_test) {
  char *str = "Searches for the last occurrence of the character";
  ck_assert_str_eq(strrchr(str, 'c'), s21_strrchr(str, 'c'));
  ck_assert_str_eq(strrchr(str, '\0'), s21_strrchr(str, '\0'));
  ck_assert_ptr_null(s21_strrchr(str, '!'));
}
END_TEST

START_TEST(s21_strstr_test) {
  char *str = "Finds the first occurrence of the entire string needle";
  ck_assert_ptr_eq(strstr(str, ""), s21_strstr(str, ""));
  ck_assert_str_eq(strstr(str, " first"), s21_strstr(str, " first"));
}
END_TEST

START_TEST(s21_strtok_several_tokens_test) {
  char str[] = "tokens! separated by delim";
  char *token_str[] = {"tokens", "separated", "by", "delim"};
  const char *delim = " ,.!";
  char *token;
  token = s21_strtok(str, delim);
  for (size_t i = 0; i < (sizeof(token_str) / sizeof(token_str[0])); i++) {
    ck_assert_str_eq(token_str[i], token);
    token = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(s21_strtok(NULL, delim));
}
END_TEST

START_TEST(s21_strtok_not_found_token_test) {
  char *str = "\0";
  ck_assert_ptr_null(s21_strtok(str, "!"));
}
END_TEST

START_TEST(s21_strtok_one_token_test) {
  char *s21_str = "separated";
  char *str = "separated";
  char *delim = "s";
  ck_assert_pstr_eq(s21_strtok(s21_str, delim), strtok(str, delim));
}
END_TEST

START_TEST(s21_to_upper_test_1) {
  char *expected = "CONVERTED!123";
  char *s21_buf = s21_to_upper("conVERTed!123");
  ck_assert_str_eq(s21_buf, expected);
  if (s21_buf != NULL) free(s21_buf);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  char *s21_buf = s21_to_upper(NULL);
  ck_assert_ptr_null(s21_buf);
  if (s21_buf != NULL) free(s21_buf);
}
END_TEST

START_TEST(s21_to_upper_test_3) {
  char *s21_buf = s21_to_upper("");
  ck_assert_str_eq(s21_buf, "");
  if (s21_buf != NULL) free(s21_buf);
}
END_TEST

START_TEST(s21_to_lower_test_1) {
  char expected[100] = "converted to lowercase!";
  char *s21_buf = s21_to_lower("CONVERTED TO lowercase!");
  ck_assert_str_eq(s21_buf, expected);
  free(s21_buf);
}
END_TEST

START_TEST(s21_to_lower_test_2) {
  char *s21_buf = s21_to_lower(NULL);
  ck_assert_ptr_null(s21_buf);
  if (s21_buf != NULL) free(s21_buf);
}
END_TEST

START_TEST(s21_to_lower_test_3) {
  char *s21_buf = s21_to_lower("\0");
  ck_assert_str_eq(s21_buf, "\0");
  free(s21_buf);
}
END_TEST

START_TEST(s21_insert_test_1) {
  char *expected = "inserted str";
  char *src = "inserted str";
  char *actual = s21_insert(src, "\0", 3);
  ck_assert_str_eq(actual, expected);
  if (actual != NULL) free(actual);
}
END_TEST

START_TEST(s21_insert_test_2) {
  char *expected = "NEW inserted str";
  char *src = "inserted str";
  char *str = "NEW ";
  char *actual = s21_insert(src, str, 0);
  ck_assert_str_eq(actual, expected);
  free(actual);
}
END_TEST

START_TEST(s21_insert_test_3) {
  char *src = "inserted";
  char *actual = s21_insert(src, NULL, 5);
  ck_assert_str_eq(actual, "inserted");
  free(actual);
}
END_TEST

START_TEST(s21_trim_test_1) {
  char *src = " !!! trim  !!! ";
  char *trim_chars = " !";
  char *actual = s21_trim(src, trim_chars);
  char *expected = "trim";
  ck_assert_str_eq(actual, expected);
  if (actual != NULL) free(actual);
}
END_TEST

START_TEST(s21_trim_test_2) {
  char *src = "t r i m ";
  char *trim_chars = "123";
  char *actual = s21_trim(src, trim_chars);
  char *expected = "t r i m ";
  ck_assert_str_eq(actual, expected);
  if (actual != NULL) free(actual);
}
END_TEST

START_TEST(s21_trim_test_3) {
  char *src = " t r i m       ";
  char *actual = s21_trim(src, NULL);
  char *expected = "t r i m";
  ck_assert_str_eq(actual, expected);
  if (actual != NULL) free(actual);
}
END_TEST

START_TEST(s21_trim_test_4) {
  char *src = " ";
  char *actual = s21_trim(src, "");
  ck_assert_str_eq(actual, "");
  if (actual != NULL) free(actual);
}
END_TEST

START_TEST(s21_trim_test_5) {
  char *actual = s21_trim(NULL, NULL);
  ck_assert_ptr_null(actual);
  if (actual != NULL) free(actual);
}
END_TEST

START_TEST(s21_strerror_1) {
  int n = 0;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST

START_TEST(s21_strerror_2) {
  int n = 88;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(s21_strerror_3) {
  int n = 53;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(s21_strerror_4) {
  int n = 101;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

START_TEST(s21_strerror_5) {
  int n = 10;
  ck_assert_str_eq(s21_strerror(n), strerror(n));
}
END_TEST

// SPRINTF START

START_TEST(s21_sprintf_test_d) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%d \n %d \n %d,";
  int a = 63763;
  int b = 0;
  int c = -5423423;
  ck_assert_int_eq(sprintf(str_spr, format, a, b, c),
                   s21_sprintf(str_s21, format, a, b, c));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%f \n %f \n %f,%f, %f";
  float a = 5254.54363763;
  float b = 0;
  float c = -542.05;
  float d = 32.4545653;
  ck_assert_int_eq(sprintf(str_spr, format, a, b, c, d, 0.432),
                   s21_sprintf(str_s21, format, a, b, c, d, 0.432));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%s!";
  char *str = "Hello darkness my old friend";
  ck_assert_int_eq(sprintf(str_spr, format, str),
                   s21_sprintf(str_s21, format, str));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%c \n %c \n %c";
  int a = 53;
  char b = 'p';
  int c = -17;
  ck_assert_int_eq(sprintf(str_spr, format, a, b, c),
                   s21_sprintf(str_s21, format, a, b, c));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%u \n %u \n %u";
  int a = 53;
  int b = -425;
  int c = 58475;
  ck_assert_int_eq(sprintf(str_spr, format, a, b, c),
                   s21_sprintf(str_s21, format, a, b, c));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%x \n %x \n %x";
  int a = 56326;
  int b = 425;
  int c = 0;
  ck_assert_int_eq(sprintf(str_spr, format, a, b, c),
                   s21_sprintf(str_s21, format, a, b, c));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_X) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%X \n %X \n ...";
  int a = 6646;
  int b = 0;
  ck_assert_int_eq(sprintf(str_spr, format, a, b),
                   s21_sprintf(str_s21, format, a, b));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
  char str_spr[50];
  char str_s21[50];
  char *format = "%o \n %o \n %o";
  int a = 6646;
  int b = -40;
  int c = 0;
  ck_assert_int_eq(sprintf(str_spr, format, a, b, c),
                   s21_sprintf(str_s21, format, a, b, c));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_e) {
  char str_spr[100];
  char str_s21[100];
  char *format = "%e, %e, %e %e, %e";
  ck_assert_int_eq(sprintf(str_spr, format, 0.0, 4.4234234325242, 43242432.2,
                           -432432.43243245235, 0.0034),
                   s21_sprintf(str_s21, format, 0.0, 4.4234234325242,
                               43242432.2, -432432.43243245235, 0.0034));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_E) {
  char str_spr[100];
  char str_s21[100];
  char *format = "%E, %E, %E %E";
  ck_assert_int_eq(sprintf(str_spr, format, 0.0, 4.4234234325242, 43242432.2,
                           -432432.43243245235),
                   s21_sprintf(str_s21, format, 0.0, 4.4234234325242,
                               43242432.2, -432432.43243245235));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%g %g %g %g %g %g %g";
  ck_assert_int_eq(
      sprintf(str_spr, format, 0.000234, 0.3424132154125, 54543234.543, 3543.2,
              4321533.4325245235, -432.543, 0.0),
      s21_sprintf(str_s21, format, 0.000234, 0.3424132154125, 54543234.543,
                  3543.2, 4321533.4325245235, -432.543, 0.0));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_G) {
  char str_spr[100];
  char str_s21[100];
  char *format = "\n!!%G %G %G, %G\n";
  ck_assert_int_eq(
      sprintf(str_spr, format, 23.543, -4423.432, 0.0, 0.432432),
      s21_sprintf(str_s21, format, 23.543, -4423.432, 0.0, 0.432432));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_space) {
  char str_spr[100];
  char str_s21[100];
  char *format = "% d   % f% e % E";
  ck_assert_int_eq(
      sprintf(str_spr, format, 6646, 4534.76537, 4.543554, 4534.76537),
      s21_sprintf(str_s21, format, 6646, 4534.76537, 4.543554, 4534.76537));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_width_1) {
  char str_spr[100];
  char str_s21[100];
  char *format = "%11d %20f %3c %8s %2X %9x %3o %15u";
  char c = 'z';
  ck_assert_int_eq(
      sprintf(str_spr, format, 5435, 653.53, c, "hi", 542, 63, 9, 535),
      s21_sprintf(str_s21, format, 5435, 653.53, c, "hi", 542, 63, 9, 535));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_width_2) {
  char str_spr[100];
  char str_s21[100];
  char *format = "%11d %20f %2X %9x %3o %15u %e %E";
  ck_assert_int_eq(sprintf(str_spr, format, 0, 0.0, 0, 0, 0, 0, 0.0, 0.0),
                   s21_sprintf(str_s21, format, 0, 0.0, 0, 0, 0, 0, 0.0, 0.0));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_plus_1) {
  char str_spr[100];
  char str_s21[100];
  char *format = "%+d/%+d %+f/%+f %+e %+E";
  ck_assert_int_eq(
      sprintf(str_spr, format, 6254, -453, 35.4, -054.45, 1.0, 432.432),
      s21_sprintf(str_s21, format, 6254, -453, 35.4, -054.45, 1.0, 432.432));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_plus_2) {
  char str_spr[100];
  char str_s21[100];
  char *format = "%+d %+f %+e %+E";
  ck_assert_int_eq(sprintf(str_spr, format, 0, 0.0, 0.0, 0.0),
                   s21_sprintf(str_s21, format, 0, 0.0, 0.0, 0.0));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_null) {
  char str_spr[100];
  char str_s21[100];
  char *format = "\n!!%05d %06f\n";
  ck_assert_int_eq(sprintf(str_spr, format, 342, 34.34),
                   s21_sprintf(str_s21, format, 342, 34.34));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_minus_1) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%-8d/%-3d %-5f/%-15f ... %-8c %-20s, %-5u %-25o %-19X, %-4x";
  char c = 'z';
  char *str = "hello";
  ck_assert_int_eq(sprintf(str_spr, format, 6254, -453, 35.4, -054.45, c, str,
                           543, 6325, 432, 422),
                   s21_sprintf(str_s21, format, 6254, -453, 35.4, -054.45, c,
                               str, 543, 6325, 432, 422));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_minus_2) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%-8d %-15f  %-5u %-25o %-19X, %-4x";
  ck_assert_int_eq(sprintf(str_spr, format, 0, 0.0, 0, 0, 0, 0),
                   s21_sprintf(str_s21, format, 0, 0.0, 0, 0, 0, 0));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_point_1) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%.8d/%.9d %.2f/%.9f %.5u %.3o %.33X, %.9g %.10x %.0d";
  ck_assert_int_eq(sprintf(str_spr, format, 6254, -453, 35.4, -054.45, 543,
                           6325, 432, 3.432, 422, 0),
                   s21_sprintf(str_s21, format, 6254, -453, 35.4, -054.45, 543,
                               6325, 432, 3.432, 422, 0));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_point_2) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%.0o %.0u %.0x %.0X";
  ck_assert_int_eq(sprintf(str_spr, format, 0, 0, 0, 0),
                   s21_sprintf(str_s21, format, 0, 0, 0, 0));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_point_3) {
  char str_spr[300];
  char str_s21[300];
  char *str = "hello";
  char *format = "%.0s %.2s %.5s %.10s %.20s";
  ck_assert_int_eq(sprintf(str_spr, format, str, str, str, str, str),
                   s21_sprintf(str_s21, format, str, str, str, str, str));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_h) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%hd :) %ho/%hu %hX, %hx";
  ck_assert_int_eq(
      sprintf(str_spr, format, 6255234, -455343, 355356, 542264, 55542523),
      s21_sprintf(str_s21, format, 6255234, -455343, 355356, 542264, 55542523));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_l) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%ld :) %lo, %lu %lx %lX";
  ck_assert_int_eq(
      sprintf(str_spr, format, 6264536455234, 17777061643062021, 6432543543535,
              4624543523, 645654353432),
      s21_sprintf(str_s21, format, 6264536455234, 17777061643062021,
                  6432543543535, 4624543523, 645654353432));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_mix) {
  char str_spr[300];
  char str_s21[300];
  char *format = "%+-20d :) %+.8f, %+-13u";
  ck_assert_int_eq(sprintf(str_spr, format, 6264, 177.021, 6432),
                   s21_sprintf(str_s21, format, 6264, 177.021, 6432));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST

START_TEST(s21_sprintf_test_e2) {
  char str_spr[100];
  char str_s21[100];
  char *format = "%+e";
  ck_assert_int_eq(sprintf(str_spr, format, 4.4234),
                   s21_sprintf(str_s21, format, 4.4234));
  ck_assert_pstr_eq(str_spr, str_s21);
}
END_TEST
// SPRINTF END

// sscanf start

START_TEST(test_decimal_parsing) {
  char fstr[] = "%d";
  char str[] = "12345";
  int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 12345);
}
END_TEST

START_TEST(test_float_parsing) {
  char fstr[] = "%f";
  char str[] = "3.14";
  float actual = 0.0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(actual, 3.14f);
}
END_TEST

START_TEST(test_float_parsing_minus) {
  char fstr[] = "%f";
  char str[] = "-3.14";
  float actual = 0.0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(actual, -3.14f);
}
END_TEST

START_TEST(test_string_parsing) {
  char fstr[] = "%s";
  char str[] = "Hello World";
  char actual[100];

  int res1 = s21_sscanf(str, fstr, actual);
  int res2 = sscanf(str, fstr, actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(actual, "Hello");
}
END_TEST

START_TEST(test_character_parsing) {
  char fstr[] = "%c";
  char str[] = "A";
  char actual = '\0';

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 'A');
}
END_TEST

START_TEST(test_hexadecimal_parsing) {
  char fstr[] = "%x";
  char str[] = "0x1A3F";
  unsigned int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 0x1A3F);
}
END_TEST

START_TEST(test_leading_whitespace) {
  char fstr[] = "%d";
  char str[] = "    42";
  int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 42);
}
END_TEST

START_TEST(test_trailing_whitespace) {
  char fstr[] = "%d";
  char str[] = "42    ";
  int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 42);
}
END_TEST

START_TEST(test_multiple_format_specifiers) {
  char fstr[] = "%d %f %s";
  char str[] = "42 3.14 Hello";
  int int_actual = 0;
  float float_actual = 0.0;
  char str_actual[100];

  int res1 = s21_sscanf(str, fstr, &int_actual, &float_actual, str_actual);
  int res2 = sscanf(str, fstr, &int_actual, &float_actual, str_actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_actual, 42);
  ck_assert_float_eq(float_actual, 3.14f);
  ck_assert_str_eq(str_actual, "Hello");
}
END_TEST

START_TEST(test_exceeding_width) {
  char fstr[] = "%5d";
  char str[] = "123456789";
  int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 12345);
}
END_TEST

START_TEST(test_exceeding_minus_d) {
  char fstr[] = "%d";
  char str[] = "-12345";
  int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, -12345);
}
END_TEST

START_TEST(test_hexadecimal_no_prefix) {
  char fstr[] = "%x";
  char str[] = "1A3F";
  unsigned int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 0x1A3F);
}
END_TEST

START_TEST(test_octal_with_prefix) {
  char fstr[] = "%o";
  char str[] = "0755";
  unsigned int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 493);
}
END_TEST

START_TEST(test_mixed_input) {
  char fstr[] = "%d %f %s %c";
  char str[] = "100 200.5 Test C";
  int int_actual = 0;
  float float_actual = 0.0;
  char str_actual[100];
  char char_actual = '\0';

  int res1 = s21_sscanf(str, fstr, &int_actual, &float_actual, str_actual,
                        &char_actual);
  int res2 =
      sscanf(str, fstr, &int_actual, &float_actual, str_actual, &char_actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(int_actual, 100);
  ck_assert_float_eq(float_actual, 200.5f);
  ck_assert_str_eq(str_actual, "Test");
  ck_assert_int_eq(char_actual, 'C');
}
END_TEST

START_TEST(test_with_long) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char str[] = "1337 21 5008 300004";
  const char fstr[] = "%1ld %3ld %1ld %4ld";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_with_stars) {
  char fstr[] = "%c%c%c%*c";
  char str[] = "ABCD";
  char a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_with_strings1) {
  char s1[100] = {'\0'};
  char s2[100] = {'\0'};
  char s3[100] = {'\0'};
  char s4[100] = {'\0'};

  char s5[100] = {'\0'};
  char s6[100] = {'\0'};
  char s7[100] = {'\0'};
  char s8[100] = {'\0'};

  const char str[] = "Aboba Floppa Keppa Shleppa Anuroba";
  const char fstr[] = "%s %s %s %s";
  int res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(test_with_strings_space) {
  char s1[100] = {'\0'};
  char s2[100] = {'\0'};
  char s3[100] = {'\0'};
  char s4[100] = {'\0'};

  char s5[100] = {'\0'};
  char s6[100] = {'\0'};
  char s7[100] = {'\0'};
  char s8[100] = {'\0'};

  const char str[] =
      "      aboba        tshlepa          asdfasdf     asdfasdf";
  const char fstr[] = "%s %s %s %s";
  int res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(test_with_strings_stars) {
  char s1[100] = {'\0'};
  char s2[100] = {'\0'};
  char s3[100] = {'\0'};
  char s4[100] = {'\0'};

  char s5[100] = {'\0'};
  char s6[100] = {'\0'};
  char s7[100] = {'\0'};
  char s8[100] = {'\0'};

  const char *str = "aboba floppa shleppa koooppa";
  const char *fstr = "%*s%*s%*s%*s";
  int res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(test_with_strings_width) {
  char s1[100] = {'\0'};
  char s2[100] = {'\0'};
  char s3[100] = {'\0'};
  char s4[100] = {'\0'};

  char s5[100] = {'\0'};
  char s6[100] = {'\0'};
  char s7[100] = {'\0'};
  char s8[100] = {'\0'};

  const char str[] = "aboba floppa shleppa koooppa";
  const char fstr[] = "%1s%1s%1s%1s";
  int res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(test_X) {
  uint32_t a1, a2;
  const char str[] = "0xFF0x0xFFF 0xFFxFF";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(test_X1) {
  uint32_t a1, a2;
  const char str[] = "0Xc0dE";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_X2) {
  uint32_t a1, a2;
  const char str[] = "0xABC123";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}

END_TEST

START_TEST(test_X3) {
  uint32_t a1, a2;
  const char str[] = "0xBADCAFE";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_X4) {
  uint32_t a1, a2;
  const char str[] = "000000";
  const char fstr[] = "%X";
  uint32_t res1 = s21_sscanf(str, fstr, &a1);
  uint32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_hexadecimal_width) {
  char fstr[] = "%2x ";
  char str[] = "10xFF0x";
  unsigned int actual = 0;
  unsigned int actual2 = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, actual2);
}
END_TEST

START_TEST(test_ptr) {
  void *a1 = 0, *a2 = 0;

  const char str[] = "0x4";
  const char fstr[] = "%p";

  unsigned int res1 = s21_sscanf(str, fstr, &a1);
  unsigned int res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
}

START_TEST(test_unsigned_u) {
  char fstr[] = "%2u";
  char str[] = "123";
  unsigned int actual;
  unsigned int actual1;
  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, actual1);
}
END_TEST

START_TEST(test_unsigned_u1) {
  char fstr[] = "%u";
  char str[] = "-1";
  unsigned int actual;
  unsigned int actual1;
  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, actual1);
}
END_TEST

START_TEST(test_int_short) {
  char fstr[] = "%hd";
  char str[] = "109876";
  short actual;
  short actual1;
  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, actual1);
}
END_TEST

START_TEST(test_hex_short) {
  char fstr[] = "%hX";
  char str[] = "F";
  unsigned int actual = 0;
  unsigned int actual1 = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual1);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(actual, actual1);
}
END_TEST

START_TEST(test_octal_long) {
  char fstr[] = "%lo";
  char str[] = "0755";
  long unsigned int actual = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, 493);
}
END_TEST

START_TEST(test_octal_long_2) {
  char fstr[] = "%2o";
  char str[] = "0758";
  long unsigned int actual = 0;
  long unsigned int actual2 = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual2, actual);
}
END_TEST

START_TEST(test_octal_long_3) {
  char fstr[] = "%o";
  char str[] = "0758";
  long unsigned int actual = 0;
  long unsigned int actual2 = 0;

  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual2, actual);
}
END_TEST

START_TEST(test_hex_short1) {
  char fstr[] = "%hx";
  char str[] = "ff";
  short unsigned int actual;
  short unsigned int actual1;
  int res1 = s21_sscanf(str, fstr, &actual);
  int res2 = sscanf(str, fstr, &actual1);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(actual, actual1);
}
END_TEST

START_TEST(test_double_L) {
  long double a1 = 1, a2 = 0;
  const char str[] = "45.670000";
  const char fstr[] = "%Lf";

  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ptr_tolower) {
  void *a1 = 0, *a2 = 0;

  const char str[] = "0xFFAA";
  const char fstr[] = "%p";

  unsigned int res1 = s21_sscanf(str, fstr, &a1);
  unsigned int res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
}

START_TEST(s21_sscanf_test_integers) {
  long int custom = 0, original = 0, custom_responce, original_responce;
  char str[64], format[64];
  strcpy(str, "500");
  strcpy(format, "%d");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "0 ");
  strcpy(format, "%d");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "-5 ");
  strcpy(format, "%d");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "500  ");
  strcpy(format, "%ld");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "500");
  strcpy(format, "%u");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
}
END_TEST

START_TEST(s21_sscanf_test_hex) {
  long int custom = 0, original = 0, custom_responce, original_responce;
  char str[64], format[64];
  strcpy(str, "  500  ");
  strcpy(format, "%x");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, " 0 ");
  strcpy(format, "%X");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "Cd500");
  strcpy(format, "%lx");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "017500");
  strcpy(format, "%o");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  void *custom_p;
  void *original_p;
  strcpy(str, " 0x7ffc292dd640");
  strcpy(format, "%p");
  custom_responce = s21_sscanf(str, format, &custom_p);
  original_responce = sscanf(str, format, &original_p);
  ck_assert_ptr_eq(custom_p, original_p);
  ck_assert_int_eq(custom_responce, original_responce);
}
END_TEST

START_TEST(s21_sscanf_test_string) {
  char custom[64], original[64];
  int custom_responce, original_responce;
  char str[64], format[64];
  strcpy(str, " avs ");
  strcpy(format, "%s");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_str_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, " \nas g avs ");
  strcpy(format, "%s");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_str_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
}
END_TEST

START_TEST(s21_sscanf_test_float) {
  double custom = 0, original = 123.123;
  int custom_responce, original_responce;
  char str[64], format[64];
  strcpy(str, "-1.123e+2");
  strcpy(format, "%lf");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "1.123e-7");
  strcpy(format, "%lf");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom_responce, original_responce);
}
END_TEST

START_TEST(s21_sscanf_test_two) {
  int custom_1 = 0, original_1 = 0, custom_2 = 0, original_2 = 0;
  int custom_responce, original_responce;
  char str[64], format[64];
  strcpy(str, "123 456");
  strcpy(format, "%d %d");
  custom_responce = s21_sscanf(str, format, &custom_1, &custom_2);
  original_responce = sscanf(str, format, &original_1, &original_2);
  ck_assert_int_eq(custom_1, original_1);
  ck_assert_int_eq(custom_2, original_2);
  ck_assert_int_eq(custom_responce, original_responce);
  strcpy(str, "123 456");
  strcpy(format, "%d  %d");
  custom_responce = s21_sscanf(str, format, &custom_1, &custom_2);
  original_responce = sscanf(str, format, &original_1, &original_2);
  ck_assert_int_eq(custom_1, original_1);
  ck_assert_int_eq(custom_2, original_2);
  ck_assert_int_eq(custom_responce, original_responce);
}
END_TEST

START_TEST(s21_sscanf_test_char) {
  char custom, original;
  int custom_responce, original_responce;
  char str[64], format[64];
  strcpy(str, "m% fg");
  strcpy(format, "%c%%");
  custom_responce = s21_sscanf(str, format, &custom);
  original_responce = sscanf(str, format, &original);
  ck_assert_int_eq(custom, original);
  ck_assert_int_eq(custom_responce, original_responce);
}
END_TEST

// sscanf end

int main(void) {
  Suite *s = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s);
  int nf;
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_memchr_test);
  tcase_add_test(tc, s21_memcmp_test);
  tcase_add_test(tc, s21_memset_test);
  tcase_add_test(tc, s21_memcpy_test);
  tcase_add_test(tc, s21_strncat_test);
  tcase_add_test(tc, s21_strchr_test);
  tcase_add_test(tc, s21_strncmp_test);
  tcase_add_test(tc, s21_strncpy_test);
  tcase_add_test(tc, s21_strcspn_test);
  tcase_add_test(tc, s21_strlen_test);
  tcase_add_test(tc, s21_strpbrk_test);
  tcase_add_test(tc, s21_strrchr_test);
  tcase_add_test(tc, s21_strstr_test);
  tcase_add_test(tc, s21_strtok_several_tokens_test);
  tcase_add_test(tc, s21_strtok_not_found_token_test);
  tcase_add_test(tc, s21_strtok_one_token_test);
  tcase_add_test(tc, s21_to_upper_test_1);
  tcase_add_test(tc, s21_to_upper_test_2);
  tcase_add_test(tc, s21_to_upper_test_3);
  tcase_add_test(tc, s21_to_lower_test_1);
  tcase_add_test(tc, s21_to_lower_test_2);
  tcase_add_test(tc, s21_to_lower_test_3);
  tcase_add_test(tc, s21_insert_test_1);
  tcase_add_test(tc, s21_insert_test_2);
  tcase_add_test(tc, s21_insert_test_3);
  tcase_add_test(tc, s21_trim_test_1);
  tcase_add_test(tc, s21_trim_test_2);
  tcase_add_test(tc, s21_trim_test_3);
  tcase_add_test(tc, s21_trim_test_4);
  tcase_add_test(tc, s21_trim_test_5);
  tcase_add_test(tc, s21_strerror_1);
  tcase_add_test(tc, s21_strerror_2);
  tcase_add_test(tc, s21_strerror_3);
  tcase_add_test(tc, s21_strerror_4);
  tcase_add_test(tc, s21_strerror_5);

  tcase_add_test(tc, s21_sprintf_test_e2);
  tcase_add_test(tc, s21_sprintf_test_d);
  tcase_add_test(tc, s21_sprintf_test_f);
  tcase_add_test(tc, s21_sprintf_test_s);
  tcase_add_test(tc, s21_sprintf_test_c);
  tcase_add_test(tc, s21_sprintf_test_u);
  tcase_add_test(tc, s21_sprintf_test_x);
  tcase_add_test(tc, s21_sprintf_test_X);
  tcase_add_test(tc, s21_sprintf_test_o);
  tcase_add_test(tc, s21_sprintf_test_e);
  tcase_add_test(tc, s21_sprintf_test_E);
  tcase_add_test(tc, s21_sprintf_test_g);
  tcase_add_test(tc, s21_sprintf_test_G);
  tcase_add_test(tc, s21_sprintf_test_space);
  tcase_add_test(tc, s21_sprintf_test_width_1);
  tcase_add_test(tc, s21_sprintf_test_width_2);
  tcase_add_test(tc, s21_sprintf_test_plus_1);
  tcase_add_test(tc, s21_sprintf_test_plus_2);
  tcase_add_test(tc, s21_sprintf_test_null);
  tcase_add_test(tc, s21_sprintf_test_minus_1);
  tcase_add_test(tc, s21_sprintf_test_minus_2);
  tcase_add_test(tc, s21_sprintf_test_point_1);
  tcase_add_test(tc, s21_sprintf_test_point_2);
  tcase_add_test(tc, s21_sprintf_test_point_3);
  tcase_add_test(tc, s21_sprintf_test_h);
  tcase_add_test(tc, s21_sprintf_test_l);
  tcase_add_test(tc, s21_sprintf_mix);

  tcase_add_test(tc, test_decimal_parsing);
  tcase_add_test(tc, test_hexadecimal_parsing);
  tcase_add_test(tc, test_float_parsing);
  tcase_add_test(tc, test_float_parsing_minus);
  tcase_add_test(tc, test_string_parsing);
  tcase_add_test(tc, test_character_parsing);
  tcase_add_test(tc, test_leading_whitespace);
  tcase_add_test(tc, test_trailing_whitespace);
  tcase_add_test(tc, test_multiple_format_specifiers);
  tcase_add_test(tc, test_exceeding_width);
  tcase_add_test(tc, test_exceeding_minus_d);
  tcase_add_test(tc, test_hexadecimal_no_prefix);
  tcase_add_test(tc, test_octal_with_prefix);
  tcase_add_test(tc, test_mixed_input);
  tcase_add_test(tc, test_with_stars);
  tcase_add_test(tc, test_with_long);
  tcase_add_test(tc, test_with_strings1);
  tcase_add_test(tc, test_with_strings_space);
  tcase_add_test(tc, test_with_strings_stars);
  tcase_add_test(tc, test_with_strings_width);
  tcase_add_test(tc, test_ptr);
  tcase_add_test(tc, test_X);
  tcase_add_test(tc, test_X1);
  tcase_add_test(tc, test_X2);
  tcase_add_test(tc, test_X3);
  tcase_add_test(tc, test_X4);
  tcase_add_test(tc, test_hexadecimal_width);
  tcase_add_test(tc, test_unsigned_u);
  tcase_add_test(tc, test_unsigned_u1);
  tcase_add_test(tc, test_int_short);
  tcase_add_test(tc, test_hex_short);
  tcase_add_test(tc, test_octal_long);
  tcase_add_test(tc, test_octal_long_2);
  tcase_add_test(tc, test_octal_long_3);
  tcase_add_test(tc, test_hex_short1);
  tcase_add_test(tc, test_double_L);
  tcase_add_test(tc, test_ptr_tolower);

  /////new:
  tcase_add_test(tc, s21_sscanf_test_integers);
  tcase_add_test(tc, s21_sscanf_test_hex);
  tcase_add_test(tc, s21_sscanf_test_float);
  tcase_add_test(tc, s21_sscanf_test_string);
  tcase_add_test(tc, s21_sscanf_test_two);
  tcase_add_test(tc, s21_sscanf_test_char);
  //////

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}