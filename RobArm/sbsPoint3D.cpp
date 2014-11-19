#include "sbsPoint3D.h"

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsPoint3D::sbsPoint3D(void)
{
	x = 0;	y = 0;	z = 0;
}

sbsPoint3D::sbsPoint3D(double x, double y, double z)
{
	this->x = x; this->y = y; this->z = z;
}

sbsPoint3D::sbsPoint3D(double p)
{
	x = p; y = x; z = x;
}

sbsPoint3D::sbsPoint3D(double* ar)
{
	x = ar[0]; y = ar[1]; z = ar[2];
}

sbsPoint3D::sbsPoint3D(float* ar)
{
	x = ar[0]; y = ar[1]; z = ar[2];
}

sbsPoint3D::~sbsPoint3D(void)
{
}

/*******************************************************************************
* Operator
********************************************************************************/

sbsPoint3D sbsPoint3D::operator + (const sbsPoint3D& v)
{
	sbsPoint3D r;

	r.x = x + v.x;
	r.y = y + v.y;
	r.z = z + v.z;

	return	r;
}

sbsPoint3D sbsPoint3D::operator - (const sbsPoint3D& v)
{
	sbsPoint3D r;

	r.x = x - v.x;
	r.y = y - v.y;
	r.z = z - v.z;

	return r;
}

sbsPoint3D sbsPoint3D::operator * (const sbsPoint3D& v)
{
	sbsPoint3D r;

	r.x = y*v.z - v.y*z;
	r.y = v.x*z - x*v.z;
	r.z = x*v.y - v.x*y;

	return r;
}

double sbsPoint3D::operator & ( sbsPoint3D& v ) //dot product
{
	return ( x * v.x + y * v.y + z * v.z );
}

double sbsPoint3D::operator /  ( sbsPoint3D& v ) //p0/p1 (parallel)
{
 	if (v.x > 0.00001 || v.x < -0.00001)
	{
		return x/v.x;
	}
	if (v.y > 0.00001 || v.y < -0.00001)
	{
		return y/v.y;
	}
	if (v.z > 0.00001 || v.z < -0.00001)
	{
		return z/v.z;
	}
	return 0;
}

bool sbsPoint3D::operator == (sbsPoint3D& v)
{
	double dx = x - v.x;
	if (!sbszero(dx))
	{
		return false;
	}

	double dy = y - v.y;
	if (!sbszero(dy))
	{
		return false;
	}

	double dz = z - v.z;
	if (!sbszero(dz))
	{
		return false;
	}

	return true;
}

bool sbsPoint3D::operator != (sbsPoint3D& v)
{
	double dx = x - v.x;
	if (!sbszero(dx))
	{
		return true;
	}

	double dy = y - v.y;
	if (!sbszero(dy))
	{
		return true;
	}

	double dz = z - v.z;
	if (!sbszero(dz))
	{
		return true;
	}

	return false;
}

void sbsPoint3D::operator += (sbsPoint3D& v)
{
	x = x + v.x;
	y = y + v.y;
	z = z + v.z;
}

void sbsPoint3D::operator -= (sbsPoint3D& v)
{
	x = x - v.x;
	y = y - v.y;
	z = z - v.z;
}

bool sbsPoint3D::operator != (double v)
{
	double dx = x - v;
	if (!sbszero(dx))
	{
		return true;
	}

	double dy = y - v;
	if (!sbszero(dy))
	{
		return true;
	}

	double dz = z - v;
	if (!sbszero(dz))
	{
		return true;
	}

	return false;
}

void sbsPoint3D::operator += (double v)
{
	x = x + v;
	y = y + v;
	z = z + v;
}

void sbsPoint3D::operator -= (double v)
{
	x = x - v;
	y = y - v;
	z = z - v;
}

void sbsPoint3D::operator *= (double v)
{
	x = x * v;
	y = y * v;
	z = z * v;
}

void sbsPoint3D::operator /= (double v)
{
	if (sbszero(v))
	{
		printf("warning:the point is divide by a small value\n");
	}
	x = x / v;
	y = y / v;
	z = z / v;
}

