#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poland.h"
#include <QPainter>
#include <QPixmap>
#include <math.h>
#include <QPainterPath>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);

    ui -> label -> setGeometry(75, 75, width() - 100, height() - 100);

    ui -> lineEdit -> setGeometry(10, 10, width() * 0.55 - 10, 0.0667 * height());

    QPushButton* button = new QPushButton(this);
    button -> setGeometry((10 + width() * 0.6625) - (0.1125 * width()), 10, 0.1125 * width(), int(0.0667 * height()));
    button -> setText("Zeitplan");

    connect(button, SIGNAL(clicked()), this, SLOT(pushButton()));
}

void MainWindow::pushButton()
{
    QString s = ui->lineEdit->text();

    QPixmap px(width() * 0.6525, height() * 0.885);
    px.fill(Qt::black);

    QPainter painter(&px);

    double xmin = -10;
    double xmax = 10;
    double ymin = -10;
    double ymax = 10;
    int x_min = 0;
    int y_min = 0;
    int x_max = px.width();
    int y_max = px.height();

    double kx = (x_max - x_min) / (xmax - xmin);
    double ky = (y_min - y_max) / (ymax - ymin);

    int x0 = x_min - kx * xmin;
    int y0 = y_min - ky * ymax;

    double x = xmin;
    double y = 0;
    int _x = 0;
    int _y = 0;
    string ss = '(' + s.toStdString() + ')';
    s = QString::fromStdString(ss);
    QPen pen(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(x0, 0, x0, px.height());
    painter.drawLine(0, y0, px.width(), y0);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    pen.setWidth(3);

    double stp = (xmax - xmin) / (x_max - x_min);

    QPainterPath path;
    if (s.isEmpty()) {
        ui -> label -> setPixmap(px);
        return;
    }
    QString ans = culc(s.toStdString(), QString::number(x).toStdString());
    int eps = 1e9;
    while (ans == "Error" && eps > 0) {
        eps--;
        x += stp;
        path.moveTo(_x, _y);
        ans = culc(s.toStdString(), QString::number(x).toStdString());
    }
    y = ans.toDouble();
    _x = x0 + kx * x;
    _y = y0 + ky * y;
    path.moveTo(_x, _y);

    while (x <= xmax && eps > 0) {
        eps--;
        ans = culc(s.toStdString(), QString::number(x).toStdString());
        if (ans == "Error") {
            x += stp;
            path.moveTo(_x, _y);
            continue;
        }
        y = ans.toDouble();
        _x = x0 + kx * x;
        _y = y0 + ky * y;
        path.lineTo(_x, _y);
        painter.drawPath(path);
        x += stp;
    }

    ui->label->setPixmap(px);
}

MainWindow::~MainWindow()
{
    delete ui;
}
