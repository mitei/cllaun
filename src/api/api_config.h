#pragma once

/*!
 * @brief 設定ファイル読み込みなどの API の提供
 *
 * config = {
 *     read : function() { ...
 * };
 */

class QScriptEngine;

namespace cllaun {

class Config;

class API_Config {
public:
    API_Config(QScriptEngine* engine);
    static Config* globalConfig();
private:
    static Config* global_config; /*!< 唯一の Config インスタンス */
private:
    API_Config();
};

}
