#ifndef _MY_HEADER
#define _MY_HEADER

#include <iostream>	
#include <fstream>
#include <string>
#include <vector>	
#include <queue>
#include <math.h>
#include <algorithm>
#include <float.h>

#include "glew/glew.h"

#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#pragma warning(disable:4056)
#pragma warning(disable:4756)
#pragma comment(lib, "glew/glew32.lib")

using namespace std;

typedef unsigned char	byte;

#define GAMETIME		m_time.msecsTo(QTime::currentTime())
#define SCREEN_WIDTH	640								//Window width
#define SCREEN_HEIGHT	480									//Window height
#define DEGTORAD(degree) ((degree) * (3.141592654f / 180.0f))
#define RADTODEG(radian) ((radian) * (180.0f / 3.141592654f))



#endif
