#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

#include <type_traits>
#include <QDebug>

using Error = std::string;

template<class Number>
class Calculator {

public:

    // Заменяет текущий результат на число n.
    void Set(Number n);

    // Возвращает текущий результат вычислений калькулятора.
    //В только что сконструированном калькуляторе этот метод возвращает 0.
    Number GetNumber() const;

    // Прибавляет число n к текущему результату внутри калькулятора.
    std::optional<Error> Add(Number n);

    // Вычитает число n из текущего результата.
    std::optional<Error> Sub(Number n);

    // Делит текущий результат на n.
    std::optional<Error> Div(Number n);

    // Умножает текущий результат на n.
    std::optional<Error> Mul(Number n);

    // Возводит текущий результат в степень n.
    std::optional<Error> Pow(Number n);

    // Сохраняет текущий результат в ячейку памяти калькулятора.
    void Save();

    // Загружает число из памяти калькулятора в текущий результат.
    void Load();

    // Возвращает memory, если ячейка памяти непустая.
    std::optional<Number> GetHasMem() const;

private:
    std::optional<Number> mem_;
    Number active_number_ = 0;
};

// ОПРЕДЕЛЕНИЕ ФУНКЦИЙ КАЛЬКУЛЯТОРА:

template<typename Number>
void Calculator<Number>::Set(Number n) {
    active_number_ = n;
}

template<typename Number>
Number Calculator<Number>::GetNumber() const {
    return active_number_;
}

template<typename Number>
std::optional<Error> Calculator<Number>::Add(Number n) {
    if constexpr (std::is_integral_v<Number>) {
        //qDebug() << "инт";
    }
    if constexpr (std::is_same_v<Number, Rational>) {
        //qDebug() << "дробь";
    }
    active_number_+=n;
    return std::nullopt;
}


template<typename Number>
std::optional<Error> Calculator<Number>::Sub(Number n) {
    active_number_ -=n;
    return std::nullopt;
}

template<typename Number>
std::optional<Error> Calculator<Number>::Div(Number n) {
    // проверяем тип числа при делении на 0:
    if (n==0) {
        if constexpr (std::is_integral_v<Number> ||
                                 std::is_same_v<Number, Rational>) {
            return "Division by zero";
        }
    }
    active_number_ /=n;
    return std::nullopt;
}

template<typename Number>
std::optional<Error> Calculator<Number>::Mul(Number n) {
    active_number_ *=n;
    return std::nullopt;
}

// Возводит текущий результат в степень n.
template<typename Number>
std::optional<Error> Calculator<Number>::Pow(Number n)
{
    if (n == 0 && active_number_ == 0) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            //qDebug() << "инт или дробь";
            return "Zero power to zero";
        }
    }
    if constexpr (std::is_integral_v<Number>) {
        if (n < 0) {
            //qDebug() << "инт";
            return "Integer negative power";
        }
        active_number_ = IntegerPow(active_number_, n);
        return std::nullopt;
    }

    if constexpr (std::is_same_v<Number, Rational>) {
        if (n.GetDenominator() != 1) {
            return "Fractional power is not supported";
        }
        //qDebug() << "дробь";
        active_number_ = RPow(active_number_, n);
        return std::nullopt;
    } else {
        active_number_ = ::pow(active_number_, n);
    }
    //qDebug() << "дабл, флоат";
    return std::nullopt;
}

template<typename Number>
void Calculator<Number>::Save() {
    mem_ = active_number_;
}

template<typename Number>
void Calculator<Number>::Load() {
    if (mem_.has_value()) {
        active_number_ = mem_.value();
    }
}

template<typename Number>
std::optional<Number> Calculator<Number>::GetHasMem() const
{
    if (mem_.has_value()) {
        return mem_;
    }
    return std::nullopt;
}
