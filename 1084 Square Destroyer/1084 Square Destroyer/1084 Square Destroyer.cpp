/*题目：POJ 1084
  思路：IDA*，开两个数组stick,square;stick[i]表示需要编号为i的木棒
  的正方形，square表示编号为[i]的正方形需要的木棒;exi[i]表示的是编号
  为i的木棒的正方形，如果exi[i]==0，表示存在，删去该正方形上的一根火柴
  exi[i]--。观察一下木棒的编号规律，提前预处理出来正方形们以及木棒们
  开始搜索，找到一个还存在的正方形，枚举删除它的哪一根木棒，递归。
  估值函数：对于当前一个状态，枚举每个正方形是否存在，如果存在，
  就删除它的所有木棍，同时res++，然后继续枚举，最后返回res。
  */


#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int T, n, k, totstick, totsquare, neibor;
int ans, maxd;           //ans与估值下限都是全局变量
int exi[65], temp[65];   //temp和exi都是全局变量函数

vector <int> stick[65];
vector <int> square[65];

int h()                  //估值函数
{                        // 估值就是放缩，估，合理地放缩
                         //拿走一条边等价拿走怎个正方形造成的破化。
    int res = 0;
    for (int i = 1; i <= totsquare; i++)
        temp[i] = exi[i];
    for (int i = 1; i <= totsquare; i++)
        if (!temp[i])             //找到所有不被坏的正方形，一个正方形一条边就能破坏
        {                        //但一条边能破坏多个正方形，因为不能原来的储存被破坏
                                 //所以要用临时的数组存储状态
            res++;
            temp[i] -= square[i].size();
            for (int j = 0; j < square[i].size(); j++)   //当前正方形的每一条边。
                for (int l = 0; l < stick[square[i][j]].size(); l++)  //每一条边对应的正方形
                {
                    temp[stick[square[i][j]][l]]--;    //破坏
                }
        }
    return res;                              //
}
bool dfs(int sum)                            //深搜是看能不能在这个估值下限，找到能够能拆掉所有正方形的方法。
{
    if (sum + h() >= maxd)                        //利用下界估值，减少递归次数，减少花费的时间
        return 0;                                //在趋近最优解时，能高效地节省时间
    int tmp = 1;
    while (exi[tmp] < 0 && tmp <= totsquare)        //一直循环都不存在的话，tmp就会超过totsquare
        tmp++;                                   //也就实现了最终目的
                                                 //再次强调正方形有大也有小，边长从小到大，对应的正方形序号从小增到大
    if (tmp > totsquare)
    {
        ans = min(sum, ans);
        return 1;
    }
    for (int i = 0; i < square[tmp].size(); i++)    //对当前正方形进行破坏，枚举每一条边破坏的情况
    {                                        //感觉这里就是枚举了，没有做任何优化
        int sti = square[tmp][i];              //提取当前正方形的每一根火柴
        for (int j = 0; j < stick[sti].size(); j++) //对每一根火柴，枚举其对应的所有正方形
            exi[stick[sti][j]]--;                //删掉该火柴的每一个对应正方形
        if (dfs(sum + 1))                       //去掉一条边，sum就加1了
            return 1;                            //成功了肯定不用回溯，直接return就行
        for (int j = 0; j < stick[sti].size(); j++)
            exi[stick[sti][j]]++;                //回溯。
    }
    return 0;
}
int main()
{
    int i;
    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        totstick = (n + 1) * n * 2;
        totsquare = 0;
        neibor = n * 2 + 1;
        for (i = 1; i < 65; i++)
        {
            stick[i].clear();
            square[i].clear();
        }
        for (int sz = 1; sz <= n; sz++)                             //sz是边的大小。
                                                             //因为正方形的边是从1~n逐级增大的。
                                                             //因为有小大正方形之分
                                                             //利用这个sz可以每次将所有边长为sz的正方形的边序号定位
                                                             //这个序号还是白皮书上的序号吧
            for (int i = 1; i <= (n - sz) * neibor + 1; i += neibor)            //i是一个正方形的上边的开始
                for (int j = i; j - i + sz <= n; j++)                           //j是一个正方形的左边的开始
                {
                    totsquare++;
                    for (int l = j; l - j < sz; l++)                          //l开始枚举
                    {                                                //这里的sz就是正方形边长的限制
                        square[totsquare].push_back(l);              //这存的是同一个正方形的上边的所有火柴
                        square[totsquare].push_back(l + sz * neibor);    //这存的是同一个正方形的下边的所有火柴
                        stick[l].push_back(totsquare);               //这存的是该火柴所属的正方形，正方形的上火柴
                        stick[l + sz * neibor].push_back(totsquare);     //这存的是该火柴所属的正方形，正方形的下火柴
                    }
                    for (int l = j + n; (l - j - sz) / neibor < sz; l += neibor) //同理，这里是左右
                    {
                        square[totsquare].push_back(l);
                        square[totsquare].push_back(l + sz);
                        stick[l].push_back(totsquare);
                        stick[l + sz].push_back(totsquare);
                    }
                }
        memset(exi, 0, sizeof(exi));            //重置存在数组，0，是表示存在。
        for (int i = 1; i <= k; i++)
        {
            int a;
            cin >> a;
            for (int j = 0; j < stick[a].size(); j++)
            {
                exi[stick[a][j]]--;           //stcik[t][j]表示t这条木棍对应的正方形
            }
            totstick--;                      //木棍拿走，总共的木棍减1.
        }
        ans = totstick;                         //一开始ans=目前最大的木棍数。
        for (maxd = 1;; maxd++)                   //定义估值下限，下限肯定是从0开始的。但这里用的是1开始
        {                                     //额，感觉这道题就不会有不用拿的情况的。
            if (dfs(0))                        //估值下限为全局变量
                break;                            //估值下限的使用方法，就是用这个for从最小开始枚举。
        }                                     //一旦找到解，则x就是最优解。
        cout << ans << endl;
    }
    return 0;
}

