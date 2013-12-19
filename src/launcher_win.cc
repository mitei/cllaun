#include "launcher.h"

#include <Windows.h>

#include <QString>
#include <QDir>
#include <QFileInfo>


/*!
 * @brief Windows 用 `ファイルを開く`
 *
 * @param path ファイルまたはディレクトリのパス
 * @param args 引数文字列
 *
 * @return 実行結果
 */
int cllaun::execute(const QString& path, const QString& args) {
    SHELLEXECUTEINFO sh_info;

    /*
     * set directory that contains path-file, as working-directory.
     */
    QDir dir(path);
    QFileInfo info(path);
    if (!info.isDir() && info.isFile())
        dir.cdUp();
    QString directory = QDir::toNativeSeparators(dir.absolutePath());

    /*
     * set SHELLEXECUTEINFO(sh_info) members.
     */
    sh_info.cbSize   = sizeof(SHELLEXECUTEINFO);
    //sh_info.fMask    = SEE_MASK_FLAG_NO_UI;
    sh_info.fMask    = NULL;
    sh_info.hwnd     = NULL;
    sh_info.lpVerb   = NULL; // "open"
    sh_info.lpFile   =
            reinterpret_cast<LPCTSTR>(QDir::toNativeSeparators(path).utf16());
    sh_info.lpParameters = (args != "") ?
            reinterpret_cast<LPCTSTR>(args.utf16()) :
            NULL;
    sh_info.lpDirectory = reinterpret_cast<LPCTSTR>(directory.utf16());
    sh_info.nShow = SW_NORMAL;
    sh_info.hInstApp = NULL;

    ShellExecuteEx(&sh_info);

    // TODO: return result
    return 1;
}
