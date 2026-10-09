#include "classDynamic.h"
#include <iostream>

int main() {
    DynamicArray arr(5);       //создаём массив из 5 элементов (все нули)

    arr.PrintArray();          

    arr.set(1, 4);             //ставим по индексу 1 значение 4
    arr.set(2, 5);             //ставим по индексу 2 значение 5
    arr.PrintArray();          //печатаем: 0 4 5 0 0

    std::cout << arr.get(2) << std::endl;   // читаем элемент по индексу 2 — выведет 5

    arr.set(6, 2);             //индекс 6 вне границ — сообщение, массив не меняется
    arr.set(0, 101);           //значение 101 вне [-100;100] — сообщение, массив не меняется
    arr.PrintArray();          //печатаем без изменений: 0 4 5 0 0

    arr.get(7);                //индекс 7 вне границ — сообщение, возвращается 0

    DynamicArray A(arr);       //конструктор копирования: A — полная независимая копия arr
    A.PrintArray();

    A.append(3);               //добавляем в конец A значение 3, размер A становится 6
    A.PrintArray();


    DynamicArray B(5);         //B = {10, 20, 30, 40, 50} 
    B.set(0, 10);
    B.set(1, 20);
    B.set(2, 30);
    B.set(3, 40);
    B.set(4, 50);
    std::cout << "B: "; B.PrintArray();

    DynamicArray sum = B;      //копия, чтобы не портить B
    sum.add(arr);              //sum[i] = B[i] + arr[i]
    std::cout << "B + arr = "; sum.PrintArray();
    //arr = {0, 4, 5, 0, 0}
    //sum = {10+0, 20+4, 30+5, 40+0, 50+0} = {10, 24, 35, 40, 50}

    DynamicArray diff = B;     //копия, чтобы не портить B
    diff.substract(arr);       //меняется diff: diff[i] = B[i] - arr[i]
    std::cout << "B - arr = "; diff.PrintArray();
    //diff = {10-0, 20-4, 30-5, 40-0, 50-0} = {10, 16, 25, 40, 50}

    //размеры не совпадают
    DynamicArray small(3);     //small={1, 2, 3}
    small.set(0, 1);
    small.set(1, 2);
    small.set(2, 3);

    DynamicArray big = B;      //копия B (размер 5)
    big.add(small);            //big[i] += small[i] для i < 3, для i >= 3 += 0
    std::cout << "B + small (недостающие = 0) = "; big.PrintArray();
    //{10+1, 20+2, 30+3, 40+0, 50+0} = {11, 22, 33, 40, 50}

    return 0;
}