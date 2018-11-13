#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    private:
        int N;
        int res = 0;
        int t;
        unordered_map<int, int> next;
        vector<int>memo;
        vector<int>counted;
        vector<int>cmemo;
    public:

        void bfs(int index, int count) {
            if (memo[index] == 1) {
                res += count - counted[index];
                memo[index] = 0;
                return;
            } else if (cmemo[index] == 1) return;
            counted[index] = count;
            cmemo[index] = 1;
            memo[index] = 1;
            bfs(next[index], count+1);
            memo[index] = 0;
        }


        void main() {
            ifstream fin ("shuffle.in");
            ofstream fout ("shuffle.out");
            fin >> N;
            for (int i = 0; i < N; i++) {
                fin >> t;
                next[i] = t-1;
                memo.push_back(0);
                counted.push_back(0);
                cmemo.push_back(0);
            }
            for (int i = 0; i < N; i++) {
                if (memo[i] == 1) continue;
                bfs(i, 0);
            }
            fout << res;

        }
};

int main() {
    Solution s;
    s.main();
}