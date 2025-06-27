#ifndef IWORKER_H
#define IWORKER_H

#include <QObject>

class IWorker : public QObject {
    Q_OBJECT
public:
    explicit IWorker(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~IWorker() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;
    virtual const char* getWorkerName() const = 0;

signals:
    void started();
    void stopped();
    void error(const QString& errorMessage);
    void dataChanged();
};

#endif 
