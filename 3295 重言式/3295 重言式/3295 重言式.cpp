/*题目：POJ 3295
  思路：p, q, r, s, and t，每个人有两种情况，综合起来一共有32种情况，
  枚举所有情况最后所有情况是真的话就是真。
  首先进行预处理，将所有情况都存放到数组num中，对于表达式，从后向前处理，
  对每一种情况分别枚举，判断最后的结果为真还是为假即可*/


#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
int num[35][6];
char s[105];

int main(){
    for (int i = 0; i < 32; ++i) {  //预处理，将每一种情况保存在num中
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
            for (int j, i = len - 1; i >= 0; --i) { //从后向前处理
                if (s[i] >= 'p' && s[i] <= 't') {
                    goal[top++] = num[k][s[i] - 'p'];
                }
                else {  //枚举每一种情况
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


