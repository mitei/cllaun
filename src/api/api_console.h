#pragma once

/*!
 * @brief モダンブラウザの console オブジェクトのエミュレート
 *
 * console = {
 *     log : function(str:String) { ...
 *     dir : function(obj:Object) { ...
 * };
 */

class QScriptEngine;

namespace cllaun {

class API_Console {
public:
    API_Console(QScriptEngine* engine);
private:
    API_Console();
};

}
