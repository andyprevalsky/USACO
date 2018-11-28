#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
using namespace std;

class Solution {
    private:
        int numPoints;
        long long upShift = 0; 
        long long minDist;
        vector<vector<int>> points;
        map<int, int> slopes;
    public:

        void readIn() {
            ifstream fin ("teleport.in");
            fin >> numPoints;
            int a, b;
            for (int i = 0; i < numPoints; i++) {
                fin >> a >> b;
                upShift += abs(a-b);

                if (abs(a-b) <= abs(a)) continue;
                slopes[b] += 2;
                if (a >= 0 && a >= b) {
                    slopes[2*b]--;
                    slopes[0]--;
                }
                else if (a >= 0 && a < b) {
                    slopes[2*a]--;
                    slopes[-2*a+2*b]--;
                }
                else if (a < 0 && a >= b) {
                    slopes[2*b-2*a]--;
                    slopes[2*a]--;
                }
                else if (a < 0 && a < b) {
                    slopes[0]--;
                    slopes[2*b]--;
                }
            }
        }



        void main() {
            readIn();
            ofstream fout ("teleport.out"); 
            minDist = upShift;
            long long currY = upShift;
            long long currSlope = 0;
            long long prevX = -2000000000;
            for (auto i: slopes) {
                int currX = i.first;
                currY += (currX - prevX) * currSlope;
                if (currY < minDist) minDist = currY;
                currSlope += i.second;
                prevX = currX;
            }
            fout << minDist << endl;

        }
};

int main() {
    Solution s;
    s.main();
}