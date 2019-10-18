/*
 * Copyright 2019 Aurélien Gâteau <mail@agateau.com>
 *
 * This file is part of Sinta.
 *
 * Sinta is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "config.h"
#include "Injector.h"

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QFile>
#include <QProcess>

#include <iostream>
#include <optional>

static constexpr char PRELOAD_ENV[] = "LD_PRELOAD";

struct Arguments {
    QString script;
    QString executable;
    QStringList arguments;

    bool process(const QCoreApplication& app) {
        QCommandLineParser parser;
        parser.addHelpOption();
        parser.addVersionOption();
        parser.addPositionalArgument("script", "Script to run");
        parser.addPositionalArgument("executable", "Executable to start");
        parser.process(app);

        auto args = parser.positionalArguments();
        if (args.length() < 2) {
            std::cerr << "Wrong number of arguments\n";
            return false;
        }

        script = args.takeFirst();
        if (!QFile::exists(script)) {
            std::cerr << qPrintable(script) << " does not exist\n";
            return false;
        }
        executable = args.takeFirst();
        if (!QFile::exists(executable)) {
            std::cerr << qPrintable(executable) << " does not exist\n";
            return false;
        }
        arguments = args;
        return true;
    }
};

std::optional<QByteArray> findSintaLib() {
    for (const auto& path : {SINTALIB_BUILD_PATH, SINTALIB_INSTALL_PATH}) {
        if (QFile::exists(path)) {
            return std::move(path);
        }
    }
    std::cerr << "Cannot find Sinta library";
    return {};
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

    return QProcess::execute(args.executable, args.arguments);
}
