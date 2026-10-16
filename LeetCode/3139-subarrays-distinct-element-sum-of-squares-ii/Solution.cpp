
class Solution {
    static constexpr int MOD = 1000000007;

    vector<int> sum, sq, lazy;
    int n;

    void apply(int v, int l, int r, long long x) {
        long long len = r - l + 1;

        sq[v] = (sq[v] + 2LL * x * sum[v] % MOD
                 + x * x % MOD * len) % MOD;

        sum[v] = (sum[v] + x * len) % MOD;
        lazy[v] = (lazy[v] + x) % MOD;
    }

    void push(int v, int l, int r) {
        if (lazy[v] == 0 || l == r) return;

        int m = (l + r) / 2;
        int x = lazy[v];

        apply(v * 2, l, m, x);
        apply(v * 2 + 1, m + 1, r, x);

        lazy[v] = 0;
    }

    void update(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            apply(v, l, r, 1);
            return;
        }

        push(v, l, r);
        int m = (l + r) / 2;

        if (ql <= m)
            update(v * 2, l, m, ql, qr);

        if (qr > m)
            update(v * 2 + 1, m + 1, r, ql, qr);

        sum[v] = (sum[v * 2] + sum[v * 2 + 1]) % MOD;
        sq[v] = (sq[v * 2] + sq[v * 2 + 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();

        sum.assign(4 * n + 5, 0);
        sq.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; ++i) {
            int left = last[nums[i]] + 1;

            update(1, 0, n - 1, left, i);

            last[nums[i]] = i;
            ans = (ans + sq[1]) % MOD;
        }

        return ans;
    }
};
