/*
    ID: andypre1
    LANG: C++11
    PROB: beads
*/

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N;
        int bestSplit = 0;
        string c;
        vector<char> necklace;
        vector<int> left;
        vector<int> right;
    public:
        int main() {
            ifstream fin ("beads.in");
            fin >> N;
            fin >> c;
            for (int i = 0; i < N; i++) {
                necklace.push_back(c[i]);
            }
            int size = necklace.size();
            for (int i = 0; i < size; i++) {
                necklace.push_back(necklace[i]);
            }
            int runningTotal;
            char runningColor;
            for (int i = 0; i <= necklace.size(); i++) {
                if (i == 0) { 
                    left.push_back(0);
                    continue;
                }
                runningColor = necklace[i-1];
                runningTotal = 0;
                for (int j = i-1; j >= 0; j--) {
                    if (necklace[j] != 'w' && runningColor == 'w') runningColor = necklace[j];
                    if (runningColor != 'w' && necklace[j] != runningColor && necklace[j] != 'w') break;
                    runningTotal += 1;
                }
                left.push_back(runningTotal);
            }

            runningTotal = 0;
            for (int i = necklace.size()-1; i >= -1; i--) {
                if (i == necklace.size()-1) { 
                    right.push_back(1);
                    continue;
                }
                runningColor = necklace[i];
                runningTotal = 0;
                for (int j = i; j < necklace.size(); j++) {
                    if (necklace[j] != 'w' && runningColor == 'w') runningColor = necklace[j];
                    if (runningColor != 'w' && necklace[j] != runningColor && necklace[j] != 'w') break;
                    runningTotal += 1;
                }
                right.push_back(runningTotal);
            }

            int split;
            for (int i = 0; i < necklace.size(); i++) {
                split = left[i] + right[necklace.size()-1-i];
                if (split > bestSplit) bestSplit = min(split, N);
            }
            return bestSplit;
        }
};

int main() {
    ofstream fout ("beads.out");
    Solution s;
    fout << s.main() << "\n";
}