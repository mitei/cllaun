#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
//#include <QSystemTrayIcon>

namespace cllaun {
    class MainWindow: public QWidget {
        Q_OBJECT
    public:
        static MainWindow* Instance() {
            static QMainWindow main_window;
            static MainWindow mymain_window(&main_window);

            return &mymain_window;
        }
        inline QLineEdit* CommandLine() { return &command_line; }

    private:
        MainWindow() { }
        MainWindow(const MainWindow& rhs) { }
        MainWindow& operator=(const MainWindow& rhs) { }
        explicit MainWindow(QWidget* parent = 0);

    private:
        QVBoxLayout layout;
        QLineEdit command_line;
        //QSystemTrayIcon tray_icon;
    public slots:
        void Run();
    };
}
