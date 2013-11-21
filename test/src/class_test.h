#pragma once

#include <QObject>
#include <QString>
#include <QDebug>
#include <QScriptEngine>
#include "api.h"

class Sample:public QScriptClass {
public:
    Sample(QScriptEngine* engine_): engine(engine_) { }
    void Show(const QString& str) {
        qDebug() << str;
    }
    QString name() const { return "Sample"; }
private:
    QScriptEngine* engine;
};

void InitClass(QScriptEngine* engine) {
}
