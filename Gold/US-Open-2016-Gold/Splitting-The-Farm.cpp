#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define INF 0x3FFFFFFFFFFFFFFFLL

class Solution {
    private:
        int N;
        vector<pair<int, int>> points;
        long long twoMin = INF;
        long long oneFence;

    public:
        void prepData() {
            ifstream fin ("split.in");
            fin >> N;
            int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a >> b;
                points.push_back(make_pair(a, b));

            }
            sort(points.begin(), points.end());

            long long xMin = min_element(points.begin(), points.end())->first;
            long long xMax = max_element(points.begin(), points.end())->first;
            long long yMin = min_element(points.begin(), points.end(), [](pair<int, int> a, pair<int, int> b){return a.second < b.second; })->second;
            long long yMax = min_element(points.begin(), points.end(), [](pair<int, int> a, pair<int, int> b){return a.second > b.second; })->second;
            
            oneFence = (xMax - xMin) * (yMax - yMin);            
        }

        void twoFence() { 
            vector<pair<int, int>> leftYs;
            vector<pair<int, int>> rightYs;
            int yMin = points[0].second;
            int yMax = yMin;
            for (auto i: points) {
                if (i.second < yMin) yMin = i.second;
                if (i.second > yMax) yMax = i.second;
                leftYs.push_back(make_pair(yMin, yMax));
            }

            reverse(points.begin(), points.end());
            yMin = points[0].second;
            yMax = yMin;
            for (auto i: points) {
                rightYs.push_back(make_pair(yMin, yMax));
                if (i.second < yMin) yMin = i.second;
                if (i.second > yMax) yMax = i.second;
            }

            reverse(rightYs.begin(), rightYs.end());
            reverse(points.begin(), points.end());

            for (int i = 0; i < points.size()-1; i++) {
                while (i < points.size()-1 && points[i] == points[i-1]) i++;
                long long lxMin = points[0].first;
                long long lxMax = points[i].first;
                long long rxMin = points[i+1].first;
                long long rxMax = points.back().first;
                long long min = (lxMax - lxMin) * (leftYs[i].second - leftYs[i].first) + (rxMax-rxMin) * (rightYs[i].second - rightYs[i].first);
                if (min < twoMin) twoMin = min;
            }  
        }

        void main() {
            prepData();
            ofstream fout ("split.out");
            twoFence();

            for (auto& i: points) {
                swap(i.first, i.second);
            }

            sort(points.begin(), points.end());
            twoFence();

            fout << oneFence - twoMin << endl;
        }

};

int main() {
    Solution s;
    s.main();
}