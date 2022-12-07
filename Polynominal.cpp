#include "Polynominal.hpp"

template<typename T>
long long Polynominal<T>::GetOrderOfPolynominal() const
{
    return OrderOfPolynominal;
}

/*template<typename T>
Polynominal<T>::Polynominal()
{
    this->OrderOfPolynominal = -1;
}*/

template<typename T>
Polynominal<T>::Polynominal(long long Order)
{
    if (Order >= 0)
    {
        OrderOfPolynominal = Order;
    }
    else
    {
        delete this;
        throw RangeError("Incorrect \"Order\" for polynomianl");
    }
}

template<typename T>
Polynominal<T>::~Polynominal()
{
    Data.clear();
}

template<typename T>
Polynominal<T>::Polynominal(const Polynominal& Other)
    {
        this->OrderOfPolynominal = Other.GetOrderOfPolynominal();
        auto it = Other.cbegin();
        for(it; it!=Other.cend();it++)
        {
            this->Data.push_back((*it));
        }
    }

template<typename T>
void Polynominal<T>::Set(long long Order, T Value)
{
    if(Value == T(0))
    {
        if(Order == OrderOfPolynominal) OrderOfPolynominal--; 
        return;
    }

    auto Cur = this->begin();

    Coefficients<T>* newbie = new Coefficients(Order, Value);

    while(Cur != this->end())    
    {
        if((*Cur).Order == Order) {Cur->Value = Value;}
        else if(Order > (*Cur).Order)
        {
            Data.insert(Cur, (*newbie));
            return;
        }
        Cur++;
    }
    
    Data.push_back((*newbie));
    return;
}

template<typename T>
T Polynominal<T>::operator[](long long Order) const
{
    auto it = cbegin();
    while (it != cend())
    {
        if (it->Order == Order)
            return it->Value;
        it++;
    }
    return 0;
}

template<typename T>
Polynominal<T> Polynominal<T>::operator+(const Polynominal &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfPolynominal() < Other.GetOrderOfPolynominal() ? Maximum = Other.GetOrderOfPolynominal() : Maximum = this->GetOrderOfPolynominal();

    Polynominal Result(Maximum);

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) + (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

template<typename T>
Polynominal<T> Polynominal<T>::operator-(const Polynominal &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfPolynominal() < Other.GetOrderOfPolynominal() ? Maximum = Other.GetOrderOfPolynominal() : Maximum = this->GetOrderOfPolynominal();

    Polynominal Result(Maximum);

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) - (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

template<typename T>
Polynominal<T> Polynominal<T>::operator*(T Val) const
{
    auto it = cbegin();
    Polynominal Result(it->Order);

    while(it != cend())
    {
        Result.Set(it->Order, it->Value * Val);
        it++;
    }
    return Result;
}

template<typename T>
Polynominal<T> Polynominal<T>::Primitive() const
{
    Polynominal Result((OrderOfPolynominal + 1));
    auto it = cbegin();
    while(it != cend())
    {
        T Coef = it->Value * (T(1) / T(it->Order + 1));
        Result.Set(((it->Order) + 1), Coef);
        it++;
    }
    return Result;
}

template<typename T>
T Polynominal<T>::CountValue(T x) const
{
    T Ans = 0;
    for (auto it = cbegin(); it != cend(); it++)
    {
        Ans += it->Value * T(pow(x, it->Order));
    }
    return Ans;
}

template class Polynominal<int>;
template class Polynominal<float>;
template class Polynominal<double>;
template class Polynominal<complex<float>>;
template class Polynominal<complex<double>>;