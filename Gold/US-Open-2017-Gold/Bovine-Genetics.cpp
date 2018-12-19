#include <fstream>
#include <vector>
#include <iostream>
#include <deque>
#include <unordered_set>
#include <math.h>
using namespace std;

class Solution {
    private:
        int N, M;
        vector<vector<char>> spotted;
        vector<vector<char>> plain;
    public:
        void prepData() {
            ifstream fin ("cownomics.in");
            fin >> N >> M;
            char c;
            for (int i = 0; i < 2*N; i++) {
                vector<char> cow;
                for (int j = 0; j < M; j++) {
                    fin >> c;
                    cow.push_back(c);
                }
                if (i >= N) plain.push_back(cow);
                else spotted.push_back(cow);
            }
        }

        bool isValid(int L) {
            vector<string> s;
            vector<string> p;
            unordered_set<string> memo;
            bool valid = true;
            for (int i = 0; i < N; i++) {
                s.push_back("");
                for (int j = 0; j < L; j++) {
                    s[i] += spotted[i][j];
                }
                memo.insert(s[i]);
            }
            for (int i = 0; i < N; i++) {
                p.push_back("");
                for (int j = 0; j < L; j++) {
                    p[i] += plain[i][j];
                }
                if (memo.find(p[i]) != memo.end()) valid = false;
            }

            if (valid) return true;
            for (int i = L; i < M; i++) {
                memo.clear();
                valid = true;
                for (int j = 0; j < s.size(); j++) {
                    s[j].erase(0, 1);
                    s[j] += spotted[j][i];
                    memo.insert(s[j]);
                }
                for (int j = 0; j < p.size(); j++) {
                    p[j].erase(0, 1);
                    p[j] += plain[j][i];
                    if (memo.find(p[j]) != memo.end()) valid = false;
                }
                if (valid) return true;
            }
            return false;

        }

        void main() {
            prepData();
            ofstream fout ("cownomics.out");
            int l = 1;
            int r = M;
            int res = M;
            while (l < r) {
                int mid = l + (r-l)/2;
                if (isValid(mid)) r = mid;
                else l = mid+1;
            }
            fout << r << endl;
        }
};

int main() {
    Solution s;
    s.main();
}