#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
    private:
        int N, B;
        vector<int> field;
        vector<vector<int>> boots;
        vector<pair<int, int>> ans;
        int memo[100000] = {};
        unordered_map<int, int> depthWidth;
    public:
        void prepData() {
            ifstream fin ("snowboots.in");
            fin >> N >> B; int a, b;
            for (int i = 0; i < N; i++) { fin >> a; field.push_back(a); }
            for (int i = 0; i < B; i++) { fin >> a >> b; boots.push_back({a, b, i}); }
            sort(boots.begin(), boots.end(), greater<vector<int>>());
            return;
        }

        int largestInterval(int min) {
            if (depthWidth.find(min) != depthWidth.end()) return depthWidth[min];
            int res = 0; int tRes = 0;
            for (auto& i: field) {
                if (i > min) tRes += 1;
                else tRes = 0;
                res = max(res, tRes);
            }
            depthWidth[min] = res;
            return res;
        }
        
        void divide(int topBound, int bottomBound, int tp, int fp, int bp) {
            if (memo[bp] == 1) return;
            memo[bp] = 1; 
            vector<int> boot = boots[bp];
            if (topBound >= boot[1]) ans.push_back(make_pair(boot[2], 0));
            else if (bottomBound < boot[1]) ans.push_back(make_pair(boot[2], 1));
            else {
                int width = largestInterval(boot[0]);
                if (width >= boot[1]) ans.push_back(make_pair(boot[2], 0));
                else ans.push_back(make_pair(boot[2], 1));
                divide(topBound, width, tp, bp, (tp+bp)/2);
                divide(width, bottomBound, bp, fp, (fp+bp+1)/2);
                return;
            }
            divide(topBound, bottomBound, tp, bp, (tp+bp)/2);
            divide(topBound, bottomBound, bp, fp, (fp+bp+1)/2);


        }

        void main() {
            prepData();
            ofstream fout ("snowboots.out");

            divide(0, 2000000000, 0, boots.size()-1, boots.size()/2);
            for (int i = 0; i < boots.size(); i++) {
                if (memo[i] != 1) {
                    cout << i << endl;
                    int m = largestInterval(boots[i][0]);
                    if (m >= boots[i][1]) ans.push_back(make_pair(boots[i][2], 0));
                    else ans.push_back(make_pair(boots[i][2], 1));
                }
            }
            sort(ans.begin(), ans.end());
            for (auto& i: ans) fout << i.second << endl;

            return;
        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}