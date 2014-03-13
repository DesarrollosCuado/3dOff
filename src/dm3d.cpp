#include "dm3d.h"


DM3d::DM3d(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
    ml=new ManagerLight(this);
    ml->setWindowFlags(Qt::Tool);
    //ml->setWindowOpacity(0.75);
    ml->gl=ui.widget;
    showMaximized();
    ml->setGeometry(width()-410,height()-260,ml->width(),ml->height());
    ml->show();
}

DM3d::~DM3d()
{

}


void DM3d::on_actionAbrir_OFF_triggered()
{
	QString s = QFileDialog::getOpenFileName(this,"Modelo 3D OFF",".off","3D (*.off)");

	if(s!=QString::null){
		QFile file(s);
		ui.widget->scale=ui.widget->scaleX=ui.widget->scaleY=ui.widget->scaleZ=1.0f;
		ui.widget->transX=ui.widget->transY=ui.widget->transZ=0.0f;
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
			QMessageBox::information(this,"Error...","No se puede abrir el archivo");
			return;
		}
		QString line = file.readLine();
		line=file.readLine();
		QStringList l=line.split(" ");
        ui.widget->vertex=QVector<CVector3Df>(l.at(0).toInt());
		int tri=l.at(1).toInt();
        CVector3Df b1(-10e30f,-10e30f,-10e30f);
        CVector3Df b2(10e30f,10e30f,10e30f);
        float maximo,maX=float(-0x3f3f3f3f),miX=float(0x3f3f3f3f);
        float maY=maX,miY=miX,maZ=maX,miZ=miX;
		int tVert=ui.widget->vertex.size();
		for(int i=0;i<tVert;++i){
			line=file.readLine();
			l=line.split(" ");
            float a=l.at(0).toDouble();
            float b=l.at(1).toDouble();
            float c=l.at(2).toDouble();
            maX=max(a,maX);
            maY=max(b,maY);
            maZ=max(c,maZ);
            miX=min(a,miX);
            miY=min(b,miY);
            miZ=min(c,miZ);
            ui.widget->vertex[i]=CVector3Df(a,b,c);
            b1.v[0]=max(b1.v[0],a);
            b1.v[1]=max(b1.v[1],b);
            b1.v[2]=max(b1.v[2],c);
            b2.v[0]=min(b2.v[0],a);
            b2.v[1]=min(b2.v[1],b);
            b2.v[2]=min(b2.v[2],c);
		}

        maximo=max(maX-miX,max(maY-miY,maZ-miZ));
        b1/=maximo;
        b2/=maximo;
        ui.widget->centro=CVector3Df((b1.v[0]+b2.v[0])/2.0f,(b1.v[1]+b2.v[1])/2.0f,(b1.v[2]+b2.v[2])/2.0f);
        b1-=ui.widget->centro;
        b2-=ui.widget->centro;

        for(int i=0;i<tVert;++i){
            ui.widget->vertex[i]/=maximo;
            ui.widget->vertex[i]-=ui.widget->centro;
        }

        ui.widget->centro=CVector3Df();
        ui.widget->ma=b1;
        ui.widget->me=b2;

        ui.widget->triangles.clear();
        for(int i=0;i<tri;++i){
            line=file.readLine();
            l=line.split(" ");
            QVector<int> t(0);
            for(int j=1;j<l.size();++j){
                QString temp=l.at(j);
                if(temp!="\n" && temp!="\t" && temp!="\t\n" && temp!="\0")
                    t.push_back(temp.toInt());
            }
            if(t.size()==3) {
                ui.widget->triangles.push_back(t);
            }else{
                for (int j = 0; j < t.size()-2; ++j) {
                    QVector<int> arr3;
                    arr3.push_back(t[0]);
                    arr3.push_back(t[j+1]);
                    arr3.push_back(t[j+2]);
                    ui.widget->triangles.push_back(arr3);
                }
            }
        }
        ui.widget->normals.clear();
        ui.widget->normals2.clear();
        ui.widget->normals=QVector<CVector3Df>(ui.widget->triangles.size());
        ui.widget->normals2=QVector<CVector3Df>(ui.widget->vertex.size(),CVector3Df(0.0,0.0,0.0));
        ui.widget->normalsCCW=QVector<CVector3Df>(ui.widget->triangles.size());
        ui.widget->normals2CCW=QVector<CVector3Df>(ui.widget->vertex.size(),CVector3Df(0.0,0.0,0.0));
        int tamV=ui.widget->vertex.size();
        int tamT=ui.widget->triangles.size();
        QVector<int> cont(ui.widget->vertex.size(),0);
        for(int i=0;i<tamT;++i){
            ui.widget->normals[i]=(ui.widget->vertex[ui.widget->triangles[i][1]]-ui.widget->vertex[ui.widget->triangles[i][0]])*(ui.widget->vertex[ui.widget->triangles[i][2]]-ui.widget->vertex[ui.widget->triangles[i][0]]);
            ui.widget->normals[i].Normalize();

            ui.widget->normalsCCW[i]=(ui.widget->vertex[ui.widget->triangles[i][2]]-ui.widget->vertex[ui.widget->triangles[i][0]])*(ui.widget->vertex[ui.widget->triangles[i][1]]-ui.widget->vertex[ui.widget->triangles[i][0]]);
            ui.widget->normalsCCW[i].Normalize();

            ui.widget->normals2[ui.widget->triangles[i][0]]+=ui.widget->normals[i];
            ui.widget->normals2[ui.widget->triangles[i][1]]+=ui.widget->normals[i];
            ui.widget->normals2[ui.widget->triangles[i][2]]+=ui.widget->normals[i];

            ui.widget->normals2CCW[ui.widget->triangles[i][0]]+=ui.widget->normalsCCW[i];
            ui.widget->normals2CCW[ui.widget->triangles[i][1]]+=ui.widget->normalsCCW[i];
            ui.widget->normals2CCW[ui.widget->triangles[i][2]]+=ui.widget->normalsCCW[i];
            ++cont[ui.widget->triangles[i][0]];
            ++cont[ui.widget->triangles[i][1]];
            ++cont[ui.widget->triangles[i][2]];
        }
        for(int i=0;i<tamV;++i){
            ui.widget->normals2[i]/=float(cont[i]);
            ui.widget->normals2[i].Normalize();
            ui.widget->normals2CCW[i]/=float(cont[i]);
            ui.widget->normals2CCW[i].Normalize();
        }
        /*
        float sumx = 0.0f;
        float sumy = 0.0f;
        float sumz = 0.0f;
        int shared=0;
        int i, j;
        for (i=0; i<tamV; ++i)
        {
        for (j=0; j<tamT; ++j)
        {
        if (ui.widget->triangles[j][0]==i || ui.widget->triangles[j][1]==i || ui.widget->triangles[j][2]==i)
        {
        sumx += ui.widget->normals[j].x;
        sumy += ui.widget->normals[j].y;
        sumz += ui.widget->normals[j].z;
        shared ++;
        }
        }

        punto3d n2(sumx,sumy,sumz);
        n2=n2/float(shared);
        n2.normalize();
        ui.widget->normals2.push_back(n2);
        sumx=0.0;
        sumy=0.0;
        sumz=0.0;
        shared=0;
        }*/
        ui.widget->changeList();
        ui.widget->updateGL();
	}else{
		QMessageBox::information(this,"Error...","No se puede abrir el archivo");
	}
}
void DM3d::resizeEvent(QResizeEvent * e){
	ui.widget->setGeometry(0,0,geometry().width(),geometry().height());
}
void DM3d::keyPressEvent(QKeyEvent * e ){

        if(e->key()==Qt::Key_N)
		ui.widget->scale-=0.05f;
	if(e->key()==Qt::Key_M) 
		ui.widget->scale+=0.05f;
	if(e->key()==Qt::Key_Z) 
		ui.widget->scaleX-=0.05f;
	if(e->key()==Qt::Key_A) 
		ui.widget->scaleX+=0.05f;
	if(e->key()==Qt::Key_X) 
		ui.widget->scaleY-=0.05f;
	if(e->key()==Qt::Key_S) 
		ui.widget->scaleY+=0.05f;
	if(e->key()==Qt::Key_C) 
		ui.widget->scaleZ-=0.05f;
	if(e->key()==Qt::Key_D) 
		ui.widget->scaleZ+=0.05f;
	ui.widget->updateGL();
}