sbsPoint3D sbsPoint3D::operator + (double v)
{
	sbsPoint3D r;

	r.x = x + v;
	r.y = y + v;
	r.z = z + v;

	return	r;
}

sbsPoint3D sbsPoint3D::operator - (double v)
{
	sbsPoint3D r;

	r.x = x - v;
	r.y = y - v;
	r.z = z - v;

	return r;
}

sbsPoint3D sbsPoint3D::operator * (double v) //scale
{
	sbsPoint3D r;

	r.x = x * (float)v;
	r.y = y * (float)v;
	r.z = z * (float)v;

	return r;
}

sbsPoint3D sbsPoint3D::operator / (double v)
{
	sbsPoint3D p;
	if (sbszero(v))
	{
		printf("warning:the point is divide by a small value\n");
	}
	p.x = x / v;
	p.y = y / v;
	p.z = z / v;
	return p;
}

/*******************************************************************************
* Public Method
********************************************************************************/

void sbsPoint3D::setXYZ(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void sbsPoint3D::setXYZ(double* x)
{
	setXYZ(x[0],x[1],x[2]);
}

void sbsPoint3D::unify()
{
	double	len = length();

	if( len < sbsEPS )
	{
		x = 1;
		y = 0;
		z = 0;
	}
	else
	{
		len = 1.0f/len;
		x *= len;
		y *= len;
		z *= len;
	}
}

double sbsPoint3D::length()
{
	return(sqrt(x*x + y*y + z*z));
}

double sbsPoint3D::length2()
{
	return(x*x + y*y + z*z);
}

bool  sbsPoint3D::isZero()
{
	return (sbszero(x)&&(sbszero(y))&&(sbszero(z)));
}

bool sbsPoint3D::isZero(double eps)
{
	if (x > eps || x < -eps)
	{
		return false;
	}
	if (y > eps || y < -eps)
	{
		return false;
	}
	if (z > eps || z < -eps)
	{
		return false;
	}
	return true;
}

bool sbsPoint3D::isInfinity()
{
	return x >= sbsMAX || y >= sbsMAX || z >= sbsMAX || x <= -sbsMAX || y <= -sbsMAX || z <=-sbsMAX;
}

void sbsPoint3D::setInfinite()
{
	setXYZ(sbsMAX,sbsMAX,sbsMAX);
}

void sbsPoint3D::applyTransformation(boost::shared_ptr<sbsMatrix4> mat)
{
	sbsPoint3D p = *this;
	x = mat->m[0][0]*p.x+mat->m[0][1]*p.y+mat->m[0][2]*p.z+mat->m[0][3];
	y = mat->m[1][0]*p.x+mat->m[1][1]*p.y+mat->m[1][2]*p.z+mat->m[1][3];
	z = mat->m[2][0]*p.x+mat->m[2][1]*p.y+mat->m[2][2]*p.z+mat->m[2][3];
}

sbsPoint3D sbsPoint3D::getMax(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1, boost::shared_ptr<sbsPoint3D> p2)
{
	boost::shared_ptr<sbsPoint3D> p(new sbsPoint3D);
    *p = getMax(p0,p1);
	return getMax(p,p2);
}

sbsPoint3D sbsPoint3D::getMax(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1)
{
	sbsPoint3D p = *p0;
	if (p.x < p1->x)
	{
		p.x = p1->x;
	}
	if (p.y < p1->y)
	{
		p.y = p1->y;
	}
	if (p.z < p1->z)
	{
		p.z = p1->z;
	}
	return p;
}

sbsPoint3D sbsPoint3D::getMin(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1, boost::shared_ptr<sbsPoint3D> p2)
{
	boost::shared_ptr<sbsPoint3D> p(new sbsPoint3D);
    *p = getMin(p0,p1);
	return getMin(p,p2);
}

sbsPoint3D sbsPoint3D::getMin(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1)
{
	sbsPoint3D p = *p0;
	if (p.x > p1->x)
	{
		p.x = p1->x;
	}
	if (p.y > p1->y)
	{
		p.y = p1->y;
	}
	if (p.z > p1->z)
	{
		p.z = p1->z;
	}
	return p;
}
