#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int N;
        vector<vector<int> > points;
    public:
        void main() {
            ifstream fin ("balancing.in");
            ofstream fout ("balancing.out");
            fin >> N;
            int p1, p2;
            for (int i = 0; i < N; i++) {
                fin >> p1 >> p2;
                points.push_back({p1, p2});
            }
            vector<vector<int> > xSorted = points;
            vector<vector<int> > ySorted = points;
            sort(xSorted.begin(), xSorted.end());
            sort(ySorted.begin(), ySorted.end(), [](vector<int> a, vector<int> b){return a[1] < b[1];});    
            int y = 0;
            int res = 9999999;

            while (y < ySorted.size()) {
                int q1 = ySorted.size()-y; //q1 starts with everything above y
                int q3 = y; //q3 starts withe everything below y
                int q2 = 0;
                int q4 = 0;
                int x = 0;
                if (max({q1, q2, q3, q4}) < res) res = max({q1, q2, q3, q4});
                while(x < xSorted.size()) {
                    if (xSorted[x][1] > ySorted[y][1]-1) {
                        q1--;
                        q2++;
                    } else {
                        q3--;
                        q4++;
                    }
                    x++;
                    while (x != xSorted.size() && xSorted[x][0] == xSorted[x-1][0]) {
                        if (xSorted[x][1] > ySorted[y][1]-1) {
                            q1--;
                            q2++;
                        } else  {
                            q3--;
                            q4++;
                        }
                        x++;
                        if (x == xSorted.size()) break;
                    }
                    if (max({q1, q2, q3, q4}) < res) res = max({q1, q2, q3, q4});
                }
                y++;
                while(y != ySorted.size() && ySorted[y][1] == ySorted[y-1][1]) {
                    y++;
                }
            }
            fout << res;
        }
};

int main() {
    Solution s;
    s.main();
}