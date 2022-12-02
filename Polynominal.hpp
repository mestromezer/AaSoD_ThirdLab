#pragma once
#include <iostream>
#include <math.h>
#include <complex>
#include <list>
#include "PolynominalError.hpp"
using namespace std;

template<typename T>
struct Coefficients
{
    T Value;
    long long Order;
    Coefficients(long long Order, T Value): Order(Order), Value(Value) {}
};

template<typename T>
class Polynominal
{
    list<Coefficients<T>> Data;

    long long OrderOfPolynominal;

    auto begin(){ return Data.begin(); }

    auto end(){ return Data.end(); }

public:

    long long GetOrderOfPolynominal() const;

    Polynominal(long long Order) = default; // https://www.bestprog.net/ru/2019/08/04/keywords-default-delete-examples-of-using-ru/

    ~Polynominal() = default;

    auto cbegin() const { return Data.cbegin(); }

    auto cend() const  { return Data.cend(); }

    void Set(long long Order, T Value);            

    T operator[](long long Order) const;

    Polynominal operator+(const Polynominal &Other) const;

    Polynominal operator-(const Polynominal &Other) const;

    Polynominal operator*(T Val) const;

    Polynominal Primitive() const;

    T CountValue(T x) const;

    //friend ostream &operator<<(ostream &os, const Polynominal<T> &Obj);
};
