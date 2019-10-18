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
#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>

class QJSValue;

class Tools : public QObject {
    Q_OBJECT
public:
    explicit Tools(QObject* parent = nullptr);

    Q_INVOKABLE void screenshot(QWidget* widget, const QString& path);
    Q_INVOKABLE QObject* findChild(QObject* parent, const QString& name);
    Q_INVOKABLE QWidget* activeWindow();
    Q_INVOKABLE void processEvents();
    Q_INVOKABLE void setTimeout(const QJSValue& value, int ms);
};

#endif // TOOLS_H
