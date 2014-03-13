#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Windows.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	Windows *w;

protected:
    void changeEvent(QEvent *e);
	void resizeEvent(QResizeEvent * e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_actionAbout_triggered();
    void on_actionScale_X_triggered();
    void on_actionScale_Y_triggered();
    void on_actionScale_Z_triggered();
    void on_actionRotate_X_triggered();
    void on_actionRotate_Y_triggered();
    void on_actionRotate_Z_triggered();
    void on_actionTransfer_Function_triggered();
    void on_actionReset_Function_triggered();
    void on_actionExit_triggered();
    void on_actionOpen_RAW_triggered();
    void on_actionOpen_PVM_triggered();
};

#endif // MAINWINDOW_H
