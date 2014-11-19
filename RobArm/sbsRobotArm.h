#pragma once

#include "sbsCStringOperator.h"
#include "../RobVisionSys/sbsGocator.h"
#include "sbsMatrix4.h"
#include "stdio.h"
#include "sbsSocket.h"
#include "sbsLocalFrame.h"
#include "sbsPolygon3D.h"
#include "sbsPoint3D.h"

/// sbsRobotArm Class
///
/// This class communicates with the robot arm through the network.
/// It translate command into packets and transmit over the network.
/// It can receive feedback on current robot position.
class sbsRobotArm : public sbsSocket
{
    public:
        /// A public sbsPoint3D object.
		/// It contain the Euler angle.
        sbsPoint3D m_tcpEuler;

        /// A public sbsLocalFrame object.
		/// It contain the x, y and z value for the robot current position.
        sbsLocalFrame m_tcp;

		/// current joint angle
		double m_joint[6];

        /// A public sbsLocalFrame object.
		/// It contain the x, y and z value for the robot home position.
        sbsLocalFrame m_homePosition;

        /// A public sbsLocalFrame object.
		/// It contain the x, y and z value for the robot start position.
        sbsLocalFrame m_startPosition;

        /// A public sbsLocalFrame object.
		/// It contain the x, y and z value for the robot calibration position.
        sbsLocalFrame m_calibrationPosition;

        /// A public sbsLocalFrame object.
		/// It contain the x, y and z value for the robot pipe start position.
        sbsLocalFrame m_pipeStartPosition;

        /// A public sbsLocalFrame object.
		/// It contain the x, y and z value for the robot pipe end position.
        sbsLocalFrame m_pipeEndPosition;

        /// A public double variable.
		/// This variable holds the angle for the gocator sensor.
        double m_pipeOrientation;

    public:
		/// A constructor.
		///
		/// This constructor creates an sbsRobotArm object.
        sbsRobotArm(void);

        /// A destructor.
		///
		/// This destructor free the resources that the object may have.
        ~sbsRobotArm(void);

    public:
        /// This member send an command over to the robot arm to receive its current tcp position.
        void updateTCP();

        /// This member send an command over to the robot arm to receive its current joint position.
        void updateJoint();

        /// This member stores the current robot TCP position with the string received from robot arm.
		///
		///@param str: string receive from robot arm
        void paserTCP(string str);

		/// This member stores the current robot joint position with the string received from robot arm.
		///
		///@param str: string receive from robot arm
		void paserJoint(string str);

        /// Not implemented
        void moveTCP(double x, double y, double z);

        /// Not implemented
        void renderTCP();

        /// Not implemented
        void printTCP();

        /// This member sets the value for home position.
        void recordHomePosition();

        /// This member send a command to robot arm to move to home position.
        void moveHome();

        /// This member send a command to robot arm to move to start position.
        void moveStart();

        /// This member send a command to robot arm to move to calibration position.
        void moveCalbrationPos();

        /// This member return a sbsPolygon3D with the robot arm position.
        ///
        ///@param poly: shared_ptr that holds the laser polygon
        ///@return a polygon which holds the robot arm position
        sbsPolygon3D polygonFromLaser(boost::shared_ptr<sbsPolygon3D> poly);

        /// This member send a command to robot arm to rotate to the position in the parameter.
        ///
        ///@param a: v1 value
		///@param b: v2 value
		///@param c: v3 value
		///@param d: v4 value
		///@param e: v5 value
		///@param f: v6 value
        void rotateJoint(double a, double b, double c, double d,double e,double f);

		/// This member send a command to robot arm to rotate to the position in the parameter.
        ///
        ///@param a: v1 value
		///@param b: v2 value
		///@param c: v3 value
		///@param d: v4 value
		///@param e: v5 value
		///@param f: v6 value
        void rotateJointToTarget(double a, double b, double c, double d,double e,double f);

        /// This member send a command to robot arm to rotate to the position in the parameter with constant speed for angular scanning.
        ///
        ///@param a: v1 value
		///@param b: v2 value
		///@param c: v3 value
		///@param d: v4 value
		///@param e: v5 value
		///@param f: v6 value
		void rotateJointWithConstantSpeed(int noOfDegree, int noOfScan);

		/// This member sends a command to move the robot arm to position with offset of x, y and z.
		///
		///@param x: x value
		///@param y: y value
		///@param z: z value
        void move(double x, double y, double z);
		void move(double x, double y, double z, double a, double b, double c );

		/// This member sends a command to move the robot arm to position with angular offset of a, b and c slowly.
		///
		///@param a: a value
		///@param b: b value
		///@param c: c value
		void moveR( double a, double b, double c );
		/// This member sends a command to move the robot arm to position with offset of x, y and z slowly.
		///
		///@param x: x value
		///@param y: y value
		///@param z: z value	
		void moveS( double x, double y, double z );

		/// This member sends a command to move the robot arm to position of x, y and z.
		///
		///@param x: x value
		///@param y: y value
		///@param z: z value
		void moveTo(double x, double y, double z);
		void moveTo(double x, double y, double z, double a, double b, double c );

};
