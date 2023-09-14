#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Rand {
    vector<double> x;
    vector<double> y;

public:
    Rand(vector<double> x, vector<double> y) : x(x), y(y) {}

    double mean(const vector<double>& v) {
        return accumulate(v.begin(), v.end(), 0.0) / v.size();
    }

    double variance(const vector<double>& v) {
        double m = mean(v);
        double temp = 0;
        for (double a : v)
            temp += (a - m) * (a - m);
        return temp / (v.size()-1);
    }

    double monteCarlo() {
        double sum = 0;
        for (int i = 0; i < x.size(); ++i)
            sum += y[i];
        return (x.back() - x.front()) * sum / x.size();
    }

    void print() {
        cout << "MO X= " << mean(x) << " Disp X= " << variance(x) << endl;
        cout << "MO Y= " << mean(y) << " Disp Y= " << variance(y) << endl;
        cout << "MonteKarlo= " << monteCarlo() << endl;
    }
};

int main() {
    int n;
    cin >> n;

    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i];
    for (int i = 0; i < n; ++i)
        cin >> y[i];

    Rand r(x, y);
    r.print();

    return 0;
}
