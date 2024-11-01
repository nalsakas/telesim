#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString style = R"(
    QDockWidget QPushButton {
        background-color: #3F51B5;
        border: none;
        color: white;
        padding: 20% 20%;
        font-size: 200%;
        border: 2px solid white;
    }

    QDockWidget QPushButton:checked {
        background-color: #E91E63;
    }

    QDockWidget QPushButton:hover {
        border-color: #E91E63;
    }
    )";

    a.setStyleSheet(style);
    return a.exec();
}
