// Include C++ Library
#include<stdio.h>

// Include QT Library
#include <QtGui>


//#include "Windows.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	printf("Iniciando...\n");
	a.setKeyboardInputInterval(1);

    MainWindow w;
    w.show();


	/*Windows w(NULL);
	w.show();
	w.setMouseTracking(true); // Detectar MouseMove
	w.setVisible(true);*/
	return a.exec();
}
