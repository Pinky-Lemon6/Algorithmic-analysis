/*题目：POJ 1475
  思路：可以用BFS，但是不一定是箱子的最短路径引起答案正确，箱子应该是
  找一条合适的路，不可在BFS完箱子后再枚举人的路径，故在BFS箱子的路径时
  顺便判断一下人的路径，看是否满足要求即可。
  */



#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <string>
#define N 25
using namespace std;
int n, m, sx, sy, bx, by, ex, ey, fuck, vis[N][N][4], to[N][N];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
char how[4] = { 'N','S','W','E' }, sm[4] = { 'n','s','w','e' }; // the dirction
char s[N][N];
// x,y 是人的坐标   tox,toy是箱子的坐标
struct node { int x, y, tox, toy; string ans; }now, nxt, pre;
queue<node> G, S;
string temp;
inline bool check(int x, int y) { if (x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] != '#') return 1; return 0; }
bool Find(int startx, int starty, int tox, int toy, int canx, int cany)
{
    temp = "";
    memset(to, 0, sizeof to);
    while (!S.empty()) S.pop();
    node bb;
    bb.x = startx, bb.y = starty; S.push(bb);
    while (!S.empty())
    {
        node last = S.front(); S.pop();
        if (last.x == tox && last.y == toy) { temp = last.ans; return true; }
        for (int i = 0; i < 4; i++)
        {
            node yy = last; yy.x += dx[i]; yy.y += dy[i];
            if (!check(yy.x, yy.y) || (yy.x == canx && yy.y == cany) || to[yy.x][yy.y]) continue;
            to[yy.x][yy.y] = 1;
            yy.ans = last.ans + sm[i];
            S.push(yy);
        }
    }
    return false;
}
string BFS_BOX()
{
    now.x = sx, now.y = sy;  // 从人所在的位置开始
    now.tox = bx, now.toy = by; // 箱子的位置
    now.ans = "";
    while (!G.empty()) G.pop();
    G.push(now);
    while (!G.empty())
    {
        now = G.front(); G.pop();
        if (now.tox == ex && now.toy == ey)
            return now.ans;
        for (int i = 0; i < 4; i++)
        {
            // 人不能走到箱子的后面，所以箱子可以移动
            // 因此只需要移动箱子然后判断人是否能够到达
            nxt = now;
            nxt.tox += dx[i], nxt.toy += dy[i];
            nxt.x = now.tox, nxt.y = now.toy;
            if (!check(nxt.tox, nxt.toy) || vis[nxt.tox][nxt.toy][i]) continue;
            if (i == 0)
            {
                if (Find(now.x, now.y, now.tox + 1, now.toy, now.tox, now.toy)) nxt.ans += temp; else continue;
            }
            if (i == 1)
            {
                if (Find(now.x, now.y, now.tox - 1, now.toy, now.tox, now.toy)) nxt.ans += temp; else continue;
            }
            if (i == 2)
            {
                if (Find(now.x, now.y, now.tox, now.toy + 1, now.tox, now.toy)) nxt.ans += temp; else continue;
            }
            if (i == 3)
            {
                if (Find(now.x, now.y, now.tox, now.toy - 1, now.tox, now.toy)) nxt.ans += temp; else continue;
            }
            vis[nxt.tox][nxt.toy][i] = 1;
            nxt.ans += how[i];
            G.push(nxt);

        }
    }
    return "Impossible.";
}
int main()
{
    while (~scanf("%d%d", &n, &m) && n && m)
    {
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> s[i][j];
                if (s[i][j] == 'S') sx = i, sy = j;
                if (s[i][j] == 'B') bx = i, by = j;
                if (s[i][j] == 'T') ex = i, ey = j;
            }
        printf("Maze #%d\n", ++fuck);
        cout << BFS_BOX() << endl;
        puts("");
    }
    return 0;
}
