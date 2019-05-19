#include "Tools.h"

#include <QApplication>
#include <QQmlEngine>
#include <QPixmap>
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
