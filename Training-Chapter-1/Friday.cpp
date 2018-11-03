/*
ID: andypre1
LANG: C++11
PROB: friday
*/

#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int years;
    public:
        void main() {
            ifstream fin ("friday.in");
            ofstream fout ("friday.out");
            fin >> years;
            vector<int> counts(7, 0);
            vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            vector<int> sanity;
            int pos = 2;
            for (int year = 1900; year < years+1900; year++) { // years 
                if (year % 100 == 0) {
                    if (year % 400 == 0)
                        months[1] = 29;
                }
                else if (year % 4 == 0)
                    months[1] = 29;
                else
                    months[1] = 28;
                for (int month = 0; month < 12; month++) { // months 
                    //cout << months[month] << " " << month << " " << year << endl;
                    for (int day = 0; day < months[month]; day++) { // days in the month
                        if (day == 12) {
                            counts[pos] += 1;
                            sanity.push_back(pos);
                        }
                        pos = (pos+1)%7;
                    }
                }
            }
            for (auto i = counts.begin(); i != counts.end(); i++) {
                fout << (*i);
                if (i+1 != counts.end())
                    fout << " ";
            }
            fout << endl;
        }
};

int main() {
    Solution s;
    s.main();
}