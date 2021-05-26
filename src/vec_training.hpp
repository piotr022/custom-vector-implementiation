//vec training lib
#ifndef VEC_T_H // include guard
#define VEC_T_H
#include <string>


/*
    naprawić copy assigment
    coś zepsułem przy porządkowaniu kodu
*/

//in cppreference it is a struct



template <class T>
class Vector
{
public:
    //constructors     TODO: copy, assigment, move
    //def constuctor
    Vector();
    Vector(unsigned int _size);     //size cosntructor
    Vector(Vector<T> *_to_copy);    //copy constructor
    //copy assigment
    Vector<T>& operator=(const Vector<T>& _to_copy);

    //methodes
    //TODO: at, front, back, data, size, zapacity, empty, push_back,
    // pop_back, clear, reserve, emplanmce_back, begin, end, erase, insert

    //at methode to return element by reference
    T& at(unsigned int _index_ui);
    //[]op
    T& operator[](unsigned int _index_ui);
    //back
    T& back();
    T& front();
  //return pointer to array used by vector
    T *data();


    //push_back - add element at the end
    void push_back(T _to_push);
    //remove elements in vec
    void clear();
    void pop_back();
    //return pointer to first element
    T *begin();
    //to last element
    T *end();
  
    //dyn alocation
    void reserve(size_t _s_to_reserve);
    

    //iterator
    class iterator
    {
        public:
        
        //constructor
        iterator();
        iterator& operator=(Vector<T>& _vec);

        T& operator*(){
            return vec->at(_it);
        }
        T* operator++(){
            return &(vec->at(++_it));
        }
        T* operator--(){
            return &(vec->at(++_it));
        }
        private:
        Vector<T> *vec;
        T* element_ptr;
        size_t _it;
    };

    //size indicators
    bool empty();
    //num of elements
    size_t size();
    //all size
    size_t a_size();
    //capacuty
    size_t capacity();

private:
    //num of elements
    size_t _size_n;
    //all size
    size_t _size_a;
    //capacity of container
    size_t _cap;
    //pointer to first element
    T *_element_ptr;
};




#endif