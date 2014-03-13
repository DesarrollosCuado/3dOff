#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "glextensions.h"
#include <QtGui>
#include <QtOpenGL>
#include "vector.h"
#include "glshaders.h"
#include "punto3d.h"
#include <algorithm>
#include <GL/glext.h>
#include <GL/glu.h>
#include "Math/Vector3Df.h"
#include "Math/Matrix4x4f.h"
#include "lightConfig.h"

using namespace std;

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
        ~GLWidget();

    GLuint primitiveList;
    QVector<punto3d> vertex;
    QVector<punto3d> normals;
    QVector<punto3d> normalsCCW;
    QVector<punto3d> normals2;
    QVector<punto3d> normals2CCW;
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
	punto3d centro;
	punto3d ma;
	punto3d me;

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
//	void keyPressEvent (QKeyEvent * event );

private:
	void normalizeAngle(int *angle);
	double normalizeInt(int angle);
	QPoint lastPos;
};

#endif

