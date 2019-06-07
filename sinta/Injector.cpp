#include "ScriptRunner.h"

#include "Injector.h"

#include <QCoreApplication>
#include <QTimer>

void setupScriptRunner() {
    QString scriptPath = qgetenv(INJECTOR_SCRIPT_ENV);
    auto* scriptRunner = new ScriptRunner;
    QTimer::singleShot(0, [scriptRunner, scriptPath] { scriptRunner->runScript(scriptPath); });
}

Q_COREAPP_STARTUP_FUNCTION(setupScriptRunner)
