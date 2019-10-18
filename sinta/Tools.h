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

/**
 * An instance of this object is exposed as `tools` in the JavaScript world
 */
class Tools : public QObject {
    Q_OBJECT
public:
    explicit Tools(QObject* parent = nullptr);

    /**
     * Takes a screenshot of widget, save it under path
     */
    Q_INVOKABLE void screenshot(QWidget* widget, const QString& path);

    /**
     * Returns the currently active window, if any
     */
    Q_INVOKABLE QWidget* activeWindow();

    /**
     * Returns the first child of parent whose objectName is name
     */
    Q_INVOKABLE QObject* findChild(QObject* parent, const QString& name);

    /**
     * Let the main loop process events
     */
    Q_INVOKABLE void processEvents();

    /**
     * Run function after ms milliseconds.
     *
     * Equivalent to the `window.setTimeout()` method available in web
     * browsers.
     */
    Q_INVOKABLE void setTimeout(const QJSValue& function, int ms);

    /**
     * Process events until a window is active.
     * If excludedWindow is not null, ignore the active window if it is excludedWindow.
     * This is useful to find child windows: you can just ignore the parent.
     *
     * Returns the window if found or nullptr if we waited for too long
     */
    Q_INVOKABLE QWidget* waitForActiveWindow(QWidget* excludedWindow = nullptr,
                                             int maxTimeout = 3000);
};

#endif // TOOLS_H
