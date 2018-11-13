#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    private:
        struct VectorHash {
            size_t operator() (const vector<char> &vc) const
            {
                return hash<string>() (string(vc.cbegin(), vc.cend()));
            }
        };

    public:
        void BovineGenomics() {
            ifstream fin ("cownomics.in");
            ofstream fout ("cownomics.out");
            int N, M;
            fin >> N >> M;
            vector<string> cows;
            char c;
            for (int i = 0; i < 2*N; i++) {
                string cow;
                for (int j = 0; j < M; j++) {
                    fin >> c;
                    cow += c;
                }
                cows.push_back(cow);
            }
            int total = 0;

            for (int i = 0; i < M-2; i++) {
                for (int j = i + 1; j < M-1; j++) {
                    for (int k = j+1; k < M; k++) {
                        unordered_set<vector<char>, VectorHash> substrings;
                        for (int x = 0; x < N; x++) {
                            substrings.insert({cows[x][i], cows[x][j], cows[x][k]});
                        }
                        for (int x = N; x < 2*N; x++) {
                            if (substrings.find({cows[x][i], cows[x][j], cows[x][k]}) != substrings.end()) break;
                            if (x == 2*N - 1) total++;
                        }
                    }
                }
            }
            cout << total << endl;
            fout << total;
        }
};

int main() {
    Solution s;
    s.BovineGenomics();
    return 0;
}