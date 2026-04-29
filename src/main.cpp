#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>

class Ulamek {
public:
    Ulamek(int a, int b) {
        this->a = a;
        this->b = b;
        this->optimize();
    }

    Ulamek operator+(const Ulamek& other) const {
        int new_a = (this->a * other.b) + (other.a * this->b);
        int new_b = this->b * other.b;
        return Ulamek(new_a, new_b);
    }

    Ulamek operator-(const Ulamek& other) const {
        int new_a = (this->a * other.b) - (other.a * this->b);
        int new_b = this->b * other.b;
        return Ulamek(new_a, new_b);
    }

    Ulamek operator*(const Ulamek& other) const {
        int new_a = this->a * other.a;
        int new_b = this->b * other.b;
        return Ulamek(new_a, new_b);
    }
    Ulamek operator/(const Ulamek& other) const {
        int new_a = this->a * other.b;
        int new_b = this->b * other.a;
        Ulamek res(new_a, new_b);
        return res;
    }

    bool operator==(const Ulamek& other) const {
        bool a = this->a == other.a;
        bool b = this->b == other.b;
        return a && b;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ulamek& u) {
        os << u.a << "/" << u.b;
        return os;
    }

private:
    void optimize() {
        int ugcd = std::gcd(this->a, this->b);
        a /= ugcd;
        b /= ugcd;
    }

    int a;
    int b;
};


int main()
{
    Ulamek ul1(3, 6);
    Ulamek ul2(5, 15);

    std::cout << ul1 << " +  " << ul2 << " = " << (ul1 + ul2) << "\n";
    std::cout << ul1 << " -  " << ul2 << " = " << (ul1 - ul2) << "\n";
    std::cout << ul1 << " *  " << ul2 << " = " << (ul1 * ul2) << "\n";
    std::cout << ul1 << " /  " << ul2 << " = " << (ul1 / ul2) << "\n";
    std::cout << ul1 << " == " << ul2 << " = " << (ul1 == ul2) << "\n";
    std::cout << ul1 << " == " << ul1 << " = " << (ul1 == ul1) << "\n";

    return 0;
}