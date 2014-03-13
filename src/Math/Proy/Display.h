#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPaintDevice>


class Display : public QWidget
{
	Q_OBJECT

public:
	Display(QWidget *parent);
	~Display();
	unsigned int trans[256];
	char color;
	bool press;
	bool change,click1;
	QPoint last;


private:
	void paintEvent(QPaintEvent * paintEvent);
	void mousePressEvent(QMouseEvent * mouseEvent);
	void mouseMoveEvent(QMouseEvent * mouseEvent);
	void mouseReleaseEvent(QMouseEvent * mouseEvent); 
	int oldX,oldY;
};

#endif // DISPLAY_H