void DM3d::on_actionMallado_triggered()
{
	ui.widget->mallado=!ui.widget->mallado;
	ui.widget->updateGL();
}

void DM3d::on_actionVertices_triggered()
{
	ui.widget->vertices=!ui.widget->vertices;
	ui.widget->updateGL();
}

void DM3d::on_actionRelleno_triggered()
{
	ui.widget->relleno=!ui.widget->relleno;
	ui.widget->updateGL();
}

void DM3d::on_actionRelleno_2_triggered()
{
	ui.widget->crelleno.setRgb(QColorDialog::getRgba(ui.widget->crelleno.rgb()));
	ui.widget->updateGL();
}

void DM3d::on_actionMallado_2_triggered()
{
	ui.widget->cmallado.setRgb(QColorDialog::getRgba(ui.widget->cmallado.rgb()));
	ui.widget->updateGL();
}

void DM3d::on_actionVertices_2_triggered()
{
	ui.widget->cvertices.setRgb(QColorDialog::getRgba(ui.widget->cvertices.rgb()));
	ui.widget->updateGL();
}
void DM3d::on_actionFog_triggered()
{
	ui.widget->cfog.setRgb(QColorDialog::getRgba(ui.widget->cfog.rgb()));
	ui.widget->updateGL();
}

void DM3d::on_actionActivar_Fog_triggered()
{
	ui.widget->fog=!ui.widget->fog;
	ui.widget->updateGL();;
}



