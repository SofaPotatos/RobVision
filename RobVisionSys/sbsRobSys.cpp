#include "sbsRobSys.h"



sbsRobSys::sbsRobSys()
{
	b_simulation = false;
	SetRealScan();
	b_profileCurve = false;
	b_profilePoint = false;
	b_hidePart = false;
	m_minimalZ = 5;
}

sbsRobSys::~sbsRobSys()
{
}

void sbsRobSys::BeginCapture()
{
	 m_profiles.clear();
}

bool sbsRobSys::AddOneProfile(bool autoAdjustCenter,bool addOnlyValid)
{
	if (b_simulation)
	{
		return false;
	}
	else
	{
		return AddOneProfile(GetOneProfile(),autoAdjustCenter,addOnlyValid);
	}
}

bool sbsRobSys::AddOneProfile(sbsProfile ps,bool autoAdjustCenter,bool addOnlyValid)
{
	if (ps.m_robotPoly.size()==0)
	{
		return false;
	}

	CheckProfileType(ps);

	if (addOnlyValid && ps.m_profileType == 1)
	{
		return false;
	}

	m_profiles.push_back(ps);
	return true;
}

void sbsRobSys::SwitchSimulation()
{
	b_simulation = !b_simulation;
	if (b_simulation)
	{
		SetSimulation();
	}
	else
	{
		SetRealScan();
	}
}

void sbsRobSys::SetSimulation()
{
	m_robot.m_deviceIP = "127.0.0.1";
	m_robot.m_devicePort = 1025;
	m_torDeg = 45;
	m_torLen = 10;
}

void sbsRobSys::SetRealScan()
{
	m_robot.m_deviceIP = "192.168.125.1";
	m_robot.m_devicePort = 1025;
	m_torDeg = 45;
	m_torLen = 5;
}

// get one profile from the laser scanner
sbsProfile sbsRobSys::GetOneProfile()
{
	sbsProfile profile;

	for (int i = 0; i < sbsProfile::m_numProfileScan; i++)
	{
		boost::shared_ptr<sbsPolygon3D> poly(new sbsPolygon3D);
		*poly = m_laser.GetLaserProfile();
		profile.m_laserPolys.push_back(*poly);
		*poly = m_robot.polygonFromLaser(poly);
		profile.m_robotPolys.push_back(*poly);
	}
	profile.finalizePolygon();

	return profile;
}

sbsProfile sbsRobSys::GenerateVirtualProfile()
{
	 sbsProfile p;
	 return p;
}

void sbsRobSys::RenderProfiles()
{
}

void sbsRobSys::AutoSaveProfile()
{
}

void sbsRobSys::SaveProfile()
{
}

void sbsRobSys::SaveProfile(string filename)
{
}

void sbsRobSys::LoadProfile()
{
}

void sbsRobSys::LoadProfile(string filename)
{
}

void sbsRobSys::CompareProfiles()
{
}

void sbsRobSys::CheckProfileType(sbsProfile& ps)
{
	ps.m_profileType = 1;
	for (size_t i = 0; i < ps.m_robotPoly.size(); i++)
	{
		if (ps.m_robotPoly[i].isInfinity())
		{
			continue;
		}
		if (ps.m_robotPoly[i].z >= m_minimalZ)
		{
			ps.m_profileType = 2;
			return;
		}
	}
}

void sbsRobSys::AddOneValideProfile()
{
	if (m_searchStep.length()==0)
	{
		return;
	}
	int num = 0;
	m_robot.move(m_searchStep.x,m_searchStep.y,m_searchStep.z);
	while (!AddOneProfile(false,true))
	{
		num++;
		if (num>=100)
		{
			return;
		}
		m_robot.move(m_searchStep.x,m_searchStep.y,m_searchStep.z);
	}
}

