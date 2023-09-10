#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// Класс Rand для представления массива действительных чисел
class Rand {
private:
    double* x; // массив значений аргумента
    double* y; // массив значений функции
    int n; // размерность массива
public:
    // Безаргументный конструктор
    Rand() {
        x = NULL;
        y = NULL;
        n = 0;
    }

    // Конструктор с одним аргументом - размерностью массива
    Rand(int n) {
        this->n = n;
        try {
            x = new double[n];
            y = new double[n];
        }
        catch (bad_alloc& ba) {
            cerr << "bad_alloc caught: " << ba.what() << endl;
            exit(1);
        }
    }

    // Конструктор с двумя аргументами-итераторами
    Rand(double* begin, double* end) {
        n = end - begin;
        try {
            x = new double[n];
            y = new double[n];
            for (int i = 0; i < n; i++) {
                x[i] = begin[i];
                y[i] = begin[i + n];
            }
        }
        catch (bad_alloc& ba) {
            cerr << "bad_alloc caught: " << ba.what() << endl;
            exit(1);
        }
    }

    // Конструктор копирования
    Rand(const Rand& r) {
        n = r.n;
        try {
            x = new double[n];
            y = new double[n];
            for (int i = 0; i < n; i++) {
                x[i] = r.x[i];
                y[i] = r.y[i];
            }
        }
        catch (bad_alloc& ba) {
            cerr << "bad_alloc caught: " << ba.what() << endl;
            exit(1);
        }
    }

    // Деструктор
    ~Rand() {
        delete[] x;
        delete[] y;
    }

    // Операция присваивания
    Rand& operator=(const Rand& r) {
        if (this != &r) {
            delete[] x;
            delete[] y;
            n = r.n;
            try {
                x = new double[n];
                y = new double[n];
                for (int i = 0; i < n; i++) {
                    x[i] = r.x[i];
                    y[i] = r.y[i];
                }
            }
            catch (bad_alloc& ba) {
                cerr << "bad_alloc caught: " << ba.what() << endl;
                exit(1);
            }
        }
        return *this;
    }

    // Операция индексирования
    double& operator {
        if (i < 0 || i >= n) {
            throw out_of_range("Index out of range");
        }
        return x[i];
    }

    // Операция ввода
    friend istream& operator>>(istream& in, Rand& r) {
        for (int i = 0; i < r.n; i++) {
            in >> r.x[i];
        }
        for (int i = 0; i < r.n; i++) {
            in >> r.y[i];
        }
        return in;
    }

    // Операция вывода
    friend ostream& operator<<(ostream& out, const Rand& r) {
        out << "argument ";
        for (int i = 0; i < r.n; i++) {
            out << r.x[i] << " ";
        }
        out << endl;
        out << "function ";
        for (int i = 0; i < r.n; i++) {
            out << r.y[i] << " ";
        }
        out << endl;
        return out;
    }

    // Метод вычисления математического ожидания
    double mean() const {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += y[i];
        }
        return sum / n;
    }

    // Метод вычисления дисперсии
    double variance() const {
        double m = mean();
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += (y[i] - m) * (y[i] - m);
        }
        return sum / n;
    }

    // Метод вычисления интеграла методом Монте-Карло
    double monteCarlo() const {
        double a = x[0]; // нижний предел интегрирования
        double b = x[n - 1]; // верхний предел интегрирования
        double max = y[0]; // максимальное значение функции на отрезке
        for (int i = 1; i < n; i++) {
            if (y[i] > max) {
                max = y[i];
            }
        }
        int N = 10000; // количество случайных точек
        int M = 0; // количество точек, попавших под график функции
        srand(time(NULL)); // инициализация генератора случайных чисел
        for (int i = 0; i < N; i++) {
            double x = a + (b - a) * rand() / RAND_MAX; // случайная координата x
            double y = max * rand() / RAND_MAX; // случайная координата y
            if (y <= f(x)) { // проверка, попала ли точка под график функции
                M++;
            }
        }
        return (b - a) * max * M / N; // приближенное значение интеграла
    }

    // Функция, заданная в условии задачи
    double f(double x) const {
        return 0.1 * x + 0.1;
    }
};

int main() {
    int n; // размерность массива
    cin >> n; // ввод размерности массива
    Rand r(n); // создание объекта класса Rand
    cin >> r; // ввод элементов массива
    cout << "input= " << r; // вывод исходных массивов
    cout << "MO X= " << r.mean() << " Disp X= " << r.variance() << endl; // вывод математического ожидания и дисперсии для значений аргумента
    cout << "MO Y= " << r.mean() << " Disp Y= " << r.variance() << endl; // вывод математического ожидания и дисперсии для значений функции
    cout << "MonteKarlo= " << r.monteCarlo() << endl; // вывод значения интеграла методом Монте-Карло
    return 0;
}
