#include <fstream>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;


class Solution {
    private:
        vector<vector<int>> points;
        char angles[200];
        int distances[200];
        int N;
        unordered_map<string, int> prefixes;
    public:
        void getAngles() {
            angles[0] = 'X';
            for (int i = 1; i < points.size()-1; i++) {
                vector<int> prev = points[i-1];
                vector<int> curr = points[i];
                vector<int> next = points[i+1];
                if (next[1] > curr[1] && curr[0] > prev[0]) { // right then up
                    angles[i] = 'o';
                }
                else if (next[1] < curr[1] && curr[0] > prev[0]) { // right then down
                    angles[i] = 'i';
                }
                else if (next[1] < curr[1] && curr[0] < prev[0]) { // left then down
                    angles[i] = 'o';
                }  
                else if (next[1] > curr[1] && curr[0] < prev[0]) { // left then up
                    angles[i] = 'i';
                }
                else if (next[0] > curr[0] && curr[1] > prev[1]) { // up then right
                    angles[i] = 'i';
                }
                else if (next[0] < curr[0] && curr[1] > prev[1]) { // up then left
                    angles[i] = 'o';
                }
                else if (next[0] < curr[0] && curr[1] < prev[1]) { // down then left
                    angles[i] = 'i';
                }
                else if (next[0] > curr[0] && curr[1] < prev[1] ) { // down then right
                    angles[i] = 'o';
                }
            }
        }

        void constructTree() {
            vector<int> prev = points[0];
            vector<string> tails;
            for (int i = 1; i < points.size()-1; i++) {
                vector<int> prev = points[i-1];
                vector<int> curr = points[i];
                string len = to_string(abs(curr[1]-prev[1]) + abs(curr[0]-prev[0]));
                for (int j = 0; j < tails.size(); j++) {
                    tails[j] += len + angles[i];
                }
                tails.push_back(angles[i-1] + len + angles[i]);
                for (auto j: tails) {
                    prefixes[j] += 1;
                }
            }
        }

        void prepData() {
            ifstream fin ("lightsout.in");
            fin >> N;
            int a, b;

            int leftDist[200];
            leftDist[0] = 0;
            int distTotal = 0;
            for (int i = 0; i < N; i++) {
                fin >> a >> b;
                points.push_back({a, b});
                if (i != 0) {
                    distTotal += (abs(points[i-1][1]-b) + abs(points[i-1][0]-a));
                    leftDist[i] = distTotal;
                }
            }

            int rightDist[200];
            int p = points.size()-1;
            vector<int> prev = points[0];
            distTotal = 0;
            for (auto i = points.rbegin(); i != points.rend(); i++) {
                distTotal += abs((*i)[1] - prev[1]) + abs((*i)[0] - prev[0]);
                rightDist[p] = distTotal;
                p--;
                prev = *i;
            }
            distances[0] = 0;

            for (int i = 1; i < points.size(); i++) {
                distances[i] = min(leftDist[i], rightDist[i]);
            }

            points.push_back(points[0]);
            getAngles();
            constructTree();

        }

        int traverse(int start) {

            int distTraveled = 0;
            vector<int> prev = points[start];
            string p(1, angles[start]);

            for (int i = start+1; i < points.size(); i++) {
                int len = abs(points[i-1][1]-points[i][1]) + abs(points[i-1][0]-points[i][0]);
                distTraveled += len;
                if (i == points.size()-1) return distTraveled;
                p += to_string(len) + angles[i];
                if (prefixes[p] == 1) {
                    return distTraveled + distances[i];
                }
            }
            cout << "ERRROR " << endl;
            return 0;
        }

        void main() {
            prepData();
            ofstream fout ("lightsout.out");

            int min = 0;
            for (int i = 1; i < points.size()-1; i++) {
               int dark = traverse(i);
               if (dark-distances[i] > min) min = dark-distances[i];
            }

            fout << min << endl;

        }
};

int main() {
    Solution s;
    s.main();
}
