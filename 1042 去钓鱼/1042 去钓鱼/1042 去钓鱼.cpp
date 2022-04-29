#include <iostream>
#include <cstdio>
#include <cstring>
#define N 30
using namespace std;

int n, m;
int f[N], d[N], left_f[N];
int t[N], wait[N], tmp[N];
int max1, max2;

void update() {
	for (int i = 0; i < n; i++)
		wait[i] = tmp[i];
}

void fishing() {
	memset(wait, 0, sizeof(wait));
	max2 = -1;
	int go_time = 0;
	int fish_time = m;
	for (int i = 0; i < n; i++) {
		max1 = 0;
		memset(tmp, 0, sizeof(tmp));
		fish_time = m-go_time;
		for (int j = 0; j < n; j++) {
			left_f[j] = f[j];
		}
		while (true) {
			if (fish_time < 5) break;
			int maxp = -1;
			int lake_id;
			for (int j = 0; j <= i; j++) {
				if (left_f[j] > maxp) {
					maxp = left_f[j];
					lake_id = j;
				}
			}
			if (!maxp) {
				tmp[0] += fish_time / 5 * 5;
				break;
			}
			tmp[lake_id] += 5;
			max1 += left_f[lake_id];
			left_f[lake_id] -= d[lake_id];
			if (left_f[lake_id] < 0) {
				left_f[lake_id] = 0;
			}
			fish_time -= 5;
		}
		if (max1 > max2) {
			max2 = max1;
			update();
		}
		else if (max1 == max2) {
			for (int j = 0; j < n; j++) {
				if (tmp[j] < wait[j]) break;
				if (tmp[j] > wait[j]) update();
			}
		}
		go_time += t[i];
		if (go_time > m) break;
	}
	cout << wait[0];
	for (int i = 1; i < n; i++)
		cout << ", " << wait[i];
	cout << endl << "Number of fish expected: " << max2 << endl << endl;
}

int main()
{
	while (~scanf("&d", &n) && n) {
		cin >> m;
		m *= 60;
		for (int i = 0; i < n; i++) {
			cin >> f[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> d[i];
		}
		for (int i = 0; i < n - 1; i++) {
			cin >> t[i];
			t[i] *= 5;
		}
		fishing();
	}
	return 0;

}


