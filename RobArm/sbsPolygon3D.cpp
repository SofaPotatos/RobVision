#include "sbsPolygon3D.h"

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsPolygon3D::sbsPolygon3D()
{
}

sbsPolygon3D::~sbsPolygon3D()
{
}

/*******************************************************************************
* Operator
********************************************************************************/

sbsPoint3D& sbsPolygon3D::operator()(size_t i)
{
	if (i > m_points.size())
	{
		cout << "can not access the polygon vertex;\n";
	}
	return m_points[i];
}

sbsPoint3D& sbsPolygon3D::operator[](size_t i)
{
	if (i > m_points.size())
	{
		cout << "can not access the polygon vertex;\n";
	}
	return m_points[i];
}

/*******************************************************************************
* Public Method
********************************************************************************/

void sbsPolygon3D::clear()
{
	m_points.clear();
}

void sbsPolygon3D::push_back(sbsPoint3D& p)
{
	m_points.push_back(p);
}

void sbsPolygon3D::pop_back()
{
	m_points.pop_back();
}

void sbsPolygon3D::reserve(size_t num)
{
	m_points.reserve(num);
}

size_t sbsPolygon3D::size()
{
	return m_points.size();
}

sbsPoint3D sbsPolygon3D::pointFirst()
{
	return m_points[0];
}

sbsPoint3D sbsPolygon3D::pointLast()
{
	return m_points[size()-1];
}
