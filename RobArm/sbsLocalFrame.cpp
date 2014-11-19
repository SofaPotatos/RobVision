#include "sbsLocalFrame.h"

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsLocalFrame::sbsLocalFrame(void)
{
	o =  sbsPoint3D(0,0,0);
	x =  sbsPoint3D(1,0,0);
	y =  sbsPoint3D(0,1,0);
	z =  sbsPoint3D(0,0,1);
	c = 0;
}

sbsLocalFrame::sbsLocalFrame(boost::shared_ptr<sbsLocalFrame> lf)
{
	o = lf->o;
	x = lf->x;
	y = lf->y;
	z = lf->z;
	c = lf->c;
}

sbsLocalFrame::sbsLocalFrame(sbsPoint3D o, sbsPoint3D x, sbsPoint3D y, sbsPoint3D z)
{
	this->o = o;
	this->x = x;
	this->y = y;
	this->z = z;

	this->z = (this->x)*(this->y);
	this->x = (this->y)*(this->z);

	this->x.unify();
	this->y.unify();
	this->z.unify();

	c =0;
}

sbsLocalFrame::sbsLocalFrame(sbsPoint3D o, sbsPoint3D x, sbsPoint3D y, sbsPoint3D z, double c)
{
	this->o = o;
	this->x = x;
	this->y = y;
	this->z = z;

	this->z = (this->x)*(this->y);
	this->x = (this->y)*(this->z);

	this->x.unify();
	this->y.unify();
	this->z.unify();

	this->c = c;
}

sbsLocalFrame::sbsLocalFrame(sbsPoint3D o, sbsPoint3D x, sbsPoint3D y)
{
	this->o = o;
	this->x = x;
	this->y = y;

	this->z = (this->x)*(this->y);
	this->x = (this->y)*(this->z);

	this->x.unify();
	this->y.unify();
	this->z.unify();

	c = 0;
}

sbsLocalFrame::~sbsLocalFrame(void)
{
}

/*******************************************************************************
* Operator
********************************************************************************/

void sbsLocalFrame::operator = (const sbsLocalFrame& lf)
{
	o = lf.o;
	x = lf.x;
	y = lf.y;
	z = lf.z;
	c = lf.c;
}

/*******************************************************************************
* Public Method
********************************************************************************/

sbsPoint3D   sbsLocalFrame::localized(sbsPoint3D p)
{
	sbsPoint3D r;
	sbsPoint3D p1 = p-o;

	r.x = p1&x;
	r.y = p1&y;
	r.z = p1&z;

	return r;
}

sbsPoint3D   sbsLocalFrame::localized_unify(sbsPoint3D p)
{
	sbsPoint3D r;
	sbsPoint3D p1 = p;

	r.x = p1&x;
	r.y = p1&y;
	r.z = p1&z;

	return r;
}

sbsPoint3D   sbsLocalFrame::getPos(sbsPoint3D p)
{
	return (x*p.x+y*p.y+z*p.z+o);
}

sbsPoint3D   sbsLocalFrame::getPos_unify(sbsPoint3D p)
{
	return (x*p.x+y*p.y+z*p.z);
}

void sbsLocalFrame::unify()
{
	z = x*y;
	x = y*z;
	x.unify();
	y.unify();
	z.unify();
}

void sbsLocalFrame::rotateFrame(sbsMatrix4& mat)
{
    boost::shared_ptr<sbsMatrix4> temp(new sbsMatrix4);
    *temp = mat;
	x.applyTransformation(temp);
	y.applyTransformation(temp);
	z.applyTransformation(temp);

	x.unify();
	y.unify();
	z.unify();
}
