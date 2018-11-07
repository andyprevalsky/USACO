#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
    private:
        int N;
        vector<vector<int> > lifeguards;
        unordered_map<int, int> timers;
        unordered_set<int> live;
        int total = 0;
    public:
        void main() {
            ifstream fin ("lifeguards.in");
            ofstream fout ("lifeguards.out");
            fin >> N;
            int a, b;
            for (int i = 1; i < N+1; i++) {
                fin >> a >> b;
                lifeguards.push_back({a, -i});
                lifeguards.push_back({b, i});
            }
            sort(lifeguards.begin(), lifeguards.end());

            int id;
            int point;
            int last;
            int startI;
            for (int i = 0; i < lifeguards.size(); i++) {
                id = lifeguards[i][1];
                point = lifeguards[i][0];
                if (id > 0) { 
                    if (live.size() == 1) {
                        timers[*live.begin()] += point-last;
                        total += point - startI;
                    }
                    live.erase(id);
                    last = point;
                } else {
                    if (live.size() == 0) startI = point;
                    if (live.size() == 1) timers[*live.begin()] += point-last;
                    last = point;
                    live.insert(-id);
                    timers[-id] = 0;
                }
            }
            int minInterval = min_element(timers.begin(), timers.end(), [](pair<int, int> l, pair<int, int> r){return l.second < r.second;})->second;
            fout << total-minInterval;
        }
};

int main() {
    Solution s;
    s.main();
}