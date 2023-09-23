#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct StringView {
    const char *ptr;
    size_t len;
} StringView;

#define SV_F "%.*s"
#define SV_ARG(sv) (int)sv.len, sv.ptr

bool sv_is_whitespace(char c);
StringView sv_from_cstr(const char *cstr);
char *sv_to_cstr(StringView sv);
StringView sv_trim_left(StringView sv);
StringView sv_trim_right(StringView sv);
StringView sv_trim(StringView sv);
StringView sv_chop_by_delim(StringView *sv, char delim);

int main() {
    StringView sv0 = sv_from_cstr("\t \nHello, World\t\n ");
    printf("--------------------\n");
    printf("default : %s\n", sv_to_cstr(sv0));
    printf("--------------------\n");
    printf("trim_left: %s\n", sv_to_cstr(sv_trim_left(sv0)));
    printf("--------------------\n");
    printf("trim_right: %s\n", sv_to_cstr(sv_trim_right(sv0)));
    printf("--------------------\n");
    printf("trim: %s\n", sv_to_cstr(sv_trim(sv0)));
    printf("--------------------\n");
    StringView sv1 = sv_from_cstr("Hello there, general Kenobi");
    StringView chop = {0};
    do {
        chop = sv_chop_by_delim(&sv1, ' ');
        printf(SV_F "\n", SV_ARG(chop));
    } while (chop.len > 0);
}

bool sv_is_whitespace(char c) {
    const char *whitespace = " \t\n";
    while (*whitespace != 0) {
        if (c == *whitespace)
            return true;
        whitespace++;
    }
    return false;
}

StringView sv_from_cstr(const char *cstr) {
    size_t cnt = strlen(cstr);
    StringView sv = {0};
    sv.ptr = cstr;
    sv.len = cnt;
    return sv;
}

char *sv_to_cstr(StringView sv) {
    char *res = malloc(sv.len + 1);
    memcpy(res, sv.ptr, sv.len);
    res[sv.len] = 0;
    return res;
}

StringView sv_trim_left(StringView sv) {
    while (sv.len > 0 && sv_is_whitespace(*sv.ptr)) {
        sv.ptr++;
        sv.len--;
    }
    return sv;
}

StringView sv_trim_right(StringView sv) {
    while (sv.len > 0 && sv_is_whitespace(sv.ptr[sv.len - 1])) {
        sv.len--;
    }
    return sv;
}

StringView sv_trim(StringView sv) { return sv_trim_right(sv_trim_left(sv)); }

StringView sv_chop_by_delim(StringView *sv, char delim) {
    size_t i = 0;
    while (i < sv->len && sv->ptr[i] != delim)
        i++;
    StringView res = {.ptr = sv->ptr, .len = i};
    if (i < sv->len) {
        sv->len -= i + 1;
        sv->ptr += i + 1;
    } else {
        sv->len -= i;
        sv->ptr += i;
    }
    return res;
}
