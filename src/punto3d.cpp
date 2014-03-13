#include "punto3d.h"

punto3d::punto3d()
{
    x=y=z=0.0f;
}
punto3d::punto3d(double a,double b,double c) : x(a),y(b),z(c)
{

}
punto3d punto3d::operator - (punto3d v)
{
	return punto3d(x - v.x,y - v.y,z - v.z);
}
punto3d punto3d::operator + (punto3d v)
{
	return punto3d(x + v.x,y + v.y,z + v.z);
}
punto3d punto3d::operator * (float e)
{
        return punto3d(x*e,y*e,z*e);
}

punto3d punto3d::operator / (float e)
{
        return punto3d(x/e,y/e,z/e);
}

void punto3d::operator /= (float e)
{
        x/=e;
        y/=e;
        z/=e;
}
void punto3d::operator += (punto3d v)
{
    x+=v.x;
    y+=v.y;
    z+=v.z;
}

void punto3d::operator -= (punto3d v)
{
    x-=v.x;
    y-=v.y;
    z-=v.z;
}