bool sbsRobSys::AddNextValideProfile()
{
	m_robot.move(m_searchStep.x,m_searchStep.y,m_searchStep.z);
	if (AddOneProfile(false,true))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void sbsRobSys::RenderReconstructedSurface()
{
}

void sbsRobSys::SurfaceFromProfile()
{
}

void sbsRobSys::RemoveLongEdge(double len)
{
}

void sbsRobSys::CalibrationDataByTCPRotate(string filename)
{
}

void sbsRobSys::CalibrationDataByTCPTranslate(char* filename)
{
	//string s = "data_only_";
	//char temp[256];
	//s.copy(temp, s.length(), 0);
	//temp[s.length()] = '\0';
	//strcat(temp, filename);
	// translate
	clearPolygons();
	vector<double> xoffset,yoffset;
	CalXYOffsetForCalibration(xoffset,yoffset);
	double allx=0;
	double ally=0;
	for (size_t i = 0; i < xoffset.size(); i++)
	{
		allx+=xoffset[i];
		ally+=yoffset[i];

		m_robot.move(xoffset[i],yoffset[i],0);
		m_robot.updateTCP();
		boost::this_thread::sleep(boost::posix_time::seconds(2));
		addOnePolygon();		
	}

	m_robot.move(-allx,-ally,0);

	savePolygons(filename, NULL);
}

void sbsRobSys::AutoCalibration()
{
}

void sbsRobSys::CalXYOffsetForCalibration(vector<double>& xoffset, vector<double>& yoffset)
{
	xoffset.clear();
	yoffset.clear();

	double cx = 0;
	double cy = 0;
	for (int i = 0; i < 3; i++)
	{
		double x = -30;
		for (int j = 0; j < 5; j++)
		{
			double y = i*10;
			x+=j*3;

			xoffset.push_back(x-cx);
			yoffset.push_back(y-cy);
			cx = x;
			cy = y;
		}
	}
}

void sbsRobSys::CalAngleForCalibration(vector<double>& ang)
{
	ang.clear();
	ang.push_back(-50);
	for (int i = 0; i < 10; i++)
	{
		ang.push_back(10);
	}
}

void sbsRobSys::LoadCalibrationData(string filename, sbsPoint3DVector& tcpPosition, sbsPoint3DVector& tcpOrientation, sbsPoint3DVector& localDiskCenter)
{
}

sbsMatrix4 sbsRobSys::CalibrationRotation(sbsPoint3DVector tcpPosition, sbsPoint3DVector tcpOrientation, sbsPoint3DVector localDiskCenter)
{
	sbsMatrix4 mat;
	return mat;
}


void sbsRobSys::performMultipleScan(char* filename, char* savefile)
{
	double v[6];
	FILE* f = NULL;
	f = fopen(filename,"r");
	if (f == NULL)
	{
		cout << "Error opening file\n";
		return;
	}
	clearPolygons();
	while(fscanf (f, "%lf,%lf,%lf,%lf,%lf,%lf", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5]) != EOF)
	{
		m_robot.rotateJointToTarget(v[0], v[1], v[2], v[3], v[4], v[5]);
		boost::this_thread::sleep(boost::posix_time::seconds(2));
		m_robot.updateTCP();
		addOnePolygon();
	}
	savePolygons(savefile, NULL);
    fclose(f);
}

void sbsRobSys::linearScan(double v1, double v2, double v3, double v4, double v5, double v6, 
						   double x, double y, double z, int noOfScan)
{
	moveJointTo(v1, v2, v3, v4, v5, v6);
	sbsPoint3D original, target;
	target.setXYZ(x,y,z);
	updateTCP();
	original =  m_robot.m_tcp.o;
	linearScan(original, target, noOfScan);
}

void sbsRobSys::AngularScan(int noOfDegree, int noOfScan)
{
	char savefile[256];
	double rotatedegree=(double)noOfDegree/(double)noOfScan;
	clearPolygons();
	m_robot.updateTCP();
	addOnePolygon();
	for (int j = 1; j < noOfScan; j++)
	{
		m_robot.rotateJoint(0,0,0,0,0,rotatedegree);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		m_robot.updateTCP();
		addOnePolygon();
	}
	sprintf(savefile,"position_AS_Dg%d_Ns%d.csv", noOfDegree,noOfScan);
	savePolygons(savefile, NULL);
	m_robot.rotateJoint(0,0,0,0,0,-1.0*noOfDegree);
}

