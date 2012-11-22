#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

typedef double (*CP)(double, double);

double add(double x, double y) {
    return x + y;
}

double multi(double x, double y) {
    return x * y;
}

//double calculate(double x, double y, double (*f)(double a, double b)) {
//    return f(x, y);
//}

double calculate(double x, double y, CP f) {
    return f(x, y);
}

double calculate_add_vector(double x, double y, vector<CP> f) {
    double r = 0;
    for (int i = 0; i < f.size(); i++) {
        r += f[i](x, y);
    }
    return r;
}

double calculate_add_vector_new(double x, double y, vector<CP> f, CP op = NULL, double neutral = 0.0) {
    double r = neutral;
    for (int i = 0; i < f.size(); i++) {
        r = op(r, f[i](x, y));
    }
    return r;
}

int main(int argc, char** argv) {


    cout << "Vysledek: " << calculate(2.5, 10.4, add) << endl;

    vector<CP> vc;
    vc.push_back(add);
    vc.push_back(multi);

    cout << "Vysledek: " << calculate_add_vector(3, 4, vc) << endl;
    cout << "Vysledek: " << calculate_add_vector_new(3, 4, vc, add) << endl;
    return 0;
}

