#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "header.hpp"

#ifdef __APPLE__
    #include <sys/errno.h>
    
    #define ERROR_MESSAGES { \
        [0] = "Undefined error: 0", \
        [EPERM] = "Operation not permitted", \
        [ENOENT] = "No such file or directory", \
        [ESRCH] = "No such process", \
        [EINTR] = "Interrupted system call", \
        [EIO] = "Input/output error", \
        [ENXIO] = "Device not configured", \
        [E2BIG] = "Argument list too long", \
        [ENOEXEC] = "Exec format error", \
        [EBADF] = "Bad file descriptor", \
        [ECHILD] = "No child processes", \
        [EDEADLK] = "Resource deadlock avoided", \
        [ENOMEM] = "Cannot allocate memory", \
        [EACCES] = "Permission denied", \
        [EFAULT] = "Bad address", \
        [ENOTBLK] = "Block device required", \
        [EBUSY] = "Device / Resource busy", \
        [EEXIST] = "File exists", \
        [EXDEV] = "Cross-device link", \
        [ENODEV] = "Operation not supported by device", \
        [ENOTDIR] = "Not a directory", \
        [EISDIR] = "Is a directory", \
        [EINVAL] = "Invalid argument", \
        [ENFILE] = "Too many open files in system", \
        [EMFILE] = "Too many open files", \
        [ENOTTY] = "Inappropriate ioctl for device", \
        [ETXTBSY] = "Text file busy", \
        [EFBIG] = "File too large", \
        [ENOSPC] = "No space left on device", \
        [ESPIPE] = "Illegal seek", \
        [EROFS] = "Read-only file system", \
        [EMLINK] = "Too many links", \
        [EPIPE] = "Broken pipe", \
        [EDOM] = "Numerical argument out of domain", \
        [ERANGE] = "Result too large", \
        [EAGAIN] = "Resource temporarily unavailable", \
        [EINPROGRESS] = "Operation now in progress", \
        [EALREADY] = "Operation already in progress", \
        [ENOTSOCK] = "Socket operation on non-socket", \
        [EDESTADDRREQ] = "Destination address required", \
        [EMSGSIZE] = "Message too long", \
        [EPROTOTYPE] = "Protocol wrong type for socket", \
        [ENOPROTOOPT] = "Protocol not available", \
        [EPROTONOSUPPORT] = "Protocol not supported", \
        [ESOCKTNOSUPPORT] = "Socket type not supported", \
        [ENOTSUP] = "Operation not supported", \
        [EPFNOSUPPORT] = "Protocol family not supported", \
        [EAFNOSUPPORT] = "Address family not supported by protocol family", \
        [EADDRINUSE] = "Address already in use", \
        [EADDRNOTAVAIL] = "Can't assign requested address", \
        [ENETDOWN] = "Network is down", \
        [ENETUNREACH] = "Network is unreachable", \
        [ENETRESET] = "Network dropped connection on reset", \
        [ECONNABORTED] = "Software caused connection abort", \
        [ECONNRESET] = "Connection reset by peer", \
        [ENOBUFS] = "No buffer space available", \
        [EISCONN] = "Socket is already connected", \
        [ENOTCONN] = "Socket is not connected", \
        [ESHUTDOWN] = "Can't send after socket shutdown", \
        [ETOOMANYREFS] = "Too many references: can't splice", \
        [ETIMEDOUT] = "Operation timed out", \
        [ECONNREFUSED] = "Connection refused", \
        [ELOOP] = "Too many levels of symbolic links", \
        [ENAMETOOLONG] = "File name too long", \
        [EHOSTDOWN] = "Host is down", \
        [EHOSTUNREACH] = "No route to host", \
        [ENOTEMPTY] = "Directory not empty", \
        [EPROCLIM] = "Too many processes", \
        [EUSERS] = "Too many users", \
        [EDQUOT] = "Disc quota exceeded", \
        [ESTALE] = "Stale NFS file handle", \
        [EREMOTE] = "Too many levels of remote in path", \
        [EBADRPC] = "RPC struct is bad", \
        [ERPCMISMATCH] = "RPC version wrong", \
        [EPROGUNAVAIL] = "RPC prog. not avail", \
        [EPROGMISMATCH] = "Program version wrong", \
        [EPROCUNAVAIL] = "Bad procedure for program", \
        [ENOLCK] = "No locks available", \
        [ENOSYS] = "Function not implemented", \
        [EFTYPE] = "Inappropriate file type or format", \
        [EAUTH] = "Authentication error", \
        [ENEEDAUTH] = "Need authenticator", \
        [EPWROFF] = "Device power is off", \
        [EDEVERR] = "Device error", \
        [EOVERFLOW] = "Value too large to be stored in data type", \
        [EBADEXEC] = "Bad executable", \
        [EBADARCH] = "Bad CPU type in executable", \
        [ESHLIBVERS] = "Shared library version mismatch", \
        [EBADMACHO] = "Malformed Macho file", \
        [ECANCELED] = "Operation canceled", \
        [EIDRM] = "Identifier removed", \
        [ENOMSG] = "No message of desired type", \
        [EILSEQ] = "Illegal byte sequence", \
        [ENOATTR] = "Attribute not found", \
        [EBADMSG] = "Bad message", \
        [EMULTIHOP] = "Reserved", \
        [ENODATA] = "No message available on STREAM", \
        [ENOLINK] = "Reserved", \
        [ENOSR] = "No STREAM resources", \
        [ENOSTR] = "Not a STREAM", \
        [EPROTO] = "Protocol error", \
        [ETIME] = "STREAM ioctl timeout", \
        [EOPNOTSUPP] = "Operation not supported on socket", \
        [ENOPOLICY] = "No such policy registered" \
    }

