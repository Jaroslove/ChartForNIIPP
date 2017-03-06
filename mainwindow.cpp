#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include<cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot()
{
    double sizeOfVector = 30*500;
    QVector<double> x(sizeOfVector), y(sizeOfVector);
    int j = 0;
    double step = -10;
    while (step<20) {
        x[j] = step;
        y[j] = step * step / sin(step/4 * M_PI) +
               exp(log(abs (step) * abs(sin(M_PI * step / 2 + 1 )))) ;
        j++;
        step+=0.02;
    }

    ui->customePlot->addGraph();
    ui->customePlot->setInteraction(QCP::iRangeDrag,true);
    ui->customePlot->setInteraction(QCP::iRangeZoom,true);
    ui->customePlot->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->customePlot->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->customePlot->xAxis->setAutoTickStep(true);
    ui->customePlot->graph(0)->setData(countX(), countY());
    ui->customePlot->rescaleAxes();
    ui->customePlot->replot();

    ui->customePlot->xAxis->setLabel("x");
    ui->customePlot->yAxis->setLabel("y");

    ui->customePlot->yAxis->setRange(100, 100);
    ui->customePlot->replot();
}

void MainWindow::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                     tr("Choose a filename to save under"),
                                                     QString(),
                                                     tr("PNG(*.png);;JPG(*.jpg);;PDF(*.pdf);;BMP(*.bmp);;All Files(*)")
                                                     );

    if (!fileName.isEmpty())
    {
        ui->customePlot->savePng(fileName);
    }
    QMessageBox::information(this,"Файл сохранён",fileName);
}

QVector<double> MainWindow::countX()
{
    int sizeOfVector = 30*500;
    QVector <double> x(sizeOfVector);
    double step = -10;
    int indexOfVector = 0;
    while (step<20) {
        x[indexOfVector]=step;
        indexOfVector++;
        step += 0.02;
    }
    return x;
}

QVector<double> MainWindow::countY()
{
    QVector <double> x = countX();
    int sizeOfVector = x.size();
    QVector<double> y(sizeOfVector);
    for(int i=0; i<sizeOfVector; i++)
    {
        y[i] = x[i] * x[i] / sin(x[i]/4 * M_PI) +
               exp(log(abs (x[i]) * abs(sin(M_PI * x[i] / 2 + 1 )))) ;
    }
    return y;
}
