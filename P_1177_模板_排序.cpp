#include <iostream>
#include <vector>
using namespace std;

void merge_sort(vector<int> &a, int l, int r) {
    if (r - l <= 1) return;
    int mid = (l + r) / 2;
    merge_sort(a, l, mid);
    merge_sort(a, mid, r);

    // merge
    int p1 = l, p2 = mid, k = 0;
    vector<int> temp(r - l);
    while (p1 < mid || p2 < r) {
        if (p2 == r || (p1 < mid && a[p1] <= a[p2])) {
            temp[k++] = a[p1++];
        } else {
            temp[k++] = a[p2++];
        }
    }
    for (int i = l; i < r; i++) {
        a[i] = temp[i - l];
    }
    return;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    merge_sort(a, 0, n);
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    return 0;
}