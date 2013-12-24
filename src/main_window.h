#pragma once

#include <QWidget>
#include <QLineEdit>

class QMainWindow;

namespace cllaun {

class MainWindow: public QWidget {
    Q_OBJECT
public:
    MainWindow();

private:
    QLineEdit command_line;
    QMainWindow* parent_window;

public slots:
    void run();
};

}
