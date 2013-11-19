#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
//#include <QSystemTrayIcon>

namespace cllaun {
    class MainWindow: public QWidget {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = 0);

    private:
        QVBoxLayout layout;
        QLineEdit command_line;
        //QSystemTrayIcon tray_icon;

    public slots:
        void Run();
    };
}
