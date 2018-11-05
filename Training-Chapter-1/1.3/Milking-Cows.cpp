/*
    ID: andypre1
    LANG: C++11
    PROB: milk2
*/
#include <fstream>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;
class Solution {
    private:
        int numFarmers;
        vector<vector<int> >intervals;
        unordered_set<int> ids;
        int notMilking = 0;
        int milking = 0;
    public:
        void main() {
            ifstream fin("milk2.in");
            ofstream fout ("milk2.out");
            fin >> numFarmers;
            int a, b;
            for (int i = 1; i < numFarmers+1; i++) {
                fin >> a >> b;
                intervals.push_back({a, -i});
                intervals.push_back({b, i});
            }
            sort(intervals.begin(), intervals.end());
            int start = 0;
            int end = 0;
            for (auto i: intervals) {
                if (i[1] > 0) {
                    ids.erase(-i[1]);
                    if (ids.empty()) {
                        end = i[0];
                        if (milking < i[0]-start) milking = i[0]-start;
                    }
                } else {
                    if(ids.empty()) {
                        if (i[0]-end > notMilking && start != 0) notMilking = i[0]-end;
                        start = i[0];
                    }
                    ids.insert(i[1]);
                }
            }
            fout << milking << " " << notMilking << "\n";
        }
};

int main() {
    Solution s;
    s.main();
}