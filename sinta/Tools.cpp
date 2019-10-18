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
#include <QTimer>
#include <QWidget>

Tools::Tools(QObject* parent) : QObject(parent) {
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
