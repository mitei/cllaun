#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>

namespace cllaun {
    class MainWindow: public QWidget {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow(){}
    private:
        QVBoxLayout layout;
        QLineEdit command_line;
    public slots:
        void Run();
    };
}
