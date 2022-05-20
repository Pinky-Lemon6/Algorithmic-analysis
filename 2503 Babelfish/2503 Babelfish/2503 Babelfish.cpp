/*题目：POJ 2503
  思路：对输入的字符串按字典序升序排列(qsort)，然后进行二分查找即可*/


#include <iostream>
# include <stdio.h>
#include<string.h>
#include<stdlib.h> 
const int MAX = 100001;
typedef struct
{
	char e[11];
	char f[11];
}Entry;
Entry entry[MAX];
int i = 0;		//词典总条数

int cmp(const void* a, const void* b) //按字典序比较
{
	return strcmp((*(Entry*)a).f, (*(Entry*)b).f);
}
int BinSearch(char c[])
{
	int low = 0, high = i - 1;
	int mid, t;
	while (low <= high) //二分查找
	{
		mid = (low + high) / 2;
		t = strcmp(entry[mid].f, c);  //字符匹配 
		if (t == 0)
			return mid;
		else if (t == -1)  //小了
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

int main()
{
	char str[25];
	int index = -1;
	while (gets_s(str))
	{
		if (str[0] == '\0')
			break;
		sscanf_s(str, "%s%s", entry[i].e, entry[i].f);
		i++;
	}
	qsort(entry, i, sizeof(Entry), cmp);  //对输入的字典进行快排
	while (gets_s(str))
	{
		index = BinSearch(str);
		if (index == -1)
			printf("eh\n");
		else
			printf("%s\n", entry[index].e);
	}

	return 0;
}
