#pragma once

/*!
 * @brief コマンドのパースなどを提供
 *
 * Parser = {
 *     parse = function(str:String): cmd:Command { ...
 *     split = function(str:String): tokens:Array { ...
 * };
 */

class QScriptEngine;

namespace cllaun {

class API_Parser {
public:
    API_Parser(QScriptEngine* engine);
private:
    API_Parser();
};

}
