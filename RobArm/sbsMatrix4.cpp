#include "sbsMatrix4.h"

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsMatrix4::sbsMatrix4(void)
{
	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
}

sbsMatrix4::sbsMatrix4(boost::shared_ptr<sbsMatrix4> matrix)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			m[i][j] = matrix->m[i][j];
}

sbsMatrix4::sbsMatrix4(float* mx)
{
	m[0][0] = mx[0];	m[0][1] = mx[1];	m[0][2] = mx[2];	m[0][3] = mx[3];
	m[1][0] = mx[4];	m[1][1] = mx[5];	m[1][2] = mx[6];	m[1][3] = mx[7];
	m[2][0] = mx[8];	m[2][1] = mx[9];	m[2][2] = mx[10];	m[2][3] = mx[11];
	m[3][0] = mx[12];	m[3][1] = mx[13];	m[3][2] = mx[14];	m[3][3] = mx[15];
}

sbsMatrix4::sbsMatrix4(double* mx)
{
	m[0][0] = mx[0];	m[0][1] = mx[1];	m[0][2] = mx[2];	m[0][3] = mx[3];
	m[1][0] = mx[4];	m[1][1] = mx[5];	m[1][2] = mx[6];	m[1][3] = mx[7];
	m[2][0] = mx[8];	m[2][1] = mx[9];	m[2][2] = mx[10];	m[2][3] = mx[11];
	m[3][0] = mx[12];	m[3][1] = mx[13];	m[3][2] = mx[14];	m[3][3] = mx[15];
}

sbsMatrix4::sbsMatrix4(double _11, double _12, double _13, double _14,
					   double _21, double _22, double _23, double _24,
					   double _31, double _32, double _33, double _34,
					   double _41, double _42, double _43, double _44 )
{
	m[0][0] = _11;   m[0][1] = _12;   m[0][2] = _13;   m[0][3] = _14;
	m[1][0] = _21;   m[1][1] = _22;   m[1][2] = _23;   m[1][3] = _24;
	m[2][0] = _31;   m[2][1] = _32;   m[2][2] = _33;   m[2][3] = _34;
	m[3][0] = _41;   m[3][1] = _42;   m[3][2] = _43;   m[3][3] = _44;
}

sbsMatrix4::~sbsMatrix4(void)
{
}

/*******************************************************************************
* Operator
********************************************************************************/

sbsMatrix4 sbsMatrix4::operator * (sbsMatrix4& mat)
{
	sbsMatrix4 product;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			product.m[i][j] = m[i][0]*mat.m[0][j]+m[i][1]*mat.m[1][j]+m[i][2]*mat.m[2][j]+m[i][3]*mat.m[3][j];
		}
	}
	return product;
}

void sbsMatrix4::operator *= (double f)
{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		{
			m[i][j] *= f;
		}
}

double& sbsMatrix4::operator ()(int i, int j)
{
	return m[i][j];
}

/*******************************************************************************
* Private Method
********************************************************************************/

double sbsMatrix4::determinant3(double* m)
{
	double det = 0.0f;
	det += m[0]*(m[4]*m[8]-m[5]*m[7]);
	det -= m[1]*(m[3]*m[8]-m[5]*m[6]);
	det += m[2]*(m[3]*m[7]-m[4]*m[6]);
	return det;
}

/*******************************************************************************
* Public Method
********************************************************************************/

void sbsMatrix4::setMatrix(double* mx)
{
	m[0][0] = mx[0];	m[0][1] = mx[1];	m[0][2] = mx[2];	m[0][3] = mx[3];
	m[1][0] = mx[4];	m[1][1] = mx[5];	m[1][2] = mx[6];	m[1][3] = mx[7];
	m[2][0] = mx[8];	m[2][1] = mx[9];	m[2][2] = mx[10];	m[2][3] = mx[11];
	m[3][0] = mx[12];	m[3][1] = mx[13];	m[3][2] = mx[14];	m[3][3] = mx[15];
}

double sbsMatrix4::getDeterminant()
{
	double det1[] = {m[1][1],m[1][2],m[1][3],m[2][1],m[2][2],m[2][3],m[3][1],m[3][2],m[3][3]};
	double det2[] = {m[1][0],m[1][2],m[1][3],m[2][0],m[2][2],m[2][3],m[3][0],m[3][2],m[3][3]};
	double det3[] = {m[1][0],m[1][1],m[1][3],m[2][0],m[2][1],m[2][3],m[3][0],m[3][1],m[3][3]};
	double det4[] = {m[1][0],m[1][1],m[1][2],m[2][0],m[2][1],m[2][2],m[3][0],m[3][1],m[3][2]};
	return (m[0][0]*determinant3(det1)-m[0][1]*determinant3(det2)+m[0][2]*determinant3(det3)-m[0][3]*determinant3(det4));
}

sbsMatrix4 sbsMatrix4::getInverse3()
{
	sbsMatrix4 inver;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			inver.m[i][j] = m[(j+2)%3][(i+2)%3]*m[(j+1)%3][(i+1)%3]-m[(j+2)%3][(i+1)%3]*m[(j+1)%3][(i+2)%3];
		}
	}

	double det = m[0][0]*inver.m[0][0]+m[0][1]*inver.m[1][0]+m[0][2]*inver.m[2][0];
	inver *= (float)(1/det);
	return inver;
}

void sbsMatrix4::printMatrix()
{
    cout << setprecision(3) << fixed;
    cout << "\t" << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << endl;
    cout << "\t" << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << endl;
    cout << "\t" << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << endl;
    cout << "\t" << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << endl;
}

