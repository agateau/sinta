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
    mEngine->globalObject().setProperty("tools", mEngine->newQObject(new Tools(mEngine.get())));
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