void DM3d::on_actionZ_Buffer_triggered()
{
	ui.widget->zbuffer=!ui.widget->zbuffer;
	ui.widget->updateGL();

}



void DM3d::on_actionRotar_triggered()
{
	ui.widget->rot=!ui.widget->rot;
	if(ui.widget->rot){
		ui.widget->trans=false;
		ui.actionTransladar->setChecked(false);
		ui.actionRotar->setChecked(true);
	}else{
		ui.widget->trans=true;
		ui.actionTransladar->setChecked(true);
		ui.actionRotar->setChecked(false);
	}
}

void DM3d::on_actionTransladar_triggered()
{
	ui.widget->trans=!ui.widget->trans;
	if(ui.widget->trans){
		ui.widget->rot=false;
		ui.actionTransladar->setChecked(true);
		ui.actionRotar->setChecked(false);
	}else{
		ui.widget->rot=true;
		ui.actionTransladar->setChecked(false);
		ui.actionRotar->setChecked(true);
	}
}

void DM3d::on_actionBoundingBox_triggered()
{
	ui.widget->bounding=!ui.widget->bounding;
	ui.widget->updateGL();
}

void DM3d::on_actionBounding_Box_triggered()
{
	ui.widget->cbounding.setRgb(QColorDialog::getRgba(ui.widget->cbounding.rgb()));
	ui.widget->updateGL();
}


void DM3d::on_actionNormales_triggered()
{
	ui.widget->normales=!ui.widget->normales;
	ui.widget->updateGL();
}

void DM3d::on_actionNormales_2_triggered()
{
	ui.widget->cnormales.setRgb(QColorDialog::getRgba(ui.widget->cnormales.rgb()));
	ui.widget->updateGL();
}

void DM3d::on_actionBackface_Culling_triggered()
{

	ui.widget->back=!ui.widget->back;
	ui.widget->updateGL();
}

void DM3d::on_actionOrtogonal_triggered()
{
	if(ui.widget->paralela){
		ui.widget->paralela=false;
		ui.actionOrtogonal->setChecked(false);
		ui.actionPerspectiva->setChecked(true);
	}else{
		ui.widget->paralela=true;
		ui.actionOrtogonal->setChecked(true);
		ui.actionPerspectiva->setChecked(false);
	}
	ui.widget->resizeGL(ui.widget->width(),ui.widget->height());
	ui.widget->updateGL();
}

