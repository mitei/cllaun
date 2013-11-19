#include "main_window.h"
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
cllaun::MainWindow::MainWindow(QWidget* parent)
        : QWidget(parent, Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint),
          command_line(this)//, tray_icon(this)
{
    setAttribute(Qt::WA_TranslucentBackground, true);

    // QSS で ID 名のように使える
    this->setObjectName("window");
    command_line.setObjectName("command_line");

    layout.addWidget(&command_line);
    this->setLayout(&layout);

    connect(&command_line, SIGNAL(returnPressed()),
            this, SLOT(Run()));
}

/*!
 * @brief 入力されたコマンドを実行
 */
void cllaun::MainWindow::Run() {
    QString command = command_line.text();
    if (command == "") /* Error! */ return;
    cllaun::Run(command);
}
