#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "glextensions.h"
#include <QtGui>
#include <QtOpenGL>
#include "glshaders.h"
#include "lightConfig.h"
#include <algorithm>
#ifdef __unix__
    #include <GL/glext.h>
#endif
#include <GL/glu.h>
#include "Math/Vector3Df.h"
#include "Math/Matrix4x4f.h"

using namespace std;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    GLuint primitiveList;
    QVector<CVector3Df> vertex;
    QVector<CVector3Df> normals;
    QVector<CVector3Df> normalsCCW;
    QVector<CVector3Df> normals2;
    QVector<CVector3Df> normals2CCW;
    QVector< QVector<int> > triangles;
    CMatrix4x4f m_rotMatrix;
    CMatrix4x4f m_rotInvMatrix;
    float scale,scaleX,scaleY,scaleZ,transX,transY,transZ,transXC,transYC,transZC;
    bool rot;
    bool trans;
    bool fog;
    bool mallado;
    bool vertices;
    bool relleno;
    bool zbuffer;
    bool bounding;
    bool normales;
    bool paralela;
    bool back;
    bool texturizado;
    bool pointL;
    bool clockwise;
    int typeMapping;
    int texInterpol;
    int typeClamp;
    GLuint textura;
    GLProgram *glsl;
    GLVertexShader *vs;
    GLFragmentShader *fs;

    float v1,v2;
    int modelLight;
    QColor cmallado;
    QColor cvertices;
    QColor crelleno;
    QColor cfog;
    QColor cbounding;
    QColor cnormales;
    CVector3Df centro;
    CVector3Df ma;
    CVector3Df me;

    lightConfig luz[5];
    lightConfig material[2];
    int shininess;

    //double maxi;
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void changeList();
    void resizeGL(int width, int height);
    void swapBuff(bool e);
    void changeTexture(QImage &img);

    bool doubleBuff;

    void setXTranslation(int distance);
    void setYTranslation(int distance);
    void setZTranslation(int distance);

protected:
    void initializeGL();
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void normalizeAngle(int *angle);
    double normalizeInt(int angle);
    QPoint lastPos;
};

#endif

