//FIXME
//#include "Config.h"
#define SINTA_LIB_PATH "/home/perso/build/sinta/sinta/libsintalib.so"

#include "Injector.h"

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QProcess>

#include <iostream>
#include <optional>

static constexpr char PRELOAD_ENV[] = "LD_PRELOAD";

struct Arguments {
    QString script;
    QString executable;

    bool process(const QCoreApplication& app) {
        QCommandLineParser parser;
        parser.addPositionalArgument("script", "Script to run");
        parser.addPositionalArgument("executable", "Executable to start");
        parser.process(app);

        auto args = parser.positionalArguments();
        if (args.length() != 2) {
            std::cerr << "Wrong number of arguments\n";
            return false;
        }

        script = args.at(0);
        if (!QFile::exists(script)) {
            std::cerr << qPrintable(script) << " does not exist\n";
            return false;
        }
        executable = args.at(1);
        if (!QFile::exists(executable)) {
            std::cerr << qPrintable(executable) << " does not exist\n";
            return false;
        }
        return true;
    }
};

std::optional<QByteArray> findSintaLib() {
    QByteArray libPath = SINTA_LIB_PATH;
    if (!QFile::exists(libPath)) {
        std::cerr << "Cannot find our library: " << qPrintable(libPath) << " does not exist.\n";
        return {};
    }
    return std::move(libPath);
}

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Arguments args;
    if (!args.process(app)) {
        return 1;
    }
    auto libPath = findSintaLib();
    if (!libPath.has_value()) {
        return 2;
    }
    qputenv(PRELOAD_ENV, libPath.value());
    qputenv(INJECTOR_SCRIPT_ENV, args.script.toUtf8());

    return QProcess::execute(args.executable);
}
