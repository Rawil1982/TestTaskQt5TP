#ifndef INCREMENTWORKER_H
#define INCREMENTWORKER_H

#include "iworker.h"
#include <memory>
#include <atomic>
#include <chrono>
#include <thread>

class ICounterRepository;

class IncrementWorker : public IWorker {
public:
    explicit IncrementWorker(std::shared_ptr<ICounterRepository> repository);
    ~IncrementWorker() override;
    
    void start() override;
    void stop() override;
    
private:
    void incrementLoop();
    
    std::shared_ptr<ICounterRepository> m_repository;
    std::atomic<bool> m_running;
    std::thread m_thread;
    std::chrono::milliseconds m_interval;
};

#endif // INCREMENTWORKER_H 