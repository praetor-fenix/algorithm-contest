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

const int MAXN = 100 + 10;

int main() {
    int n, k, m;
    int queue[MAXN];
    while((scanf("%d%d%d", &n, &k, &m) == 3) && (n > 0 && k > 0 && m > 0)) {
        memset(queue, 0, sizeof(int) * MAXN);
        int num = n;
        int left = 0, right = n + 1;
        while(num > 0) {
            for(int i = 0; i < k; ++i) {
                do {
                    if(++left > n) {
                        left = 1;
                    }
                } while(queue[left] == 1);
            }

            for(int i = 0; i < m; ++i) {
                do {
                    if(--right < 1) {
                        right = n;
                    }
                } while(queue[right] == 1);
            }

            num -= (left == right ? 1 : 2);
            queue[left] = queue[right] = 1;
            if(left == right) {
                printf("%3d%c", left, (num <= 0 ? '\n' : ','));
            } else {
                printf("%3d%3d%c", left, right, (num <= 0 ? '\n' : ','));
            }
        }
    }
    
    return 0;
}