/*题目：POJ 1753
  思路：枚举，假如第一行的状态已经确定，则剩下行的翻转方法也可确定了；
       则只需按照求4个数的子集的方式，枚举第一行的翻转方法就可以枚举
       出所有的可能*/


#include <stdio.h>
#include <iostream>
#include <string>
using namespace  std;

string s[4];//输入矩阵
string tmp[4];//当前棋子状态矩阵
bool b[4];//判断枚举，1-4的子集生成
int foot = 100;//步子数
void back2(int x, int y) {//将tmp中的元素性质翻转，例如b转成w，w转成b
    if (tmp[x][y] == 'b')tmp[x][y] = 'w';
    else
        tmp[x][y] = 'b';
}
bool test() {//判断输入矩阵是否直接为全黑或者全白
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (s[i][j] != s[0][0])return false;
        }
    }
    return true;
}
bool test2() {//判断当前棋子矩阵是否直接为全黑或者全白
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tmp[i][j] != tmp[0][0])return false;
        }
    }
    return true;
}
void genera(char flag) {//将当前棋子矩阵变为全黑或者全白的步数
    int root = 0;
    for (int i = 0; i < 4; i++) {//将当前状态初始化为输入状态
        tmp[i] = s[i];
    }
    for (int i = 0; i < 4; i++) {//根据第一行的子集进行转换，即改变第一行的状态
        if (b[i]) {
            root++;
            back2(0, i);
            back2(1, i);
            if (i <= 2)back2(0, i + 1);
            if (i >= 1)back2(0, i - 1);
        }

    }
    for (int i = 0; i < 4; i++) {//根据第一行改变第二行
        if (tmp[0][i] != flag) {
            root++;
            tmp[0][i] = flag;
            back2(1, i);
            if (i <= 2)back2(1, i + 1);
            if (i >= 1)back2(1, i - 1);
            back2(2, i);

        }
    }
    for (int j = 2; j < 4; j++) {//改变第三和第四行
        for (int i = 0; i < 4; i++) {
            if (tmp[j - 1][i] != flag) {
                root++;
                tmp[j - 1][i] = flag;
                back2(j, i);
                if (i <= 2)back2(j, i + 1);
                if (i >= 1)back2(j, i - 1);
                if (j <= 2)back2(j + 1, i);

            }
        }
    }
    if (test2() && root < foot) {//如果当前棋子为全黑或全白则改变最小步数
        foot = root;
    }

}
void gen(int y) {//第一行的全部子集
    if (y == 4) {
        genera('b');//全黑
        genera('w');//全白
    }
    else {
        b[y] = true;//使用位向量法构造第一行的全部子集数
        gen(y + 1);
        b[y] = false;
        gen(y + 1);
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        cin >> s[i];
        b[i] = false;
    }
    if (test()) {
        cout << 0 << endl;//判断当前是否为已经排列好的矩阵
    }
    else
    {//构造矩阵
        gen(0);
        if (foot != 100) {
            cout << foot << endl;
        }
        else
            cout << "Impossible" << endl;//如果无法生成则输出
    }
    return 0;
}