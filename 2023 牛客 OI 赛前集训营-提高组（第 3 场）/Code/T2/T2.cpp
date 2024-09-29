#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXW = 1e9 + 5; // 假设最大重量
struct SegmentTree {
    struct Node {
        int count;     // 区间内乘客的数量
        long long sum; // 区间内乘客的总重量
    };
    vector<Node> tree;
    int n;

    SegmentTree(int size) : n(size) { tree.resize(4 * n); }

    void update(int idx, int l, int r, int pos, int value) {
        if (l == r) {
            tree[idx].count += 1;
            tree[idx].sum += value;
        } else {
            int mid = (l + r) / 2;
            if (pos <= mid)
                update(2 * idx, l, mid, pos, value);
            else
                update(2 * idx + 1, mid + 1, r, pos, value);
            tree[idx].count = tree[2 * idx].count + tree[2 * idx + 1].count;
            tree[idx].sum = tree[2 * idx].sum + tree[2 * idx + 1].sum;
        }
    }

    // 查询区间 [1, pos] 内能放多少乘客使得重量小于等于 M
    int query(int idx, int l, int r, long long &M) {
        if (l == r) {
            if (tree[idx].sum <= M) {
                M -= tree[idx].sum;
                return tree[idx].count;
            }
            return 0;
        }
        int mid = (l + r) / 2;
        if (tree[2 * idx].sum <= M) {
            M -= tree[2 * idx].sum;
            return tree[2 * idx].count + query(2 * idx + 1, mid + 1, r, M);
        } else {
            return query(2 * idx, l, mid, M);
        }
    }
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        long long M;
        cin >> n >> M;

        vector<int> passengers(n);
        for (int i = 0; i < n; ++i) {
            cin >> passengers[i];
        }

        // 假设乘客的最大体重为 MAXW，线段树范围应该覆盖所有体重
        SegmentTree segTree(MAXW);

        vector<int> result(n, 0);

        for (int i = 0; i < n; ++i) {
            long long remaining_capacity = M;
            int able_to_board =
                segTree.query(1, 0, MAXW - 1, remaining_capacity);
            result[i] = i - able_to_board;

            // 更新线段树，加入当前乘客的重量
            segTree.update(1, 0, MAXW - 1, passengers[i], passengers[i]);
        }

        // 输出每个测试用例的结果
        for (int i = 0; i < n; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
