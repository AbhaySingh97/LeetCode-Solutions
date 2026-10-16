
class Solution {
    static constexpr int MOD = 1000000007;

    vector<int> s, q, lz;
    int n;

    inline void add(int v, int l, int r) {
        long long len = r - l + 1;
        q[v] = (q[v] + 2LL * s[v] + len) % MOD;
        s[v] = (s[v] + len) % MOD;
        lz[v]++;
    }

    inline void push(int v, int l, int r) {
        if (!lz[v] || l == r) return;

        int m = (l + r) >> 1;
        int t = lz[v];

        long long len1 = m - l + 1;
        long long len2 = r - m;

        q[v << 1] = (q[v << 1] + 2LL * t * s[v << 1]
                     + 1LL * t * t % MOD * len1) % MOD;
        s[v << 1] = (s[v << 1] + 1LL * t * len1) % MOD;
        lz[v << 1] += t;

        q[v << 1 | 1] = (q[v << 1 | 1]
                     + 2LL * t * s[v << 1 | 1]
                     + 1LL * t * t % MOD * len2) % MOD;
        s[v << 1 | 1] = (s[v << 1 | 1]
                     + 1LL * t * len2) % MOD;
        lz[v << 1 | 1] += t;

        lz[v] = 0;
    }

    void update(int v, int l, int r, int a, int b) {
        if (a <= l && r <= b) {
            add(v, l, r);
            return;
        }

        push(v, l, r);
        int m = (l + r) >> 1;

        if (a <= m) update(v << 1, l, m, a, b);
        if (b > m) update(v << 1 | 1, m + 1, r, a, b);

        s[v] = (s[v << 1] + s[v << 1 | 1]) % MOD;
        q[v] = (q[v << 1] + q[v << 1 | 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();

        s.assign(4 * n, 0);
        q.assign(4 * n, 0);
        lz.assign(4 * n, 0);

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; ++i) {
            int left = last[nums[i]] + 1;

            update(1, 0, n - 1, left, i);

            last[nums[i]] = i;
            ans += q[1];
            if (ans >= MOD) ans -= MOD;
        }

        return ans;
    }
};
