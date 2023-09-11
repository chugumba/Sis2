#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

class Rand {
    std::vector<double> x;
    std::vector<double> y;

public:
    Rand(std::vector<double> x, std::vector<double> y) : x(x), y(y) {}

    double mean(const std::vector<double>& v) {
        return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    }

    double variance(const std::vector<double>& v) {
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
        std::cout << "MO X= " << mean(x) << " Disp X= " << variance(x) << std::endl;
        std::cout << "MO Y= " << mean(y) << " Disp Y= " << variance(y) << std::endl;
        std::cout << "MonteKarlo= " << monteCarlo() << std::endl;
    }
};

int main() {
    int n;
    std::cin >> n;

    std::vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i)
        std::cin >> x[i];
    for (int i = 0; i < n; ++i)
        std::cin >> y[i];

    Rand r(x, y);
    r.print();

    return 0;
}
