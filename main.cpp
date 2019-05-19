#include "MainWindow.h"
#include "Tools.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QJSEngine>
#include <QTimer>

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

void setupEngine(QJSEngine* engine) {
    engine->installExtensions(QJSEngine::AllExtensions);
    engine->globalObject().setProperty("tools", engine->newQObject(new Tools));
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Q_ASSERT(app.arguments().length() == 2);
    auto path = app.arguments().last();
    auto maybeScript = loadScript(path);
    if (!maybeScript.has_value()) {
        return 1;
    }
    auto script = maybeScript.value();

    MainWindow window;

    QJSEngine engine;
    setupEngine(&engine);

    QTimer::singleShot(0, &engine, [&engine, &script, &path] {
        QJSValue result = engine.evaluate(script, path);
        if (result.isError()) {
            qWarning() << "Error line" << result.property("lineNumber").toInt() << ":"
                       << result.toString();
        } else {
            qInfo() << "result=" << result.toString();
        }
    });

    window.show();

    return app.exec();
}
