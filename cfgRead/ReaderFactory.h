#ifndef READER_FACTORY_H
#define READER_FACTORY_H

#include <memory>
#include "ConcreteReader.h"
#include "common/concepts.h"

template <typename... Args>
class BaseReaderFactory {
public:
    virtual std::unique_ptr<BaseReader> create(Args&&... args) = 0;
    virtual ~BaseReaderFactory() = default;
};

template <Derivative<BaseReader> ConReader, typename... Args>
requires ConstructibleWith<ConReader, Args...>
class ConcreteReaderFactory : public BaseReaderFactory<Args> {
public:
    std::unique_ptr<BaseReader> create(Args&&... args) override;
};

using DefaultReaderCreator = ConcreteReaderFactory<ConcreteReader, std::string_view>;

#endif