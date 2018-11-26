#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int trailLength, numStops, fjSpeed, bessSpeed;
        vector<vector<unsigned long long>> stops;
        vector<int> toStop;
        int bessPos = 0;
        unsigned long long tastiness = 0;
    public:
        void readIn() {
            ifstream fin ("reststops.in");
            fin >> trailLength >> numStops >> fjSpeed >> bessSpeed;
            unsigned long long a, b;
            for (int i = 0; i < numStops; i++) {
                fin >> a >> b;
                stops.push_back({a, b});
            }
            //sort(stops.begin(), stops.end());
            toStop.push_back(1);
            int max = stops.back()[1];
            for (int j = stops.size()-2; j >= 0; j--) {
                if (stops[j][1] > max) {
                    max = stops[j][1];
                    toStop.push_back(1);
                } else toStop.push_back(0);
            }
        }

        void main() { // stop at the first max for as long as possible and the next max and so on
            readIn();
            ofstream fout ("reststops.out");
            int j = toStop.size()-1;
 
            int fjLag = fjSpeed - bessSpeed;
            for (auto i: stops) {
                if (toStop[j] == 1) { //bessie will eat
                     unsigned long long fjLagTime = fjLag*(i[0]-bessPos); // i[0] - bessPos == meters traveled since last rest point;
                     bessPos = i[0];
                     tastiness += (unsigned long long) fjLagTime*i[1];
                    }
                j--;
            }
            fout << tastiness << endl;
        }
};

int main() {
    Solution s;
    s.main();
}