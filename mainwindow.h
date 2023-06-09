#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QPushButton button;
    ~MainWindow();

private slots:
    void pushButton();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
