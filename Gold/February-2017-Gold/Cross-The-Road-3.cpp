#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> entries;
        int memo[50001] = {};
        int BIT[50001] = {};
        long long res = 0;
    public:
        void prepData() {
            ifstream fin ("circlecross.in");
            fin >> N;
            int a;
            for (int i = 0; i < 2*N; i++) {
                fin >> a;
                if (memo[a] == 1) entries.push_back(-a);
                else { entries.push_back(a); memo[a] = 1; }
            }
        }

        void add(int index, int val) {
            while (index < 50001) {
                BIT[index] += val;
                index += index & -index;
            }
        }

        void remove(int index, int val) {
            while (index < 50001) {
                BIT[index] -= val;
                index += index & -index;
            }
        }

        int getSum(int index) {
            int res = 0; 
            while (index > 0) {
                res += BIT[index];
                index -= index & -index;
            }
            return res;
        }

        void main() {
            prepData();
            ofstream fout ("circlecross.out");

            int counter = 50000;
            for (auto i: entries) {
                if (i > 0) {
                    memo[i] = counter;
                    add(counter, 1);
                    counter--;
                }
                else {
                    remove(memo[-i], 1);
                    res += getSum(memo[-i]);
                }
            }
            fout << res << endl;
        }
};

int main() {
    Solution s;
    s.main();
}