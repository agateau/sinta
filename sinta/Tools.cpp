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
#include <QDebug>
#include <QPixmap>
#include <QQmlEngine>
#include <QTime>
#include <QTimer>
#include <QWidget>

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

void Tools::setTimeout(const QJSValue& value_, int ms) {
    QJSValue value = value_;
    QTimer::singleShot(ms, nullptr, [value] {
        // Don't know why, but g++ thinks `value` is const, so create a local
        // copy to be able to call `QJSValue::call()`
        QJSValue(value).call();
    });
}

QWidget* Tools::waitForActiveWindow(QWidget* excludedWindow, int maxTimeout) {
    QTime chrono;
    chrono.start();
    while (chrono.elapsed() < maxTimeout) {
        auto* window = activeWindow();
        if (window && window != excludedWindow) {
            return window;
        }
        processEvents();
    }
    qWarning() << QString("Call to waitForActiveWindow(%1, %2) hit timeout (waited for %3ms).")
                      .arg(reinterpret_cast<intptr_t>(excludedWindow))
                      .arg(maxTimeout)
                      .arg(chrono.elapsed());
    return nullptr;
}

void Tools::waitForActiveWindowAsync(const QJSValue& function,
                                     QWidget* excludedWindow,
                                     int maxTimeout) {
    QTime deadLine = QTime::currentTime().addMSecs(maxTimeout);
    waitForActiveWindowAsyncImpl(function, excludedWindow, deadLine);
}

void Tools::waitForActiveWindowAsyncImpl(const QJSValue& function,
                                         QWidget* excludedWindow,
                                         const QTime& deadLine) {
    if (QTime::currentTime() > deadLine) {
        qWarning() << QString("Call to waitForActiveWindowAsync() hit timeout.");
        QJSValue(function).call({QJSValue()});
        return;
    }
    auto* window = activeWindow();
    if (window && window != excludedWindow) {
        // We found it
        auto windowValue = mEngine->newQObject(window);
        QJSValue(function).call({windowValue});
    } else {
        // Try again
        QTimer::singleShot(0, this, [this, function, excludedWindow, deadLine] {
            waitForActiveWindowAsyncImpl(function, excludedWindow, deadLine);
        });
    }
}
