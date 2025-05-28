#pragma once

#include <iostream>
#include <cstdlib>
#include <compare>
#include <cstdint>
#include <numeric>

//#include "pow.h"

// Реализуйте класс Rational.
class Rational {
public:
    //Rational() = default;
    Rational() 
        : numerator_(0)
        , denominator_(1)  { } 
    
    Rational (int num) 
        : numerator_(num)
        , denominator_(1) { }	
    
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
            if (denominator_ == 0) {
                std::abort();
            }
        Reduction();
    }

    Rational (const Rational& r) 
        : numerator_(r.numerator_)
        , denominator_(r.denominator_) {
        Reduction();
        }	

    // Функции ввода-вывода  
    friend inline std::istream& operator >> (std::istream& is, Rational& r);
    friend inline std::ostream& operator << (std::ostream& os, const Rational& r);

    // Перегрузка операции сравнения.
    bool operator==(const Rational& r) const {
        Rational temp = r; // вводим временную переменную для упрощения, не меняя оригинал
        temp.Reduction();
        bool comparison = (numerator_ == temp.numerator_) 
            && (denominator_ == temp.denominator_);
        return comparison;
        }
      
    // Перегрузка арифметических операций
    Rational operator+(const Rational& r) const {
        Rational total = *this;
        return total += r;
    }
    
    Rational operator-(const Rational& r) const {
        Rational total = *this;
        return total -= r;
    }

    Rational operator*(const Rational& r) const {
        Rational total = *this;
        return total *= r;
    }

    Rational operator/(const Rational& r) const {
        Rational total = *this;
        return total /= r;
    }

    // Перегрузки присваивающих операций.
    Rational& operator=(const int& number) {
            numerator_ = number;
            denominator_ = 1;
            return *this;
        } 
        
    Rational& operator=(const Rational& ratio) = default;    
    
    Rational& operator+=(const Rational& ratio) {
            Reduction();
            numerator_ = numerator_ * ratio.denominator_ + denominator_ * ratio.numerator_;
            denominator_ = denominator_ * ratio.denominator_;
            Reduction();
            return *this;
        }
    
    Rational& operator-=(const Rational& ratio) {
            Reduction();
            numerator_ = numerator_ * ratio.denominator_ - denominator_ * ratio.numerator_;
            denominator_ = denominator_ * ratio.denominator_;
            Reduction();
            return *this;
        }
    
    Rational& operator*=(const Rational& ratio) {
            Reduction();
            numerator_ = numerator_ * ratio.numerator_;
            denominator_ = denominator_ * ratio.denominator_;
            Reduction();
            return *this;
        }
    
    Rational& operator/=(const Rational& ratio) {
            Reduction();
            numerator_ = numerator_ * ratio.denominator_;
            denominator_ = denominator_ * ratio.numerator_;
            Reduction();
            return *this;
        }

    // Перегрузка унарных +-
    Rational operator +() const {
        return *this;
    }
    
    Rational operator -() const {
        //Rational::numerator_ = -numerator_;
        return Rational {-numerator_, denominator_};
    }
          
    // Перегрузка приведения к десятичной дроби
    explicit operator double() const {
            return 1.*numerator_/denominator_;
        }

    // Инвертированная дробь
    Rational Inv() const {
            return {denominator_, numerator_};
        }

    int GetNumerator() const {
            return numerator_;
        }
          
    int GetDenominator() const {
            return denominator_;
        }

private:
    // Метод для приведения дроби к корректной форме.
    void Reduction() {
            if (denominator_ < 0) {
                numerator_ = -numerator_;
                denominator_ = -denominator_;
            }
            const int divisor = std::gcd(numerator_, denominator_);
            numerator_ /= divisor;
            denominator_ /= divisor;
        }
    
    int numerator_ = 0;
    int denominator_ = 1;
};

// ВЫВОД ДРОБИ
inline std::ostream& operator << (std::ostream& os, const Rational& r) {
        if (r.denominator_ == 1) {
            os << r.numerator_;
            return os;
        }
        os << r.numerator_ << " / " << r.denominator_;  
        return os;
    }
    
// ВВОД
inline std::istream& operator>>(std::istream& is, Rational& r) {
        int n, d;
        char div;
    
        if (!(is >> n)) {
            return is;
        }
    
        if (!(is >> std::ws >> div)) {
            r = Rational(n, 1);
            is.clear();
            return is;
        }
        
        if (div != '/') {
            r = Rational(n, 1);
            is.unget();
            return is;
        }
    
        if (!(is >> d) || (d == 0)) {
            is.setstate(std::ios::failbit);
            return is;
        }
    
        r = Rational(n, d);
    
        return is;
    }

// Перегрузки сравнения
inline auto operator <=> (const Rational& a, const Rational& b) {
            std::int64_t c1 = static_cast<std::int64_t>(a.GetNumerator()) * 
                                static_cast<std::int64_t>(b.GetDenominator());
            std::int64_t c2 = static_cast<std::int64_t>(b.GetNumerator()) * a.GetDenominator();
            return c1 <=> c2; 
        }
        
/*inline bool operator == (const Rational& a, const Rational& b) {
            //std::int64_t c1 = static_cast<std::int64_t>(a.GetNumerator() * b.GetDenominator());
            //std::int64_t c2 = static_cast<std::int64_t>(b.GetNumerator() * a.GetDenominator());
            return !(a < b) && !(a > b); 
        }
        */
