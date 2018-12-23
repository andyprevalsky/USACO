#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
 
class Solution {
    private:
        long long N; 
        vector<vector<int>> cows;
        struct set {
            int size;
            vector<int> flavors;
            bool operator== (const set &b) const
            {
                for (int j=0; j<5; j++) {
                    if (this->flavors[j] != b.flavors[j]) return false;
                }
                return true;
            }
        };
        struct VectorHash {
            size_t operator()(const set& a) const {
                vector<int> v = a.flavors;
                std::hash<int> hasher;
                size_t seed = 0;
                for (int i : v) {
                    seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                }
                return seed;
            }
        };
        unordered_map<set, int, VectorHash> s;
    public:
        void prepData() {
            ifstream fin ("cowpatibility.in");
            fin >> N; int a;
            for (int i = 0; i < N; i++) {
                vector<int> flavors;
                for (int j = 0; j < 5; j++) { fin >> a; flavors.push_back(a); }
                sort(flavors.begin(), flavors.end());
                cows.push_back(flavors);
            }
        }

        void getSets(vector<int>& c) {
            for (int i = 1; i < 32; i++) {
                vector<int> subS(5, 0); int p = 0;
                for (int j = 0; j < 5; j++) {
                    if (1<<(j)&i) subS[p++] = c[j]; 
                }
                s[set{p, subS}]++;
            }
        }

        void main() {
            prepData();
            ofstream fout ("cowpatibility.out");
            for (auto& i: cows) getSets(i);

            long long incExc[5] = {1, -1, 1, -1, 1};
            long long ans = (N * (N-1)) / 2;

            for (auto& e: s) {
                ans -= incExc[e.first.size-1] * e.second * (e.second-1) / 2;
            }
            fout << ans;
        }
};

int main() {
    Solution s;
    s.main();
}