#pragma once //защита от единственного включения
#include <cstddef>//size_t
#include <stdexcept>//std::out_of_range, std::invalid_argument
#include <new>//std::bad_alloc
#include <type_traits>//std::is_integral_v, std::is_arithmetic_v  трейты типов
#include <typeinfo>//std::bad_typeid  для расстояния между нечисловыми типами
#include <cmath>//std::sqrt корень для distance
#include <iostream>//std::ostream

template <typename T>
//Шаблон класса где за место T любой тип элементов
//Позволяет создавать DynamicArray<int>, DynamicArray<std::string> и т.д.
//Реализация полностью в .h,тк шаблоны компилируются в точке использования
class DynamicArray {
private:
    T*          ptr;       //указатель на данные
    std::size_t size;      //размер массива (сколько реально элементов)
    std::size_t capacity;  //запас (сколько помещается в выделенной памяти)

public:
    DynamicArray();                  //конструктор по умолчанию
    DynamicArray(std::size_t s);     //конструктор с размером
    DynamicArray(const DynamicArray& other);//конструктор копирования
    ~DynamicArray();                 //деструктор

    void PrintArray() const;         //вывод значений
    T& get(std::size_t index) const; //геттер  возвращает ссылку
    void set(std::size_t index, const T& value);  //сеттер(const T&  не копируем большие объекты)

    void append(const T& value);     //добавление в конец (синоним push_back)
    void push_back(const T& value);  //добавление в конец с расширением

    void add(const DynamicArray& other);        //поэлементное сложение
    void substract(const DynamicArray& other);  //поэлементное вычитание

    std::size_t getSize() const     { return size; }      //геттер размера
    std::size_t getCapacity() const { return capacity; }  //геттер ёмкости

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr) {
    //os левый операнд (поток), arr правый (массив)
    //возвращаем тот же поток для цепочек: std::cout << a << b
    for (std::size_t i = 0; i < arr.size; ++i) {
        os << arr.ptr[i];
        if (i + 1 < arr.size) os << ' ';  //пробел между элементами
    }
    return os;
}
};

//Конструктор по умолчанию 
//ниче криминального крч
template <typename T>
DynamicArray<T>::DynamicArray()
    : ptr(nullptr), size(0), capacity(0) {
    //нет выделенной памяти и нулевой размер
}

//Конструктор с размером
template <typename T>
DynamicArray<T>::DynamicArray(std::size_t s)
    : ptr(nullptr), size(s), capacity(s) {
    //выделяем память под s элементов и инициализируем их значениями по умолчанию
    //Для int  это 0, для std::string пустая строка
    if (size > 0) {
        ptr = new T[capacity]();  //() зануление для int, пустая строка для string
        //может бросить std::bad_alloc
    }
}

//Конструктор копирования(глубокая копия)
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : ptr(nullptr), size(other.size), capacity(other.capacity) {
    //глубокая копия: выделяем свою память, поэлементно копируем
    if (capacity > 0) {
        ptr = new T[capacity]; //может бросить std::bad_alloc
        for (std::size_t i = 0; i < size; ++i) {
            ptr[i] = other.ptr[i];
        }
    }
}

//Деструктор
template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] ptr;  //освобождаем массив, если он был
}

//Вывод
template <typename T>
void DynamicArray<T>::PrintArray() const {
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
}

//Геттер 
template <typename T>
T& DynamicArray<T>::get(std::size_t index) const {
    //проверяем, что индекс в допустимых границах
    if (index >= size) {
        throw std::out_of_range("get: индекс вне границ массива");
    }
    return ptr[index]; //возвращаем ссылку
// по ней можна читать и менять значение
}

//Сеттер
template <typename T>
void DynamicArray<T>::set(std::size_t index, const T& value) {
    //проверяем индекс
    if (index >= size) {
        throw std::out_of_range("set: индекс вне границ массива");
    }
    //Задание 1: проверка диапазона для целочисленных типов
    if constexpr (std::is_integral_v<T>) { //особый иф кот. Вычисляет условие 
//во время компиляции
        //Эта ветка компилируется только если T целочисленный тип
        //Для std::string ветка является ложной и отбрасывается компилятором 
        if (value < T(-100) || value > T(100)) {
            throw std::invalid_argument("set: значение вне диапазона [-100; 100]");
        }
    }
    ptr[index] = value;  //при успехе записываем
}

//append аля push_back 
template <typename T>
void DynamicArray<T>::append(const T& value) {
    push_back(value);
}

//Пуш бэк
template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    //проверка диапазона только для целочисленных
    if constexpr (std::is_integral_v<T>) {
        if (value < T(-100) || value > T(100)) {
            throw std::invalid_argument("push_back: значение вне диапазона [-100; 100]");
        }
    }
    //если места нет расширяем вдвое 
    if (size == capacity) {
        std::size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
//если массив пуст выделяем одну ячейку
//если нет то новый запас вдвое больше старого
        T* tmpPtr = new T[new_capacity];  //может бросить std::bad_alloc
        for (std::size_t i = 0; i < size; ++i) {
            tmpPtr[i] = ptr[i];
        }
        delete[] ptr;
        ptr = tmpPtr;
        capacity = new_capacity;
    }
    ptr[size] = value;
    ++size;
}

//add: *this = *this + other
template <typename T>
void DynamicArray<T>::add(const DynamicArray& other) {
    for (std::size_t i = 0; i < size; ++i) {
        if (i < other.size) {
            ptr[i] += other.ptr[i];  //есть элемент складываем
        }
        //если у other нет элемента недостающий = 0 пропускаем
        //размер *this не меняется
    }
}

//substract: *this = *this - other
template <typename T>
void DynamicArray<T>::substract(const DynamicArray& other) {
    for (std::size_t i = 0; i < size; ++i) {
        if (i < other.size) {
            ptr[i] -= other.ptr[i];  //вычитаем (единственное отличие от add)
        }
    }
}


//Задание 3: distance евклидово расстояние
template <typename T>
//Отдельная свободная функция вне класса, поэтому template <typename T> заново
//Без template компилятор не поймёт, чё такое T
double distance(const DynamicArray<T>& a, const DynamicArray<T>& b) {
    //размеры должны совпадать
    if (a.getSize() != b.getSize()) {
        throw std::invalid_argument("distance: размеры массивов не совпадают");
    }
    //только для числовых типов
    if constexpr (!std::is_arithmetic_v<T>) {
        //Если T не число (например string) выбрасываем bad_typeid
        throw std::bad_typeid();
    } else {
        //T явл числом считаем sqrt(Σ(a[i] - b[i])²)
        double sum = 0.0;
        for (std::size_t i = 0; i < a.getSize(); ++i) {
            double diff = static_cast<double>(a.get(i)) - static_cast<double>(b.get(i));
            sum += diff * diff;
        }
        return std::sqrt(sum);
    }
}
