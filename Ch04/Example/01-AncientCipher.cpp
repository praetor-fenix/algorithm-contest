#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
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

const int MAXN = 100 + 10;
const int LETTER = 26;

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    char line1[MAXN], line2[MAXN];
    int count1[LETTER], count2[LETTER];
    while(scanf("%s%s", line1, line2) == 2) {
        memset(count1, 0, sizeof(int) * LETTER);
        memset(count2, 0, sizeof(int) * LETTER);
        
        int len1 = strlen(line1), len2 = strlen(line2);
        for(int i = 0; i < len1; ++i) {
            count1[line1[i] - 'A'] += 1;
        }
        for(int i = 0; i < len2; ++i) {
            count2[line2[i] - 'A'] += 1;
        }

        qsort(count1, LETTER, sizeof(int), cmp);
        qsort(count2, LETTER, sizeof(int), cmp);

        bool ok = true;
        for(int i = 0; i < LETTER; ++i) {
            if(count1[i] != count2[i]) {
                ok = false;
                break;
            }
        }

        printf("%s\n", (ok ? "YES" : "NO"));
    }
    
    return 0;
}