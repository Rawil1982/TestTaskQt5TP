#ifndef IDATABASE_H
#define IDATABASE_H

#include <vector>

class IDatabase {
public:
    virtual ~IDatabase() = default;
    
    virtual std::vector<int> loadCounters() = 0;
    virtual void saveCounters(const std::vector<int>& counters) = 0;
    virtual bool isOpen() const = 0;
};

#endif // IDATABASE_H 