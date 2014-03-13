#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	w=ui->widget;
    showMaximized();
	w->tfUI->setGeometry(width()-525,height()-355,w->tfUI->width(),w->tfUI->height());
	w->setGeometry(0,0,width(),height());
	setWindowTitle("PVM and RAW Volumes Viewer with Ray-Casting");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::resizeEvent(QResizeEvent * e){
	w->setGeometry(0,0,e->size().width(),e->size().height());
}


void MainWindow::on_actionOpen_PVM_triggered()
{
	QString s = QFileDialog::getOpenFileName(this,"Volume PVM",".pvm","Volume PVM (*.pvm)");
	if(s!=QString::null){
		w->texid=w->loadTexture3D(s.toAscii().data());
		on_actionReset_Function_triggered();
		w->calcularHistograma();
	}
}

void MainWindow::on_actionOpen_RAW_triggered()
{
	QString s = QFileDialog::getOpenFileName(this,"Volume RAW",".raw","Volume RAW (*.raw)");
	if(s!=QString::null){
		bool ok;
		int wi=QInputDialog::getInt(this,"Get Width","Width of Volume:",1,1,1024,1,&ok);
		if(!ok) return;
		int he=QInputDialog::getInt(this,"Get Height","Height of Volume:",1,1,1024,1,&ok);
		if(!ok) return;
		int de=QInputDialog::getInt(this,"Get Depth","Depth (or slice) of Volume:",1,1,1024,1,&ok);
		if(!ok) return;
		w->texid=w->loadTexture3D(s.toAscii().data(),true,wi,he,de);
		on_actionReset_Function_triggered();
		w->calcularHistograma();
	}
}

void MainWindow::on_actionExit_triggered()
{
	close();
}

void MainWindow::on_actionRotate_X_triggered()
{
	w->rotate[0]=!w->rotate[0];
}

void MainWindow::on_actionRotate_Y_triggered()
{

	w->rotate[1]=!w->rotate[1];
	w->rotate[2]=!w->rotate[1];
	ui->actionRotate_Y->setChecked(w->rotate[1]);
	ui->actionRotate_Z->setChecked(w->rotate[2]);
}

void MainWindow::on_actionRotate_Z_triggered()
{

	w->rotate[2]=!w->rotate[2];
	w->rotate[1]=!w->rotate[2];
	ui->actionRotate_Y->setChecked(w->rotate[1]);
	ui->actionRotate_Z->setChecked(w->rotate[2]);
}

void MainWindow::on_actionScale_X_triggered()
{
	w->scale[0]=!w->scale[0];
}

void MainWindow::on_actionScale_Y_triggered()
{
	w->scale[1]=!w->scale[1];
	w->scale[2]=!w->scale[1];
	ui->actionScale_Y->setChecked(w->scale[1]);
	ui->actionScale_Z->setChecked(w->scale[2]);
}

void MainWindow::on_actionScale_Z_triggered()
{
	w->scale[2]=!w->scale[2];
	w->scale[1]=!w->scale[2];
	ui->actionScale_Y->setChecked(w->scale[1]);
	ui->actionScale_Z->setChecked(w->scale[2]);

}

void MainWindow::on_actionTransfer_Function_triggered()
{
	if(w->tfUI->isVisible()){
		w->tfUI->setVisible(false);
	}else{
		w->tfUI->setVisible(true);
	}
}

void MainWindow::on_actionReset_Function_triggered()
{
	memset(w->tfUI->ui.DisplayR->trans,0,sizeof(w->tfUI->ui.DisplayR->trans));
	memset(w->tfUI->ui.DisplayG->trans,0,sizeof(w->tfUI->ui.DisplayG->trans));
	memset(w->tfUI->ui.DisplayB->trans,0,sizeof(w->tfUI->ui.DisplayB->trans));
	memset(w->tfUI->ui.DisplayA->trans,0,sizeof(w->tfUI->ui.DisplayA->trans));
	w->tfUI->ui.DisplayA->change=true;
	w->tfUI->ui.DisplayR->update();
	w->tfUI->ui.DisplayG->update();
	w->tfUI->ui.DisplayB->update();
	w->tfUI->ui.DisplayA->update();
}


void MainWindow::on_actionAbout_triggered()
{
	QMessageBox msgBox;msgBox.setText("Kijam Lopez B."); msgBox.setWindowTitle("About...");msgBox.exec();
}