void DM3d::on_actionPerspectiva_triggered()
{

	if(ui.widget->paralela){
		ui.widget->paralela=false;
		ui.actionOrtogonal->setChecked(false);
		ui.actionPerspectiva->setChecked(true);
	}else{
		ui.widget->paralela=true;
		ui.actionOrtogonal->setChecked(true);
		ui.actionPerspectiva->setChecked(false);
	}
	ui.widget->resizeGL(ui.widget->width(),ui.widget->height());
	ui.widget->updateGL();
}

void DM3d::on_actionInformacion_del_Objeto_triggered()
{
	QString s;
	char tam[20];
	sprintf(tam,"%d",ui.widget->vertex.size());
	QString v(tam);
	sprintf(tam,"%d",ui.widget->triangles.size());
	QString t(tam);
	sprintf(tam,"%d",ui.widget->triangles.size()*3);
	QString l(tam);


	s="Numero de Vertices: "+v+"\nNumero de Poligonos: "+t+"\nNumero de Lados: "+l;
	QMessageBox::information(this,"Informacion del objeto 3d",s);
}

void DM3d::on_actionFlikering_triggered()
{
	ui.widget->swapBuff(!ui.widget->doubleBuff);
	ui.widget->updateGL();
	
}


void DM3d::on_actionNormal_clockwise_triggered()
{
    if(ui.widget->clockwise){
     ui.actionNormal_clockwise->setChecked(false);
     ui.actionNormal_counter_clockwise->setChecked(true);
   }else{
     ui.actionNormal_clockwise->setChecked(true);
     ui.actionNormal_counter_clockwise->setChecked(false);
   }

   ui.widget->clockwise = !ui.widget->clockwise;
    ui.widget->changeList();
    ui.widget->updateGL();
    qCritical("sii");
}

void DM3d::on_actionNormal_counter_clockwise_triggered()
{

    if(ui.widget->clockwise){
     ui.actionNormal_clockwise->setChecked(false);
     ui.actionNormal_counter_clockwise->setChecked(true);
   }else{
     ui.actionNormal_clockwise->setChecked(true);
     ui.actionNormal_counter_clockwise->setChecked(false);
   }

   ui.widget->clockwise = !ui.widget->clockwise;
    ui.widget->changeList();
    ui.widget->updateGL();
    //qCritical("siii");
}

void DM3d::on_actionCargar_Textura_triggered()
{
    QString s = QFileDialog::getOpenFileName(this,"Image","","Images (*.png *.bmp *.jpg *.gif)");

        if(s!=QString::null){
            QImage img;
            if(!img.load(s)){
                QMessageBox::information(this,"Error...","Formato de imagen invalido");
            }else{
                ui.widget->changeTexture(img);
            }
        }
}

void DM3d::on_actionActivar_Textura_triggered()
{
    if(ui.widget->textura>0){
        ui.widget->texturizado=!ui.widget->texturizado;
    }else
                QMessageBox::information(this,"Error...","No se cargo ninguna textura...");
        ui.actionActivar_Textura->setChecked(ui.widget->texturizado);
}

void DM3d::on_actionCilindrico_triggered()
{
    ui.widget->typeMapping=0;
    ui.actionCilindrico->setChecked(true);
    ui.actionEsferico->setChecked(false);
}

void DM3d::on_actionEsferico_triggered()
{
    ui.widget->typeMapping=1;
    ui.actionCilindrico->setChecked(false);
    ui.actionEsferico->setChecked(true);

}

void DM3d::on_actionNeares_triggered()
{
    ui.widget->texInterpol=0;
    ui.actionNeares->setChecked(true);
    ui.actionLinear->setChecked(false);
}


void DM3d::on_actionLinear_triggered()
{

    ui.widget->texInterpol=1;
    ui.actionNeares->setChecked(false);
    ui.actionLinear->setChecked(true);
}

void DM3d::on_actionRepeat_triggered()
{

    ui.widget->typeClamp=0;
    ui.actionRepeat->setChecked(true);
    ui.actionClamp->setChecked(false);
}

void DM3d::on_actionClamp_triggered()
{
    ui.widget->typeClamp=1;
    ui.actionRepeat->setChecked(false);
    ui.actionClamp->setChecked(true);
}
