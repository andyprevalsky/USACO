#include <fstream>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int N;
        int largestNum = 0;
        vector<int> nums;
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
            ifstream fin ("248.in");
            fin >> N;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                nums.push_back(a);
            }
        }

        void sift(int i, vector<int> n) {
            bool edit = true;

            while (edit) {
                edit = false;
                vector<int> targets = n;
                sort(targets.begin(), targets.end());
                for (auto target: targets) {
                    for (int j = i; j < n.size()-1; j++) {
                        if (n[j] == n[j+1] && n[j] == target) {
                            n[j]++; n.erase(n.begin()+j+1);
                            edit = true;
                        }
                    }
                }
            }
            reverse(n.begin(), n.end());
            
            edit = true;
            while (edit) {
                edit = false;
                vector<int> targets = n;
                sort(targets.begin(), targets.end());
                for (auto target: targets) {
                    for (int j = 0; j < n.size()-1; j++) {
                        if (n[j] == n[j+1] && n[j] == target) {
                            n[j]++; n.erase(n.begin()+j+1);
                            edit = true;
                        }
                    }
                }
            }

            for (auto i: n) {
                if (i > largestNum) largestNum = i;
            }
        }

        void main() {
            prepData();
            ofstream fout ("248.out");

            for (int i = 0; i < nums.size(); i++) {
                vector<int> n = nums;
                sift(i, n);
            }
            
            fout << largestNum << endl;
        }
};

int main() {
    Solution s;
    s.main();
}