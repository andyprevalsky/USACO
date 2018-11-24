#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
    private:
        int X, Y, K, M; //x = pailoneSize, y = pailtwoSize, k = maxiterations, m = target milk level
        int closest = 10000;
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
        queue<vector<int> > q;

    public:
        void readIn() {
            ifstream fin ("pails.in");
            fin >> X >> Y >> K >> M;    
        }

        void main() {
            readIn();
            ofstream fout ("pails.out");
            q.push({0, 0});
            int iterations = 0;
            while(iterations <= K) {
                int size = q.size();
                for (int i = 0; i < size; i++) {
                    vector<int> node = q.front();
                    q.pop();
                    if (memo.find(node) != memo.end()) continue;
                    if (abs(M-node[0]-node[1]) < closest) {
                        closest = abs(M-node[0]-node[1]);
                    }
                    memo.insert(node);
                    q.push({X, node[1]});
                    q.push({node[0], Y});
                    q.push({0, node[1]});
                    q.push({node[0], 0});
                    if (node[0] + node[1] > X) q.push({X, node[1]-(X-node[0])});
                    else q.push({node[0]+node[1], 0});
                    if (node[1] + node[0] > Y) q.push({node[0]-(Y-node[1]), Y});
                    else q.push({0, node[0]+node[1]});
                }
                iterations++;
            }


            fout << closest << endl;
        }
};

int main() {
    Solution s;
    s.main();
}