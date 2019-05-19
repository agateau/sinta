#include "MainWindow.h"

#include "ScriptRunner.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Q_ASSERT(app.arguments().length() == 2);
    auto path = app.arguments().last();

    MainWindow window;

    ScriptRunner runner;

    QTimer::singleShot(0, &runner, [&runner, &path] {
        runner.runScript(path);
    });

    window.show();

    return app.exec();
}
