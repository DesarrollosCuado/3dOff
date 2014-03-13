#pragma once

#include "headers.h"
#include "Volumen.h"
#include "Shader.h"
#include "TransferFunction.h"

#include <QtGui>
#include <QGLWidget>
class Windows :
	public QGLWidget
{
public:
	Windows(QWidget *parent);						//Window Handler
	~Windows();
	int histograma[256];
	int maximoValorHistograma;
	GLuint texid;
	TransferFunction *tfUI;
	GLuint loadTexture2D(char * imgName);
	GLuint loadTexture3D(char * imgName,bool RAW=false,int widthImagen=0,int heightImagen=0,int depthImagen=0);
	void calcularHistograma();
	bool rotate[3],scale[3];
	
protected:
	int wi,he;
	int bufferWi,bufferHe;
	int mX,mY;
    int sec;
	int fps;
	bool clickLeft,clickRight;
	float scaleX,scaleY,scaleZ,rotateX,rotateY,rotateZ;
	double ratio;
	vector<Shader> shaders;
	Volumen v;
    QTimer *m_timer;
	QTime m_time;	
	QString debugDisplay;
	GLuint buffer0,buffer1,depth_rb,fb,histo;
	inline void Cube(float bug);
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent (QKeyEvent * event );
	void keyReleaseEvent(QKeyEvent * event );
};
