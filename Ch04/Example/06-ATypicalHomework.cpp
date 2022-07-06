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
const int MAX_LEN = 10 + 10;
const int MAX_SCORE = 4;
const int PASS_SCORE = 60;

struct Student {
    char sid[MAX_LEN];
    int cid;
    char name[MAX_LEN];
    int score[MAX_SCORE];

    int total() const {
        int res = 0;
        for(int i = 0; i < MAX_SCORE; ++i) {
            res += score[i];
        }

        return res;
    }

    double average() const {
        double res = 0.0;
        for(int i = 0; i < MAX_SCORE; ++i) {
            res += score[i];
        }

        return res / (MAX_SCORE * 1.0) + 1e-5;
    }
};

const char *SUBJECT_NAME[] = {
    "Chinese",
    "Mathematics",
    "English",
    "Programming",
};

int main_menu() {
    printf("Welcome to Student Performance Management System (SPMS).\n\n");
    printf("1 - Add\n");
    printf("2 - Remove\n");
    printf("3 - Query\n");
    printf("4 - Show ranking\n");
    printf("5 - Show Statistics\n");
    printf("0 - Exit\n\n");

    int n = 0;
    scanf("%d", &n);
    return n;
}

void add_student(vector<Student> &list) {
    while(true) {
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");

        Student entry;
        scanf("%s", entry.sid);
        if(strlen(entry.sid) == 1 && strncmp(entry.sid, "0", 1) == 0) {
            break;
        }

        scanf("%d", &entry.cid);
        scanf("%s", entry.name);
        for(int i = 0; i < MAX_SCORE; ++i) {
            scanf("%d", &entry.score[i]);
        }

        bool valid = true;
        for(int i = 0; i < list.size(); ++i) {
            if(strncmp(list[i].sid, entry.sid, MAXN) == 0) {
                valid = false;
                break;
            }
        }

        if(!valid) {
            printf("Duplicated SID.\n");
        } else {
            list.push_back(entry);
        }
    }
}

void remove_student(vector<Student> &list) {
    char query[MAX_LEN];
    while(true) {
        printf("Please enter SID or name. Enter 0 to finish.\n");

        scanf("%s", query);
        if(strlen(query) == 1 && strncmp(query, "0", 1) == 0) {
            break;
        }

        int cnt = 0;
        for(int i = list.size() - 1; i >= 0; --i) {
            if(strncmp(list[i].sid, query, MAX_LEN) == 0 || 
                strncmp(list[i].name, query, MAX_LEN) == 0) {
                list.erase(list.begin() + i);
                ++cnt;
            }
        }

        printf("%d student(s) removed.\n", cnt);
    }
}

void query_student(const vector<Student> &list) {
    char query[MAX_LEN];
    while(true) {
        printf("Please enter SID or name. Enter 0 to finish.\n");

        scanf("%s", query);
        if(strlen(query) == 1 && strncmp(query, "0", 1) == 0) {
            break;
        }

        for(int i = 0; i < list.size(); ++i) {
            if(strncmp(list[i].sid, query, MAX_LEN) == 0 ||
                strncmp(list[i].name, query, MAX_LEN) == 0) {
                int rank = 1;
                int total = list[i].total();
                for(int j = 0; j < list.size(); ++j) {
                    if(list[j].total() > total) {
                        ++rank;
                    }
                }

                printf("%d %s %d %s ", rank, list[i].sid, list[i].cid, list[i].name);
                for(int j = 0; j < MAX_SCORE; ++j) {
                    printf("%d ", list[i].score[j]);
                }
                printf("%d %.2lf\n", list[i].total(), list[i].average());
            }
        }
    }
}

void show_rank() {
    printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
}

void show_stat(const vector<Student> &list) {
    printf("Please enter class ID, 0 for the whole statistics.\n");

    int query = 0;
    scanf("%d", &query);

    int num = 0;
    int total[MAX_SCORE], pass[MAX_SCORE];
    int overall[MAX_SCORE + 1];
    memset(total, 0, sizeof(int) * MAX_SCORE);
    memset(pass, 0, sizeof(int) * MAX_SCORE);
    memset(overall, 0, sizeof(int) * (MAX_SCORE + 1));
    
    for(int i = 0; i < list.size(); ++i) {
        if(query == 0 || list[i].cid == query) {
            ++num;
            int cnt = 0;
            for(int j = 0; j < MAX_SCORE; ++j) {
                int score = list[i].score[j];
                total[j] += score;
                if(score >= PASS_SCORE) {
                    ++cnt;
                    pass[j] += 1;
                }
            }

            overall[cnt] += 1;
        }
    }

    for(int i = 0; i < MAX_SCORE; ++i) {
        printf("%s\n", SUBJECT_NAME[i]);
        printf("Average Score: %.2lf\n", (double)total[i] / (double)num + 1e-5);
        printf("Number of passed students: %d\n", pass[i]);
        printf("Number of failed students: %d\n\n", num - pass[i]);
    }

    printf("Overall:\n");
    printf("Number of students who passed all subjects: %d\n", overall[MAX_SCORE]);
    for(int i = MAX_SCORE - 1; i > 0; --i) {
        overall[i] += overall[i + 1];
        printf("Number of students who passed %d or more subjects: %d\n", i, overall[i]);
    }
    printf("Number of students who failed all subjects: %d\n\n", overall[0]);
}

int main() {
    vector<Student> list;
    int cmd = 0;
    do {
        cmd = main_menu();
        switch(cmd) {
            case 1:
                add_student(list);
                break;
            case 2:
                remove_student(list);
                break;
            case 3:
                query_student(list);
                break;
            case 4:
                show_rank();
                break;
            case 5:
                show_stat(list);
                break;
        }
    } while(cmd > 0);

    return 0;
}