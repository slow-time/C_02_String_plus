#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL (void *)0

typedef long unsigned s21_size_t;

#define BUFF_SIZE 1024
#if defined(__APPLE__) || defined(__MACH__)
#define S21_ERRLIST_SIZE 107
#else
#define S21_ERRLIST_SIZE 134
#endif
#if defined(__APPLE__) || defined(__MACH__)

static const char *const s21_sys_errlist[S21_ERRLIST_SIZE] = {
    [0] = "Undefined error: 0",
    [1] = "Operation not permitted",
    [2] = "No such file or directory",
    [3] = "No such process",
    [4] = "Interrupted system call",
    [5] = "Input/output error",
    [6] = "Device not configured",
    [7] = "Argument list too long",
    [8] = "Exec format error",
    [9] = "Bad file descriptor",
    [10] = "No child processes",
    [11] = "Resource deadlock avoided",
    [12] = "Cannot allocate memory",
    [13] = "Permission denied",
    [14] = "Bad address",
    [15] = "Block device required",
    [16] = "Resource busy",
    [17] = "File exists",
    [18] = "Cross-device link",
    [19] = "Operation not supported by device",
    [20] = "Not a directory",
    [21] = "Is a directory",
    [22] = "Invalid argument",
    [23] = "Too many open files in system",
    [24] = "Too many open files",
    [25] = "Inappropriate ioctl for device",
    [26] = "Text file busy",
    [27] = "File too large",
    [28] = "No space left on device",
    [29] = "Illegal seek",
    [30] = "Read-only file system",
    [31] = "Too many links",
    [32] = "Broken pipe",
    [33] = "Numerical argument out of domain",
    [34] = "Result too large",
    [35] = "Resource temporarily unavailable",
    [36] = "Operation now in progress",
    [37] = "Operation already in progress",
    [38] = "Socket operation on non-socket",
    [39] = "Destination address required",
    [40] = "Message too long",
    [41] = "Protocol wrong type for socket",
    [42] = "Protocol not available",
    [43] = "Protocol not supported",
    [44] = "Socket type not supported",
    [45] = "Operation not supported",
    [46] = "Protocol family not supported",
    [47] = "Address family not supported by protocol family",
    [48] = "Address already in use",
    [49] = "Can't assign requested address",
    [50] = "Network is down",
    [51] = "Network is unreachable",
    [52] = "Network dropped connection on reset",
    [53] = "Software caused connection abort",
    [54] = "Connection reset by peer",
    [55] = "No buffer space available",
    [56] = "Socket is already connected",
    [57] = "Socket is not connected",
    [58] = "Can't send after socket shutdown",
    [59] = "Too many references: can't splice",
    [60] = "Operation timed out",
    [61] = "Connection refused",
    [62] = "Too many levels of symbolic links",
    [63] = "File name too long",
    [64] = "Host is down",
    [65] = "No route to host",
    [66] = "Directory not empty",
    [67] = "Too many processes",
    [68] = "Too many users",
    [69] = "Disc quota exceeded",
    [70] = "Stale NFS file handle",
    [71] = "Too many levels of remote in path",
    [72] = "RPC struct is bad",
    [73] = "RPC version wrong",
    [74] = "RPC prog. not avail",
    [75] = "Program version wrong",
    [76] = "Bad procedure for program",
    [77] = "No locks available",
    [78] = "Function not implemented",
    [79] = "Inappropriate file type or format",
    [80] = "Authentication error",
    [81] = "Need authenticator",
    [82] = "Device power is off",
    [83] = "Device error",
    [84] = "Value too large to be stored in data type",
    [85] = "Bad executable (or shared library)",
    [86] = "Bad CPU type in executable",
    [87] = "Shared library version mismatch",
    [88] = "Malformed Mach-o file",
    [89] = "Operation canceled",
    [90] = "Identifier removed",
    [91] = "No message of desired type",
    [92] = "Illegal byte sequence",
    [93] = "Attribute not found",
    [94] = "Bad message",
    [95] = "EMULTIHOP (Reserved)",
    [96] = "No message available on STREAM",
    [97] = "ENOLINK (Reserved)",
    [98] = "No STREAM resources",
    [99] = "Not a STREAM",
    [100] = "Protocol error",
    [101] = "STREAM ioctl timeout",
    [102] = "Operation not supported on socket",
    [103] = "Policy not found",
    [104] = "State not recoverable",
    [105] = "Previous owner died",
    [106] = "Interface output queue is full"};
