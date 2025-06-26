#ifndef IWORKERMANAGER_H
#define IWORKERMANAGER_H

#include <QObject>
#include <memory>

class IWorker;
class IDatabase;
class CounterManager;

class IWorkerManager : public QObject {
    Q_OBJECT
public:
    explicit IWorkerManager(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~IWorkerManager() = default;
    virtual void startAll() = 0;
    virtual void stopAll() = 0;
    virtual void pauseAll() = 0;
    virtual void resumeAll() = 0;
    virtual IWorker* getDatabaseWorker() const = 0;
    virtual IWorker* getIncrementWorker() const = 0;

signals:
    void allWorkersStarted();
    void allWorkersStopped();
    void workerError(const QString& workerName, const QString& errorMessage);
};

#endif 