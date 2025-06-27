#ifndef COUNTER_H
#define COUNTER_H

#include <QString>

class Counter {
public:
    Counter(const int id = 0, const int value = 0);
    
    int getId() const;
    void setId(const int id);
    
    int getValue() const;
    void setValue(const int value);
    
    void increment();
    
private:
    int m_id;
    int m_value;
};

#endif // COUNTER_H 