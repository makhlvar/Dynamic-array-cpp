#include "classDynamic.h"
#include<iostream>
#include<stdexcept>//для std::out_of_range, std::invalid_argument
#include<new>//для std::bad_alloc

int main(){
    DynamicArray arr(5);//создаём массив из 5 элементов (все нули)
    
    arr.PrintArray();//0 0 0 0 0

    arr.set(1,4);//ставим по индексу 1 значение 4
    arr.set(2,5);//ставим по индексу 2 значение 5
    arr.PrintArray();//0 4 5 0 0

    std::cout << arr.get(2) << std::endl;//читаем элемент по индексу 2 — выведет 5

    try{
        arr.set(6,2);//индекс 6 вне границ (массив от 0 до 4) — out_of_range
    }
    catch(const std::out_of_range& e){
        std::cerr << "set(6,2) out_of_range: " << e.what() << '\n';
    }

    try{
        arr.set(0,101);//101 вне [-100;100] — invalid_argument
    }
    catch(const std::invalid_argument& e){//
        std::cerr << "set(0,101) invalid_argument: " << e.what() << '\n';
    }
    
    arr.PrintArray();//0 4 5 0 0

    try{
         arr.get(7);//индекс 7 вне границ — out_of_range
    }
    catch(const std::out_of_range& e){
        std::cerr << "get(7) out_of_range: " << e.what() << '\n';
    }
    
    DynamicArray A(arr);//конструктор копирования: A — полная независимая копия arr
    A.PrintArray();

    try{
        A.append(500);//500 вне [-100;100] — выброшено invalid_argument
    }
    catch(const std::invalid_argument& e){
        std::cerr << "append(500) invalid_argument: " << e.what() << '\n';
    }

    A.append(3);//добавляем в конец A значение 3, размер A становится 6
    A.PrintArray();//печатаем A: 0 4 5 0 0 3

    A.add(arr);
    A.PrintArray();//печатаем A после add

    A.substract(arr);
    A.PrintArray();//A после substract

    try{
        DynamicArray huge(1000000000000ULL);//10^12 int — заведомо много
        std::cout << "huge создан (неожиданно)\n";
    }
    catch(const std::bad_alloc& e){
        std::cerr << "bad_alloc: " << e.what() << std::endl;
    }

    return 0;
}