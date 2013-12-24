#include "main_window.h"

#include <QString>
#include <QMainWindow>

#include "launcher.h"


/*!
 * @brief コンストラクタ
 * @param 親ウィジェット
 *
 * @note QWidget( QWidget* parent = 0, QWindowFlags flags = 0 );
 *       Qt::Dialog - ウィジェットは独立したウィンドウを持つ
 *       Qt::FramelessWindowHint - デフォルトのウィンドウ枠を持たない
 *       Qt::WindowStaysOnTopHint - 常に最前面表示
 */
cllaun::MainWindow::MainWindow()
        : QWidget(nullptr),
          command_line(this),
          parent_window(new QMainWindow)
{
    setParent(parent_window, Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    this->setObjectName("window");
    command_line.setObjectName("command_line");

    connect(&command_line, SIGNAL(returnPressed()),
            this, SLOT(run()));
}


/*!
 * @brief 入力されたコマンドを実行
 */
void cllaun::MainWindow::run() {
    QString command = command_line.text();
    if (command == "") /* Error! */ return;
    cllaun::run(command);
}
