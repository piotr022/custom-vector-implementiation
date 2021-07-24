//vec training lib
#pragma once
#include <string>



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
    //emplancce_back, also returns pointer to modified element
    template <class ... Types>
    T *emplace_back(Types ... args);
    

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


//default constructor
template <class T>
Vector<T>::Vector()
    : _size_n(0), _cap(0), _size_a(), _element_ptr(NULL)
{
}

//size constructor
template <class T>
Vector<T>::Vector(unsigned int _size)
    : _size_n(_size), _cap(_size), _element_ptr(new T[_size]), _size_a(sizeof(this))
{
}

//copy constructor
template <class T>
Vector<T>::Vector(Vector<T> *_to_copy)
    : _size_n(_to_copy->size()), _size_a(_to_copy->a_size()),
      _element_ptr(new T[_to_copy->size()]), _cap(_to_copy->capacity())
{
    //lenhgt to copy = num of elements * single element size
    memcpy(_element_ptr, _to_copy->begin(), _to_copy->size() * sizeof(T));
}

//copy assignent, overloading operator =
template <class T>
inline Vector<T> &Vector<T>::operator=(const Vector<T> &_to_copy)
{
    // self assigment guard, sugested in cppreference
    if (this == &_to_copy)
        return *this;

    if (_size_n != _to_copy._size_n)
    {
        delete[] _element_ptr;
        _element_ptr = new T[_to_copy._size_n];
    }

    _size_n = _to_copy._size_n;
    _size_a = _to_copy._size_a;
    _cap = _to_copy._cap;
    //copy elements
    memcpy(_element_ptr, _to_copy._element_ptr, _size_n * sizeof(T));
    return *this;
}

//at methode
template <class T>
T &Vector<T>::at(unsigned int _index_ui)
{
    //value of _index_ui element of vec
    return *(this->_element_ptr + _index_ui);
}

//back, returns previous element
template <class T>
T &Vector<T>::back()
{
    return _element_ptr[_size_n - 1];
}

//front returns first element
template <class T>
T &Vector<T>::front()
{
    return _element_ptr[0];
}

template <class T>
T &Vector<T>::operator[](unsigned int _index_ui)
{
    return *(this->_element_ptr + _index_ui);
}

//push_back 
template <class T>
void Vector<T>::push_back(T _to_push)
{
    //if table is to small
    if ((_size_n + 1) >= _cap)
        reserve(_size_n + 1);
    //adding last element
    this->_element_ptr[_size_n] = _to_push;
    _size_n++;
}

//clear just sets size to 0
template <class T>
void Vector<T>::clear()
{
    _size_n = 0;
}

//pop_back removes last element, decresee size
template <class T>
void Vector<T>::pop_back()
{
    _size_n--;
}

//begin returns pointer to first element
template <class T>
T *Vector<T>::begin()
{
    return this->_element_ptr;
}

template <class T>
T *Vector<T>::end()
{
    return (this->_element_ptr) + _size_n;
}

//data() - return pionter to array used by vec
template <class T>
T *Vector<T>::data()
{
    return this->_element_ptr;
}

//returns true if empty
template <class T>
bool Vector<T>::empty()
{
    return (_size_n <= 0) ? 1 : 0;
}

//size of elements methode
template <class T>
size_t Vector<T>::size()
{
    return this->_size_n;
}

//all vector size
template <class T>
size_t Vector<T>::a_size()
{
    return sizeof(this);
}

//capacity od table using by vec
template <class T>
size_t Vector<T>::capacity()
{
    return this->_cap;
}

//iterator methodes
template <class T>
Vector<T>::iterator::iterator()
    : element_ptr(NULL), _it(0)
{
}

template <class T> //typename xD
typename Vector<T>::iterator &Vector<T>::iterator::operator=(Vector<T> &_vec)
{
    vec = &_vec;
    element_ptr = vec->begin();
    _it = 0;

    return *this;
}

//dyn alocation
template <class T>
void Vector<T>::reserve(size_t _s_to_reserve)
{
    if (_s_to_reserve <= _cap)
        return; //exit if nothing to do

    T *fresh_tab = new T[_s_to_reserve];

    //copy tab
    unsigned int cnt =0;
    for(T i : *this)
        fresh_tab[cnt++] = i;
    //faster way but not working with classes with std::string
    // memcpy(fresh_tab, this->_element_ptr, this->size() * sizeof(T));

    delete[] _element_ptr;
    _element_ptr = fresh_tab;
    //delete[] fresh_tab;
    // causing seg fault

    _cap = _s_to_reserve;
}

//emplance_back
template<class T>
template<class... Types>
T* Vector<T>::emplace_back(Types ... args)
{
   //if table is to small
    if ((_size_n + 1) >= _cap)
        reserve(_size_n + 1);
    //adding last element
    this->_element_ptr[_size_n] = T(args...);
    _size_n++;
    return this->_element_ptr + _size_n;
}
