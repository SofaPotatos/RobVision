#pragma once

#include <iostream>
#include <iomanip>
#include <math.h>
#include <boost/shared_ptr.hpp>

#define PI 3.14159265

using namespace std;

/// sbsMatrix4 Class
///
/// This class works on a 4x4 rotation matrix, it contains basic methods
/// to get, set and print the rotation matrix.
/// It contains operators to do addition, subtraction, cross product and
/// dot product.
/// It contains methods to converts rotation matrix to euler angle and
/// quaternion unit, and vise versa.
class sbsMatrix4
{
    public:
		/// A public 4 x 4 array.
		/// This array stores the value of the 4 x 4 matrix.
		double m[4][4];

	public:
		/// A constructor.
		///
		/// This constructor creates and set the 4x4 matric into a identity matrix.
		sbsMatrix4(void);

		/// A constructor.
		///
		/// This constructor creates and set the 4x4 matric identical to the param matrix.
		///
		///@param matrix: A 4x4 matrix
		sbsMatrix4(boost::shared_ptr<sbsMatrix4> matrix);

		/// A constructor.
		///
		/// This constructor creates and set the 4x4 matric with the value given in an array.
		///
		///@param mx: An array that stores the value of the 4x4 matric
		sbsMatrix4(float* mx);

		/// A constructor.
		///
		/// This constructor creates and set the 4x4 matric with the value given in an array.
		///
		///@param mx: An array that stores the value of the 4x4 matric
		sbsMatrix4(double* mx);

		/// A constructor.
		///
		/// This constructor creates and set the 4x4 matric with the value given.
        ///
		///@param _11 : The value for [0][0]
		///@param _12 : The value for [0][1]
		///@param _13 : The value for [0][2]
		///@param _14 : The value for [0][3]
		///@param _21 : The value for [1][0]
		///@param _22 : The value for [1][1]
		///@param _23 : The value for [1][2]
		///@param _24 : The value for [1][3]
		///@param _31 : The value for [2][0]
		///@param _32 : The value for [2][1]
		///@param _33 : The value for [2][2]
		///@param _34 : The value for [2][3]
		///@param _41 : The value for [3][0]
		///@param _42 : The value for [3][1]
		///@param _43 : The value for [3][2]
		///@param _44 : The value for [3][3]
		sbsMatrix4( double _11, double _12, double _13, double _14,
					double _21, double _22, double _23, double _24,
					double _31, double _32, double _33, double _34,
					double _41, double _42, double _43, double _44 );

		/// A destructor.
		///
		/// This destructor free the resources that the object may have.
		~sbsMatrix4(void);

	public:
		// unary operators
		sbsMatrix4 operator + () const;
		sbsMatrix4 operator - () const;

		// binary operators
		sbsMatrix4 operator + (sbsMatrix4&) ;
		sbsMatrix4 operator - (sbsMatrix4&) ;
		sbsMatrix4 operator / (double) const;
		sbsMatrix4 operator * (sbsMatrix4&);
		void       operator *= (double);
		double&    operator ()(int i, int j);

	private:
		/// This member calculate the determinant from the given array.
		///
		///@param mx: An array the contain the value of a 3 x 3 matrix
		///@return determinant of the 3 x 3 matrix
		double determinant3(double* mx);

	public:
		/// This member takes in and set the 4 x 4 array with the value given in an array.
		///
		///@param mx: An array thats holds the values for the 4 x 4 array
		void setMatrix(double* mx);

		/// This member calculate and return the determinant.
		///
		///@return determinant
		double getDeterminant();

		/// This member return the inverse matrix.
		///
		///@return inverse matrix
		sbsMatrix4 getInverse3();

		/// This member prints the 4 x 4 matrix
		void printMatrix();

        /// This member set the 4 x 4 matrix with euler angle.
		///
		///@param xAng: Euler angle of x
		///@param yAng: Euler angle of y
		///@param zAng: Euler angle of z
		void setRotateMatrix(double xAng, double yAng, double zAng);

		/// This member return the address of the matrix.
		///
		///@return the address of the matrix
		double* getMatrix();

		/// This member return the transpose matrix.
		///
		///@return transpose matrix
		sbsMatrix4 getTranspose();

		/// This member sets the 4 x 4 matrix into a translation matrix.
		///
		///@param xAng: Translation of x
		///@param yAng: Translation of y
		///@param zAng: Translation of z
		void setTranslationMatrix(double x, double y, double z);

		/// This member remove the translation from the 4 x 4 matrix.
		void removeTranslation();

		/// This member add the translation without changing the rotation of the 4 x 4 matrix.
		///
		///@param xAng: Translation of x
		///@param yAng: Translation of y
		///@param zAng: Translation of z
		void addTranslationAfterRotate(double x, double y, double z);

		/// This member converts euler angle to matrix.
		///
		///@param xAng: Euler angle of x
		///@param yAng: Euler angle of y
		///@param zAng: Euler angle of z
		void matrixFromEulerAngle(double xAng, double yAng, double zAng);

		/// This member converts matrix to euler angle.
		///
		///@param xAng: Euler angle of x
		///@param yAng: Euler angle of y
		///@param zAng: Euler angle of z
		void matrixToEulerAngle(double& xAng, double& yAng, double& zAng);

		/// This member converts matrix to quaternion unit.
		///
		///@param a: Quaternion unit of a
		///@param b: Quaternion unit of b
		///@param c: Quaternion unit of c
		///@param d: Quaternion unit of d
		void matrixFromQuaternion(double a, double b, double c, double d);

		/// This member converts quaternion unit to matrix.
		///
		///@param a: Quaternion unit of a
		///@param b: Quaternion unit of b
		///@param c: Quaternion unit of c
		///@param d: Quaternion unit of d
		void matrixToQuaternion(double& a, double& b, double& c, double& d);

		/// This member test the functionality of MatrixFromEulerAngle and MatricToEulerAngle.
		///
		///@param xAng: Euler angle of x
		///@param yAng: Euler angle of y
		///@param zAng: Euler angle of z
		void testEulerAngle(double x, double y, double z);

		/// This member test the functionality of MatrixFromQuaternion and MatrixToQuaternion.
		///
		///@param a: Quaternion unit of a
		///@param b: Quaternion unit of b
		///@param c: Quaternion unit of c
		///@param d: Quaternion unit of d
		void testQuaternion(double a, double b, double c, double d);
};