void sbsRobSys::DynamicAngularScan(int noOfDegree, int noOfScan)
{
	char savefile[256];
	char buffer[256];
	clock_t t;
	clearPolygons();
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	m_robot.updateTCP();
    sprintf(buffer,"8 %.3f %.3f %.3f %.3f %.3f %.3f", 0.0, 0.0, 0.0, 0.0, 0.0, (float)noOfDegree);
	boost::shared_ptr<string> msg(new string(buffer));
	string temp;
	t = clock();
	if(m_robot.connect())
		if(m_robot.sendMessage(*msg))
		{
			for (int i = 0; i < noOfScan; i++)
			{
				//t = clock();
				addOnePolygon();
				//t = clock() - t;
				//printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
				//boost::this_thread::sleep(boost::posix_time::microseconds(100));
			}
			temp = m_robot.getMessage();
			t = clock() - t;
			printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
		    m_robot.disconnect();
			sprintf(savefile,"position_NAS_Dg%d_Ns%d.csv", noOfDegree,noOfScan);
			savePolygons(savefile, NULL);
			m_robot.rotateJoint(0,0,0,0,0,-1.0*noOfDegree);
		}
		else
		{
			cout << "Error: error occurs during dynamic angular scan" << endl;
		}
}

void sbsRobSys::linearScan(sbsPoint3D original, sbsPoint3D target, int noOfScan)
{
	sbsPoint3D dir = target - original;
	if (noOfScan <= 1)
	{
		cout << "Error: The number of scans needs to be more than 1." << endl;
		return;
	}
	
	sbsPoint3D step = dir/(noOfScan-1); //sbsPoint3D step = dir/(0.33*(noOfScan-1));
	m_robot.updateTCP();
	addOnePolygon();

	for (int i = 1; i < noOfScan; i++)
	{
		m_robot.move(step.x,step.y,step.z);
		boost::this_thread::sleep(boost::posix_time::seconds(5));
		m_robot.updateTCP();
		addOnePolygon();
	}
}


void sbsRobSys::linearScan(double v1, double v2, double v3, double v4, double v5, double v6, 
						   double x, double y, double z, int noOfScan, double waittime)
{
	char savefile[256];
	char buffer[256];
	//clock_t t;
	moveJointTo(v1, v2, v3, v4, v5, v6);
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	sbsPoint3D original, target;
	target.setXYZ(x,y,z);
	updateTCP();
	addOnePolygon();
	original =  m_robot.m_tcp.o;
	sbsPoint3D dir = target - original;

	clearPolygons();
	if (noOfScan <= 1)
	{
		cout << "Error: The number of scans needs to be more than 1." << endl;
		return;
	}
	sbsPoint3D step = dir/(noOfScan-1); //sbsPoint3D step = dir/(0.33*(noOfScan-1));
	m_robot.updateTCP();
	addOnePolygon();

	for (int i = 1; i < noOfScan; i++)
	{
		m_robot.moveS(step.x,step.y,step.z);
		boost::this_thread::sleep(boost::posix_time::seconds(waittime));
		m_robot.updateTCP();
		addOnePolygon();
	}
	//sprintf(savefile,"position_Linear_S%f_%d.csv",waittime, noOfScan);
	sprintf(savefile,"position_Linear_%d.csv",noOfScan);
	savePolygons(savefile, NULL);
}

void sbsRobSys::DynamicLinearScan(double v1, double v2, double v3, double v4, double v5, double v6, 
						   double x, double y, double z, int noOfScan)
{
	char savefile[256];
	char buffer[256];
	clock_t t;
	clearPolygons();
	moveJointTo(v1, v2, v3, v4, v5, v6);
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	sbsPoint3D original, target;
	target.setXYZ(x,y,z);
	updateTCP();
	addOnePolygon();
	original =  m_robot.m_tcp.o;
	sbsPoint3D dir = target - original;

	if (noOfScan <= 1)
	{
		cout << "Error: The number of scans needs to be more than 1." << endl;
		return;
	}
	sprintf(buffer,"7 %.3f %.3f %.3f", dir.x, dir.y, dir.z);
	boost::shared_ptr<string> msg(new string(buffer));
	string temp;
	t = clock();
	if(m_robot.connect())
		if(m_robot.sendMessage(*msg))
		{
			for (int i = 0; i < noOfScan; i++)
			{
				addOnePolygon();
				printf ("One profile taken: %d.\n",i);
			}
			temp = m_robot.getMessage();
			t = clock() - t;
			printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
		    m_robot.disconnect();
			sprintf(savefile,"position_DynamicLinear_%d.csv", noOfScan);
			savePolygons(savefile, NULL);
		}
		else
		{
			cout << "Error: error occurs during dynamic linear scan" << endl;
		}
}


//The method open a csv file and load the value in the following format
//joint1,joint2,joint3,joint4,joint5,joint6,x,y,z
//The method construction the starting and the target object and run them with linearScan

