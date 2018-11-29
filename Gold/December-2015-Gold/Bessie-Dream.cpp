#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
    private:
        int N, M;
        int memoOrange[1000][1000] = {};
        int memoNonOrange[1000][1000] = {};
        int memoPurple[1000][1000] = {};
        vector<vector<int>> grid;
        queue<vector<int>> q;
    public:
        void prepData() {
            ifstream fin ("dream.in");
            fin >> N >> M;
            int a;
            for (int i = 0; i < N; i++) {
                vector<int> row;
                for (int j = 0; j < M; j++) {
                    fin >> a;
                    row.push_back(a);
                }
                grid.push_back(row);
            }
        }

        void main() {
            prepData();
            ofstream fout ("dream.out");
            q.push({0, 0, 0, 0, 0});
            vector<vector<int>> changes = {{-1 ,0}, {1, 0}, {0, -1}, {0, 1}};
            int moves = -1;
            while(!q.empty()) {
                moves++;
                int size = q.size();
                for (int i = 0; i < size; i++) {
                    vector<int> state = q.front();
                    q.pop();
                    int row = state[0];
                    int col = state[1];

                    if (row == N-1 && col == M-1) { // end if the final square is reached
                        fout << moves;
                        return;
                    }

                    int tile = grid[row][col];
                    if (tile == 4) state[3] = 0;
                    else if (tile == 3 && state[3] == 0) continue;
                    else if (tile == 2) state[3] = 1;
                    else if (tile == 0) continue;


                    if (tile != 4) { //if tile is purple then character will slide, dont memo this tile because it is too much
                        if (state[3] == 0) {
                            if (memoNonOrange[row][col] == 1) continue;
                            memoNonOrange[row][col] = 1;
                        }
                        else if (state[3] == 1) {
                            if (memoOrange[row][col] == 1) continue;
                            memoOrange[row][col] = 1;
                        }
                    } else {
                        int mVal = memoPurple[row][col];
                        mVal /= pow(10, state[2]-1);
                        if (mVal%10 == 1) continue;
                        memoPurple[row][col] += pow(10, (state[2]-1));
                    }

                    if (tile == 4) { //begin sliding
                        int dir = state[2];
                        int nextRow = row;
                        int nextCol = col;
                        if (dir == 4) nextRow = row-1;
                        else if (dir == 2) nextRow = row+1;
                        else if (dir == 3) nextCol = col+1;
                        else if (dir == 1) nextCol = col-1;
                        if (nextRow >= 0 && nextRow < N && nextCol >= 0 && nextCol < M) {
                            int nextTile = grid[nextRow][nextCol];
                            if (nextTile != 3 && nextTile != 0) {
                                q.push({nextRow, nextCol, dir, state[3]});
                                continue;
                            }
                        }
                    };


                    for (auto i: changes) {
                        int nextRow = i[0] + row;
                        int nextCol = i[1] + col;
                        int dir;
                        if (i == vector<int>{-1, 0}) dir = 4;
                        else if (i == vector<int>{1, 0}) dir = 2;
                        else if (i == vector<int>{0, 1}) dir  = 3;
                        else if (i == vector<int>{0, -1}) dir = 1;
                        if (nextRow >= 0 && nextRow < N && nextCol >= 0 && nextCol < M) q.push({nextRow, nextCol, dir, state[3]});
                    }
                    
                }
            }
            fout << -1 << endl;

            
        }   
};

int main() {
    Solution s;
    s.main();
}