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
