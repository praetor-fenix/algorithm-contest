#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

const int MAX_LEN = 10;
const int MAX_CHAR = 1 << MAX_LEN;
const int MAXN = 10000 + 10;

bool read_line(char line[]) {
    int p = 0;
    char ch = '\0';
    memset(line, 0, sizeof(char) * MAXN);
    while(scanf("%c", &ch) == 1 && ch != '\n') {
        line[p++] = ch;
    }

    return strlen(line) > 0;
}

int read_len() {
    int len = 0;
    char ch = '\0';
    for(int i = 0; i < 3; ++i) {
        do {
            scanf("%c", &ch);
        } while(ch != '0' && ch != '1');
        len = (len << 1) + (ch - '0');
    }

    return len;
}

int read_key(int len) {
    int key = 0;
    char ch = '\0';
    for(int i = 0; i < len; ++i) {
        do {
            scanf("%c", &ch);
        } while(ch != '0' && ch != '1');
        key = (key << 1) + (ch - '0');
    }

    return key;
}

int main() {
    char input[MAXN], output[MAXN];
    char table[MAX_LEN][MAX_CHAR];
    while(read_line(input)) {
        int row = 1, col = 0;

        memset(table, 0, sizeof(char) * MAX_LEN * MAX_CHAR);
        int input_len = strlen(input);
        for(int i = 0; i < input_len; ++i) {
            table[row][col] = input[i];
            if(++col == ((1 << row) - 1)) {
                col = 0;
                ++row;
            }
        }

        memset(output, 0, sizeof(char) * MAXN);
        int p = 0, len = 0, key = 0;
        while((len = read_len()) != 0) {
            while((key = read_key(len)) != ((1 << len) - 1)) {
                output[p++] = table[len][key];
            }
        }

        printf("%s\n", output);

        char ch = '\0';
        while(ch != '\n') {
            scanf("%c", &ch);
        }
    }

    return 0;
}