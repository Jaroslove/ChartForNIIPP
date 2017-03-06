#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void makePlot();
    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> countX();
    QVector<double> countY();
};

#endif // MAINWINDOW_H
