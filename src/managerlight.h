#ifndef MANAGERLIGHT_H
#define MANAGERLIGHT_H

#include <QtGui>
#include "glwidget.h"

namespace Ui {
    class ManagerLight;
}

class ManagerLight : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(ManagerLight)
public:
    explicit ManagerLight(QWidget *parent = 0);
    virtual ~ManagerLight();
    GLWidget *gl;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ManagerLight *m_ui;

private slots:
    void on_matEsp_clicked();
    void on_matDiff_clicked();
    void on_shininess_valueChanged(int );
    void on_checkBox_clicked();
    void on_posAmbZ6_valueChanged(int value);
    void on_posAmbY6_valueChanged(int value);
    void on_posAmbX6_valueChanged(int value);
    void on_chColorEsp2_clicked();
    void on_posAmbZ5_valueChanged(int value);
    void on_posAmbY5_valueChanged(int value);
    void on_posAmbX5_valueChanged(int value);
    void on_chColorEsp1_clicked();
    void on_posAmbZ4_valueChanged(int value);
    void on_posAmbY4_valueChanged(int value);
    void on_posAmbX4_valueChanged(int value);
    void on_chColorDif2_clicked();
    void on_posAmbZ3_valueChanged(int value);
    void on_posAmbY3_valueChanged(int value);
    void on_posAmbX3_valueChanged(int value);
    void on_chColorDif1_clicked();
    void on_chColorAmb1_clicked();
    void on_activeEspecular2_clicked();
    void on_activeEspecular1_clicked();
    void on_activeDifusa2_clicked();
    void on_activeDifusa1_clicked();
    void on_activeAmbienta1_clicked();
    void on_Phong_released();
    void on_Gouraud_released();
    void on_Flat_released();
};

#endif // MANAGERLIGHT_H