#elif __linux__
    #include <string.h>
    
    #define ERROR_MESSAGES { \
        [0] = "Success", \
        [EPERM] = "Operation not permitted", \
        [ENOENT] = "No such file or directory", \
        [ESRCH] = "No such process", \
        [EINTR] = "Interrupted system call", \
        [EIO] = "Input/output error", \
        [ENXIO] = "No such device or address", \
        [E2BIG] = "Argument list too long", \
        [ENOEXEC] = "Exec format error", \
        [EBADF] = "Bad file descriptor", \
        [ECHILD] = "No child processes", \
        [EAGAIN] = "Resource temporarily unavailable", \
        [ENOMEM] = "Cannot allocate memory", \
        [EACCES] = "Permission denied", \
        [EFAULT] = "Bad address", \
        [ENOTBLK] = "Block device required", \
        [EBUSY] = "Device or resource busy", \
        [EEXIST] = "File exists", \
        [EXDEV] = "Invalid cross-device link", \
        [ENODEV] = "No such device", \
        [ENOTDIR] = "Not a directory", \
        [EISDIR] = "Is a directory", \
        [EINVAL] = "Invalid argument", \
        [ENFILE] = "Too many open files in system", \
        [EMFILE] = "Too many open files", \
        [ENOTTY] = "Inappropriate ioctl for device", \
        [ETXTBSY] = "Text file busy", \
        [EFBIG] = "File too large", \
        [ENOSPC] = "No space left on device", \
        [ESPIPE] = "Illegal seek", \
        [EROFS] = "Read-only file system", \
        [EMLINK] = "Too many links", \
        [EPIPE] = "Broken pipe", \
        [EDOM] = "Numerical argument out of domain", \
        [ERANGE] = "Numerical result out of range", \
        [EDEADLK] = "Resource deadlock avoided", \
        [ENAMETOOLONG] = "File name too long", \
        [ENOLCK] = "No locks available", \
        [ENOSYS] = "Function not implemented", \
        [ENOTEMPTY] = "Directory not empty", \
        [ELOOP] = "Too many levels of symbolic links", \
        [ENOMSG] = "No message of desired type", \
        [EIDRM] = "Identifier removed", \
        [ECHRNG] = "Channel number out of range", \
        [EL2NSYNC] = "Level 2 not synchronized", \
        [EL3HLT] = "Level 3 halted", \
        [EL3RST] = "Level 3 reset", \
        [ELNRNG] = "Link number out of range", \
        [EUNATCH] = "Protocol driver not attached", \
        [ENOCSI] = "No CSI structure available", \
        [EL2HLT] = "Level 2 halted", \
        [EBADE] = "Invalid exchange", \
        [EBADR] = "Invalid request descriptor", \
        [EXFULL] = "Exchange full", \
        [ENOANO] = "No anode", \
        [EBADRQC] = "Invalid request code", \
        [EBADSLT] = "Invalid slot", \
        [EDEADLOCK] = "File locking deadlock error", \
        [EBFONT] = "Bad font file format", \
        [ENOSTR] = "Device not a stream", \
        [ENODATA] = "No data available", \
        [ETIME] = "Timer expired", \
        [ENOSR] = "Out of streams resources", \
        [ENONET] = "Machine is not on the network", \
        [ENOPKG] = "Package not installed", \
        [EREMOTE] = "Object is remote", \
        [ENOLINK] = "Link has been severed", \
        [EADV] = "Advertise error", \
        [ESRMNT] = "Srmount error", \
        [ECOMM] = "Communication error on send", \
        [EPROTO] = "Protocol error", \
        [EMULTIHOP] = "Multihop attempted", \
        [EDOTDOT] = "RFS specific error", \
        [EBADMSG] = "Bad message", \
        [EOVERFLOW] = "Value too large for defined data type", \
        [ENOTUNIQ] = "Name not unique on network", \
        [EBADFD] = "File descriptor in bad state", \
        [EREMCHG] = "Remote address changed", \
        [ELIBACC] = "Can not access a needed shared library", \
        [ELIBBAD] = "Accessing a corrupted shared library", \
        [ELIBSCN] = ".lib section in a.out corrupted", \
        [ELIBMAX] = "Attempting to link in too many shared libraries", \
        [ELIBEXEC] = "Cannot exec a shared library directly", \
        [EILSEQ] = "Invalid or incomplete multibyte or wide character", \
        [ERESTART] = "Interrupted system call should be restarted", \
        [ESTRPIPE] = "Streams pipe error", \
        [EUSERS] = "Too many users", \
        [ENOTSOCK] = "Socket operation on non-socket", \
        [EDESTADDRREQ] = "Destination address required", \
        [EMSGSIZE] = "Message too long", \
        [EPROTOTYPE] = "Protocol wrong type for socket", \
        [ENOPROTOOPT] = "Protocol not available", \
        [EPROTONOSUPPORT] = "Protocol not supported", \
        [ESOCKTNOSUPPORT] = "Socket type not supported", \
        [EOPNOTSUPP] = "Operation not supported", \
        [EPFNOSUPPORT] = "Protocol family not supported", \
        [EAFNOSUPPORT] = "Address family not supported by protocol", \
        [EADDRINUSE] = "Address already in use", \
        [EADDRNOTAVAIL] = "Cannot assign requested address", \
        [ENETDOWN] = "Network is down", \
        [ENETUNREACH] = "Network is unreachable", \
        [ENETRESET] = "Network dropped connection on reset", \
        [ECONNABORTED] = "Software caused connection abort", \
        [ECONNRESET] = "Connection reset by peer", \
        [ENOBUFS] = "No buffer space available", \
        [EISCONN] = "Transport endpoint is already connected", \
        [ENOTCONN] = "Transport endpoint is not connected", \
        [ESHUTDOWN] = "Cannot send after transport endpoint shutdown", \
        [ETOOMANYREFS] = "Too many references: cannot splice", \
        [ETIMEDOUT] = "Connection timed out", \
        [ECONNREFUSED] = "Connection refused", \
        [EHOSTDOWN] = "Host is down", \
        [EHOSTUNREACH] = "No route to host", \
        [EALREADY] = "Operation already in progress", \
        [EINPROGRESS] = "Operation now in progress", \
        [ESTALE] = "Stale file handle", \
        [EUCLEAN] = "Structure needs cleaning", \
        [ENOTNAM] = "Not a XENIX named type file", \
        [ENAVAIL] = "No XENIX semaphores available", \
        [EISNAM] = "Is a named type file", \
        [EREMOTEIO] = "Remote I/O error", \
        [EDQUOT] = "Disk quota exceeded", \
        [ENOMEDIUM] = "No medium found", \
        [EMEDIUMTYPE] = "Wrong medium type", \
        [ECANCELED] = "Operation canceled", \
        [ENOKEY] = "Required key not available", \
        [EKEYEXPIRED] = "Key has expired", \
        [EKEYREVOKED] = "Key has been revoked", \
        [EKEYREJECTED] = "Key was rejected by service", \
        [EOWNERDEAD] = "Owner died", \
        [ENOTRECOVERABLE] = "State not recoverable", \
        [ERFKILL] = "Operation not possible due to RF-kill", \
        [EHWPOISON] = "Memory page has hardware error" \
    }
