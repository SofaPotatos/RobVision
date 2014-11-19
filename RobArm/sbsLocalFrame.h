#pragma once

#include "sbsPoint3D.h"
#include "sbsMatrix4.h"

/// sbsLocalFrame Class
///
/// This class
class sbsLocalFrame
{
    public:
        /// A public sbsPoint3D object
		/// This object contain original value of x, y and z.
        sbsPoint3D   o;
        sbsPoint3D   x;
        sbsPoint3D   y;
        sbsPoint3D   z;
        double		 c; // mean curvature

    public:
		/// A constructor.
		///
		/// This constructor creates a
        sbsLocalFrame(void);
        sbsLocalFrame(boost::shared_ptr<sbsLocalFrame> lf);
        sbsLocalFrame(sbsPoint3D o, sbsPoint3D x, sbsPoint3D y, sbsPoint3D z);
        sbsLocalFrame(sbsPoint3D o, sbsPoint3D x, sbsPoint3D y, sbsPoint3D z, double c);
        sbsLocalFrame(sbsPoint3D o, sbsPoint3D x, sbsPoint3D y);
        ~sbsLocalFrame(void);

    public:
        void operator = (const sbsLocalFrame& lf);

    public:
        sbsPoint3D   localized(sbsPoint3D p);
        sbsPoint3D   getPos(sbsPoint3D p);
        sbsPoint3D   localized_unify(sbsPoint3D p);
        sbsPoint3D   getPos_unify(sbsPoint3D p);
        void         unify();
        void         rotateFrame(sbsMatrix4& mat);
        void         render(double len, double radius);
};
