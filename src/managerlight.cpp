#include "managerlight.h"
#include "ui_managerlight.h"

ManagerLight::ManagerLight(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ManagerLight)
{
    m_ui->setupUi(this);

    m_ui->colorAmb1->setAutoFillBackground(true);
    m_ui->colorAmb1->setPalette(QPalette(QColor(64,64,64)));
    m_ui->colorDif1->setAutoFillBackground(true);
    m_ui->colorDif1->setPalette(QPalette(QColor(0,0,0)));
    m_ui->colorDif2->setAutoFillBackground(true);
    m_ui->colorDif2->setPalette(QPalette(QColor(0,0,0)));
    m_ui->colorEsp1->setAutoFillBackground(true);
    m_ui->colorEsp1->setPalette(QPalette(QColor(0,0,0)));
    m_ui->colorEsp2->setAutoFillBackground(true);
    m_ui->colorEsp2->setPalette(QPalette(QColor(0,0,0)));
    m_ui->colorDiff->setAutoFillBackground(true);
    m_ui->colorDiff->setPalette(QPalette(QColor(64,64,64)));
    m_ui->colorEsp->setAutoFillBackground(true);
    m_ui->colorEsp->setPalette(QPalette(QColor(0,0,0)));

}

ManagerLight::~ManagerLight()
{
    delete m_ui;
}

void ManagerLight::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ManagerLight::on_Flat_released()
{
    gl->modelLight=0;
    gl->updateGL();
}

void ManagerLight::on_Gouraud_released()
{
   gl->modelLight=1;
   gl->updateGL();
}

void ManagerLight::on_Phong_released()
{

   gl->modelLight=2;
   gl->updateGL();
}

void ManagerLight::on_activeAmbienta1_clicked()
{
    gl->luz[0].active=!gl->luz[0].active;
   gl->updateGL();
}

void ManagerLight::on_activeDifusa1_clicked()
{
    gl->luz[1].active=!gl->luz[1].active;
   gl->updateGL();

}

void ManagerLight::on_activeDifusa2_clicked()
{
    gl->luz[2].active=!gl->luz[2].active;
   gl->updateGL();

}

void ManagerLight::on_activeEspecular1_clicked()
{
    gl->luz[3].active=!gl->luz[3].active;
   gl->updateGL();

}

void ManagerLight::on_activeEspecular2_clicked()
{
    gl->luz[4].active=!gl->luz[4].active;
   gl->updateGL();

}

void ManagerLight::on_chColorAmb1_clicked()
{
    QColor c = QColorDialog::getRgba(QColor(int(gl->luz[0].color[0]*255.0f),int(gl->luz[0].color[1]*255.0f),int(gl->luz[0].color[2]*255.0f)).rgb());
    gl->luz[0].color[0]=c.redF();
    gl->luz[0].color[1]=c.greenF();
    gl->luz[0].color[2]=c.blueF();
    m_ui->colorAmb1->setPalette(QPalette(c));
   gl->updateGL();

}

void ManagerLight::on_chColorDif1_clicked()
{
    QColor c = QColorDialog::getRgba(QColor(int(gl->luz[1].color[0]*255.0f),int(gl->luz[1].color[1]*255.0f),int(gl->luz[1].color[2]*255.0f)).rgb());
    gl->luz[1].color[0]=c.redF();
    gl->luz[1].color[1]=c.greenF();
    gl->luz[1].color[2]=c.blueF();
    m_ui->colorDif1->setPalette(QPalette(c));
   gl->updateGL();

}

