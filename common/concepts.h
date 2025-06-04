#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <iostream>
#include <concepts>

template <typename T, typename... Args>
concept ConstructibleWith = requires(Args&&... args) {
    T{std::forward<Args>(args)...};
};

template <typename Derived, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

template <typename Type>
concept Abstract = std::is_abstract_v<Type>;

template <typename Type>
concept DefaultConstructible = std::is_default_constructible_v<Type>;



#endif