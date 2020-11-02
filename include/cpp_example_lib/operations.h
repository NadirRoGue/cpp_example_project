#ifndef CPP_EXAMPLE_LIB_OPERATIONS_H
#define CPP_EXAMPLE_LIB_OPERATIONS_H

#include <type_traits>

#include "types.h"

namespace bbp {
namespace examplelib {

template <
    typename T,
    typename = std::enable_if_t<std::is_same<T, Integer>::value || std::is_same<T, Real>::value>>
T add(T a, T b) {
    return a + b;
}

template <
    typename T,
    typename = std::enable_if_t<std::is_same<T, Integer>::value || std::is_same<T, Real>::value>>
T sub(T a, T b) {
    return a - b;
}

template <
    typename T,
    typename = std::enable_if_t<std::is_same<T, Integer>::value || std::is_same<T, Real>::value>>
T mul(T a, T b) {
    return a * b;
}

template <
    typename T,
    typename = std::enable_if_t<std::is_same<T, Integer>::value || std::is_same<T, Real>::value>>
T divideBy(T a, T b) {
    return a / b;
}

}  // namespace examplelib
}  // namespace bbp

#endif
