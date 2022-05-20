/*题目：POJ 1860
  思路：使用Bellman—Ford算法，但是不能在循环一圈之后就与本金比是否
  增大，因为万一转为本金的佣金很高，但是存在一个一次增加一点点的正环
  的话就需要循环很多次才可以高于本金。
*/


#include<iostream>
#include<cstring>

using namespace std;

const int maxm = 105;

struct node {
    int ci, cj;//交换点交换的两种货币
    double cij;//i->j的汇率
    double mij; //手续费
}state[2 * maxm];

int n, m;
int type;//Nick手上的货币种类
double qua;//Nick手上货币的价值
bool flag;
double dist[maxm];

bool solve_case(int v0)
{
    flag = false;
    memset(dist, 0, sizeof(dist));
    dist[v0] = qua;
    for (int k = 1; k <= n; k++)//进行n次 松弛操作
    {
        flag = false;
        for (int i = 0; i < 2 * m; i++) {//判断每一条有向边，加入它是否能使得最大距离增加
            if ((dist[state[i].ci] - state[i].mij) * state[i].cij > dist[state[i].cj])
            {
                dist[state[i].cj] = (dist[state[i].ci] - state[i].mij) * state[i].cij;
                flag = true;
            }
        }
        if (!flag)//已经不再进行松弛
            break;
    }

    for (int k = 0; k < 2 * m; k++)
        if (dist[state[k].cj] < (dist[state[k].ci] - state[k].mij) * state[k].cij)
            return true;
    return false;

}

int cin_case()
{
    while (cin >> n) {
        cin >> m;
        cin >> type >> qua;
        for (int i = 0; i < 2 * m; i += 2) {//输入交换点的信息
            cin >> state[i].ci >> state[i].cj >> state[i].cij >> state[i].mij >> state[i + 1].cij >> state[i + 1].mij;
            state[i + 1].cj = state[i].ci; state[i + 1].ci = state[i].cj;
        }
        return 1;
    }
    return 0;
}

int main()
{
    while (cin_case())
    {
        if (solve_case(type)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}