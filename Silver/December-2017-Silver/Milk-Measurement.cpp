#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
    private:
        int initProduction;
        int N;
        int res = 0;
        vector<vector<int> > changes;
        map<int, int, greater<int> > cowPerProduction;
        unordered_map<int, int> cows;
    public:
        void main() {
            ifstream fin ("measurement.in");
            ofstream fout ("measurement.out");
            fin >> N >> initProduction;
            int a, b, c;
            for (int i = 0; i < N; i++) {
                fin >> a >> b >> c;
                changes.push_back({a, b, c});
            }

            sort(changes.begin(), changes.end());
            cowPerProduction[initProduction] = 999999; 

            int id, change, currMax;
            int pMax = initProduction;
            int pNum = 999999;
            for(int i = 0; i < changes.size(); i++) {
                id = changes[i][1];
                change = changes[i][2];
                if (cows.find(id) == cows.end()) cows[id] = initProduction; //if new cow then start production at init
                cowPerProduction[cows[id]]--; //decrement cow before change
                if (cowPerProduction[cows[id]] == 0) cowPerProduction.erase(cows[id]); //erase node if no cows there
                cows[id] += change; //change cow value
                cowPerProduction[cows[id]]++; //increment cow production at said level
                currMax = cowPerProduction.begin()->first;

                if (currMax > pMax && (pNum != 1 || cows[id]-change != pMax)) {
                    res++;
                } else if (currMax < pMax && (cows[id] != currMax || cowPerProduction.begin()->second != 1)) {
                    res ++;
                } 
                else if (currMax == pMax && pNum != cowPerProduction.begin()->second) {
                    res++;
                }

                pNum = cowPerProduction.begin()->second;
                pMax = cowPerProduction.begin()->first;
            }
            fout << res;
        }
};

int main() {
    Solution s;
    s.main();
}