#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    private:
        int N, M, R;
        vector<int> cows;
        vector<vector<int> > stores;
        vector<int> rent;
        long long totalMilk = 0;
        long long result = 0;
        long long rental = 0;
        long long milk = 0;
    public:
        void readIn() {
            ifstream fin ("rental.in");
            fin >> N >> M >> R;
            int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a;
                totalMilk += a;
                cows.push_back(a);
            }
            for (int i = 0; i < M; i++) {
                fin >> a >> b;
                stores.push_back({a, b});
            }
            for (int i = 0; i < R; i++) {
                fin >> a;
                rental += a;
                rent.push_back(a);
            }
            sort(cows.begin(), cows.end());
            sort(stores.begin(), stores.end(), [](vector<int>a, vector<int>b){return a[1] < b[1];});
            sort(rent.begin(), rent.end(), [](int a, int b){return a > b;});
        }

        long long sellMilk(int milk) {
            long long res = 0;
            int index = stores.size()-1;
            while (milk != 0 && index >= 0) {
                if (stores[index][0] < milk) {
                    milk -= stores[index][0];
                    res += stores[index][1]*stores[index][0];
                    index--;
                } else { 
                    res += stores[index][1]*(milk);
                    milk = 0;
                }
            }
            return res;
        }

        long long getRental(int numCows) {
            long long res = 0;
            for(int i = 0; i < numCows; i++) {
                res += rent[i];
            }
            return res;
        }

        long long getMilkTotal(int index) {
            long long milk = 0;
            for (int i = index; i < cows.size(); i++) {
                milk += cows[i];
            }
            return sellMilk(milk);
        }

        void main() {
            ofstream fout ("rental.out");
            readIn();
            int l = 0;
            int r = min(rent.size(), cows.size());
            int mid;
            long long res;
            long long rRes;
            long long lRes;
            while (l < r) {
                mid = l + (r-l)/2;
                res = getRental(mid) + getMilkTotal(mid);
                rRes = getRental(mid+1) + getMilkTotal(mid+1);
                lRes = getRental(mid-1) + getMilkTotal(mid-1);
                if (res > lRes && res > rRes) break;
                if (rRes > res) l = mid+1;
                else if (lRes > res) r = mid-1;
                else l++;
            }
            fout << max(max(res, lRes), rRes) << endl;

        }
};

int main() {
    Solution s;
    s.main();
}