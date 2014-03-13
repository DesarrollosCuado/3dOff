#include "Display.h"
#include "TransferFunction.h"
#include "Windows.h"

Display::Display(QWidget *parent)
	: QWidget(parent)
{
	setAutoFillBackground(true);
	setBackgroundRole(QPalette::Base);
	memset(trans,0,sizeof(trans));
	press=false;
	change=true;
	click1=true;
}

Display::~Display()
{

}

void Display::paintEvent(QPaintEvent * paintEvent)
{
	QPainter p(this);

	QColor bH(0,0,0);
	if(color=='R') bH.setRed(255);
	if(color=='G') bH.setGreen(255);
	if(color=='B') bH.setBlue(255);
	if(color=='A'){
		bH.setBlue(200);
		bH.setGreen(200);
		bH.setRed(200);
	}
	p.setPen(bH);
	p.setBrush(QBrush(bH));
	TransferFunction *aa=(TransferFunction*)parentWidget();
	Windows *a=(Windows*)aa->parentWidget();
	if(a->maximoValorHistograma>0)
		for(int i=0;i<256;++i){
			p.drawLine(i+1,151,i+1,151-a->histograma[i]*150/a->maximoValorHistograma);
		}

	QColor b(0,0,0);
	p.setPen(b);
	p.setBrush(QBrush(b));
	for(int i=0;i<256;++i){
		p.drawPoint(i+1,150-trans[i]);
	}


}

void Display::mousePressEvent(QMouseEvent * mouseEvent)
{
	if(mouseEvent->button() & Qt::LeftButton){
		press=true;
		last=mouseEvent->pos();
		click1=true;
	}else
	if(mouseEvent->button() & Qt::RightButton && click1) last=mouseEvent->pos();
}

void Display::mouseMoveEvent(QMouseEvent * mouseEvent)
{
	if(press){
		click1=true;
		if(mouseEvent->x()>=1 && mouseEvent->x()<=255){
			if(mouseEvent->y()>=1 && mouseEvent->y()<=150){
				float b,m;
				int x1,x2,y1,y2;
				if(mouseEvent->x()<last.x()){
					x1=mouseEvent->x();
					y1=mouseEvent->y();
					x2=last.x();
					y2=last.y();
				}else{
					x2=mouseEvent->x();
					y2=mouseEvent->y();
					x1=last.x();
					y1=last.y();
				}
			

				m=float(y2-y1)/float(x2-x1);
				b=y1-m*x1;

				for(int i=x1;i<=x2;++i){
					trans[i]=min(255,150-int(m*i+b));
				}

				change=true;
				trans[0]=trans[255]=0;
				last=mouseEvent->pos();
				update();
			}
		}
	}
}

void Display::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
	if(mouseEvent->button() & Qt::RightButton){
		click1=!click1;
		if(click1){
			if(mouseEvent->x()>=1 && mouseEvent->x()<=255){
				if(mouseEvent->y()>=1 && mouseEvent->y()<=150){
					float b,m;
					int x1,x2,y1,y2;
					if(mouseEvent->x()<last.x()){
						x1=mouseEvent->x();
						y1=mouseEvent->y();
						x2=last.x();
						y2=last.y();
					}else{
						x2=mouseEvent->x();
						y2=mouseEvent->y();
						x1=last.x();
						y1=last.y();
					}
				

					m=float(y2-y1)/float(x2-x1);
					b=y1-m*x1;

					for(int i=x1;i<=x2;++i){
						trans[i]=min(255,150-int(m*i+b));
					}

					change=true;
					trans[0]=trans[255]=0;
					last=mouseEvent->pos();
					update();
				}
			}
		}
	}else 
		click1=true;
	if(mouseEvent->button() & Qt::LeftButton) press=false;
} 