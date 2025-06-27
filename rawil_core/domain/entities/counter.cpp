#include "counter.h"

namespace {
    constexpr int DEFAULT_ID = 0;
    constexpr int DEFAULT_VALUE = 0;
    constexpr int INCREMENT_STEP = 1;
}

Counter::Counter(int id, int value) : m_id(id), m_value(value) {}

int Counter::getId() const {
    return m_id;
}

void Counter::setId(const int id) {
    m_id = id;
}

int Counter::getValue() const {
    return m_value;
}

void Counter::setValue(const int value) {
    m_value = value;
}

void Counter::increment() {
    m_value += INCREMENT_STEP;
} 