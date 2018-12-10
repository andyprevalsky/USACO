#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
    private:
        int numPoints;
        pair<int, int> start;
        pair<int, int> end;
        set<pair<int, int>> xSorted;
        set<pair<int, int>> ySorted;
        struct VectorHash {
            size_t operator()(const std::vector<int>& v) const {
                std::hash<int> hasher;
                size_t seed = 0;
                for (int i : v) {
                    seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                }
                return seed;
            }
        };
        unordered_set<vector<int>, VectorHash> memo;
    public:
        void prepData() {
            ifstream fin ("lasers.in");
            fin >> numPoints;
            int a, b;
            fin >> a >> b;
            start = make_pair(a, b);
            xSorted.insert(start);
            ySorted.insert(make_pair(b, a));
            fin >> a >> b;
            end = make_pair(a, b);
            xSorted.insert(end);
            ySorted.insert(make_pair(b, a));
            for (int i = 0; i < numPoints; i++) {
                fin >> a >> b;
                xSorted.insert(make_pair(a, b));
                ySorted.insert(make_pair(b, a));
            }
        }

        vector<pair<int, int>> childrenX(pair<int, int> a) {
            vector<pair<int, int>> res;
            auto s = xSorted.lower_bound(a);
            auto i = s;
            while (i != xSorted.begin() && (--i)->first == a.first) {
                res.push_back(*i);
            }
            i = s;
            while (i != (--xSorted.end()) && (++i)->first == a.first) {
                res.push_back(*i);
            } 
            return res;
        }

        vector<pair<int, int>> childrenY(pair<int, int> a) {
            vector<pair<int, int>> res;
            auto s = ySorted.lower_bound(a);
            auto i = s;
            while (i != ySorted.begin() && (--i)->first == a.first) {
                res.push_back(*i);
            }
            i = s;
            while (i != (--ySorted.end()) && (++i)->first == a.first) {
                res.push_back(*i);
            } 
            return res;
        }

        void main() {
            prepData();
            ofstream fout ("lasers.out");
            queue<vector<int>> q;
            q.push({end.first, end.second, 0}); // 0 is horizontal, 1 is vertical
            q.push({end.first, end.second, 1});
            int moves = -1;
            while(!q.empty()) {
                int size = q.size();
                moves ++;
                for (int i = 0; i < size; i++) {
                    vector<int> n = q.front(); q.pop();
                    if (memo.find({n[0], n[1]}) != memo.end()) continue;
                    if (make_pair(n[0], n[1]) == start) {
                        fout << moves-1 << endl;
                        return;
                    }
                    if (make_pair(n[0], n[1]) != end || n[2] == 1) memo.insert({n[0], n[1]});
                    vector<pair<int, int>> xChildren;
                    vector<pair<int, int>> yChildren;
                    if (n[2] == 1) xChildren = childrenX(make_pair(n[0], n[1]));
                    else yChildren = childrenY(make_pair(n[1], n[0]));
                    for (auto i: xChildren) q.push({i.first, i.second, 0});
                    for (auto i: yChildren) q.push({i.second, i.first, 1});
                }
            }
            fout << -1 << endl;
        }
};

int main() {
    Solution s;
    s.main();
}