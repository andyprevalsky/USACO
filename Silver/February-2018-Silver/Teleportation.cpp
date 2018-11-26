#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
    private:
        int numPoints;
        long long totalDist = 0; 
        vector<vector<int>> points;

    public:
        void readIn() {
            ifstream fin ("teleport.in");
            fin >> numPoints;
            int a, b;
            for (int i = 0; i < numPoints; i++) {
                fin >> a >> b;
                if (abs(a-b) <= abs(a)) totalDist += abs(a-b);
                else { 
                    points.push_back({a, b});
                }
            }
            sort(points.begin(), points.end(), [](vector<int> a, vector<int> b){return a[1] <  b[1];});
        }



        void main() {
            readIn();
            ofstream fout ("teleport.out"); 

        }
};

int main() {
    Solution s;
    s.main();
}