#ifndef IWORKER_H
#define IWORKER_H

class IWorker {
public:
    virtual ~IWorker() = default;
    
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // IWORKER_H 