#include "classDynamic.h"
#include<iostream>
#include<exception>//искл

DynamicArray::DynamicArray(): ptr(nullptr),size(0) {//конструктор
    //нет выделенной памяти и нулевой размер
}

DynamicArray::DynamicArray(std::size_t s): ptr(nullptr),size(s){//конструктор с размером массива на входе
    //выделяем память под s элементов
    //и инициализируем их нулями
    if (size > 0){
        ptr = new int [size];
        for(int i = 0;i < size; ++i){
            ptr[i] = 0;
        }
    }
}

DynamicArray::DynamicArray(const DynamicArray& other): size(other.size), ptr(nullptr){//констр. копирования
    //копируем размер и выделяем собственную память,
    //затем поэлементно переносим значения
    //глубокая копия гарантирует, что два объекта
    //не будут делить один и тот же участок памяти
    if (size > 0) {
        ptr = new int [size];
        //может бросить std::bad_alloc
        for(int i = 0;i < size; ++i){
            ptr[i] = other.ptr[i];
        }
    }
}

DynamicArray::~DynamicArray(){//деструктор
    //освобождаем память, если она была выделена
    //После этого объект больше не используется
    if(ptr != nullptr) delete [] ptr;
    //Обнуляем поля, чтобы даже после удаления состояние
    //объекта было предсказуемым
    ptr = nullptr;
    size = 0;
}

void DynamicArray::PrintArray() const {//const — метод не меняет объект
    //проходим по всем элементам и печатаем их
    //Никаких изменений полей не происходит
    for(int i = 0;i < size; ++i){
        std::cout << ptr[i] << " " ;
    }
    std::cout << std::endl;
}

int DynamicArray::get(std::size_t index)const{//геттер
    //сначала проверяем, что индекс в допустимых
    //границах. Если нет — бросаем исключение
    //Если да — возвращаем элемент. Поля не меняются
    if(index >= size){
        //было сообщение и return 0
        //теперь — выброс правильного типа
        throw std::out_of_range("get: индекс вне границ массива");
    }
    return ptr[index];
}

void DynamicArray::set(std::size_t index,int value){//сеттер
    //проверяем индекс и значение на корректность
    //При нарушении — бросаем соответствующее исключение
    //При успехе — записываем значение
    if(index >= size){
        throw std::out_of_range("set: индекс вне границ массива");
    }
    if(value < -100 || value > 100){
        throw std::invalid_argument("set: значение вне диапазона [-100; 100]");
    }
    ptr[index] = value;
}

void DynamicArray::append(int value){//добавление в конец
    //проверяем значение; создаём новый массив
    //на 1 элемент больше; копируем туда старые данные и новый элемент
    //освобождаем старую память, подменяем указатель и увеличиваем size
    if(value < -100 || value > 100){
        throw std::invalid_argument("append: значение вне диапазона [-100; 100]");
    }
    int* tmpPtr = new int[size + 1]; //может бросить std::bad_alloc
    for(int i = 0;i < size;++i){
        tmpPtr[i] = ptr[i];
    }
    tmpPtr[size] = value;
    size++;
    delete[] ptr;
    ptr = tmpPtr;
}

void DynamicArray::add(const DynamicArray& other){
    //Индексов за границами нет — элементы other, которых не хватает, считаются нулями
    //поэтому исключение здесь не бросается
    for(std::size_t i = 0; i < size;++i){
        int other_value;
        if(i < other.size){
            other_value = other.ptr[i];//есть элемент берем его
        } else {
            other_value = 0;
        }
        ptr[i] += other_value;//читаем текущее и прибавляем other value
    }
}

void DynamicArray::substract(const DynamicArray& other){
    for(std::size_t i = 0; i < size;++i){
        int other_value;
        if(i < other.size){
            other_value = other.ptr[i];
        } else {
            other_value = 0;
        }
        ptr[i] -= other_value;
    }
}