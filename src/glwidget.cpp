#include "glwidget.h"
#define PI 3.14159265f

GLWidget::GLWidget(QWidget *parent)
 : QGLWidget(parent)
{

    m_rotMatrix.SetIdentity();
    m_rotInvMatrix.SetIdentity();
    modelLight=0;
    clockwise=true;
    textura=0;
    cbounding.setRgb(255,255,255);
    cvertices.setRgb(255,255,255);
    cmallado.setRgb(255,0,0);
    cnormales.setRgb(0,255,0);
    crelleno.setRgb(150,150,150);
    luz[0].color[0]=luz[0].color[1]=luz[0].color[2]=0.25f;
    luz[0].color[3]=0.0f;
    material[0].color[0]=material[0].color[1]=material[0].color[2]=0.25f;
    material[1].color[1]=material[1].color[1]=material[0].color[2]=0.0f;
    material[0].color[3]=material[1].color[3]=1.0f;
    relleno=false;
    mallado=true;
    vertices=false;
    zbuffer=false;
    bounding=false;
    texturizado=false;
    paralela=false;
    back=true;
    fog=false;
    rot=true;
    trans=false;
    normales=false;
    doubleBuff=true;
    scale=scaleX=scaleY=scaleZ=1.0f;
    shininess=30;
    transX=transY=transZ=transXC=transYC=transZC=0.0f;
    pointL=false;
    //memset(lightActive,false,sizeof(lightActive));
    changeList();

}

GLWidget::~GLWidget()
{
    glDeleteLists(primitiveList,5);
    makeCurrent();
}

void GLWidget::changeTexture(QImage &img){
    textura= bindTexture(img, GL_TEXTURE_2D);
}