#endif

// a
void *memchr(const void *str, int c, size_t n) {
    const unsigned char *p = (const unsigned char *)str;
    unsigned char uc = (unsigned char)c;
    for (size_t i = 0; i < n; i++) {
        if (p[i] == uc) {
            return (void *)(p + i);
        }
    }
    return NULL;
}
// b
int memcmp(const void* str1, const void* str2, size_t n) {
    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        } 
    }
    return 0;
}
// c
void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *dst = (unsigned char *)dest;
    const unsigned char* src_bytes = (const unsigned char *)src;

    for (size_t i = 0; i < n; i++) {
        dst[i] = src_bytes[i];
    }

    return dest;
}
// d
void* memset(void* str, int c, size_t n) {
    unsigned char *string = (unsigned char *)str;
    unsigned char ch = (unsigned char)c;
    for (size_t i = 0; i < n; i++) {
        string[i] = ch;
    }
    return str;
}
// e
char *strncat(char *dest, const char *src, size_t n) {
    char *dest_end = dest;
    while (*dest_end != '\0') {
        dest_end++;
    }

    size_t i = 0;
    while (i < n && src[i] != '\0') {
        dest_end[i] = src[i];
        i++;
    }

    dest_end[i] = '\0';

    return dest;
}
// f
char *strchr(const char *str, int c) {
    unsigned char uc = (unsigned char)c;
    
    while (*str != '\0') {
        if ((unsigned char)*str == uc) {
            return (char *)str;
        }
        str++;
    }
    
    if (uc == '\0') {
        return (char *)str;
    }
    
    return NULL;
}
// g
int strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        unsigned char c1 = (unsigned char)str1[i];
        unsigned char c2 = (unsigned char)str2[i];
        if (c1 != c2) {
            return (c1 > c2) ? 1 : -1;
        }
        if (c1 == '\0') {
            break;
        }
    }
    return 0;
}
// h
char *strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}
// i
size_t strspn(const char *str1, const char *str2) {
    _Bool charset[256] = { 0 };
    for (const unsigned char *c = (const unsigned char *)str2; *c; c++) {
        charset[*c] = 1;
    }
    const unsigned char *start = (const unsigned char *)str1;
    const unsigned char *curr;
    for (curr = start; charset[*curr]; curr++) {};
    return curr - start;
}
// j
char *strerror(int errnum) {
    static const char *error_messages[] = ERROR_MESSAGES;
    
    if (errnum < 0 || errnum >= (int)(sizeof(error_messages) / sizeof(error_messages[0]))) {
        return "Unknown error";
    }
    
    if (error_messages[errnum] == NULL) {
        return "Unknown error";
    }
    
    return (char *)error_messages[errnum];
}
// k
size_t strlen(const char *str) {
    if (str == NULL) return 0;
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
//l
char *strpbrk(const char *str1, const char *str2) {
    _Bool charset[256] = {0};
    for (const unsigned char *c = (const unsigned char *)str2; *c; c++) {
        charset[*c] = 1;
    }
    for (const unsigned char *p = (const unsigned char *)str1; *p; p++) {
        if (charset[*p]) {
            return (char *)p;
        }
    }
    return NULL;
}
//m
char *strrchr(const char *str, int c) {
    const char *last = NULL;
    unsigned char uc = (unsigned char)c;
    for (const unsigned char *p = (const unsigned char *)str; ; p++) {
        if (*p == uc) {
            last = (const char *)p;
        }
        if (*p == '\0') {
            break;
        }
    }
    return (char *)last;
}
//n
char *strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for ( ; *haystack; haystack++) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        if (!*n) return (char *)haystack;
    }
    return NULL;
}
//o
char *strtok(char *str, const char *delim) {
    static char *next_token = NULL;

    if (str != NULL) {
        next_token = str;
    }

    if (next_token == NULL || *next_token == '\0') {
        return NULL;
    }

    // Пропускаем начальные разделители
    const char *d;
    while (*next_token != '\0') {
        d = delim;
        while (*d != '\0') {
            if (*next_token == *d) {
                break;
            }
            d++;
        }
        if (*d == '\0') {
            // Текущий символ — не разделитель → начало токена
            break;
        }
        next_token++;
    }

    // Если дошли до конца строки — нет токена
    if (*next_token == '\0') {
        next_token = NULL;
        return NULL;
    }

    // Указатель на начало токена
    char *token_start = next_token;

    // Ищем конец токена (следующий разделитель или конец строки)
    while (*next_token != '\0') {
        d = delim;
        while (*d != '\0') {
            if (*next_token == *d) {
                // Найден разделитель — заменяем на '\0' и выходим
                *next_token = '\0';
                next_token++; // следующий вызов начнётся после разделителя
                return token_start;
            }
            d++;
        }
        next_token++;
    }

    // Достигли конца строки — возвращаем последний токен
    next_token = NULL;
    return token_start;
}