void sbsRobSys::viewpointScan(char* filename)
{
	int count = 0;
	double v[6];
	double x, y, z, a ,b ,c;
	sbsPoint3D original;
	char savefile[256];

	FILE* f = NULL;
	f = fopen(filename,"r");
	
	if (f == NULL)
	{
		cout << "Error opening file\n";
		return;
	}
	if(fscanf (f, "%lf,%lf,%lf,%lf,%lf,%lf", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5]) != EOF)
	{
		clearPolygons();
		m_robot.rotateJointToTarget(v[0], v[1], v[2], v[3], v[4], v[5]);
	}
	while(fscanf (f, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &x, &y, &z, &a, &b, &c) != EOF)
	{
		count++;
		m_robot.moveTo(x,y,z,a,b,c);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		m_robot.updateTCP();
		addOnePolygon();
	}
	sprintf(savefile,"ViewPointScan_%d.csv", count);
	savePolygons(savefile, NULL);
	fclose(f);
}


void sbsRobSys::multipleLinearScan(char* filename, int noOfScan)
{
	int count = 0;
	double v[6];
	double x, y, z;
	sbsPoint3D original;
	sbsPoint3D target;
	char savefile[256];

	FILE* f = NULL;
	f = fopen(filename,"r");
	
	if (f == NULL)
	{
		cout << "Error opening file\n";
		return;
	}

	while(fscanf (f, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &x, &y, &z) != EOF)
	{
		count++;
		
		clearPolygons();

		m_robot.rotateJointToTarget(v[0], v[1], v[2], v[3], v[4], v[5]);
		m_robot.updateTCP();

		original =  m_robot.m_tcp.o;
		target.setXYZ(x, y, z);
		linearScan(original, target, noOfScan);
		
		sprintf(savefile,"position_%d_%d.csv", count, noOfScan);
		savePolygons(savefile, NULL);
	}
	fclose(f);

}

void sbsRobSys::connectLaserAsynchronousMode()
{
	m_laser.tryAsyncConnect();
}

bool sbsRobSys::setExposure(double exp)
{
	if(isValidExposure(exp))
	{
		return m_laser.setExposure(exp);
	}
	return false;
}

bool sbsRobSys::setFrameRate(double fr)
{
	if((fr>0)&&(fr<=200))
	{
		return m_laser.setFrameRate(fr);
	}

	return false;
}

double sbsRobSys::getExposure()
{
	return m_laser.getExposure();
}

double sbsRobSys::getMaxExposureRange()
{
	double max, min;
	if(m_laser.getExposureRange(min, max))
	{	
		return max;
	}
	cout << "Laser not connected." << endl;
	return 0;
}

double sbsRobSys::getMinExposureRange()
{
	double max, min;
	if(m_laser.getExposureRange(min, max))
	{	
		return min;
	}
	cout << "Laser not connected." << endl;
	return 0;
}

bool sbsRobSys::isValidExposure(double exp)
{
	if((exp >= getMinExposureRange())&&(exp <= getMaxExposureRange()))
	{
		return true;
	}
	return false;
}

void sbsRobSys::disconnectLaser()
{
	m_laser.disconnect();
}

void sbsRobSys::addOnePolygon()
{
	m_robPosition.push_back(m_robot.m_tcp.o);
	m_robOrientation.push_back(m_robot.m_tcpEuler);

	sbsPolygon3D poly = m_laser.GetLaserProfile();
	m_laserPolygon.push_back(poly);
}

void sbsRobSys::clearPolygons()
{
	m_robPosition.clear();
	m_robOrientation.clear();
	m_laserPolygon.clear();
}

int sbsRobSys::getPloygonsize()
{
	return m_robPosition.size();
}

