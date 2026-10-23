#include "classDynamic.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <typeinfo>

int main() {
    std::cout << "\n=== Часть 3.1. int: конструктор, set, operator<< ===\n";

    DynamicArray<int> a(3);//массив из 3 нулей
    a.set(0, 1); a.set(1, 2); a.set(2, 3);//a = {1, 2, 3}
    std::cout << "a = " << a << '\n';//через operator<< 1 2 3

    std::cout << "\n=== Часть 3.2. if constexpr: проверка диапазона только для int ===\n";
    try {
        a.set(0, 200);//200 вне [-100; 100]выкид throw std::invalid_argument
    } catch (const std::invalid_argument& e) {
        std::cerr << "set(0,200) invalid_argument: " << e.what() << '\n';
    }

    std::cout << "\n=== Часть 3.3. distance для int ===\n";
    DynamicArray<int> b(3);
    b.set(0, 4); b.set(1, 5); b.set(2, 6);//b = {4, 5, 6}
    std::cout << "b = " << b << '\n';
    std::cout << "distance(a, b) = " << distance(a, b) << '\n';

    std::cout << "\n=== Часть 3.4. std::string: проверка диапазона не работает ===\n";
    DynamicArray<std::string> s(2);
    s.set(0, "hello");
    s.set(1, "world");
    //Для T = std::string ветка if constexpr не компилируется,
    //поэтому любые строки допустимы
    std::cout << "s = " << s << '\n';

    std::cout << "\n=== Часть 3.5. distance для std::string bad_typeid ===\n";
    try {
        DynamicArray<std::string> s2(2);
        s2.set(0, "a"); s2.set(1, "b");
        distance(s, s2);//T = std::string throw std::bad_typeid
    } catch (const std::bad_typeid& e) {
        std::cerr << "distance(string) bad_typeid: " << e.what() << '\n';
    }

    std::cout << "\n=== Часть 3.6. distance при разных размерах invalid_argument ===\n";
    try {
        DynamicArray<int> c(5);
        distance(a, c);//a.size = 3, c.size = 5 throw std::invalid_argument
    } catch (const std::invalid_argument& e) {
        std::cerr << "distance(a,c) invalid_argument: " << e.what() << '\n';
    }

    return 0;
}

