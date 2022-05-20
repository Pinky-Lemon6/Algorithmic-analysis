/*题目：POJ 1700
  思路：假设n个人单独过河所需要的时间存储在数组t中，将数组t按升序排序，
  每次要将单独过河时间最多的两个人送到对岸，1.可以让最快的和次快的过河，
  然后最快的把船划回来，再让最慢的和次慢的过河，次快的把船划回来，时间为
  t[0]+2*t[1]+t[n-1];2.最快的和最慢的过河,然后最快的将船划回来,再最快的
  和次慢的过河,然后最快的将船划回来，时间为2*t[0]+t[n-2]+t[n-1]；对剩余的
  人采用同样的方式，在计算时间时从两种方式中寻找最小值相加
*/


#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int T, n, t[1001];
    int i,sum;
    cin >> T;
    while (T--) {
        cin >> n;
        sum = 0;
        for (i = 0; i < n; i++) {
            cin >> t[i];
        }
        sort(t, t + n);
        for (i = n - 1; i > 2; i-=2) {
            if (t[0] + 2 * t[1] + t[i] > 2 * t[0] + t[i - 1] + t[i]) {
                sum += 2 * t[0] + t[i - 1] + t[i];
            }
            else sum += t[0] + 2 * t[1] + t[i];
        }
        if (i == 2) sum += t[0] + t[1] + t[2];
        else if (i == 1) sum += t[1];
        else sum += t[0];
        cout << sum << endl;
    }
    return 0;
}

