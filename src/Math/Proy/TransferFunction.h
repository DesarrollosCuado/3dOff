#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <QWidget>
#include "ui_TransferFunction.h"

class TransferFunction : public QWidget
{
	Q_OBJECT

public:
	TransferFunction(QWidget *parent = 0);
	~TransferFunction();
	int histograma[256];
	int maximoValor;
	Ui::TransferFunctionClass ui;

private:
	void closeEvent(QCloseEvent *event);
};

#endif // TRANSFERFUNCTION_H
