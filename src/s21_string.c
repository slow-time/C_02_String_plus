#include "s21_string.h"

// 1
void *s21_memchr(const void *str, int ch, s21_size_t n) {
  const unsigned char *ptr = str;
  bool isExist = 0;
  for (s21_size_t i = 0; i < n && isExist == 0 && *ptr != '\0'; i++) {
    if (*ptr == ch) {
      isExist = 1;
    } else {
      ptr++;
    }
  }
  return isExist == 1 ? (void *)ptr : s21_NULL;
}

// 2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr1 = str1;
  const unsigned char *ptr2 = str2;
  bool flag = true;
  int result = 0;
  for (s21_size_t i = 0; i < n && flag; i++) {
    if (ptr1[i] != ptr2[i]) {
      flag = false;
      result = ptr1[i] - ptr2[i];
    }
  }
  return result;
}

// 3
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *ptr_dest = (char *)dest;
  char *ptr_src = (char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    ptr_dest[i] = ptr_src[i];
  }
  return dest;
}
// 4

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = str;
  unsigned char ch = c;
  while (n-- && *ptr != '\0') {
    *ptr++ = ch;
  }
  return str;
}
// 5

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest != s21_NULL && src != s21_NULL && n > 0) {
    s21_size_t index = s21_strlen(dest);
    const char *ptr_src = src;
    while (n-- && *ptr_src != '\0') {
      dest[index++] = *ptr_src++;
    }
  }
  return dest;
}

// 6
char *s21_strchr(const char *str, int c) {
  char ch = (char)c;
  while (*str != '\0' && *str != ch) {
    str++;
  }
  return *str == ch ? (char *)str : s21_NULL;
}

// 7
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int found = 0;
  for (s21_size_t i = 0; i < n && (str1[i] != '\0' || str2[i] != '\0'); i++) {
    if (str1[i] != str2[i]) {
      found = str1[i] - str2[i];
      i = n;
    }
  }
  return found;
}

// 8
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *processed = dest;
  while (n > 0 && *src != '\0') {
    --n;
    *processed++ = *src++;
  }
  while (n) {
    --n;
    *processed = '\0';
  }
  return dest;
}

// 9
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int result = 0;
  while (str1[result] != '\0' && !s21_strchr(str2, str1[result])) result++;

  return result;
}

// 10
char *s21_strerror(int errnum) {
  static char res[BUFF_SIZE] = {'\0'};

  if (errnum < 0 || errnum >= S21_ERRLIST_SIZE)
    s21_sprintf(res, "Unknown error %d", errnum);
  else
    s21_sprintf(res, "%s", s21_sys_errlist[errnum]);
  return res;
}

// 11
s21_size_t s21_strlen(const char *str) {
  s21_size_t number = 0;
  if (str != s21_NULL) {
    while (str[number]) {
      number++;
    }
  }
  return number;
}

// 12
char *s21_strpbrk(const char *str1, const char *str2) {
  int size1 = s21_strlen(str1);
  int size2 = s21_strlen(str2);
  char *result;
  int control_result = 1;
  for (int i = 0; i < size1; i++) {
    for (int j = 0; j < size2; j++) {
      if (str2[j]) {
        if (str1[i] == str2[j] && control_result) {
          result = (char *)&str1[i];
          control_result = 0;
        }
      }
    }
  }
  return control_result ? s21_NULL : result;
}

// 13
char *s21_strrchr(const char *str, int c) {
  int size = s21_strlen(str);
  char *result;
  bool control_result = true;
  for (int i = size; i >= 0; i--) {
    if (c == str[i] && control_result) {
      result = (char *)&str[i];
      control_result = false;
    }
  }
  return control_result ? s21_NULL : result;
}

// 14
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t length1 = s21_strlen(haystack);
  s21_size_t length2 = s21_strlen(needle);
  char *result = s21_NULL;
  bool flag = true;
  for (s21_size_t i = 0; i < length1; i++) {
    if (s21_strncmp(haystack + i, needle, length2) == 0 && flag) {
      result = (char *)&haystack[i];
      flag = false;
    }
  }
  return result;
}

// 15
char *s21_strtok(char *str, const char *delim) {
  static char *ptr_last = s21_NULL;
  if (str == s21_NULL) {
    str = ptr_last;
  }
  char *token = s21_NULL;
  if (str != s21_NULL) {
    while (*str != '\0' && s21_strchr(delim, *str) != s21_NULL) {
      str++;
    }
    if (*str == '\0') {
      ptr_last = s21_NULL;
    } else {
      token = str;
      while (*str != '\0' && s21_strchr(delim, *str) == s21_NULL) {
        str++;
      }
      if (*str != '\0') {
        *str = '\0';
        ptr_last = str + 1;
      } else {
        ptr_last = s21_NULL;
      }
    }
  }
  return token;
}

void *s21_to_upper(const char *str) {
  if (!str) return s21_NULL;
  s21_size_t length = s21_strlen(str);
  char *str_upper = s21_NULL;

  str_upper = (char *)malloc((length + 1) * sizeof(char));
  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str_upper[i] = str[i] - ('a' - 'A');
    } else {
      str_upper[i] = str[i];
    }
  }
  str_upper[length] = '\0';
  return str_upper;
}

void *s21_to_lower(const char *str) {
  if (!str) return s21_NULL;
  s21_size_t length = s21_strlen(str);
  char *str_lower = (char *)malloc((length + 1) * sizeof(char));
  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str_lower[i] = str[i] + ('a' - 'A');
    } else {
      str_lower[i] = str[i];
    }
  }
  str_lower[length] = '\0';
  return str_lower;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *str_new = s21_NULL;
  s21_size_t src_length = s21_strlen(src);
  s21_size_t str_length = s21_strlen(str);
  if (start_index < src_length) {
    str_new = calloc(src_length + str_length + 1, sizeof(char));
    if (start_index > 0) {
      s21_strncpy(str_new, src, start_index);
      s21_strncat(str_new, str, str_length);
    } else {
      s21_strncpy(str_new, str, str_length);
    }
    s21_strncat(str_new, src + start_index, src_length - start_index);
  }
  return (void *)str_new;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *trim_str = s21_NULL;
  if (src != s21_NULL) {
    if (trim_chars == s21_NULL || s21_strlen(trim_chars) == 0) {
      const char default_chars[7] = " \n\t\v\f\r";
      trim_str = trim_chars_from_src(src, default_chars);
    } else {
      trim_str = trim_chars_from_src(src, trim_chars);
    }
  }
  return (void *)trim_str;
}

char *trim_chars_from_src(const char *src, const char *trim_chars) {
  s21_size_t lenght = s21_strlen(src);
  s21_size_t start_i = 0;
  while (*src != '\0' && s21_strchr(trim_chars, *src) != s21_NULL) {
    start_i++;
    src++;
  }
  lenght -= start_i;
  char *dest = (char *)malloc((lenght + 1) * sizeof(char));
  if (dest) {
    s21_strncpy(dest, src, lenght);
    dest[lenght] = '\0';
    if (lenght != 0) {
      while ((lenght != 0) &&
             s21_strchr(trim_chars, dest[lenght - 1]) != s21_NULL) {
        dest[lenght - 1] = '\0';
        lenght--;
      }
    }
  }
  return dest;
}