#endif

#if defined(__linux__)

static const char *const s21_sys_errlist[S21_ERRLIST_SIZE] = {
    [0] = "Success",
    [1] = "Operation not permitted",
    [2] = "No such file or directory",
    [3] = "No such process",
    [4] = "Interrupted system call",
    [5] = "Input/output error",
    [6] = "No such device or address",
    [7] = "Argument list too long",
    [8] = "Exec format error",
    [9] = "Bad file descriptor",
    [10] = "No child processes",
    [11] = "Resource temporarily unavailable",
    [12] = "Cannot allocate memory",
    [13] = "Permission denied",
    [14] = "Bad address",
    [15] = "Block device required",
    [16] = "Device or resource busy",
    [17] = "File exists",
    [18] = "Invalid cross-device link",
    [19] = "No such device",
    [20] = "Not a directory",
    [21] = "Is a directory",
    [22] = "Invalid argument",
    [23] = "Too many open files in system",
    [24] = "Too many open files",
    [25] = "Inappropriate ioctl for device",
    [26] = "Text file busy",
    [27] = "File too large",
    [29] = "No space left on device",
    [30] = "Illegal seek",
    [31] = "Read-only file system",
    [32] = "Too many links",
    [33] = "Broken pipe",
    [34] = "Numerical argument out of domain",
    [35] = "Numerical result out of range",
    [36] = "Resource deadlock avoided",
    [37] = "File name too long",
    [38] = "No locks available",
    [39] = "Function not implemented",
    [40] = "Directory not empty",
    [41] = "Too many levels of symbolic links",
    [42] = "Unknown error 41",
    [43] = "No message of desired type",
    [44] = "Identifier removed",
    [45] = "Channel number out of range",
    [46] = "Level 2 not synchronized",
    [47] = "Level 3 halted",
    [48] = "Level 3 reset",
    [49] = "Link number out of range",
    [50] = "Protocol driver not attached",
    [51] = "No CSI structure available",
    [52] = "Level 2 halted",
    [53] = "Invalid request descriptor",
    [54] = "Invalid exchange",
    [55] = "Exchange full",
    [56] = "No anode",
    [57] = "Invalid request code",
    [58] = "Invalid slot",
    [59] = "Unknown error 58",
    [60] = "Bad font file format",
    [61] = "Device not a stream",
    [62] = "No data available",
    [63] = "Timer expired",
    [64] = "Out of streams resources",
    [65] = "Machine is not on the network",
    [66] = "Package not installed",
    [67] = "Object is remote",
    [68] = "Link has been severed",
    [69] = "Advertise error",
    [70] = "Srmount error",
    [71] = "Communication error on send",
    [72] = "Protocol error",
    [73] = "Multihop attempted",
    [74] = "RFS specific error",
    [75] = "Bad message",
    [76] = "Value too large for defined data type",
    [77] = "Name not unique on network",
    [78] = "File descriptor in bad state",
    [79] = "Remote address changed",
    [80] = "Can not access a needed shared library",
    [81] = "Accessing a corrupted shared library",
    [82] = ".lib section in exrcutable file is corrupted",
    [83] = "Attempting to link in too many shared libraries",
    [84] = "Invalid or incomplete multibyte or wide character",
    [85] = "Interrupted system call should be restarted",
    [86] = "Streams pipe error",
    [87] = "Too many users",
    [88] = "Socket operation on non-socket",
    [89] = "Destination address required",
    [90] = "Message too long",
    [91] = "Protocol wrong type for socket",
    [92] = "Protocol not available",
    [93] = "Protocol not supported",
    [94] = "Socket type not supported",
    [95] = "Operation not supported",
    [96] = "Protocol family not supported",
    [97] = "Address family not supported by protocol",
    [98] = "Address already in use",
    [99] = "Cannot assign requested address",
    [100] = "Network is down",
    [101] = "Network is unreachable",
    [102] = "Network dropped connection on reset",
    [103] = "Software caused connection abort",
    [104] = "Connection reset by peer",
    [105] = "No buffer space available",
    [106] = "Transport endpoint is already connected",
    [107] = "Transport endpoint is not connected",
    [108] = "Cannot send after transport endpoint shutdown",
    [109] = "Too many references: cannot splice",
    [110] = "Connection timed out",
    [111] = "Connection refused",
    [112] = "Host is down",
    [113] = "No route to host",
    [114] = "Operation already in progress",
    [115] = "Operation now in progress",
    [116] = "Stale file handle",
    [117] = "Structure needs cleaning",
    [118] = "Not a XENIX named type file",
    [119] = "No XENIX semaphores available",
    [120] = "Is a named type file",
    [121] = "Remote I/O error",
    [122] = "Disk quota exceeded",
    [123] = "No medium found",
    [124] = "Wrong medium type",
    [125] = "Operation canceled",
    [126] = "Required key not available",
    [127] = "Key has expired",
    [128] = "Key has been revoked",
    [129] = "Key was rejected by service",
    [130] = "Owner died",
    [131] = "State not recoverable",
    [132] = "Operation not possible due to RF-kill",
    [133] = "Memory page has hardware error",
};
#endif

