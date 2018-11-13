#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Solution {
    private:
       int pailOne;
       int pailTwo;
       int moves;
       int target;
       int closest = 0;
    public:
        int main() {
            ifstream fin ("pails.in");
            fin >> pailOne >> pailTwo >> moves >> target;
            if (pailOne > pailTwo) { // pail one has the smaller size
                int tmp = pailTwo;
                pailTwo = pailOne;
                pailOne = tmp;
            }
            if (target == pailOne || target == pailTwo || (target == pailOne + pailTwo && moves >= 2)) return 0;

            if (target < pailOne) {
                closest = pailOne-target;
                int exchanges = 1;
                int tPailTwo = pailTwo;
                while (exchanges+2 <= moves && tPailTwo > 0) {
                    tPailTwo -= pailOne;
                    if (abs(tPailTwo-target) < closest) closest = abs(tPailTwo-target);
                }
            }

            if (target < pailTwo) {
                closest = min(target-pailOne, pailTwo-target);
                int exchanges = 1;
                int tPailOne = 0;
                int tPailTwo = pailTwo;
                while (exchanges+2 <= moves && tPailTwo > pailOne) {
                    cout << tPailTwo << endl;
                    tPailTwo -= pailOne;
                    if (abs(tPailTwo-target) < closest) closest = abs(tPailTwo-target);
                }
            }

            cout << closest << endl;
            return closest;
        }
};

int main() {
    ofstream fout ("pails.out");
    Solution s;
    fout << s.main();
}