#include "skin.h"

#include <QString>
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QScriptEngine>

#include "dirs.h"


/*!
 * @brief スキン本体の QSS ファイルの名前
 */
const char* cllaun::Skin::skin_file_name = "style.qss";

QScriptValue cllaun::Skin::newQObject(QScriptEngine* engine, QApplication* _app) {
    QScriptValue skin_obj = engine->newQObject(new Skin(_app), QScriptEngine::ScriptOwnership);
    skin_obj.setProperty("dirs", engine->newArray(), QScriptValue::Undeletable);
    return skin_obj;
}

cllaun::Skin::Skin(QApplication* _app)
    : app(_app)
{
}

/*!
 * @brief 指定されたスキンを読み込む
 *
 * @param name スキン名
 */
void cllaun::Skin::read(const QString& name) {
    QStringList dirs = qscriptvalue_cast<QStringList>(thisObject().property("dirs"));
    const Dirs search_dirs(dirs);
    const QString skin_dir_path = search_dirs.dirPath(name);
    if (!skin_dir_path.isEmpty()) {
        QDir skin_dir(skin_dir_path);
        if (skin_dir.exists(skin_file_name)) {
            QFile style_file(skin_dir.filePath(skin_file_name));
            style_file.open(QFile::ReadOnly);
            QString str_style = QString::fromUtf8(style_file.readAll());
            style_file.close();
            app->setStyleSheet(str_style);
        }
    }
}
