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
#include "Tools.h"

#include <QApplication>
#include <QDeadlineTimer>
#include <QDebug>
#include <QPixmap>
#include <QQmlEngine>
#include <QTimer>
#include <QWidget>

// Call a JS function, abort if it failed
static QJSValue checkJsCall(const QJSValue& function, const QJSValueList& args = {}) {
    auto result = QJSValue(function).call(args);
    if (result.isError()) {
        int line = result.property("lineNumber").toInt();
        QString message = result.toString();
        qFatal("Error line %d: %s", line, qPrintable(message));
    }
    return result;
}

Tools::Tools(QJSEngine* engine, QObject* parent) : QObject(parent), mEngine(engine) {
}

void Tools::screenshot(QWidget* widget, const QString& path) {
    QPixmap pix = widget->grab();
    pix.save(path);
}

QObject* Tools::findChild(QObject* parent, const QString& name) {
    return parent->findChild<QObject*>(name);
}

QWidget* Tools::activeWindow() {
    QWidget* widget = QApplication::activeWindow();
    QQmlEngine::setObjectOwnership(widget, QQmlEngine::CppOwnership);
    return widget;
}

void Tools::processEvents() {
    QApplication::processEvents();
}

void Tools::setTimeout(const QJSValue& function, int ms) {
    QTimer::singleShot(ms, nullptr, [function] {
        checkJsCall(function);
    });
}

QWidget* Tools::waitForActiveWindow(QWidget* excludedWindow, int maxTimeout) {
    QDeadlineTimer timer(maxTimeout);
    while (!timer.hasExpired()) {
        auto* window = activeWindow();
        if (window && window != excludedWindow) {
            return window;
        }
        processEvents();
    }
    qWarning() << QString("Call to waitForActiveWindow(%1, %2) hit timeout.")
                      .arg(reinterpret_cast<intptr_t>(excludedWindow))
                      .arg(maxTimeout);
    return nullptr;
}

void Tools::waitForActiveWindowAsync(const QJSValue& function,
                                     QWidget* excludedWindow,
                                     int maxTimeout) {
    waitForActiveWindowAsyncImpl(function, excludedWindow, QDeadlineTimer(maxTimeout));
}

void Tools::waitForActiveWindowAsyncImpl(const QJSValue& function,
                                         QWidget* excludedWindow,
                                         const QDeadlineTimer& timer) {
    if (timer.hasExpired()) {
        qWarning() << QString("Call to waitForActiveWindowAsync() hit timeout.");
        checkJsCall(function, {QJSValue()});
        return;
    }
    auto* window = activeWindow();
    if (window && window != excludedWindow) {
        // We found it
        auto windowValue = mEngine->newQObject(window);
        checkJsCall(function, {windowValue});
    } else {
        // Try again
        QTimer::singleShot(0, this, [this, function, excludedWindow, timer] {
            waitForActiveWindowAsyncImpl(function, excludedWindow, timer);
        });
    }
}
