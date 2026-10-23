#include"classDynamic.h"
#include<iostream>
#include<string>
#include<stdexcept>
#include<utility>//std::move

void foo(DynamicArray<int> array){
    array.PrintArray();
}

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
// Использует begin() const / end() const возвр const T*
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
// auto el (без &) копия. Изменение не влияет на массив
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

      std::cout << "\n=== Часть 5.1. operator= (копирующее присваивание) ===\n";
    DynamicArray<int> a(3);
    a.set(0, 1); a.set(1, 2); a.set(2, 3);
    std::cout << "a = " << a << '\n';

    DynamicArray<int> b;
    b = a;   //operator=(const DynamicArray&)
    std::cout << "b = " << b << '\n';
    b[0] = 99;
    std::cout << "после b[0] = 99: a = " << a << ", b = " << b << '\n';
    //a не изменился(глубокая копия)

    std::cout << "\n=== Часть 5.2. Move-конструктор (std::move) ===\n";
    DynamicArray<int> c(3);
    c.set(0, 10); c.set(1, 20); c.set(2, 30);
    std::cout << "c = " << c << '\n';

    DynamicArray<int> g = std::move(c);   //move-конструктор
    std::cout << "g (из c через move) = " << g << '\n';
    std::cout << "c после move: size = " << c.getSize()
              << ", capacity = " << c.getCapacity()
              << " c стал пустым\n";

    std::cout << "\n=== Часть 5.3. Move-присваивание ===\n";
    DynamicArray<int> e;
    e = std::move(g); 
    std::cout << "e (из g через move) = " << e << '\n';
    std::cout << "g после move: size = " << g.getSize()
              << ", capacity = " << g.getCapacity() << '\n';

    std::cout << "\n=== Часть 5.4. Демонстрация: копия vs move в функции ===\n";
    DynamicArray<int> big(5);
    big.set(0, 1); big.set(1, 2); big.set(2, 3); big.set(3, 4); big.set(4, 5);
    std::cout << "big = " << big << '\n';

    std::cout << "--- передача по значению (копия эт дорого) ---\n";
    foo(big);   //срабатывает конструктор копирования

    std::cout << "--- передача через move ---\n";
    foo(std::move(big));   //срабатывает move-конструктор
    std::cout << "big после move: size = " << big.getSize()
              << ", capacity = " << big.getCapacity() << '\n';

    std::cout << "\n=== Часть 5.5. Rule of five: краткая проверка ===\n";
    DynamicArray<std::string> st(2);
    st.set(0, "cat");
    st.set(1, "dog");
    std::cout << "st = " << st << std::endl;

    DynamicArray<std::string> s2 = st; 
    s2[0] = "lion";
    std::cout << "st = " << st << ", s2 = " << s2 << '\n';

    DynamicArray<std::string> s3 = std::move(s2);   //move для строк
    std::cout << "s3 (из s2) = " << s3 << '\n';
    std::cout << "s2 после move: size = " << s2.getSize() << '\n';

    std::cout << "\nГотово. Если собрано с -fsanitize=address, "
              << "утечек и двойных освобождений не должно быть\n";

    return 0;
}
