#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
    private:
        int N, M;
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
        int res = 0;
        unordered_map<vector<int>, vector<vector<int> >, VectorHash> switches;
        unordered_set<vector<int>, VectorHash> lit;
        unordered_set<vector<int>, VectorHash> memo;
    public:
        void readIn() {
            ifstream fin ("lightson.in");
            fin >> N >> M;
            int a, b, c, d;
            for (int i = 0; i < M; i++) {
                fin >> a >> b >> c >> d;
                switches[{a, b}].push_back({c, d});
            }
        }

        void main() {
            readIn();
            ofstream fout ("lightson.out");
            queue<vector<int> > q;
            vector<vector<int> > changes = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
            q.push({1, 1});
            int prevSize = 0;
            lit.insert({1, 1});
            while (q.size() != prevSize) {
                prevSize = q.size();
                for (int i = 0; i < prevSize; i++) {
                    vector<int> n = q.front();
                    q.pop();
                    //cout << res <<  endl;
                    if (memo.find(n) != memo.end()) { //if node is already counted as lit
                        q.push(n);
                        continue;
                    }
                    if (lit.find(n) == lit.end()) { //if node is not lit then just keep on stack for later
                        q.push(n);
                        continue;
                    }
                    memo.insert(n); // node is lit
                    for (auto i: changes) {
                        vector<int> child = {n[0]+i[0], n[1]+i[1]};
                        if (child[0] < 1 || child[0] > N || child[1] < 1 || child[1] > N) continue;
                        q.push(child);
                    }
                    for (auto i: switches[n]) { // turn on all lights
                        lit.insert(i);
                    }
                }
            }
            for (auto i: lit) {
                res++;
            }
            fout << res << endl;
        }
};

int main() {
    Solution s;
    s.main();
}