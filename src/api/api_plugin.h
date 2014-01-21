#pragma once

/*!
 * @brief プラグインの読み込みなどを提供
 *
 * plugin = {
 *     imported : [],
 *     available : [],
 *     ignore : [],
 *     import : function(name:String) { ...
 *     importAll : function() { ...
 * };
 */

class QScriptEngine;

namespace cllaun {

class API_Plugin {
public:
    API_Plugin(QScriptEngine* engine);
private:
    API_Plugin();
};

}