typedef struct Flags {
  bool space;
  bool sign;
  bool sprint_null;
  bool width;
  bool minus;
  bool point;
  bool h;
  bool l;
} Flags;

typedef struct Arguments {
  int width;
  bool is_width_set;
  bool is_long;
  bool is_long_double;
  bool is_short;
} Arguments;

void *s21_memchr(const void *str, int ch, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
char *trim_chars_from_src(const char *src, const char *trim_chars);

int s21_sprintf(char *str, const char *format, ...);
void s21_sprintf_d(va_list *arg, char *str, s21_size_t *i_str, const int *num_e,
                   bool spec_e, Flags flag, int *counter_switch,
                   s21_size_t *i_format, const char *format,
                   const int *counter_null_width_tmp);
void s21_sprintf_c(va_list *args, char *str, s21_size_t *i_str,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp,
                   Flags flag);
void s21_sprintf_s(va_list *args, char *str, s21_size_t *i_str,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp,
                   Flags flag);
void s21_sprintf_save_s(char *str, s21_size_t *i_str, s21_size_t *i_format,
                        const char *format, int *counter_switch,
                        int *counter_null_width_tmp, Flags flag, char *s,
                        bool spec_e);
void s21_sprintf_f(va_list *args, char *str, s21_size_t *i_str,
                   const double *num_e, bool spec_e, Flags flag,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp,
                   bool spec_g);
void s21_sprintf_u(va_list *args, char *str, s21_size_t *i_str, Flags flag,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp);
void s21_sprintf_x(va_list *args, char *str, s21_size_t *i_str, bool upper,
                   Flags flag, s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp);
void s21_sprintf_e(va_list *args, char *str, s21_size_t *i_str, bool upper,
                   Flags flag, int *counter_switch, s21_size_t *i_format,
                   const char *format, int *counter_null_width_tmp, bool spec_g,
                   double num_g);
void s21_sprintf_o(va_list *args, char *str, s21_size_t *i_str, Flags flag,
                   s21_size_t *i_format, const char *format,
                   int *counter_switch, int *counter_null_width_tmp);
void s21_sprintf_g(va_list *args, char *str, s21_size_t *i_str, bool upper,
                   Flags flag, int *counter_switch, s21_size_t *i_format,
                   const char *format, int *counter_null_width_tmp);
void space(char *str, s21_size_t *i_str);
void sign(char *str, s21_size_t *i_str);
void switch_flags(va_list *args, char *str, s21_size_t *i_str,
                  s21_size_t *i_format, const char *format);
void switch_spec(va_list *args, char *str, s21_size_t *i_str,
                 s21_size_t *i_format, const char *format, Flags flag,
                 int *counter_switch);
int read_null_width(const s21_size_t *i_format, const char *format,
                    int *counter_switch);
int counter_null_width(const s21_size_t *i_format, const char *format,
                       const int *counter_switch);
void add_nulls_width(char *str, s21_size_t *i_str, int *digitals,
                     const s21_size_t *container, Flags flag);
void width_char(s21_size_t *i_format, const char *format, int *counter_switch,
                const int *counter_null_width_tmp, Flags flag, char *str,
                s21_size_t *i_str, s21_size_t container);
void add_spec(va_list *args, char *str, s21_size_t *i_str, s21_size_t *i_format,
              const char *format, Flags flag, int *counter_switch,
              int *counter_null_width_tmp);
void add_flags(const s21_size_t *i_format, const char *format, Flags *flag,
               int *counter_switch);
void s21_sprintf_d_null(char *str, s21_size_t *i_str, bool spec_e, Flags flag,
                        int *digitals);
void s21_sprintf_d_not_null(char *str, s21_size_t *i_str, bool spec_e,
                            Flags flag, long int *num, int *digitals,
                            s21_size_t *container, bool *minus);
void s21_sprintf_f_save(char *str, s21_size_t *i_str, Flags flag,
                        s21_size_t *i_format, const char *format,
                        int *counter_switch, int *counter_null_width_tmp,
                        int *counter_double, bool minus, bool num_null,
                        bool first_null, int *counter, double *d_num,
                        const char *change_num, const s21_size_t *container,
                        bool spec_g);
void s21_sprintf_u_not_null(char *str, s21_size_t *i_str, Flags flag,
                            s21_size_t *i_format, const char *format,
                            int *counter_switch, int *counter_null_width_tmp,
                            unsigned long int *num);
void s21_sprintf_x_not_null(char *str, s21_size_t *i_str, bool upper,
                            Flags flag, s21_size_t *i_format,
                            const char *format, int *counter_switch,
                            int *counter_null_width_tmp,
                            unsigned long int *num);
void s21_sprintf_e_not_null(va_list *args, char *str, s21_size_t *i_str,
                            bool upper, Flags flag, int *counter_switch,
                            s21_size_t *i_format, const char *format,
                            int *counter_null_width_tmp, double *num,
                            bool spec_g);
void s21_sprintf_o_not_null(char *str, s21_size_t *i_str, Flags flag,
                            s21_size_t *i_format, const char *format,
                            int *counter_switch, int *counter_null_width_tmp,
                            unsigned long int *num);
void s21_sprintf_f_point(double *d_num, int *counter_double, char *str,
                         s21_size_t *i_str, int *container_g, bool spec_g);

void skip_whitespace(const char **str);
int s21_sscanf(const char *str, const char *format, ...);
void skip_value(const char **str, const char **format);
void process_format_specifier(const char **str, const char **format,
                              va_list *args, Arguments arg);
void s21_sscanf_d(const char **str, va_list *args, Arguments arg);
void s21_sscanf_c(const char **str, va_list *args);
void s21_sscanf_s(const char **str, va_list *args, Arguments arg);
void s21_sscanf_f(const char **str, va_list *args, Arguments arg);
void s21_sscanf_u(const char **str, va_list *args, Arguments arg);
void s21_sscanf_x(const char **str, va_list *args, Arguments arg);
void s21_sscanf_o(const char **str, va_list *args, Arguments arg);
void s21_sscanf_p(const char **str, va_list *args);