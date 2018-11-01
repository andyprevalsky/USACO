#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>

using namespace std;

class Solution {
    private:
        deque<vector<int> > xSorted;
        deque<vector<int> > ySorted;
        long long int bestArea = 2500000000;

    public:
        void pop(char c, vector<vector<int> >& popped, deque<vector<int> >& ySortCpy, deque<vector<int> >& xSortCpy) {
            if (c == 'U') {
                vector<int> yTop = ySortCpy.back();
                if (find(popped.begin(), popped.end(), yTop) != popped.end()) {
                    ySortCpy.pop_back();
                    pop('U', popped, ySortCpy, xSortCpy);
                    return;
                }
                ySortCpy.pop_back();
                popped.push_back(yTop);
                return;
            } else if (c == 'D') {
                vector<int> yBot = ySortCpy.front();
                if (find(popped.begin(), popped.end(), yBot) != popped.end()) {
                    ySortCpy.pop_front();
                    pop('D', popped, ySortCpy, xSortCpy);
                    return;
                }
                ySortCpy.pop_front();
                popped.push_back(yBot);
                return;
            } else if (c == 'L') {
                vector<int> xBot = xSortCpy.front();
                if (find(popped.begin(), popped.end(), xBot) != popped.end()) {
                    xSortCpy.pop_front();
                    pop('L', popped, ySortCpy, xSortCpy);
                    return;
                }
                xSortCpy.pop_front();
                popped.push_back(xBot);
                return;                
            } else { // c == 'R'
                vector<int> xTop = xSortCpy.back();
                if (find(popped.begin(), popped.end(), xTop) != popped.end()) {
                    xSortCpy.pop_back();
                    pop('R', popped, ySortCpy, xSortCpy);
                    return;
                }
                xSortCpy.pop_back();
                popped.push_back(xTop);
                return;
            }
    }

        void getArea(string pops) {
            deque<vector<int> > xSortCpy = xSorted;
            deque<vector<int> > ySortCpy = ySorted;
            vector<vector<int> > popped;

            for (auto i = pops.begin(); i != pops.end(); i++) {
                pop(*i, popped, ySortCpy, xSortCpy);
            }
            vector<int> leftBound = xSortCpy.front();
            vector<int> rightBound = xSortCpy.back();
            vector<int> topBound = ySortCpy.back();
            vector<int> bottomBound = ySortCpy.front();
            while (find(popped.begin(), popped.end(), leftBound) != popped.end()) {
                xSortCpy.pop_front();
                leftBound = xSortCpy.front();
            }
            while (find(popped.begin(), popped.end(), rightBound) != popped.end()) {
                xSortCpy.pop_back();
                rightBound = xSortCpy.back();
            }
            while (find(popped.begin(), popped.end(), topBound) != popped.end()) {
                ySortCpy.pop_back();
                topBound = ySortCpy.back();
            }
            while (find(popped.begin(), popped.end(), bottomBound) != popped.end()) {
                ySortCpy.pop_front();
                bottomBound = ySortCpy.front();
            }
            //cout << "LeftBound: " << leftBound[0] << " RightBound: " << rightBound[0] << " TopBound: " << topBound[1] << " BottomBound: " << bottomBound[1] << endl;
            //cout << (rightBound[0]-leftBound[0]) * (topBound[1]-bottomBound[1]) <<  endl;
            long long int area = (rightBound[0]-leftBound[0]) * (topBound[1]-bottomBound[1]);
            if (area < bestArea) bestArea = area;
        };


        int main() {
            ifstream fin ("reduce.in");
            int N;
            fin >> N;
            vector<vector<int> > points;
            int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a >> b;
                points.push_back({a, b});
            }
            sort(points.begin(), points.end());  
            xSorted = deque<vector<int> >(points.begin(), points.end());
            sort(points.begin(), points.end(), [](vector<int> a, vector<int> b){return a[1] < b[1];});
            ySorted = deque<vector<int> >(points.begin(), points.end());
            vector<char> moves = {'U', 'L', 'D', 'R'};

            for (int i = 0; i < moves.size(); i++) {
                for (int j = 0; j < moves.size(); j++) { 
                    for (int k = 0; k < moves.size(); k++) {
                        string s = "";
                        //cout << s+moves[i]+moves[j]+moves[k] << endl;
                        getArea(s + moves[i] + moves[j] + moves[k]);
                    }
                }
            }
            return bestArea;
        }
};

int main() {
    ofstream fout ("reduce.out");
    Solution s;
    fout << s.main();
}