void sbsRobSys::savePolygons(char* filename, char* option)
{

	char temp[256];
	sprintf(temp,"%RAW_%s", filename);

	unsigned int i, j, k;

	FILE* processed = NULL;
	FILE* raw = NULL;

	if (option == NULL)
	{
		option = "w";
	}

	processed = fopen(filename,option);
	raw = fopen(temp, option);

	if (processed == NULL)
	{
		printf("Error: Opening file\n");
		return;
	}
	if (raw == NULL)
	{
		printf("Error: Opening file\n");
		return;
	}

	for (k=0; k < m_laserPolygon.size(); k++)
	{
		fprintf(processed, "%f,%f,%f,",m_robPosition[k].x ,m_robPosition[k].y, m_robPosition[k].z); 
		fprintf(processed, "%f,%f,%f\n",m_robOrientation[k].x ,m_robOrientation[k].y, m_robOrientation[k].z);
		fprintf(raw, "%f,%f,%f,",m_robPosition[k].x ,m_robPosition[k].y, m_robPosition[k].z); 
		fprintf(raw, "%f,%f,%f\n",m_robOrientation[k].x ,m_robOrientation[k].y, m_robOrientation[k].z);
		for (i = 0; i < m_laserPolygon[k].size(); ++i)
		{
			if (m_laserPolygon[k].m_points[i].z > -262.0)
			{
				fprintf(processed, "%f", m_laserPolygon[k].m_points[i].x);
				if (i < m_laserPolygon[k].size())
				{
					fprintf(processed, ",");
				}
			}
			fprintf(raw, "%f", m_laserPolygon[k].m_points[i].x);
			if (i < m_laserPolygon[k].size())
			{
				fprintf(raw, ",");
			}
		}
		fprintf(raw, "\n");
		fprintf(processed, "\n");
		for (j = 0; j < m_laserPolygon[k].size(); ++j)
		{
			if (m_laserPolygon[k].m_points[j].z > -262.0)
			{
				fprintf(processed, "%f", m_laserPolygon[k].m_points[j].z);
				if (j < m_laserPolygon[k].size())
				{
					fprintf(processed, ",");
				}
			}
			fprintf(raw, "%f", m_laserPolygon[k].m_points[j].z);
			if (j < m_laserPolygon[k].size())
			{
				fprintf(raw, ",");
			}
		}
		fprintf(raw, "\n");
		fprintf(processed, "\n");
	}

	fclose(raw);
	fclose(processed);
}

void sbsRobSys::moveJointBy(double j1, double j2, double j3, double j4, double j5, double j6)
{
	m_robot.rotateJoint(j1, j2, j3, j4, j5, j6);
}

void sbsRobSys::moveJointTo(double j1, double j2, double j3, double j4, double j5, double j6)
{
	m_robot.rotateJointToTarget(j1, j2, j3, j4, j5, j6);
}

void sbsRobSys::updateJoint()
{
	m_robot.updateJoint();
}

void sbsRobSys::moveTCPBy(double x, double y, double z)
{
	m_robot.move(x, y, z);
}

void sbsRobSys::moveTCPTo(double x, double y, double z)
{
	m_robot.moveTo(x, y, z);
}

void sbsRobSys::updateTCP()
{
	m_robot.updateTCP();
}

void sbsRobSys::moveToPosition(position pos)
{
	moveJointTo(pos.joint_1, pos.joint_2, pos.joint_3, pos.joint_4,pos.joint_5, pos.joint_6);
}

void sbsRobSys::loadPositionFromFile(char* filename)
{
	FILE* file = NULL;
	file = fopen(filename,"r");
	position temp;
	
	if (file == NULL)
	{
		cout << "Error opening file\n";
		return;
	}

	while(fscanf(file, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf\n", temp.name, &temp.joint_1, &temp.joint_2, &temp.joint_3, &temp.joint_4
		, &temp.joint_5, &temp.joint_6) != EOF)
	{
		recorded_position.push_back(temp);
	}
    fclose(file);
}

void sbsRobSys::printListOfPosition()
{
	for(unsigned int i=0; i < recorded_position.size(); i++)
	{
		cout << "\t" << i << ": " << recorded_position[i].name << endl;
	}
}


//Methods for scanning pipe, hardcode

void sbsRobSys::scanPipe( int num )
{
	double v[10];
	v[9] = num;

	 //  0-5 starting joint
	v[0] = 32.9;
	v[1] = 40.1;
	v[2] = -55;
	v[3] = 0.0;
	v[4] = 104.9;
	v[5] = -4.1;

	//6-8 target
	v[6] = 440.9;
	v[7] = 128.4;
	v[8] = 569.9;
	scanPipe(v);
}
void sbsRobSys::scanPipe( double* v )
{
	char filename[256];
	int num = v[9];
	clock_t t1, t2;
	double totaltime;
	int temp;

	if (num<=2)
	{
		num = 3;
	}

	clearPolygons();

	m_robot.moveHome();
	m_robot.rotateJoint(v[0],v[1],v[2],v[3],v[4]-90,v[5]);
	boost::this_thread::sleep(boost::posix_time::seconds(2));
	m_robot.updateTCP();
	addOnePolygon();

	sbsPoint3D original = m_robot.m_tcp.o;
	sbsPoint3D target(v[6],v[7],v[8]);
	sbsPoint3D dir = target - original;
	sbsPoint3D step = dir / (v[9]-1);
	t1 = clock();
	for (int i = 1; i < num; i++)
	{
		m_robot.move(step.x,step.y,step.z);
		boost::this_thread::sleep(boost::posix_time::seconds(2));
		m_robot.updateTCP();
		addOnePolygon();
	}
	t2 = clock();
	totaltime = (double)(t2-t1)/ CLOCKS_PER_SEC;
	temp = totaltime;
	sprintf(filename,"pipe_%d_%d.csv", num, temp);
	savePolygons(filename, NULL);
	m_robot.moveHome();
}

