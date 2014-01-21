#include "config.h"
#include "dirs.h"
#include "api.h"


/*!
 * @brief 設定ファイルの拡張子
 */
QStringList cllaun::Config::file_list;

/*!
 * @brief Config スクリプトオブジェクトの生成
 *
 * @param engine   オブジェクトの生成に使用するスクリプトエンジン
 * @return         生成した Config スクリプトオブジェクト
 */
QScriptValue cllaun::Config::newQObject(QScriptEngine* engine) {
    QScriptValue config_obj = engine->newQObject(new Config, QScriptEngine::ScriptOwnership);
    config_obj.setProperty("dirs", engine->newArray(), QScriptValue::Undeletable);
    return config_obj;
}

/*!
 * @brief コンストラクタ
 */
cllaun::Config::Config() {
    if (file_list.isEmpty()) {
        file_list << ".cllaun"
                  << "_cllaun";
    }
}

/*!
 * @brief 設定ファイルを読み込む
 */
void cllaun::Config::read() const {
    QStringList dirs = qscriptvalue_cast<QStringList>(thisObject().property("dirs"));
    const Dirs search_dirs(dirs);
    foreach (const QString file_name, file_list) {
        const QString conf_file_path = search_dirs.filePath(file_name);
        if (!conf_file_path.isEmpty()) {
            runScriptFile(engine(), conf_file_path);
        }
    }

}
