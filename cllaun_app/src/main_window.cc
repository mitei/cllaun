#include "main_window.h"
#include "launcher.h"

cllaun::MainWindow::MainWindow(QWidget* parent)
        : QWidget(parent, Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint),
          command_line(this)
{
    setAttribute(Qt::WA_TranslucentBackground, true);

    this->setObjectName("window");
    command_line.setObjectName("command_line");

    layout.addWidget(&command_line);
    this->setLayout(&layout);

    connect(&command_line, SIGNAL(returnPressed()),
            this, SLOT(Run()));
}

void cllaun::MainWindow::Run() {
    QString command = command_line.text();
    cllaun::Run(command);
}