void sbsMatrix4::setRotateMatrix(double xAng, double yAng, double zAng)
{
	matrixFromEulerAngle(xAng, yAng, zAng);
}

double* sbsMatrix4::getMatrix()
{
	double * ptr = (double*)m;
	return ptr;
}

sbsMatrix4 sbsMatrix4::getTranspose()
{
	sbsMatrix4 mat;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			mat.m[i][j] = m[j][i];
		}
	}
	return mat;
}

void sbsMatrix4::setTranslationMatrix(double x, double y, double z)
{
	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = x;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = y;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = z;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
}

void sbsMatrix4::removeTranslation()
{
		m[0][3] = 0;
		m[1][3] = 0;
		m[2][3] = 0;
}

void sbsMatrix4::addTranslationAfterRotate(double x, double y, double z)
{
	m[0][3] += x;
	m[1][3] += y;
	m[2][3] += z;
}

void sbsMatrix4::matrixFromEulerAngle(double xAng, double yAng, double zAng)
{
	//ZYX convention of Eular Angle.
	//xAng : rotation around x-axis
	//yAng : rotation around y-axis
	//zAng : rotation around z-axis
	double c3 = cos(xAng*PI/180);
	double s3 = sin(xAng*PI/180);
	double c2 = cos(yAng*PI/180);
	double s2 = sin(yAng*PI/180);
	double c1 = cos(zAng*PI/180);
	double s1 = sin(zAng*PI/180);
	m[0][0] = c1*c2;	m[0][1] = c1*s2*s3-s1*c3;		m[0][2] = c1*s2*c3+s1*s3;		m[0][3] = 0;
	m[1][0] = s1*c2;	m[1][1] = s1*s2*s3+c1*c3;		m[1][2] = s1*s2*c3-c1*s3;		m[1][3] = 0;
	m[2][0] = -s2;		m[2][1] = c2*s3;				m[2][2] = c2*c3;				m[2][3] = 0;
	m[3][0] = 0;		m[3][1] = 0;					m[3][2] = 0;					m[3][3] = 1;
}

void sbsMatrix4::matrixToEulerAngle(double& xAng, double& yAng, double& zAng)
{
	if (m[2][0] > 0.999)
	{
		// singularity at north pole
		xAng = atan2(-m[1][2],m[1][1]);
		yAng = PI/2;
		zAng = 0;
		return;
	}
	if (m[2][0] < -0.999)
	{
		// singularity at south pole
		xAng = atan2(-m[1][2],m[1][1]);
		yAng = -PI/2;
		zAng = 0;
		return;
	}
	zAng = (atan2(m[1][0],m[0][0]))*180/PI; //rotation around z-axis
	xAng = (atan2(m[2][1],m[2][2]))*180/PI; //rotation around x-axis
	yAng = (asin(-m[2][0]))*180/PI; //rotation around y-axis
}

void sbsMatrix4::matrixFromQuaternion(double w, double x, double y, double z)
{
	double mag = sqrt(w*w + x*x + y*y + z*z);
	w/=mag;
	x/=mag;
	y/=mag;
	z/=mag;

	m[0][0] = 1-2*y*y-2*z*z;	m[0][1] = 2*x*y - 2*w*z;	m[0][2] = 2*x*z + 2*w*y;	m[0][3] = 0;
	m[1][0] = 2*y*x + 2*w*z;	m[1][1] = 1-2*x*x-2*z*z;	m[1][2] = 2*z*y - 2*w*x;	m[1][3] = 0;
	m[2][0] = 2*x*z - 2*w*y;	m[2][1] = 2*z*y + 2*w*x;	m[2][2] = 1-2*y*y - 2*x*x;	m[2][3] = 0;
	m[3][0] = 0;				m[3][1] = 0;				m[3][2] = 0;				m[3][3] = 1;
}

void sbsMatrix4::matrixToQuaternion(double& a, double& b, double& c, double& d)
{
	a = sqrt(1.0 + m[0][0] + m[1][1] + m[2][2]) / 2.0;
	b = (m[2][1] - m[1][2]) / (4.0 * a) ;
	c = (m[0][2] - m[2][0]) / (4.0 * a) ;
	d = (m[1][0] - m[0][1]) / (4.0 * a) ;
}

void sbsMatrix4::testEulerAngle(double x, double y, double z)
{
    cout << "Matrix from Euler Angle:" << x << " " << y << " " << z << endl;
	matrixFromEulerAngle(x,y,z);
	printMatrix();

    cout << "Check rotation matrix" << endl;
	sbsMatrix4 mat = getTranspose();
	mat = mat*(*this);
	mat.printMatrix();

    cout << "Matrix to Euler Angle:" << endl;
    matrixToEulerAngle(x,y,z);
	cout << "\tEuler Angle:" << x << " " << y << " " << z << endl;
}

void sbsMatrix4::testQuaternion(double w, double x, double y, double z)
{
	double mag = sqrt(w*w + x*x + y*y + z*z);
	w/=mag;
	x/=mag;
	y/=mag;
	z/=mag;

    cout << "Matrix from Quaternion: " << w << " " << x << " " << y << " " << z << endl;
	matrixFromQuaternion(w,x,y,z);
	printMatrix();

    cout << "Check rotation matrix" << endl;
	sbsMatrix4 mat = getTranspose();
	mat = mat*(*this);
	mat.printMatrix();

    cout << "Matrix to Quaternion:" << endl;
	matrixToQuaternion(w,x,y,z);
	cout << "\tQuaternion: " << w << " " << x << " " << y << " " << z << endl;
}
