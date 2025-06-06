#include "ReaderFactory.h"


template <Derivative<BaseReader> ConReader, typename... Args>
std::unique_ptr<BaseReader> ConcreteReaderFactory<ConReader, Args...>::create(Args&&... args) {
    return std::make_unique<ConReader>(std::forward<Args>(args...));
}