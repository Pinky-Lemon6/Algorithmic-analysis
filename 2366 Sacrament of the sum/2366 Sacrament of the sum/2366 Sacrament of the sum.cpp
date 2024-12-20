﻿/*题目：POJ 2366
  思路：由于两个数组一个递增，一个递减，对于a[i]的每个值，
  在b中使用二分查找，寻找能加起来为10000的值。*/

#include<cstdio>
#include <iostream>

using namespace std;

int a[50005], b[50005];
int n1, n2;

int main()
{
    int min, mid, max;
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        cin >> a[i];
    }
    cin >> n2;
    for (int i = 0; i < n2; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n1; i++) { //对于a[i]的值，在b中进行二分查找
        for (min = 0, max = n2 - 1, mid = (min + max) / 2; min <= max; mid = (min + max) / 2) {
            if (a[i] + b[mid] == 10000) {
                cout << "YES";
                return 0;
            }
            else if (a[i] + b[mid] > 10000) {
                min = mid + 1;
            }
            else max = mid - 1;
        }
    }
    cout << "NO";
    return 0;
}
