
class Solution {
    static const int MOD = 1e9 + 7;

    vector<long long> sum, sq, lazy;
    int n;

    void update(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            long long len = r - l + 1;

            sq[node] = (sq[node] + 2 * sum[node] + len) % MOD;
            sum[node] = (sum[node] + len) % MOD;
            lazy[node]++;

            return;
        }

        int mid = (l + r) / 2;
        push(node, l, r);

        if (ql <= mid)
            update(node * 2, l, mid, ql, qr);

        if (qr > mid)
            update(node * 2 + 1, mid + 1, r, ql, qr);

        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
        sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0 || l == r)
            return;

        int mid = (l + r) / 2;
        apply(node * 2, l, mid, lazy[node]);
        apply(node * 2 + 1, mid + 1, r, lazy[node]);

        lazy[node] = 0;
    }

    void apply(int node, int l, int r, long long v) {
        long long len = r - l + 1;

        sq[node] = (sq[node] + 2 * v * sum[node]
                    + v * v % MOD * len) % MOD;

        sum[node] = (sum[node] + v * len) % MOD;
        lazy[node] = (lazy[node] + v) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();

        sum.assign(4 * n, 0);
        sq.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int p = last[nums[r]];

            update(1, 0, n - 1, p + 1, r);

            last[nums[r]] = r;
            ans = (ans + sq[1]) % MOD;
        }

        return ans;
    }
};
