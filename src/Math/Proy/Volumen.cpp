#include "Volumen.h"

#include "ddsbase.h"

Volumen::Volumen(void)
{
	volume=NULL;
}

Volumen::~Volumen(void)
{
		if(volume!=NULL) free(volume);
}

void Volumen::load(char* name)
{

	printf("reading PVM file\n");

	if ((volume=readPVMvolume(name,&width,&height,&depth,&components,&scalex,&scaley,&scalez))==NULL){

		printf("No se pudo abrir el modelo\n");
		return;
	}
	printf("found volume with width=%d height=%d depth=%d components=%d\n",width,height,depth,components);
	if (scalex!=1.0f || scaley!=1.0f || scalez!=1.0f) 
		printf("and edge length %g/%g/%g\n",scalex,scaley,scalez);
	else{
		float maxSize = (float)max(width, max(height, depth));
		scalex=width/maxSize;
		scaley=height/maxSize;
		scalez=depth/maxSize;
	}
	printf("and data checksum=%08X\n",checksum(volume,width*height*depth*components));
	if (components==2) volume=quantize(volume,width,height,depth);
    StepSize[0]=(1.0f / (float)width);
    StepSize[1]=(1.0f / (float)height);
    StepSize[2]=(1.0f / (float)depth);
	Iterations=maxSize;

}

void Volumen::loadRAW(char *name,int widthImagen,int heightImagen,int depthImagen)
{
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result; 
	pFile = fopen (name, "rb" );
	if (pFile==NULL) {
		printf ("File error");
	}else{
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		rewind (pFile);

		if(volume!=NULL) free(volume);

		volume = (unsigned char*) malloc (sizeof(unsigned char)*lSize);
		if (volume == NULL) printf ("Memory error");

		result = fread (volume,1,lSize,pFile);
		if (result != lSize) printf ("Reading error");
		
		width=widthImagen;
		height=heightImagen;
		depth=depthImagen;
		float maxSize = (float)max(width, max(height, depth));
		scalex=width/maxSize;
		scaley=height/maxSize;
		scalez=depth/maxSize;
		Iterations=maxSize;
	}



}
