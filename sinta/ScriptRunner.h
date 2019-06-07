#ifndef SCRIPTRUNNER_H
#define SCRIPTRUNNER_H

#include <QObject>

#include <memory>

class QJSEngine;

class ScriptRunner : public QObject {
public:
    ScriptRunner();
    ~ScriptRunner();

    void runScript(const QString& path);

private:
    const std::unique_ptr<QJSEngine> mEngine;
};

#endif // SCRIPTRUNNER_H
