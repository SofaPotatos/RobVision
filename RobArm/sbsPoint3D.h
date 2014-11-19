/************************************************************************
* 1. create and initiated at 3-Oct-2006.  cwy
*
************************************************************************/

#pragma once

#include "sbsMatrix4.h"
#include <math.h>
#include <vector>
#include <float.h>

#define sbsEPS          DBL_EPSILON
#define sbsEPS_LARGE    1E-3F
#define sbsZERO         1E-5F

#define sbsMAX          1e-20
#define sbsMIN          -sbsMAX
#define sbsPI           3.1415926f

#define sbsmax(a,b)         (((a)>(b))?((a):(b)))
#define sbsmin(a,b)         (((a)<(b))?((a):(b)))
#define sbsabs(a)           ((a>=0) ? a:-a)
#define sbszero(a)          (a<sbsEPS_LARGE&&a>-sbsEPS_LARGE)
#define sbszeroeps(a,eps)   (a<eps&&a>-eps)
#define sbsequal(a,b)       ((a-b)<sbsEPS_LARGE&&(a-b)>-sbsEPS_LARGE)
#define sbszeroEX(a)        (a<sbsZERO&&a>-sbsZERO)

using namespace std;

/// sbsPoint3D Class
///
/// This class works on a 3D point, it has basic methods to set z,y and z value
/// It contains operators to do arithmetic operation on 3D point.
/// It contains methods to retrieve information from the 3D point.
class sbsPoint3D
{
    public:
        /// A public double x, y and z.
        /// Variable x, y and z stores the value of x, y, z value of the 3D point
        /// respectively.
        double x,y,z;

    public:
        /// A constructor.
		///
		/// This constructor creates the 3D point with the value of 0 for x, y and z.
        sbsPoint3D();

        /// A constructor.
		///
		/// This constructor creates the 3D point with the value of x, y and z.
        ///
		///@param x: The value of x
		///@param x: The value of y
		///@param x: The value of z
        sbsPoint3D(double x, double y, double z);

        /// A constructor.
		///
		/// This constructor creates the 3D point with the value p for all x, y and z.
        ///
		///@param p: The value of x, y and z
        sbsPoint3D(double p);

        /// A constructor.
		///
		/// This constructor creates the 3D point with the value store in an array.
        ///
		///@param ar: An array which stores the value of x, y and z
        sbsPoint3D(double* ar);

        /// A constructor.
		///
		/// This constructor creates the 3D point with the value store in an array.
        ///
		///@param ar: An array which stores the value of x, y and z
        sbsPoint3D(float* ar);

        /// A destructor.
		///
		/// This destructor free the resources that the object may have.
        ~sbsPoint3D(void);

    public:
        sbsPoint3D	operator +  (const sbsPoint3D& v);
        sbsPoint3D	operator -  (const sbsPoint3D& v);
        sbsPoint3D	operator *  (const sbsPoint3D& v);
        double	    operator &  (sbsPoint3D& v);
        double	    operator /  (sbsPoint3D& v);
        bool    	operator == (sbsPoint3D& v);
        bool       	operator != (sbsPoint3D& v);
        void        operator += (sbsPoint3D& v);
        void        operator -= (sbsPoint3D& v);
        bool    	operator != (double v);
        void        operator += (double v);
        void        operator -= (double v);
        void        operator *= (double v);
        void        operator /= (double v);
        sbsPoint3D	operator +  (double v);
        sbsPoint3D	operator -  (double v);
        sbsPoint3D	operator *  (double v);
        sbsPoint3D	operator /  (double v);

    public:
        /// This member takes sets the value of x, y and z.
        ///
		///@param x: The value of x
		///@param x: The value of y
		///@param x: The value of z
        void    setXYZ(double x, double y, double z);

        /// This member takes sets the value of x, y and z.
        ///
		///@param x: An array which stores the value of x, y and z
        void    setXYZ(double* x);

        /// This member takes unify the value of x, y and z.
        void	unify();

        /// This member return the length of the 3D point.
        ///
        /// @return Length of 3D point
        double	length();

        /// This member return the sum of sqrt(x), sqrt(y) and sqrt(z).
        ///
        ///@return Sum of sqrt(x), sqrt(y) and sqrt(z)
        double  length2();

        /// This member check if the 3D point is zero.
        ///
        ///@return true if zero, false otherwise
        bool    isZero();

        /// This member check if the 3D point is zero with a epsilon value,
        /// any value lesser that the epsilon value is consider zero.
        ///
        ///@return true if zero, false otherwise
        bool    isZero(double eps);

        /// This member check if the 3D point is infinity.
        ///
        ///@return true if infinity, false otherwise
        bool    isInfinity();

        /// This member sets the value of x, y and z to infinity.
        void    setInfinite();

        /// This member apply transformation with the matrix given.
        ///
        ///@param mat: A pointer that points to the transformation matrix
        void    applyTransformation(boost::shared_ptr<sbsMatrix4> mat);

        /// This member return the greater 3D point
        ///
        ///@param p0: A pointer that points to a 3Dpoint
        ///@param p1: A pointer that points to a 3Dpoint
        ///@param p2: A pointer that points to a 3Dpoint
        sbsPoint3D getMax(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1, boost::shared_ptr<sbsPoint3D> p2);

        /// This member return the greater 3D point
        ///
        ///@param p0: A pointer that points to a 3Dpoint
        ///@param p1: A pointer that points to a 3Dpoint
        sbsPoint3D getMax(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1);

        /// This member return the smaller 3D point
        ///
        ///@param p0: A pointer that points to a 3Dpoint
        ///@param p1: A pointer that points to a 3Dpoint
        ///@param p2: A pointer that points to a 3Dpoint
        sbsPoint3D getMin(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1, boost::shared_ptr<sbsPoint3D> p2);

        /// This member return the smaller 3D point
        ///
        ///@param p0: A pointer that points to a 3Dpoint
        ///@param p1: A pointer that points to a 3Dpoint
        sbsPoint3D getMin(boost::shared_ptr<sbsPoint3D> p0, boost::shared_ptr<sbsPoint3D> p1);
};

#define sbsPoint3DVector vector<sbsPoint3D>
