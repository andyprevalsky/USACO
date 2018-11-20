#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
    private:
        int N;
        int x = 0;
        int y = 0;
        int rightBound = 0;
        int leftBound = 0;
        int topBound = 0;
        int bottomBound = 0;
        int islands = 0;
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
        vector<char> moves;
        vector<vector<vector<int> > > grid;
        unordered_set<vector<int>, VectorHash> memo;
    public:
        void readIn() {
            ifstream fin ("gates.in");
            fin >> N;
            char c;
            for (int i = 0; i < N; i++) {
                fin >> c;
                if (c == 'N') y += 1;
                else if (c == 'S') y-= 1;
                else if (c == 'E') x += 1;
                else if (c == 'W') x -= 1;
                if (x > rightBound) rightBound = x;
                if (x < leftBound) leftBound = x;
                if (y > topBound) topBound = y;
                if (y < bottomBound) bottomBound = y;
                moves.push_back(c);
            }
            for (int j = bottomBound-2; j <= topBound; j++) {
                vector<vector<int> > row;
                for (int i = leftBound-2; i <= rightBound; i++) {
                    row.push_back({0, 0, 0, 0});
                }
                grid.push_back(row);
            }

            int xPos = -leftBound+1;
            int yPos = topBound+1;
            int count = 0;
            for (auto i: moves) {
                if (i == 'N') {
                    grid[yPos][xPos-1][1] = 1; 
                    grid[yPos][xPos][0] = 1;
                    yPos--;
                } else if (i == 'S') {
                    yPos++;
                    grid[yPos][xPos-1][1] = 1; 
                    grid[yPos][xPos][0] = 1;    
                } else if (i == 'W') {
                    xPos--; 
                    grid[yPos+1][xPos][2] = 1; 
                    grid[yPos][xPos][3] = 1;                
                } else if (i == 'E') {    
                    grid[yPos+1][xPos][2] = 1; 
                    grid[yPos][xPos][3] = 1;     
                    xPos++;
                }
                count++;
            }
        }

        void dfs(int row, int col) {
            if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size()) return;
            if (memo.find({row, col}) != memo.end()) return;
            memo.insert({row, col});
            if (grid[row][col][0] != 1) dfs(row, col-1);
            if (grid[row][col][1] != 1) dfs(row, col+1);
            if (grid[row][col][3] != 1) dfs(row+1, col);
            if (grid[row][col][2] != 1) dfs(row-1, col);
        }

        void main() {
            readIn();
            ofstream fout ("gates.out");
            for (int row = 0; row < grid.size(); row++) {
                for (int col = 0; col < grid[row].size(); col++) {
                    if (memo.find({row, col}) == memo.end()) {
                        dfs(row, col);
                        islands++;
                    }
                }
            }
            fout << islands-1 << endl;
        }
};

int main() {
    Solution s;
    s.main();
}