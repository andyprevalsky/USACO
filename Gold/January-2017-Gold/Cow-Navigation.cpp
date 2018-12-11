#include <fstream>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N;
        queue<vector<int>> q;
        int memo[20][20][20][20] = {};
        char grid[21][21];
    public:
        void prepData() {
            ifstream fin ("cownav.in");
            fin >> N;
            char c;
            memset(grid, 'X', sizeof(grid));
            for (int i = N; i >= 0; i--) {
                for (int j = 0; j < N; j++) {
                    fin >> c;
                    grid[20-i][j] = c;
                }
            }
        }
        void main() {
            prepData();
            ofstream fout ("cownav.out");
            q.push({19, 0, 0, 19, 0, 1});  //0 is facing up, 1 is facing right, 2 is facing down, 3 is facing left
            int moves = -1;
            while(!q.empty()) {
                int size = q.size(); moves++;
                for (int i = 0; i < size; i++) {
                    vector<int> s = q.front(); q.pop();
                    if (s[3] == 20-N && s[4]== N-1 && s[0] == 20-N && s[1]== N-1) { fout << moves; return; }


                    // constraining with memo
                    int m = memo[s[0]][s[1]][s[3]][s[4]];
                    vector<int> rotations = {0, 0, 0, 0, 0, 0, 0, 0};
                    int c = 0;
                    while (m != 0) { int bit = m%10; rotations[c] = bit; c++; m /= 10; }
                    if (rotations[s[2]] == 1 && rotations[4+s[5]] == 1) continue;
                    rotations[s[2]] = 1; rotations[4+s[5]] = 1;

                    int total = 0;
                    for (int i = 0; i < rotations.size(); i++) total += pow(10, i)*rotations[i];
                    memo[s[0]][s[1]][s[3]][s[4]] = total;
                    // end of memo alterations 

                    q.push({s[0], s[1], (s[2]+1)%4, s[3], s[4], (s[5]+1)%4});
                    q.push({s[0], s[1], (s[2]-1 < 0 ? 3: s[2]-1), s[3], s[4], (s[5]-1 < 0 ? 3: s[5]-1)});


                    int nRow1 = s[0], nCol1 = s[1], nRow2 = s[3], nCol2 = s[4];
                    if (s[0] != 20-N || s[1] != N-1) {
                        if (s[2] == 0) {
                            nRow1--; nCol1 = s[1];
                            if (nRow1 < 20-N || grid[nRow1][nCol1] == 'H') nRow1++;
                        } else if (s[2] == 1) {
                            nRow1 = s[0]; nCol1++;
                            if (nCol1 == N || grid[nRow1][nCol1] == 'H') nCol1--;
                        } else if (s[2] == 2) {
                            nRow1++; nCol1 = s[1];
                            if (nRow1 == 20 || grid[nRow1][nCol1] == 'H') nRow1--;
                        } else if (s[2] == 3) {
                            nRow1 = s[0]; nCol1--;
                            if (nCol1 < 0 || grid[nRow1][nCol1] == 'H') nCol1++;
                        }   
                    }
                    if (s[3] != 20-N || s[4] != N-1) {
                        if (s[5] == 0) {
                            nRow2--; nCol2 = s[4];
                            if (nRow2 < 20-N || grid[nRow2][nCol2] == 'H') nRow2++;
                        } else if (s[5] == 1) {
                            nRow2 = s[3]; nCol2++;
                            if (nCol2 == N || grid[nRow2][nCol2] == 'H') nCol2--;
                        } else if (s[5] == 2) {
                            nRow2++; nCol2 = s[4];
                            if (nRow2 == 20 || grid[nRow2][nCol2] == 'H') nRow2--;
                        } else if (s[5] == 3) {
                            nRow2 = s[3]; nCol2--;
                            if (nCol2 < 0 || grid[nRow2][nCol2] == 'H') nCol2++;
                        } 
                    }
                    q.push({nRow1, nCol1, s[2], nRow2, nCol2, s[5]});                   
                }
            }
        }
};

int main() {
    Solution s;
    s.main();
}