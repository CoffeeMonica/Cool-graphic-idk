/*
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poland.h"
#include <QPainter>
#include <QPixmap>
#include <math.h>
#include <QPainterPath>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);

    ui->label->setGeometry(10, 60, width() * 0.6625, height() - 60);

    ui->lineEdit->setGeometry(10, 10, width() * 0.55 - 10, 0.0667 * height());

    QPushButton* button = new QPushButton(this);
    button->setGeometry((10 + width() * 0.6625) - (0.1125 * width()), 10, 0.1125 * width(), int(0.0667 * height()));
    button->setText("Zeitplan");

    connect(button, SIGNAL(clicked()), this, SLOT(pushButton()));
}

void MainWindow::pushButton()
{
    QString s = ui->lineEdit->text();

    QPixmap px(width() * 0.6525, height() * 0.885);
    px.fill(Qt::black);

    QPainter painter(&px);

    double xmin = -100;
    double xmax = 100;
    double ymin = -100;
    double ymax = 100;
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

    QPen pen(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(x0, 0, x0, px.height());
    painter.drawLine(0, y0, px.width(), y0);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    double stp = (xmax - xmin) / (x_max - x_min);

    QPainterPath path;
    if (s.isEmpty()) {
        ui->label->setPixmap(px);
        return;
    }
    path.moveTo(_x, _y);

    while (x <= xmax) {
        QString result = culc(s.toStdString(), QString::number(x).toStdString());
        if (result != "FEHLER! FEHLER! FEHLER! FEHLER! FEHLER!") {
            y = result.toDouble();
            _x = x0 + kx * x;
            _y = y0 + ky * y;
            path.moveTo(_x, _y);
        }

        while (x <= xmax && (_y >= y_min || _y <= y_max)) {
            x += stp;
            _x = x0 + kx * x;
            _y = y0 + ky * y;
            path.lineTo(_x, _y);
        }

        if (_y >= y_min && _y <= y_max) {
            painter.drawPath(path);
        }

        path = QPainterPath();
        path.moveTo(_x, _y);
    }

    ui->label->setPixmap(px);
}

MainWindow::~MainWindow()
{
    delete ui;
}
*/
