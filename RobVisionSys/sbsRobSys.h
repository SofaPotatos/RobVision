#pragma once

#include "../RobArm/sbsRobotArm.h"
#include "sbsGocator.h"
#include "../RobArm/sbsPolygon3D.h"
#include "sbsProfile.h"

struct position{
	char name[100];
	double joint_1, joint_2, joint_3, joint_4, joint_5, joint_6;
};

class sbsRobSys
{
public:
	sbsRobSys(void);
	~sbsRobSys(void);
	void BeginCapture();
	bool AddOneProfile(bool autoAdjustCenter = false,bool addOnlyValid = false);
	bool AddOneProfile(sbsProfile poly,bool autoAdjustCenter,bool addOnlyValid = false);
	void SwitchSimulation();
	void SetSimulation();
	void SetRealScan();
	sbsProfile GetOneProfile();
	sbsProfile GenerateVirtualProfile();
	void RenderProfiles();
	void RenderReconstructedSurface();
	void AutoSaveProfile();
	void SaveProfile();
	void SaveProfile(string filename);
	void LoadProfile();
	void LoadProfile(string filename);
	void CompareProfiles();
	void CheckProfileType(sbsProfile& ps);
	void AddOneValideProfile();
	bool AddNextValideProfile();
	void SurfaceFromProfile();
	void RemoveLongEdge(double len);
	void CalibrationDataByTCPTranslate(char* filename);
	void AutoCalibration();
	void CalXYOffsetForCalibration(vector<double>& xoffset, vector<double>& yoffset);
	void CalibrationDataByTCPRotate(string filename);
	void CalAngleForCalibration(vector<double>& ang);
	void LoadCalibrationData(string filename, sbsPoint3DVector& tcpPosition, sbsPoint3DVector& tcpOrientation, sbsPoint3DVector& localDiskCenter);
	sbsMatrix4 CalibrationRotation(sbsPoint3DVector tcpPosition, sbsPoint3DVector tcpOrientation, sbsPoint3DVector localDiskCenter);
public:
	vector<position> recorded_position;
	sbsRobotArm m_robot;
	double m_minimalZ;
	sbsGocator m_laser;
	bool b_simulation;
	bool b_profileCurve;
	bool b_profilePoint;
	bool b_hidePart;
	vector<sbsProfile> m_profiles;
	double m_torDeg;
	double m_torLen;
	sbsPoint3D m_searchStep;


public:
	sbsPoint3DVector m_robPosition;
	sbsPoint3DVector m_robOrientation;
	sbsPolygon3DVector m_laserPolygon;

public:

	void scanPipe( double* v );
	void scanPipe( int num );
	void performMultipleScan(char* filename, char* savefile);

	void linearScan(sbsPoint3D original, sbsPoint3D target, int noOfScan);
	void linearScan(double v1, double v2, double v3, double v4, double v5, double v6, 
				    double x, double y, double z, int noOfScan);
	void linearScan(double v1, double v2, double v3, double v4, double v5, double v6, 
						   double x, double y, double z, int noOfScan, double waittime);
	void DynamicLinearScan(double v1, double v2, double v3, double v4, double v5, double v6, 
						   double x, double y, double z, int noOfScan);
	void viewpointScan(char* filename);
	void multipleLinearScan(char* filename, int noOfScan);
	void AngularScan(int noOfDegree, int noOfScan);
	void DynamicAngularScan(int noOfDegree, int noOfScan);
	//void sphereLinearScan(char* filename, char* savefile)
	
	void connectLaserAsynchronousMode();
	bool setExposure(double exp);
	bool setFrameRate(double fr);
	double getExposure();
	double getMaxExposureRange();
	double getMinExposureRange();
	bool isValidExposure(double exp);
	void disconnectLaser();

	void addOnePolygon();
	void clearPolygons();
	int getPloygonsize();
	//Generate 2 save files, 1 processed, 1 raw
	void savePolygons(char* filename, char* option);

	void moveJointBy(double j1, double j2, double j3, double j4, double j5, double j6);
	void moveJointTo(double j1, double j2, double j3, double j4, double j5, double j6);
	void updateJoint();
	void moveTCPBy(double x, double y, double z);
	void moveTCPTo(double x, double y, double z);
	void updateTCP();
	void moveToPosition(position pos);
	void loadPositionFromFile(char* filename);
	void printListOfPosition();
	void robotAccuracyTest(position pos[4], char* filename, int noOfStep);

};

