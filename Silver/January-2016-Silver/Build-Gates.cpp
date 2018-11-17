#include <fstream>
#include <vector>
#include <string>
#include <iostream>
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
        vector<char> moves;
        vector<vector<vector<int> > > grid;
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

            cout << rightBound << " " << leftBound << " " << bottomBound << " " << topBound << endl;
            for (int j = bottomBound-2; j <= topBound+1; j++) {
                vector<vector<int> > row;
                for (int i = leftBound-2; i <= rightBound+1; i++) {
                    row.push_back({0, 0, 0, 0});
                }
                grid.push_back(row);
            }

            int xPos = -leftBound+2;
            int yPos = -bottomBound+2;
            int count = 0;
            for (auto i: moves) {
                // first pos fence to the left, second pos fence to the right, third pos fence above, fourth pos fence below
                if (i == 'N') {
                    grid[yPos][xPos-1][1] = 1; 
                    grid[yPos][xPos][0] = 1;
                    yPos++;
                } else if (i == 'S') {
                    grid[yPos][xPos-1][1] = 1; 
                    grid[yPos][xPos][0] = 1;    
                    yPos--;
                } else if (i == 'W') {
                    grid[yPos-1][xPos][2] = 1; 
                    grid[yPos][xPos][3] = 1;   
                    xPos--;              
                } else if (i == 'E') {
                    grid[yPos-1][xPos][2] = 1; 
                    grid[yPos][xPos][3] = 1;     
                    xPos++;
                }
                if (count == 3) break;
                count++;
            }
            for (int i = 0; i < grid.size(); i++) {
                for (int j = 0; j < grid[i].size(); j++) {
                    for (auto k: grid[i][j]) {
                        cout << k << " ";
                    }
                    cout << " * ";
                }
                cout << endl;
            }
        }

        void main() {
            readIn();
            ofstream fout ("gates.out");
        }
};

int main() {
    Solution s;
    s.main();
}