void sbsRobSys::robotAccuracyTest(position pos[5], 
							   char* filename, int noOfStep)
{
	vector<double> temp[30];
	position step;
	moveToPosition(pos[0]);

	moveJointTo(pos[0].joint_1, pos[0].joint_2, pos[0].joint_3, pos[0].joint_4, pos[0].joint_5, pos[0].joint_6);
	
	for (int i = 0; i<4; i++)
	{
		step.joint_1 = (pos[i+1].joint_1-pos[i].joint_1)/noOfStep;
		step.joint_2 = (pos[i+1].joint_2-pos[i].joint_2)/noOfStep;
		step.joint_3 = (pos[i+1].joint_3-pos[i].joint_3)/noOfStep;
		step.joint_4 = (pos[i+1].joint_4-pos[i].joint_4)/noOfStep;
		step.joint_5 = (pos[i+1].joint_5-pos[i].joint_5)/noOfStep;
		step.joint_6 = (pos[i+1].joint_6-pos[i].joint_6)/noOfStep;
		for(int j = 0; j < noOfStep; j++)
		{
			updateJoint();
			updateTCP();
			temp[0].push_back(m_robot.m_joint[0]);
			temp[1].push_back(m_robot.m_joint[1]);
			temp[2].push_back(m_robot.m_joint[2]);
			temp[3].push_back(m_robot.m_joint[3]);
			temp[4].push_back(m_robot.m_joint[4]);
			temp[5].push_back(m_robot.m_joint[5]);
			temp[6].push_back(m_robot.m_tcp.o.x);
			temp[7].push_back(m_robot.m_tcp.o.y);
			temp[8].push_back(m_robot.m_tcp.o.z);
			temp[9].push_back(m_robot.m_tcpEuler.x);
			temp[10].push_back(m_robot.m_tcpEuler.y);
			temp[11].push_back(m_robot.m_tcpEuler.z);
			temp[12].push_back(step.joint_1);
			temp[13].push_back(step.joint_2);
			temp[14].push_back(step.joint_3);
			temp[15].push_back(step.joint_4);
			temp[16].push_back(step.joint_5);
			temp[17].push_back(step.joint_6);

			moveJointBy(step.joint_1, step.joint_2, step.joint_3, step.joint_4, step.joint_5, step.joint_6);
			boost::this_thread::sleep(boost::posix_time::seconds(5));
			updateJoint();
			updateTCP();
			temp[18].push_back(m_robot.m_joint[0]);
			temp[19].push_back(m_robot.m_joint[1]);
			temp[20].push_back(m_robot.m_joint[2]);
			temp[21].push_back(m_robot.m_joint[3]);
			temp[22].push_back(m_robot.m_joint[4]);
			temp[23].push_back(m_robot.m_joint[5]);
			temp[24].push_back(m_robot.m_tcp.o.x);
			temp[25].push_back(m_robot.m_tcp.o.y);
			temp[26].push_back(m_robot.m_tcp.o.z);
			temp[27].push_back(m_robot.m_tcpEuler.x);
			temp[28].push_back(m_robot.m_tcpEuler.y);
			temp[29].push_back(m_robot.m_tcpEuler.z);
			cout << i << " " << j << endl;
		}
	}
	
	char* option;
	FILE* processed = NULL;
	option = "w";

	processed = fopen(filename,option);

	if (processed == NULL)
	{
		printf("Error: Opening file\n");
		return;
	}
	for (unsigned int k = 0; k < temp[0].size(); k++)
	{
		for(int l = 0; l < 30; l++)
		{
			fprintf(processed, "%f,", temp[l][k]);
		}
		fprintf(processed, "\n");
	}

	fclose(processed);
}