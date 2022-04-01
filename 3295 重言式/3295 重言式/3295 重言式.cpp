#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
int num[35][6];
char s[105];

int main(){
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i & (1 << j)) {
                num[i][j] = 1;
            }
            else {
                num[i][j] = 0;
            }
        }
    }

    while (scanf("%s",s)==1) {
        int flag = 1;
        if (s[0] == '0') break;
        for (int k = 0; k < 32; ++k) {
            int len = strlen(s);
            int top = 0;
            int goal[105];
            for (int j, i = len - 1; i >= 0; --i) {
                if (s[i] >= 'p' && s[i] <= 't') {
                    goal[top++] = num[k][s[i] - 'p'];
                }
                else {
                    switch (s[i])
                    {
                    case 'K':
                        goal[top - 2] = goal[top - 2] && goal[top - 1];
                        --top;
                        break;
                    case 'A':
                        goal[top - 2] = goal[top - 2] || goal[top - 1];
                        --top;
                        break;
                    case 'N':
                        goal[top - 1] = !goal[top - 1];
                        break;
                    case 'C':
                        goal[top - 2] = !goal[top - 2] || goal[top - 1];
                        --top;
                        break;
                    case 'E':
                        goal[top - 2] = goal[top - 2] == goal[top - 1];
                        --top;
                        break;
                    default:
                        break;
                    }
                }

            }
            if (goal[0] == 0) flag = 0;
            if (flag == 0) break;

        }
        if (flag) cout << "tautology" << endl;
        else cout << "not" << endl;
    }
        return 0;
}


