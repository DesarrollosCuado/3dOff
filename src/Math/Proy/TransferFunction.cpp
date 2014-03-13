#include "TransferFunction.h"

TransferFunction::TransferFunction(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.DisplayR->color='R';
	ui.DisplayG->color='G';
	ui.DisplayB->color='B';
	ui.DisplayA->color='A';
	maximoValor=0;
	ui.DisplayR->setMouseTracking(true);
	ui.DisplayG->setMouseTracking(true);
	ui.DisplayB->setMouseTracking(true);
	ui.DisplayA->setMouseTracking(true);
}

TransferFunction::~TransferFunction()
{

}
void TransferFunction::closeEvent(QCloseEvent *event)
 {
     event->ignore();
 }