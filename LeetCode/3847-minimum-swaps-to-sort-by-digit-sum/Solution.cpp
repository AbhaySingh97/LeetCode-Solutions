
class Solution {
public:
    int digitSum(int n) {
        int s = 0;
        while (n) {
            s += n % 10;
            n /= 10;
        }
        return s;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> a(n);

        for (int i = 0; i < n; ++i)
            a[i] = {nums[i], i};

        sort(a.begin(), a.end(), [&](auto& x, auto& y) {
            int sx = digitSum(x.first);
            int sy = digitSum(y.first);
            return sx != sy ? sx < sy : x.first < y.first;
        });

        vector<bool> vis(n, false);
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            if (vis[i] || a[i].second == i)
                continue;

            int j = i, len = 0;
            while (!vis[j]) {
                vis[j] = true;
                j = a[j].second;
                ++len;
            }
            ans += len - 1;
        }

        return ans;
    }
};
