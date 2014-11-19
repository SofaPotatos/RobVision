#include "sbsRobotArm.h"

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsRobotArm::sbsRobotArm()
{
	m_homePosition.o.setXYZ(302,0,558);
	//m_calibrationPosition.o.setXYZ(290.8,-337.7,507.5);//sphere
	m_calibrationPosition.o.setXYZ(290.8,-337.7,377.5);
	m_pipeOrientation = 45;
}

sbsRobotArm::~sbsRobotArm()
{
}

/*******************************************************************************
* Public Method
********************************************************************************/

void sbsRobotArm::updateTCP()
{
    boost::shared_ptr<string> temp(new string("0"));
	string str = getOneMessage(temp);
	paserTCP(str);
}

void sbsRobotArm::updateJoint()
{
    boost::shared_ptr<string> temp(new string("1"));
	string str = getOneMessage(temp);
	paserJoint(str);
	cout << "Joint: " << m_joint[0] << " " << m_joint[1] << " " << m_joint[2] << " " << m_joint[3] << " " << m_joint[4] << " "
		 << m_joint[5] << endl;
}

void sbsRobotArm::paserJoint(string str)
{
	str = sbsCStringOperator::stringBetween(str,"(",")");
	vector<string> values = sbsCStringOperator::stringTrimming(str,",");
	if (values.size()<6)
	{
		cout << "No enough values " << values.size() << endl;
		cout << "input: " << str << endl;
		return;
	}
	
	m_joint[0] = sbsCStringOperator::stringToDouble(values[0]);
	m_joint[1] = sbsCStringOperator::stringToDouble(values[1]);
	m_joint[2] = sbsCStringOperator::stringToDouble(values[2]);
	m_joint[3] = sbsCStringOperator::stringToDouble(values[3]);
	m_joint[4] = sbsCStringOperator::stringToDouble(values[4]);
	m_joint[5] = sbsCStringOperator::stringToDouble(values[5]);

}

void sbsRobotArm::paserTCP(string str)
{
	str = sbsCStringOperator::stringBetween(str,"(",")");
	vector<string> values = sbsCStringOperator::stringTrimming(str,",");
	if (values.size()<6)
	{
		cout << "No enough values " << values.size() << endl;
		cout << "input: " << str << endl;
		return;
	}

	m_tcp.o.x = sbsCStringOperator::stringToDouble(values[0]);
	m_tcp.o.y = sbsCStringOperator::stringToDouble(values[1]);
	m_tcp.o.z = sbsCStringOperator::stringToDouble(values[2]);

	m_tcp.x.setXYZ(1,0,0);
	m_tcp.y.setXYZ(0,1,0);
	m_tcp.z.setXYZ(0,0,1);

	double a = sbsCStringOperator::stringToDouble(values[3]);
	double b = sbsCStringOperator::stringToDouble(values[4]);
	double c = sbsCStringOperator::stringToDouble(values[5]);
	double r = sbsPI/180;

	a*=r;
	b*=r;
	c*=r;

	sbsMatrix4 mat;
	mat.setRotateMatrix(a,b,c);
	m_tcp.rotateFrame(mat);
	m_tcpEuler.setXYZ(a,b,c);
}

void sbsRobotArm::moveTCP( double x, double y, double z )
{
}

void sbsRobotArm::renderTCP()
{
}

void sbsRobotArm::printTCP()
{
}

void sbsRobotArm::recordHomePosition()
{
	updateTCP();
	m_homePosition = m_tcp;
	m_homePosition.o.setXYZ(302,0,558);
	//100,120,-108
	m_startPosition = m_homePosition;
	m_startPosition.o.x += 100;
	m_startPosition.o.y += 120;
	m_startPosition.o.z -= 192;
}

void sbsRobotArm::moveHome()
{
	updateTCP();
	sbsPoint3D dp = m_homePosition.o - m_tcp.o;
	move(dp.x,dp.y,dp.z);
}

void sbsRobotArm::moveStart()
{
	return;
	updateTCP();
	sbsPoint3D dp = m_startPosition.o - m_tcp.o;
	move(dp.x,dp.y,dp.z);
}

void sbsRobotArm::moveCalbrationPos()
{
	updateTCP();
	sbsPoint3D dp = m_calibrationPosition.o - m_tcp.o;
	move(dp.x,dp.y,dp.z);
}

