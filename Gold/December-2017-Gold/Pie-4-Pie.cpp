#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <queue>
#include <functional>
using namespace std;

class Solution {
    private:
        int N, D;
        set<pair<int, int>, greater<pair<int, int>>> b;
        set<pair<int, int>, greater<pair<int, int>>> e;
        vector<pair<int, int>> bStart;
        queue<vector<int>> q;

        struct PairHash {
            size_t operator()(const std::pair<int, int>& e) const {
                vector<int> v = {e.first, e.second};
                std::hash<int> hasher;
                size_t seed = 0;
                for (int i : v) {
                    seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                }
                return seed;
            }
        };
        unordered_map<pair<int, int>, int, PairHash> shortestB;
    public:
        void prepData() {
            ifstream fin ("piepie.in");
            fin >> N >> D;
            int t1, t2;
            for (int i = 0; i < 2*N; i++) {
                fin >> t1 >> t2;
                if (i < N) { b.insert(make_pair(t2, t1)); bStart.push_back(make_pair(t2, t1)); }
                else e.insert(make_pair(t1, t2));
            }
        }

        void main() {
            prepData();
            ofstream fout ("piepie.out");   
            int count = 0; 
            for (auto i: b) if (i.first == 0) { q.push({i.first, i.second, 1}), b.erase(i); }
            for (auto i: e) if (i.first == 0) { q.push({i.first, i.second, 0}), e.erase(i); }
            for (auto i: b) shortestB[i] = -1;
            int moves = 0;
            while(!q.empty()) {
                int size = q.size(); moves++;
                for (int j = 0; j < size; j++) {
                    vector<int> curr = q.front(); q.pop();
                    if (curr[2] == 1) {
                        shortestB[make_pair(curr[0], curr[1])] = moves;
                        auto i = (e.lower_bound(make_pair(curr[1], 2000000000)));
                        while (i != e.end() && curr[1] - i->first <= D) {
                            q.push({i->first, i->second, 0}); e.erase(i++);
                        }
                    }
                    else {
                        auto i = (b.lower_bound(make_pair(curr[1], 2000000000)));
                        while (i != b.end() && curr[1] - i->first <= D) {
                            q.push({i->first, i->second, 1}); b.erase(i++);
                        }
                    }
                    
                }
            }

            for (auto i: bStart) {
                fout << shortestB[i] << endl;
            }
        }
};

int main() {
    Solution s;
    s.main();
}