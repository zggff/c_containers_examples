#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2

typedef struct StringBuilder {
    char *str;
    int len;
    int cap;
} StringBuilder;

StringBuilder *sb_start() {
    StringBuilder *sb = malloc(sizeof(StringBuilder));
    sb->str = malloc(INITIAL_CAPACITY);
    sb->cap = INITIAL_CAPACITY;
    return sb;
}

void sb_append(StringBuilder *sb, const char *str) {
    int len = strlen(str);
    if (sb->len + len + 1 > sb->cap)
        sb->str = realloc(sb->str, sb->cap * 2);
    memcpy(sb->str + sb->len, str, len);
    sb->len += len;
    sb->str[sb->len] = 0;
}

void sb_push(StringBuilder *sb, char val) {
    if (sb->len + 2 > sb->cap) {
        sb->str = realloc(sb->str, sb->cap * 2);
    }
    sb->str[sb->len] = val;
    sb->len++;
    sb->str[sb->len] = 0;
}

char *sb_end(StringBuilder *sb) {
    char *res = sb->str;
    free(sb);
    return res;
}

void sb_free(StringBuilder *sb) {
    free(sb->str);
    free(sb);
}

int main() {
    StringBuilder *sb = sb_start();
    sb_push(sb , 'Z');
    sb_append(sb, "ewa");
    sb_push(sb, '\n');
    sb_append(sb, "Hello, World\n");
    sb_append(sb, "This is String Builder\n");
    char *str = sb_end(sb);
    printf("%s", str);
}
