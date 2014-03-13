#ifndef DM3D_H
#define DM3D_H

#include <QtGui>
#include <complex>
#include <math.h>
#include <algorithm>
#include <qmessagebox.h>
#include <qfile.h>
#include <qfiledialog.h>
#include "ui_dm3d.h"
#include "managerlight.h"

using namespace std;

class DM3d : public QMainWindow
{
    Q_OBJECT

public:
    DM3d(QWidget *parent = 0);
    ~DM3d();
    void resizeEvent(QResizeEvent * e);
    void keyPressEvent(QKeyEvent * e);
    ManagerLight *ml;

private:
    Ui::DM3dClass ui;

private slots:
    void on_actionClamp_triggered();
    void on_actionRepeat_triggered();
    void on_actionLinear_triggered();
    void on_actionEsferico_triggered();
    void on_actionNeares_triggered();
    void on_actionCilindrico_triggered();
    void on_actionActivar_Textura_triggered();
    void on_actionCargar_Textura_triggered();
    void on_actionNormal_counter_clockwise_triggered();
    void on_actionNormal_clockwise_triggered();
    void on_actionFlikering_triggered();
    void on_actionInformacion_del_Objeto_triggered();
    void on_actionPerspectiva_triggered();
    void on_actionOrtogonal_triggered();
    void on_actionBackface_Culling_triggered();
    void on_actionNormales_2_triggered();
    void on_actionNormales_triggered();
    void on_actionBounding_Box_triggered();
    void on_actionBoundingBox_triggered();
    void on_actionTransladar_triggered();
    void on_actionRotar_triggered();
    void on_actionZ_Buffer_triggered();
    void on_actionVertices_2_triggered();
    void on_actionActivar_Fog_triggered();
    void on_actionFog_triggered();
    void on_actionMallado_2_triggered();
    void on_actionRelleno_2_triggered();
    void on_actionRelleno_triggered();
    void on_actionVertices_triggered();
    void on_actionMallado_triggered();
    void on_actionAbrir_OFF_triggered();
};

#endif // DM3D_H
