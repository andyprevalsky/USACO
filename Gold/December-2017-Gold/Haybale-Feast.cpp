#include <fstream>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

#define INF 0x3FFFFFFFFFFFFFFFLL

class Solution {
    private:
        int N; long long minFlavor;
        vector<vector<int>> h;
        multiset<int> spicy;
        int minSpicy = 2000000000;
    public:
        void prepData() {
            ifstream fin ("hayfeast.in");
            fin >> N >> minFlavor;
            int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a >> b;
                h.push_back({a, b});
            }
        }

        void main() {
            prepData();
            ofstream fout ("hayfeast.out");
            int p1 = 0; int p2 = 0;
            long long totalF = 0;
            while (p2 != h.size()) {
                while (p2 != h.size() && totalF < minFlavor) {
                    totalF += h[p2][0]; spicy.insert(h[p2][1]);
                    p2++;
                }
                while (totalF >= minFlavor) {
                    minSpicy = min(minSpicy, *spicy.rbegin());
                    totalF -= h[p1][0];  spicy.erase(spicy.equal_range(h[p1][1]).first);
                    p1++;
                }
            }
            fout << minSpicy << endl;
        }
};

int main() {
    Solution s;
    s.main();
}