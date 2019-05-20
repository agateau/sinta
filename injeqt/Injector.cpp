#include "ScriptRunner.h"

#include <QCoreApplication>
#include <QTimer>

void setupScriptRunner() {
    QString scriptPath = qgetenv("INJECT_SCRIPT");
    auto* scriptRunner = new ScriptRunner;
    QTimer::singleShot(0, [scriptRunner, scriptPath] { scriptRunner->runScript(scriptPath); });
}

Q_COREAPP_STARTUP_FUNCTION(setupScriptRunner)
