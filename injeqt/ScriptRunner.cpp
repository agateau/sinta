#include "ScriptRunner.h"

#include "Tools.h"

#include <QDebug>
#include <QFile>
#include <QJSEngine>

#include <optional>

using std::optional;

optional<QString> loadScript(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open" << path << file.errorString();
        return {};
    }
    QByteArray data = file.readAll();
    return QString::fromUtf8(data);
}

ScriptRunner::ScriptRunner() : mEngine(std::make_unique<QJSEngine>()) {
    mEngine->installExtensions(QJSEngine::AllExtensions);
    mEngine->globalObject().setProperty("tools", mEngine->newQObject(new Tools));
}

ScriptRunner::~ScriptRunner() {
}

void ScriptRunner::runScript(const QString& path) {
    optional<QString> maybeScript = loadScript(path);
    if (!maybeScript.has_value()) {
        return;
    }
    QJSValue result = mEngine->evaluate(maybeScript.value(), path);
    if (result.isError()) {
        qWarning() << "Error line" << result.property("lineNumber").toInt() << ":"
                   << result.toString();
    } else if (!result.isUndefined()) {
        qInfo() << "result=" << result.toString();
    }
}
