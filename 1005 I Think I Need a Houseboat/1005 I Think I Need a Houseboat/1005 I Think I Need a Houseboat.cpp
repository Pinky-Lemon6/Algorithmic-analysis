/*题目：POJ 1005
  思路：根据题目要求，满足关系式
  time = (PI *( pow(x, 2) + pow(y, 2) )/ 100)+1
  分别对每个输入的点进行判断即可
  */

#include <iostream>
#include <math.h>
using namespace std;


int main()
{
    int n;
    cin >> n;
    float PI, x, y, time;
    PI = 3.1415926;
    
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        time = (int)(PI *( pow(x, 2) + pow(y, 2) )/ 100)+1;
        cout << "Property "<<i<<": This property will begin eroding in year "<< time<<".\n"  ;
    }
    cout << "END OF OUTPUT."<<endl;
    return 0;
}


