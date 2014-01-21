#pragma once
/*!
 * @brief 一般的な API の提供
 *
 * exit = function() { ...
 * eval = function(code:String) { ...
 */

class QScriptEngine;

namespace cllaun {

class API_Common {
public:
    API_Common(QScriptEngine* engine);
private:
    API_Common();
};

}