sbsPolygon3D sbsRobotArm::polygonFromLaser(boost::shared_ptr<sbsPolygon3D> poly)
{
	sbsPolygon3D rpoly=*poly;
	for (size_t i = 0; i < (*poly).size(); i++)
	{
		sbsPoint3D& p = rpoly[i];
        if (p.z <= sbsGocator::m_threathhole)
		{
			p.setInfinite();
			continue;
		}
		p.z *= -1;
		p = m_tcp.getPos(p);
		p.z -= (558-192);
	}

	return rpoly;
}

void sbsRobotArm::rotateJoint( double a, double b, double c, double d,double e,double f )
{
	char buffer[256];
    sprintf(buffer,"3 %.3f %.3f %.3f %.3f %.3f %.3f", a, b, c, d, e, f);
	boost::shared_ptr<string> msg(new string(buffer));
	string str = getOneMessage(msg);

}

void sbsRobotArm::rotateJointWithConstantSpeed(int noOfDegree, int noOfScan)
{
	char buffer[256];
    sprintf(buffer,"8 %.3f %.3f %.3f %.3f %.3f %.3f", 0, 0, 0, 0, 0, (double)noOfDegree);
	boost::shared_ptr<string> msg(new string(buffer));
	sendOneMessage(msg);
}


void sbsRobotArm::rotateJointToTarget( double a, double b, double c, double d,double e,double f )
{
	updateJoint();

	a-=m_joint[0];
	b-=m_joint[1];
	c-=m_joint[2];
	d-=m_joint[3];
	e-=m_joint[4];
	f-=m_joint[5];

	rotateJoint(a, b, c, d, e, f);
}

void sbsRobotArm::move( double x, double y, double z )
{
	char buffer[256];
    sprintf(buffer,"2 %.3f %.3f %.3f", x, y, z);
    //string temp = buffer;
	boost::shared_ptr<string> msg(new string(buffer));
	string str = getOneMessage(msg);
	paserTCP(str);
}

void sbsRobotArm::move( double x, double y, double z, double a, double b, double c )
{
	char buffer[256];
	sprintf(buffer,"4 %.3f %.3f %.3f %.3f %.3f %.3f", x, y, z, a, b, c);
	boost::shared_ptr<string> msg(new string(buffer));
	string str = getOneMessage(msg);
	paserTCP(str);
}

void sbsRobotArm::moveR( double a, double b, double c )
{
	char buffer[256];
	sprintf(buffer,"4 0 0 0 %.3f %.3f %.3f", a, b, c);
	std::cout<<buffer<<endl;
	boost::shared_ptr<string> msg(new string(buffer));
	string str = getOneMessage(msg);
	paserTCP(str);
}

void sbsRobotArm::moveS( double x, double y, double z )
{
	char buffer[256];
    sprintf(buffer,"7 %.3f %.3f %.3f", x, y, z);
	boost::shared_ptr<string> msg(new string(buffer));
	string str = getOneMessage(msg);
	paserTCP(str);
}

void sbsRobotArm::moveTo(double x, double y, double z)
{
	updateTCP();
	x-=m_tcp.o.x;
    y-=m_tcp.o.y;
	z-=m_tcp.o.z;
	move(x, y, z);
}

void sbsRobotArm::moveTo(double x, double y, double z, double a, double b, double c )
{
	double da,db,dc,dx,dy,dz,wdx,wdy,wdz;
	sbsMatrix4 cTCP;
	sbsMatrix4 tTCP;
	sbsMatrix4 invcTCP;
	sbsMatrix4 dTCP;
	updateTCP();
	cTCP.matrixFromEulerAngle(m_tcpEuler.x*180/sbsPI, m_tcpEuler.y*180/sbsPI, m_tcpEuler.z*180/sbsPI);
	tTCP.matrixFromEulerAngle(a, b, c);
	invcTCP=cTCP.getInverse3();
	dTCP=invcTCP*tTCP;
	dTCP.matrixToEulerAngle(da, db, dc);
	wdx=x-m_tcp.o.x;
	wdy=y-m_tcp.o.y;
	wdz=z-m_tcp.o.z;
	dx=invcTCP(0,0)*wdx+invcTCP(0,1)*wdy+invcTCP(0,2)*wdz;
	dy=invcTCP(1,0)*wdx+invcTCP(1,1)*wdy+invcTCP(1,2)*wdz;
	dz=invcTCP(2,0)*wdx+invcTCP(2,1)*wdy+invcTCP(2,2)*wdz;
	move(dx, dy, dz, da, db, dc); //equal to move(wdx,wdy,wdz);moveR(da,0,0);moveR(0,db,0);moveR(0,0,dc);
}