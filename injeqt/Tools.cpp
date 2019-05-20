#include "Tools.h"

#include <QApplication>
#include <QDebug>
#include <QQmlEngine>
#include <QPixmap>
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