void ManagerLight::on_posAmbX3_valueChanged(int value)
{
    gl->luz[1].position[0]=float(value)/42.0f;
    m_ui->ledPosX3->setText(QString::number((double)gl->luz[1].position[0],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbY3_valueChanged(int value)
{
    gl->luz[1].position[1]=float(value)/42.0f;
    m_ui->ledPosY3->setText(QString::number((double)gl->luz[1].position[1],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbZ3_valueChanged(int value)
{
    gl->luz[1].position[2]=float(value)/42.0f;
    m_ui->ledPosZ3->setText(QString::number((double)gl->luz[1].position[2],'f',2));
   gl->updateGL();

}

void ManagerLight::on_chColorDif2_clicked()
{
    QColor c = QColorDialog::getRgba(QColor(int(gl->luz[2].color[0]*255.0f),int(gl->luz[2].color[1]*255.0f),int(gl->luz[2].color[2]*255.0f)).rgb());
    gl->luz[2].color[0]=c.redF();
    gl->luz[2].color[1]=c.greenF();
    gl->luz[2].color[2]=c.blueF();
    m_ui->colorDif2->setPalette(QPalette(c));
   gl->updateGL();

}

void ManagerLight::on_posAmbX4_valueChanged(int value)
{
    gl->luz[2].position[0]=float(value)/42.0f;
    m_ui->ledPosX4->setText(QString::number((double)gl->luz[2].position[0],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbY4_valueChanged(int value)
{
    gl->luz[2].position[1]=float(value)/42.0f;
    m_ui->ledPosY4->setText(QString::number((double)gl->luz[2].position[1],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbZ4_valueChanged(int value)
{
    gl->luz[2].position[2]=float(value)/42.0f;
    m_ui->ledPosZ4->setText(QString::number((double)gl->luz[2].position[2],'f',2));
   gl->updateGL();

}

void ManagerLight::on_chColorEsp1_clicked()
{
    QColor c = QColorDialog::getRgba(QColor(int(gl->luz[3].color[0]*255.0f),int(gl->luz[3].color[1]*255.0f),int(gl->luz[3].color[2]*255.0f)).rgb());
    gl->luz[3].color[0]=c.redF();
    gl->luz[3].color[1]=c.greenF();
    gl->luz[3].color[2]=c.blueF();
    m_ui->colorEsp1->setPalette(QPalette(c));
   gl->updateGL();

}

void ManagerLight::on_posAmbX5_valueChanged(int value)
{
    gl->luz[3].position[0]=float(value)/42.0f;
    m_ui->ledPosX5->setText(QString::number((double)gl->luz[3].position[0],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbY5_valueChanged(int value)
{
    gl->luz[3].position[1]=float(value)/42.0f;
    m_ui->ledPosY5->setText(QString::number((double)gl->luz[3].position[1],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbZ5_valueChanged(int value)
{
    gl->luz[3].position[2]=float(value)/42.0f;
    m_ui->ledPosZ5->setText(QString::number((double)gl->luz[3].position[2],'f',2));
   gl->updateGL();

}

void ManagerLight::on_chColorEsp2_clicked()
{
    QColor c = QColorDialog::getRgba(QColor(int(gl->luz[4].color[0]*255.0f),int(gl->luz[4].color[1]*255.0f),int(gl->luz[4].color[2]*255.0f)).rgb());
    gl->luz[4].color[0]=c.redF();
    gl->luz[4].color[1]=c.greenF();
    gl->luz[4].color[2]=c.blueF();
    m_ui->colorEsp2->setPalette(QPalette(c));
   gl->updateGL();

}

void ManagerLight::on_posAmbX6_valueChanged(int value)
{
    gl->luz[4].position[0]=float(value)/42.0f;
    m_ui->ledPosX6->setText(QString::number((double)gl->luz[4].position[0],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbY6_valueChanged(int value)
{
    gl->luz[4].position[1]=float(value)/42.0f;
    m_ui->ledPosY6->setText(QString::number((double)gl->luz[4].position[1],'f',2));
   gl->updateGL();

}

void ManagerLight::on_posAmbZ6_valueChanged(int value)
{
    gl->luz[4].position[2]=float(value)/42.0f;
    m_ui->ledPosZ6->setText(QString::number((double)gl->luz[4].position[2],'f',2));
   gl->updateGL();

}

void ManagerLight::on_checkBox_clicked()
{
    gl->pointL=! gl->pointL;
   gl->updateGL();
}

void ManagerLight::on_shininess_valueChanged(int v)
{
    gl->shininess=v;
   gl->updateGL();
}


void ManagerLight::on_matDiff_clicked()
{
   QColor c = QColorDialog::getRgba(QColor(int(gl->material[0].color[0]*255.0f),int(gl->material[0].color[1]*255.0f),int(gl->material[0].color[2]*255.0f)).rgb());
    gl->material[0].color[0]=c.redF();
    gl->material[0].color[1]=c.greenF();
    gl->material[0].color[2]=c.blueF();
    m_ui->colorDiff->setPalette(QPalette(c));
   gl->updateGL();

}

void ManagerLight::on_matEsp_clicked()
{
   QColor c = QColorDialog::getRgba(QColor(int(gl->material[1].color[0]*255.0f),int(gl->material[1].color[1]*255.0f),int(gl->material[1].color[2]*255.0f)).rgb());
    gl->material[1].color[0]=c.redF();
    gl->material[1].color[1]=c.greenF();
    gl->material[1].color[2]=c.blueF();
    m_ui->colorEsp->setPalette(QPalette(c));
   gl->updateGL();
}
