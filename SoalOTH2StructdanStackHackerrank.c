#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

int twoStacks(int maxSum, int a_count, int* a, int b_count, int* b) {
    int max = 0;
    int sum = 0;
    int items = 0;
    int apos = 0, bpos = 0;
    while (sum <= maxSum && apos < a_count) {
        if (sum + a[apos] > maxSum)
            break;
        sum += a[apos];
        apos++;
        items++;
    }
    while (sum <= maxSum && bpos < b_count) {
        if (sum + b[bpos] > maxSum)
            break;
        sum += b[bpos];
        bpos++;
        items++;
    }
    max = items;
    while (1) {
        if (apos <= 0)
            break;
        apos--;
        sum -= a[apos];
        items--;
        while (sum <= maxSum && bpos < b_count) {
            if (sum + b[bpos] > maxSum)
                break;
            sum += b[bpos];
            bpos++;
            items++;
        }
        if (items > max)
            max = items;
        if (bpos == b_count)
            break;
    }
    return max;
}

int main() {
    int g;
    scanf("%d", &g);
    for (int a0 = 0; a0 < g; a0++) {
        int n;
        int m;
        int x;
        scanf("%d %d %d", &n, &m, &x);
        int* a = malloc(sizeof(int) * n);
        for (int a_i = 0; a_i < n; a_i++) {
            scanf("%d", &a[a_i]);
        }
        int* b = malloc(sizeof(int) * m);
        for (int b_i = 0; b_i < m; b_i++) {
            scanf("%d", &b[b_i]);
        }
        // your code goes here
        int result = twoStacks(x, n, a, m, b);
        printf("%d\n", result);
        free(a);
        free(b);
    }
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);
    while (1) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line)
            break;
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
            break;
        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) {
            data = '\0';
            break;
        }
    }
    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data)
            data = '\0';
    } else {
        data = realloc(data, data_length + 1);
        if (!data)
            data = '\0';
        else
            data[data_length] = '\0';
    }
    return data;
}

char* ltrim(char* str) {
    if (!str)
        return '\0';
    if (!*str)
        return str;
    while (*str != '\0' && isspace(*str))
        str++;
    return str;
}

char* rtrim(char* str) {
    if (!str)
        return '\0';
    if (!*str)
        return str;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end))
        end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;
    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits)
            return splits;
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }
    return value;
}