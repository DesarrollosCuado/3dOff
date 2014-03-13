#pragma once

#include <math.h>

class punto3d
{
public:
	double x,y,z;
	punto3d(double a,double b,double c);
        punto3d operator - (punto3d v);
        punto3d operator + (punto3d v);
        void operator += (punto3d v);
        void operator -= (punto3d v);
        punto3d operator * (float e);
        punto3d operator / (float e);
        void operator /= (float e);
        static punto3d normalize(punto3d v)
        {
                float norm = sqrtf((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
                return punto3d(v.x/norm,v.y/norm,v.z/norm);
        }
        void normalize(){
           punto3d p=punto3d::normalize(*this);
           x=p.x;
           y=p.y;
           z=p.z;
        }
        static punto3d proX(punto3d v1, punto3d v2)
        {
                return normalize(punto3d((v1.y*v2.z)-(v1.z*v2.y),(v1.z*v2.x)-(v1.x*v2.z),(v1.x*v2.y)-(v1.y*v2.x)));
        }
	punto3d();
};
