#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e6 + 5;
int a[MAXN];

int q_sort(int left, int right) {
    int mid = a[left];
    while (left < right) {
        while (left < right && mid <= a[right])
            right--;
        a[left] = a[right];
        while (left < right && a[left] <= mid) 
            left++;
        a[right] = a[left];
    }
    a[left] = mid;
    return left;
}

void find_kth(int left, int right, int k) {
    int pos = q_sort(left, right);
    if (k == pos)
        cout << a[k];
    else if (k < pos)
        find_kth(left, pos - 1, k);
    else
        find_kth(pos +  1, right, k);
    return;
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) 
        scanf("%d", &a[i]);
    find_kth(0, n - 1, k);
    return 0;
}