void GLWidget::swapBuff(bool e)
{
    doubleBuff=e;
    QGLFormat fmt;
    fmt.setDoubleBuffer(e);
    setFormat(fmt);
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::setXTranslation(int angle)
{
    double t=normalizeInt(angle);
    if(t!=0.0){
        transX+=normalizeInt(angle)/300.0f;
        updateGL();
    }
}

void GLWidget::setYTranslation(int angle)
{
    double t=normalizeInt(angle);
    if(t!=0.0){
        transY-=normalizeInt(angle)/300.0f;
        updateGL();
    }
}

void GLWidget::setZTranslation(int angle)
{
    double t=normalizeInt(angle);
    if(t!=0.0){
        transZ-=normalizeInt(angle)/300.0f;
        updateGL();
    }
}

void GLWidget::initializeGL()
{
        glEnable(GL_DEPTH_TEST);
        vs = new GLVertexShader(":/GLSL/shaders/phong.vsh");
        fs = new GLFragmentShader(":/GLSL/shaders/phong.fsh");
        glsl=new GLProgram;
        glsl->attach(*vs);
        if(glsl->failed()){
            qCritical("Error Compiled Vertex GLSL");
        }
        glsl->attach(*fs);
        if(glsl->failed()){
            qCritical("Error Compiled Fragment GLSL");
        }
        changeList();
}

void GLWidget::changeList()
{
    glDeleteLists(primitiveList,6);
    primitiveList  = glGenLists(6);

    glNewList(primitiveList,GL_COMPILE);   // Normals
        glBegin(GL_LINES);
            for(int i=0;i<normals.size();i++)
            {
                if(clockwise)
                    glNormal3fv(normals[i].v);
                else
                    glNormal3fv(normalsCCW[i].v);
                CVector3Df r=(vertex[triangles[i][0]]+vertex[triangles[i][1]]+vertex[triangles[i][2]])*0.333333333f;
                CVector3Df in=normals[i]*0.02f+r;
                glVertex3fv(in.v);
                glVertex3fv(r.v);
            }
        glEnd();
    glEndList();


    glNewList(primitiveList+1,GL_COMPILE); // Vertex

        glNormal3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);
            for(int i=0;i<vertex.size();i++)
            {
                glVertex3fv(vertex[i].v);
            }
        glEnd();
    glEndList();


    glNewList(primitiveList+2,GL_COMPILE); // Lines
        glBegin(GL_LINES);
            for(int i=0;i<triangles.size();i++)
            {
                if(clockwise)
                    glNormal3fv(normals[i].v);
                else
                    glNormal3fv(normalsCCW[i].v);

                glVertex3fv(vertex[triangles[i][0]].v);
                glVertex3fv(vertex[triangles[i][1]].v);
                glVertex3fv(vertex[triangles[i][2]].v);
                glVertex3fv(vertex[triangles[i][0]].v);
                glVertex3fv(vertex[triangles[i][1]].v);
                glVertex3fv(vertex[triangles[i][2]].v);
            }
        glEnd();
    glEndList();


    glNewList(primitiveList+3,GL_COMPILE); // Trianges/Solid Planar
        glBegin(GL_TRIANGLES);
            for(int i=0;i<triangles.size();i++)
            {
                for(int j=0;j<3;++j) {
                    if(clockwise)
                        glNormal3fv(normals2[triangles[i][j]].v);
                    else
                        glNormal3fv(normals2CCW[triangles[i][j]].v);

                    glTexCoord2fv((vertex[triangles[i][j]]+0.5f).v);
                    glVertex3fv(vertex[triangles[i][j]].v);
                }
            }
        glEnd();
    glEndList();


    glNewList(primitiveList+4,GL_COMPILE); // Bounding Box
        glNormal3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
            //Cara 1
            glVertex3f(me.v[0],ma.v[1],me.v[2]);
            glVertex3f(ma.v[0],ma.v[1],me.v[2]);
            glVertex3f(me.v[0],me.v[1],me.v[2]);
            glVertex3f(ma.v[0],me.v[1],me.v[2]);
            glVertex3f(ma.v[0],ma.v[1],me.v[2]);
            glVertex3f(ma.v[0],me.v[1],me.v[2]);
            glVertex3f(me.v[0],ma.v[1],me.v[2]);
            glVertex3f(me.v[0],me.v[1],me.v[2]);
            //Cara 2
            glVertex3f(me.v[0],ma.v[1],ma.v[2]);
            glVertex3f(ma.v[0],ma.v[1],ma.v[2]);
            glVertex3f(me.v[0],me.v[1],ma.v[2]);
            glVertex3f(ma.v[0],me.v[1],ma.v[2]);
            glVertex3f(ma.v[0],ma.v[1],ma.v[2]);
            glVertex3f(ma.v[0],me.v[1],ma.v[2]);
            glVertex3f(me.v[0],ma.v[1],ma.v[2]);
            glVertex3f(me.v[0],me.v[1],ma.v[2]);
            //Casos faltantes
            glVertex3f(me.v[0],me.v[1],ma.v[2]);
            glVertex3f(me.v[0],me.v[1],me.v[2]);
            glVertex3f(ma.v[0],ma.v[1],ma.v[2]);
            glVertex3f(ma.v[0],ma.v[1],me.v[2]);
            glVertex3f(me.v[0],ma.v[1],ma.v[2]);
            glVertex3f(me.v[0],ma.v[1],me.v[2]);
            glVertex3f(ma.v[0],me.v[1],ma.v[2]);
            glVertex3f(ma.v[0],me.v[1],me.v[2]);
        glEnd();
    glEndList();

    glNewList(primitiveList+5,GL_COMPILE); // Trianges/Solid Cilindrico Coord Texture
        glBegin(GL_TRIANGLES);
            float S,T,x,y;
            for(int i=0;i<triangles.size();i++)
            {
                for(int j=0;j<3;++j) {
                    if(clockwise)
                        glNormal3fv(normals2[triangles[i][j]].v);
                    else
                        glNormal3fv(normals2CCW[triangles[i][j]].v);

                    x=vertex[triangles[i][j]].v[0]+0.5f;
                    y=vertex[triangles[i][j]].v[1]+0.5f;
                    T=vertex[triangles[i][j]].v[2]+0.5f;
                    S=atan2(y,x)/(2*PI);

                    glTexCoord2f(S,T);
                    glVertex3fv(vertex[triangles[i][j]].v);
                }
            }
        glEnd();
    glEndList();
}
void GLWidget::paintGL()
{
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_COLOR_MATERIAL);
    if(zbuffer){
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
    }else{
        glDisable(GL_DEPTH_TEST);
    }

    if(modelLight==0)
        glShadeModel(GL_FLAT);

    if(modelLight==1)
        glShadeModel(GL_SMOOTH);

    if(modelLight==2)
        glsl->bind();
    else
        glsl->unbind();

    if(!clockwise)
        glFrontFace(GL_CW);
    else
        glFrontFace(GL_CCW);

    if(luz[0].active || luz[1].active || luz[2].active || luz[3].active || luz[4].active){
        glEnable(GL_LIGHTING);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    }else{
        glDisable(GL_LIGHTING);
    }

    glPointSize(4.0f);
    float blanco[]={0.8f,0.8f,0.8f,1.0f};
    float zero[]={0.0f,0.0f,0.0f,0.0f};
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , blanco);

    if(luz[0].active){
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[0]"),1);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, luz[0].position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, luz[0].color);
        glLightfv(GL_LIGHT0, GL_SPECULAR, zero);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, zero);
    }else{
        if(modelLight==2) glsl->setInt(QString("LuzAct[0]"),0);
        glDisable(GL_LIGHT0);
    }

    glColor4fv(blanco);

    if(luz[1].active){
        if(modelLight==2) glsl->setInt(QString("LuzAct[1]"),1);
        if(pointL){
            glBegin(GL_POINTS);
                glNormal3f(0.0f, 0.0f, 0.0f);
                glVertex3fv(luz[1].position);
            glEnd();
        }
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, luz[1].position);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, luz[1].color);
        glLightfv(GL_LIGHT1, GL_AMBIENT, zero);
        glLightfv(GL_LIGHT1, GL_SPECULAR, zero);
    }else{
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[1]"),0);
        glDisable(GL_LIGHT1);
    }

    if(luz[2].active){
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[2]"),1);

        if(pointL){
            glBegin(GL_POINTS);
                glNormal3f(0.0f, 0.0f, 0.0f);
                glVertex3fv(luz[2].position);
            glEnd();
        }

        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_POSITION, luz[2].position);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, luz[2].color);
        glLightfv(GL_LIGHT2, GL_AMBIENT, zero);
        glLightfv(GL_LIGHT2, GL_SPECULAR, zero);
    }else{
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[2]"),0);
        glDisable(GL_LIGHT2);
    }

    if(luz[3].active) {
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[3]"),1);

        if(pointL){
            glBegin(GL_POINTS);
                glNormal3f(0.0f, 0.0f, 0.0f);
                glVertex3fv(luz[3].position);
            glEnd();
        }

        glLightfv(GL_LIGHT3, GL_POSITION, luz[3].position);
        glLightfv(GL_LIGHT3, GL_SPECULAR, luz[3].color);
        glLightfv(GL_LIGHT3, GL_AMBIENT, zero);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, zero);
        glEnable(GL_LIGHT3);
    }else{
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[3]"),0);
        glDisable(GL_LIGHT3);
    }

    if(luz[4].active) {
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[4]"),1);

        if(pointL){
            glBegin(GL_POINTS);
                glNormal3f(0.0f, 0.0f, 0.0f);
                glVertex3fv(luz[4].position);
            glEnd();
        }
        glEnable(GL_LIGHT4);
        glLightfv(GL_LIGHT4, GL_POSITION, luz[4].position);
        glLightfv(GL_LIGHT4, GL_SPECULAR, luz[4].color);
        glLightfv(GL_LIGHT4, GL_AMBIENT, zero);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, zero);
    }else{
        if(modelLight==2)
            glsl->setInt(QString("LuzAct[4]"),0);
        glDisable(GL_LIGHT4);
    }

    if(fog){
        if(modelLight==2)
            glsl->setInt(QString("fogA"),1);
        glEnable(GL_DEPTH_TEST);
        GLfloat fogColor[4];
        fogColor[0]=cfog.redF();
        fogColor[1]=cfog.greenF();
        fogColor[2]=cfog.blueF();
        fogColor[3]=1.0f;
        glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
        glFogf (GL_FOG_DENSITY, 0.75f); //set the density to the value above
        glFogi (GL_FOG_MODE, GL_LINEAR); //set the fog mode to GL_EXP2
        glFogf (GL_FOG_START, 1.0f);
        glFogf (GL_FOG_END, 4.0f);
        glHint (GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on
        glEnable (GL_FOG); //enable the fog
    }else{
        if(modelLight==2)
            glsl->setInt(QString("fogA"),0);
        glDisable (GL_FOG);
    }

    glPolygonOffset(1.0,0.0);
    glPointSize(2.0f);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    if(back){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }else{
        glDisable(GL_CULL_FACE);
    }

    glTranslatef(transX,transY,transZ);//traslada
    glTranslatef(0.0f,0.0f,-2.0f);
    glMultMatrixf(m_rotInvMatrix.m_vector);

    glScalef(scaleX,scaleY,scaleZ);

    if(normales){
        glColor3f(cnormales.redF(),cnormales.greenF(),cnormales.blueF());
        glCallList(primitiveList);
    }

    if(vertices){
        glColor3f(cvertices.redF(),cvertices.greenF(),cvertices.blueF());
        glCallList(primitiveList+1);
    }

    if(mallado){
        glColor3f(cmallado.redF(),cmallado.greenF(),cmallado.blueF());
        glCallList(primitiveList+2);
    }

    if(relleno){
        if(texturizado){
            glsl->setInt("textura",1);
            if(texInterpol){
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }else{
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
            if(typeClamp){
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            }else{
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            }
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textura);
        }else {
            glDisable(GL_TEXTURE_2D);
            glsl->setInt("textura",0);
        }

        glColor3f(crelleno.redF(),crelleno.greenF(),crelleno.blueF());
        if(typeMapping){
            glCallList(primitiveList+3);
        }else{
            glCallList(primitiveList+5);
        }
    }

    if(bounding){
        glColor3f(cbounding.redF(),cbounding.greenF(),cbounding.blueF());
        glCallList(primitiveList+4);
    }
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(paralela)
        glOrtho(-0.8, +0.8, -0.8, 0.8, 0.01f, 10.0f);
    else
        gluPerspective(45.0f, 1.33, 0.01f, 10.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    static const float PIm = (3.1415926535897932/2.0);
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        if(rot){
            CVector3Df mouseVec(-dx, dy, 0);
            CVector3Df perpendMouseVec;
            perpendMouseVec[0] =  cos(PIm) * mouseVec[0] + sin(PIm) * mouseVec[1];
            perpendMouseVec[1] = -sin(PIm) * mouseVec[0] + cos(PIm) * mouseVec[1];
            perpendMouseVec[2] = 0.0f;
            perpendMouseVec.Normalize();

            CMatrix4x4f rotmat;

            rotmat.SetIdentity();
            rotmat.Rotate(-mouseVec.Modulus()*0.01f, perpendMouseVec[0], perpendMouseVec[1], 0);
            m_rotInvMatrix.PostMult(rotmat);

            rotmat.SetIdentity();
            rotmat.Rotate(+mouseVec.Modulus()*0.01f, perpendMouseVec[0], perpendMouseVec[1], 0);
            m_rotMatrix.PreMult(rotmat);
            updateGL();
        }else if(trans){
            setXTranslation(dx);
            setYTranslation(dy);
        }
    }else if (event->buttons() & Qt::RightButton) {
        if(trans){
            setXTranslation(dx);
            setZTranslation(dy);
        }
    }
    lastPos = event->pos();
}

void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}
double GLWidget::normalizeInt(int angle)
{
    while (angle < -100)
        angle += 100;
    while (angle > 100)
        angle -= 100;
    return angle;
}
