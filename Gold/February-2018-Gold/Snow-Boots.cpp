#include <functional>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

class Solution {
    private:
        int N, B;
        vector<vector<int>> boots; // each boot is depth size per boot then step size per boot
        vector<int> field;
        int next[100000];
        int widths[100000];
    public:
        void prepData() {
            ifstream fin ("snowboots.in");
            fin >> N >> B; int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a; field.push_back(a);
            }
            for (int i = 0; i < B; i++) {
                fin >> a >> b; boots.push_back({a, b, i});
            }
            sort(boots.begin(), boots.end(), greater<vector<int>>());

            for (int i = 0; i < N; i++) next[i] = i+1;

            for (int i = 0; i < 100000; i++) widths[i] = 1;
        }

        void combine(int a, int b) {
            widths[a] += widths[b];
            next[a] = next[b];
        }
        
        void main() {
            prepData();
            ofstream fout ("snowboots.out");
            
            vector<pair<int, int>> ans;
            for (auto& i: boots) {
                int j = 1; int lWidth = 0; int mxWidth = 0; int prevJ = 0;
                // cout << " --------- " <<endl;
                while (j != N) {
                    // cout << prevJ << " " << j << endl;
                    if (field[prevJ] > i[0]) { 
                        if (field[j] > i[0]) { combine(prevJ, j); lWidth = widths[prevJ]; }
                        else { lWidth = widths[prevJ]; prevJ = j; }
                    }
                    else prevJ = j;
                    if (lWidth > mxWidth) mxWidth = lWidth;
                    j = next[j]; 
                }
                // for (int z = 0; z < N; z++) cout << widths[z] << " ";
                // cout << endl;
                // cout << i[0] << " " << i[1] << " " << mxWidth << endl;
                if (mxWidth >= i[1]) ans.push_back(make_pair(i[2], 0));
                else ans.push_back(make_pair(i[2], 1));
            }

            sort(ans.begin(), ans.end());

            for (auto& i: ans) cout << i.second << endl;

        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}