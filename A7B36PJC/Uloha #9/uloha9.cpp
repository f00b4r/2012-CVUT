#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class FunnySet {
    vector<double> values;

public:

    FunnySet & operator<<(double a) {
        values.push_back(a);
        return *this;
    }

    FunnySet operator+(const FunnySet &a) {
        FunnySet temp;
        // Prida prvni set (this)
        for (int i = 0; i < values.size(); i++) {
            temp.values.push_back(values[i]);
        }
        // Prida druhy set (a)
        for (int i = 0; i < a.values.size(); i++) {
            if (std::find(values.begin(), values.end(), a.values[i]) != values.end()) {
            } else {
                temp.values.push_back(a.values[i]);
            }
        }
        return temp;
    }

    FunnySet operator++(int x) {
        FunnySet temp;
        // Prida se set a + 1
        for (int i = 0; i < values.size(); i++) {
            temp.values.push_back(values[i]);
            values[i] += 1;
        }
        return temp;
    }

    FunnySet operator++(void) {
        for (int i = 0; i < values.size(); i++) {
            values[i] += 1;
        }
        return *this;
    }

    FunnySet operator-(const FunnySet &a) {
        FunnySet temp;

        // Prida prvni set (this)
        for (int i = 0; i < values.size(); i++) {
            if (std::find(a.values.begin(), a.values.end(), values[i]) != a.values.end()) {
            } else {
                temp.values.push_back(values[i]);
            }
        }

        // Prida druhy set (a)
        for (int i = 0; i < a.values.size(); i++) {
            if (std::find(values.begin(), values.end(), a.values[i]) != values.end()) {
            } else {
                temp.values.push_back(a.values[i]);
            }
        }
        return temp;
    }


    friend void operator <<(std::ostream &s, const FunnySet &b);

};

void operator<<(std::ostream &s, const FunnySet &set) {

    for (int i = 0; i < set.values.size(); i++) {
        s << set.values[i] << " ";
    }

    s << endl;

}

int main(int argc, char** argv) {

    FunnySet A, B, C, D;

    A << 3 << 5 << 8 << 3.1 << -8.9;
    cout << A; // -8.9 3 3.1 5 8
    B << 3 << 7 << 9 << 3.1;
    cout << B; // 3 3.1 7 9
    C = A + B;
    cout << C; // -8.9 3 3.1 5 7 8 9
    D = A - B;
    cout << D; // -8.9 5 7 8 9
    D = A++;
    cout << D; // -8.9 3 3.1 5 8
    cout << A; // -7.9 4 4.1 6 9
    D = ++B;
    cout << D; // 4 4.1 8 10
    cout << B; // 4 4.1 8 10

    return 0;
}

