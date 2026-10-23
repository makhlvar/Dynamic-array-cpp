#include"classDynamic.h"
#include<iostream>
#include<string>
#include<stdexcept>

int main(){
    std::cout <<"\n===Часть 4.1 оператор []===\n";
    DynamicArray<int> arr(5);
    arr.set(0,1);
    arr.set(1,2);
    arr.set(2,9);
    arr.set(3,8);
    arr.set(4,5);
    std::cout << "arr = " << arr << std::endl;
    arr[0] = 2;
    std::cout << "arr[0] = 2" << arr << std::endl;
    try{
        arr[8] = 0;//
    } catch(const std::out_of_range& e){
        std::cerr << "arr[8] = 0 std::out_of_range" << e.what() << '\n';
    }
    int d = arr[2]; //чтение через оператор []
    std::cout << "arr[2] = " << d << std::endl;
    std::cout << "\n===Часть 4.2 операторы равно и не равно===\n";
    DynamicArray<int>one(3);
    one.set(0,1);one.set(1,1);one.set(2,1);
    DynamicArray<int>two(3);
    two.set(0,2);two.set(1,2);two.set(2,2);
    std::cout << "one = " << one << '\n';
    std::cout << "two = " << two << '\n';
    std::cout << "one == two ?" << (one == two ? "yep равны" : "nope не равны") << '\n';
    std::cout << "one != two ?" << (one != two ? "yep не равны" : "nope равны");
    std::cout << "\n===Часть 4.3 операторы плюс и минус равно для массивов==\n";
    one += two; std::cout << "one += two" << one << '\n';
    one -= two; std::cout << "one -= two" << one << " вернулся в прежнее состояние\n";

    std::cout << "\n=== Часть 4.4. Итераторы (range-based for) ===\n";
//ranged based for синтаксический сахар над begin
//const-обход: только чтнение
// const auto& ссылка на константу. Менять нельзя.
// Использует begin() const / end() const возвр const T*.
    std::cout << "const-обход two (только чтение): ";
    for (const auto& el : two) {
        std::cout << el << ' ';
    }
    std::cout << '\n';
//неконстантный обход: можно менять
//auto& изменяемая ссылка. ++el меняет элемент в массиве
//Использует begin() / end() возвр T*
    std::cout << "неконстантный обход one (++el, меняем элементы): ";
    for (auto& el : one) {
        ++el;                    // меняем элемент в массиве
        std::cout << el << ' ';  // печатаем изменённое
    }
    std::cout << '\n';

//доказательство: one реально изменился
    std::cout << "one после обхода: " << one << '\n';

        //ручной обход через begin()/end()
//Это ровно то, во что разворачивается range-based for
    std::cout << "ручной обход one через begin()/end(): ";
    for (int* it = one.begin(); it != one.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

//для сравнения: обход по значению (копия)
// auto el (без &) копия. Изменение не влияет на массив.
    std::cout << "обход one по значению (auto el): ";
    for (auto el : one) {
        ++el;
        std::cout << el << ' ';
    }
    std::cout << '\n';
    std::cout << "one после обхода по значению: " << one << '\n';
    // one не изменился тк el был копией 

    std::cout << "\n===Часть 4.6 std::string: operator[] и итераторы===\n";

    DynamicArray<std::string> s(2);
    s.set(0, "cat");
    s.set(1, "dog");
    std::cout << "s = " << s << '\n';

    s[0] = "Lev";//operator[] для строк
    std::cout << "после s[0] = \"Lev\": " << s << '\n';

    std::cout << "const-обход s: ";
    for (const auto& el : s) std::cout << el << ' ';
    std::cout << '\n';

    std::cout << "\n=== Часть 4.7. distance (как в части 3) ===\n";
    DynamicArray<int> p(3); p.set(0, 1); p.set(1, 2); p.set(2, 3);
    DynamicArray<int> q(3); q.set(0, 4); q.set(1, 5); q.set(2, 6);
    std::cout << "distance(p, q) = " << distance(p, q) << '\n';

    return 0;
}
