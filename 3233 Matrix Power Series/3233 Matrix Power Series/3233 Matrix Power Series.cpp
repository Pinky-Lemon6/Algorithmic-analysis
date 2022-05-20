/*题目：POJ 3233
  思路：使用二分策略，当k为偶数时，有
  S＝A^1+A^2+……+A^k＝(A^1+A^2+…+A^(k/2))*(1+A^(k/2))
  当k为奇数时只需要加上一个A^k即可*/


#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

struct Mat {
    int a[40][40];
};
Mat a, res;
int n, m, k;

Mat Multi(Mat a, Mat b) {  //矩阵乘法
    Mat c;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c.a[i][j] = 0;
            for (int k = 1; k <= n; k++) {
                c.a[i][j] = ((a.a[i][k] * b.a[k][j]) % m + c.a[i][j]) % m;
            }
        }
    }
    return c;
}

Mat qpow(Mat a, int k) { //矩阵快速幂
    Mat c;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j) c.a[i][j] = 1;
            else c.a[i][j] = 0;
    for (; k; k >>= 1, a = Multi(a, a))
        if (k & 1) c = Multi(c, a);
    return c;
}
void work(int k) {  //二分策略
    if (k == 1) {
        res = a;
        return;
    }
    work(k / 2);
    Mat c = qpow(a, k / 2);
    for (int i = 1; i <= n; i++) {
        c.a[i][i]++;
    }
    res = Multi(res, c);
    if (k % 2 != 0) { //k为奇数时
        Mat d = qpow(a, k);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                res.a[i][j] = (res.a[i][j] + d.a[i][j]) % m;
            }
        }
    }

}
int main()
{
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a.a[i][j]);
        }
    }
    work(k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", res.a[i][j]);
        }
        printf("\n");
    }
    return 0;
}

