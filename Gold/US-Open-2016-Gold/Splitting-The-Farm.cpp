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
        vector<pair<int, int>> xSorted;
        vector<pair<int, int>> ySorted;
        long long oneFence;
    public:
        void prepData() {
            ifstream fin ("split.in");
            fin >> N;
            int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a >> b;
                points.push_back(make_pair(a, b));
                xSorted.push_back(make_pair(a, b));
                ySorted.push_back(make_pair(a, b));
            }

            sort(xSorted.begin(), xSorted.end());
            sort(ySorted.begin(), ySorted.end(), [](pair<int, int> a, pair<int, int> b){ return a.second < b.second; });

            oneFence = (xSorted.back().first - xSorted[0].first ) * (ySorted.back().second - ySorted[0].second );
            
        }

        long long getAreaY(int midCut) {
            if (midCut >= points.size()-2 || midCut == 0) return INF;
            int xMax = 0;
            int xMin = 2000000000;
            int i = 0;
            while (i < ySorted.size() && ySorted[i].second <= ySorted[midCut].second) {
                if (ySorted[i].first < xMin) xMin = ySorted[i].first;
                if (ySorted[i].first > xMax) xMax = ySorted[i].first;
                i++;
            }


            int xMax2 = 0;
            int xMin2 = 2000000000;
            for (; i < xSorted.size(); i++) {
                //cout << ySorted[i].first << " ";
                if (ySorted[i].first < xMin2) xMin2 = ySorted[i].first;
                if (ySorted[i].first> xMax2) xMax2 = ySorted[i].first;
            }

            //cout << xMax << " " << xMin << " " << xMax2 << " " << xMin2 << endl;

            return (ySorted[midCut].second - ySorted[0].second) * (xMax - xMin) + (ySorted.back().second - ySorted[midCut+1].second) * (xMax2 - xMin2);

        }

        long long getAreaX(int midCut) {
            if (midCut >= points.size()-2 || midCut == 0) return INF;
            int yMax = 0;
            int yMin = 2000000000;
            int i = 0;
            while (i < xSorted.size() && xSorted[i].first <= xSorted[midCut].first) {
                if (xSorted[i].second < yMin) yMin = xSorted[i].second;
                if (xSorted[i].second > yMax) yMax = xSorted[i].second;
                i++;
            }

            int yMax2 = 0;
            int yMin2 = 2000000000;
            for (; i < xSorted.size(); i++) {
                if (xSorted[i].second < yMin2) yMin2 = xSorted[i].second;
                if (xSorted[i].second > yMax2) yMax2 = xSorted[i].second;
            }
            return (xSorted[midCut].first - xSorted[0].first) * (yMax - yMin) + (xSorted.back().first - xSorted[midCut+1].first) * (yMax2 - yMin2);
        }

        void main() {
            prepData();
            ofstream fout ("split.out");
            long long min = INF;
            long long a;
            for (int i = 0; i < points.size(); i++) {
                a = getAreaX(i);
                if (a < min) min = a;
                a = getAreaY(i);
                if (a < min) min = a;
            }

            int l = 0;
            int r = points.size()-1;
            
            while(l < r) {
                int midv = (l+r)/2;
                long long mid = getAreaX(midv);
                long long lMid = getAreaX(midv-1);
                long long rMid = getAreaX(midv+1);
                if (mid < min) min = mid;
                if (lMid < min) min = lMid;
                if (rMid < min) min = rMid;

                if (mid > lMid) l = mid+1;
                else if (mid > rMid) r = mid-1;
                else {
                    cout << "ERROR";
                    exit(1);
                }
            }

            l = 0;
            r = points.size()-1;

            while (l < r) {
                int midv = (l+r)/2;
                long long mid = getAreaY((l+r)/2);
                long long lMid = getAreaY(midv-1);
                long long rMid = getAreaY(midv+1);
                if (mid < min) min = mid;
                if (lMid < min) min = lMid;
                if (rMid < min) min = rMid;

                if (mid > lMid) l = mid+1;
                else if (mid > rMid) r = mid-1;
                else {
                    cout << "ERROR";
                    exit(1);
                }
            }


            fout << oneFence - min << endl;;
        }

};

int main() {
    Solution s;
    s.main();
}