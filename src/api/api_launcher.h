#pragma once

/*!
 * @brief 一般的なランチャの機能の提供
 *
 * Launcher = {
 *     run = function(cmd:Command):Number { ...
 *     execute = function(path:String, args:String):Number { ...
 * };
 */

class QScriptEngine;

namespace cllaun {

class API_Launcher {
public:
    API_Launcher(QScriptEngine* engine);

private:
    API_Launcher();
};

}
