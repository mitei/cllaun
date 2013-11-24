#include <QDebug>
#include <QCoreApplication>
#include <QObject>
#include <QScriptEngine>

class Sample: public QObject {
public:
    Sample() { qDebug("Sample constructor"); }
    Sample(int x_, int y_): x(x_), y(y_) { qDebug("Sample constructor"); }
    virtual ~Sample() { qDebug("Sample destructor"); }

    static QScriptValue New(QScriptContext* context, QScriptEngine* engine) {
        qint32 x = context->argument(0).toInt32();
        qint32 y = context->argument(1).toInt32();

        Sample* obj = new Sample(x, y);

        QScriptValue instance = (context->isCalledAsConstructor() ?
                                     engine->newQObject(context->thisObject(), obj, QScriptEngine::AutoOwnership) :
                                     engine->newQObject(obj, QScriptEngine::AutoOwnership));
        instance.setProperty("x", engine->newFunction(AccessorX), QScriptValue::PropertyGetter|QScriptValue::PropertySetter);
        instance.setProperty("y", engine->newFunction(AccessorY), QScriptValue::PropertyGetter|QScriptValue::PropertySetter);

        return instance;
    }

    static QScriptValue AccessorX(QScriptContext* context,  QScriptEngine* engine) {
        Sample* sample = dynamic_cast<Sample*>(context->thisObject().toQObject());
        if (sample == nullptr) {
            return QScriptValue::UndefinedValue;
        }
        QScriptValue result;
        if (context->argumentCount() == 1) {
            // Setter
            QScriptValue rhs = context->argument(0);
            if (rhs.isNumber()) {
                qint32 val = rhs.toInt32();
                sample->x = val;
                result = rhs;
            } else {
                return QScriptValue::UndefinedValue;
            }
        } else {
            // Getter
            result = QScriptValue(sample->x);
        }
        return result;
    }

    static QScriptValue AccessorY(QScriptContext* context,  QScriptEngine* engine) {
        Sample* sample = dynamic_cast<Sample*>(context->thisObject().toQObject());
        if (sample == nullptr) {
            return QScriptValue::UndefinedValue;
        }
        QScriptValue result;
        if (context->argumentCount() == 1) {
            // Setter
            QScriptValue rhs = context->argument(0);
            if (rhs.isNumber()) {
                qint32 val = rhs.toInt32();
                sample->y = val;
                result = rhs;
            } else {
                return QScriptValue::UndefinedValue;
            }
        } else {
            // Getter
            result = QScriptValue(sample->y);
        }
        return result;
    }

    int x, y;
};

QScriptValue Print(QScriptContext* context, QScriptEngine* engine) {
    for (int i = 0; i < context->argumentCount(); ++i) {
        qDebug() << context->argument(i).toString();
    }
    return QScriptValue::UndefinedValue;
}

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    QScriptEngine engine;

    engine.globalObject().setProperty("print", engine.newFunction(Print));

    QScriptValue sample_ctr = engine.newFunction(Sample::New);
    engine.globalObject().setProperty("Sample", sample_ctr);

    engine.evaluate("var sample = new Sample(100, 234);\
                     print(sample.x);\
                     print(sample.y);\
                     sample.x = 454;\
                     sample.y = 321;\
                     print(sample.x);\
                     print(sample.y);\
                    ");
    return 0;
}