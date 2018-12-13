#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
    private:
        int N, D;
        set<pair<int, int>> b;
        set<pair<int, int>> e;
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
        unordered_set<pair<int, int>, PairHash> eMemo;
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

        //take one pie, then recurse on all the next possible pies to give, when a pie is given back how to 
        // ensure that we dont regive one of the same pies we have already given

        void main() {
            prepData();
            ofstream fout ("piepie.out");   
            int count = 0; 
            for (auto i: b) if (i.first == 0) q.push({i.first, i.second, 1, 0});
            for (auto i: e) if (i.first == 0) q.push({i.first, i.second, 0, 1});
            for (auto i: b) shortestB[i] = -1;
            int moves = 0;
            while(!q.empty()) {
                int size = q.size(); moves++;
                for (int i = 0; i < size; i++) {
                    vector<int> curr = q.front(); q.pop();
                    cout << curr[0] << " " << curr[1] << " " << curr[2] << " " << curr[3] << endl;
                    if (curr[2] == 1) {
                        if (shortestB[make_pair(curr[0], curr[1])] != -1) continue;
                        shortestB[make_pair(curr[0], curr[1])] = moves+curr[3];
                        auto end = e.begin(); end--;
                        for (auto i = (--e.upper_bound(make_pair(curr[1], 2000000000))); i != end && curr[1] - i->first <= D; i--) {
                            q.push({i->first, i->second, 0, curr[3]});
                        }
                    }
                    else {
                        if (eMemo.find(make_pair(curr[0], curr[1])) != eMemo.end()) continue;
                        eMemo.insert(make_pair(curr[0], curr[1]));
                        auto end = b.begin(); end--;
                        for (auto i = (--b.upper_bound(make_pair(curr[1], 2000000000))); i != end && curr[1] - i->first <= D; i--) {
                            q.push({i->first, i->second, 1, curr[3]});
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