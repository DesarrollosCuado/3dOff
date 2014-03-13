#pragma once

class Volumen
{
public:
	Volumen(void);
	~Volumen(void);
	
   unsigned char *volume;
   unsigned int width,height,depth,components;
   float scalex,scaley,scalez;
	float StepSize[3],maxSize,Iterations;
   void load(char *name);
   void loadRAW(char *name,int widthImagen,int heightImagen,int depthImagen);
};
