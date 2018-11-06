#include <fstream>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> questions;
        double min = 99999;
        double total = 0;
        double count = 0;
        deque<double> averages;
        vector<int> answers;
        double max = 0;
    public:
        void main() {
            ifstream fin ("homework.in");
            ofstream fout ("homework.out");
            fin >> N;
            int t;
            for (int i = 0; i < N; i++) {
                fin >> t;
                questions.push_back(t);
            }   
            for (auto i = questions.rbegin(); i != questions.rend(); i++) {
                if (*i < min) {
                    min = *i;
                }
                total += (*i);
                count++;
                if (count != 1) averages.emplace_front((total-min)/(count-1));
                else averages.emplace_back(0);
            }
            count = 0;
            for (auto i: averages) {
                if (count == 0 || count > averages.size()-2) {
                    count++;
                    continue;
                }
                if (i > max) {
                    max = i;
                    answers = {};
                    answers.push_back(count);
                } else if (i == max) {
                    answers.push_back(count);
                }
                count ++;
            }
            for (auto i: answers) {
                fout << i << "\n";
            }
            
        }
};

int main() {
    Solution s;
    s.main();
}