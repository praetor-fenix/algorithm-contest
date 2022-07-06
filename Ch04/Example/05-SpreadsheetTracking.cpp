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

const int MAX_OP = 1000 + 10;
const int MAX_CMD = 10 + 10;
const int MAX_LABEL = 10 + 10;

const char DR[] = "DR";
const char DC[] = "DC";
const char IR[] = "IR";
const char IC[] = "IC";
const char EX[] = "EX";
const char CMD_LEN = 2;

struct Operation {
    char cmd[MAX_CMD];
    int num;
    int label[MAX_LABEL];
};

int main() {
    int rnd = 0;
    int mr = 0, mc = 0;
    Operation ops[MAX_OP];
    while((scanf("%d%d", &mr, &mc) == 2) && (mr != 0 && mc != 0)) {
        int o = 0;
        scanf("%d", &o);
        for(int i = 0; i < o; ++i) {
            Operation *p = &ops[i];
            scanf("%s", p->cmd);
            if(strncmp(p->cmd, EX, CMD_LEN) == 0) {
                p->num = 4;
            } else {
                scanf("%d", &p->num);
            }

            for(int i = 0; i < p->num; ++i) {
                scanf("%d", &p->label[i]);
            }
        }

        if(rnd++ > 0) {
            printf("\n");
        }
        printf("Spreadsheet #%d\n", rnd);

        int q = 0;
        scanf("%d", &q);
        for(int i = 0; i < q; ++i) {
            int sr = 0, sc = 0;
            scanf("%d%d", &sr, &sc);
            int qr = sr, qc = sc;
            bool ok = true;
            for(int j = 0; j < o; ++j) {
                int d = 0;
                Operation *p = &ops[j];
                if(strncmp(p->cmd, IR, CMD_LEN) == 0) {
                    for(int k = 0; k < p->num; ++k) {
                        if(p->label[k] <= qr) {
                            ++d;
                        }
                    }
                    qr += d;
                } else if(strncmp(p->cmd, IC, CMD_LEN) == 0) {
                    for(int k = 0; k < p->num; ++k) {
                        if(p->label[k] <= qc) {
                            ++d;
                        }
                    }
                    qc += d;
                } else if(strncmp(p->cmd, DR, CMD_LEN) == 0) {
                    for(int k = 0; k < p->num; ++k) {
                        if(p->label[k] == qr) {
                            ok = false;
                            break;
                        } else if(p->label[k] < qr) {
                            ++d;
                        }
                    }
                    qr -= d;
                } else if(strncmp(p->cmd, DC, CMD_LEN) == 0) {
                    for(int k = 0; k < p->num; ++k) {
                        if(p->label[k] == qc) {
                            ok = false;
                            break;
                        } else if(p->label[k] < qc) {
                            ++d;
                        }
                    }
                    qc -= d;
                } else {
                    if(p->label[0] == qr && p->label[1] == qc) {
                        qr = p->label[2];
                        qc = p->label[3];
                    } else if(p->label[2] == qr && p->label[3] == qc) {
                        qr = p->label[0];
                        qc = p->label[1];
                    }
                }

                if(!ok) {
                    break;
                }
            }

            if(!ok) {
                printf("Cell data in (%d,%d) GONE\n", sr, sc);
            } else {
                printf("Cell data in (%d,%d) moved to (%d,%d)\n", sr, sc, qr, qc);
            }
        }
    }
    
    return 0;
}