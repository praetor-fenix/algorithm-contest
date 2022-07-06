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

const int MAXN = 10000 + 10;
const int MAX_ERROR = 7;
const int LETTER = 26;

int main() {
    int round = 0;
    char word[MAXN], guess[MAXN];
    while((scanf("%d", &round) > 0) && round >= 0) {
        scanf("%s", word);
        scanf("%s", guess);
        
        int time = strlen(guess);
        int len = strlen(word);
        int error = 0, left = len;
        
        bool letter[LETTER];
        for(int i = 0; i < LETTER; ++i) {
            letter[i] = false;
        }

        for(int i = 0; i < time; ++i) {
            char ch = guess[i];
            int hit = 0;
            for(int j = 0; j < len; ++j) {
                if(word[j] == ch) {
                    word[j] = ' ';
                    ++hit;
                }
            }

            if(hit > 0) {
                left -= hit;
            } else if(!letter[ch - 'a']) {
                error += 1;
            }

            letter[ch - 'a'] = true;
            if(left <= 0 || error >= MAX_ERROR) {
                break;
            }
        }

        printf("Round %d\n", round);
        if(left <= 0) {
            printf("You win.\n");
        } else {
            if(error >= MAX_ERROR) {
                printf("You lose.\n");
            } else {
                printf("You chickened out.\n");
            }
        }
    }
    
    return 0;
}