#include "sbsGocator.h"

/*******************************************************************************
* Global Declaration
********************************************************************************/

sbsPolygon3D sbsGocator::m_polyAsync;
sbsPolygon3D sbsGocator::m_polyAsyncBuilding;
bool sbsGocator::b_profileUpdated = false;
double sbsGocator::m_threathhole = -262;

/*******************************************************************************
* Call Back Function
********************************************************************************/

int GO2_CALL OnLaserData(void* ctx, void* sys, void* data)
{
	if (!sbsGocator::b_profileUpdated)
	{
		sbsGocator::BuildPolygonFromData(sbsGocator::m_polyAsyncBuilding,data);
		sbsGocator::m_polyAsync = sbsGocator::m_polyAsyncBuilding;
		sbsGocator::b_profileUpdated = true;
	}

	int status;
	if ((status = Go2Data_Destroy(data)) != GO2_OK)
	{
		cout << "Error: Go2Data_Destroy: " << status << endl;
		return GO2_ERROR;
	}

	return GO2_OK;
}

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsGocator::sbsGocator()
{
	m_gocator = GO2_NULL;
	m_mainSensor = GO2_NULL;
	b_connected = false;
	b_started = false;
	m_timeOut = 20000;
	b_sync = true;
	m_alignmentCalibrationExposure = 200;
}

sbsGocator::~sbsGocator()
{
	if (b_connected)
	{
		disconnect();
	}
}

/*******************************************************************************
* Public Method
********************************************************************************/

bool sbsGocator::ConnectASync()
{
	if (!InitConnection())
	{
		return false;
	}

	cout << "> Async connection\n";
	if ((status = Go2System_ConnectData(m_gocator, OnLaserData, GO2_NULL)) != GO2_OK)
	{
		cout << "Error: Go2System_ConnectData: " << status << endl;
		return false;
	}

	b_sync = false;
	return true;
}

bool sbsGocator::ConnectSync()
{
	if (!InitConnection())
	{
		return false;
	}

	cout << "> Sync connection\n";
	if ((status = Go2System_ConnectData(m_gocator, GO2_NULL, GO2_NULL)) != GO2_OK)
	{
		cout << "Error: Go2System_ConnectData: " << status << endl;
		return false;
	}

	b_sync = true;
	return true;
}

bool sbsGocator::UpdateProfileSync()
{
	if (!b_started)
	{
		if (!StartData())
		{
			cout << "Can not start a data connection\n";
			return false;
		}
	}

	Go2Data data= GO2_NULL;
	int i = 0;
	while (i<1000)
	{
		i++;
		if (Go2System_ReceiveData(m_gocator, m_timeOut, &data) != GO2_OK)
		{
			continue;
		}
		break;
	}

	if (i>=1000)
	{
		disconnect();
		return false;
	}

	BuildPolygonFromData(m_poly,data);

	if ((status = Go2Data_Destroy(data)) != GO2_OK)
	{
		cout << "Error: Go2Data_Destroy: " << status << endl;
		return false;
	}

	return true;
}

void sbsGocator::disconnect()
{
	// stop
	if ((status = Go2System_Stop(m_gocator)) != GO2_OK)
	{
		cout << "Error: Go2System_Stop: " << status << endl;
		return;
	}
	// destroy system handle
	if ((status = Go2System_Destroy(m_gocator)) != GO2_OK)
	{
		cout << "Error: Go2System_Destroy: " << status << endl;
		return;
	}

	// terminate Go2 API
	if ((status = Go2Api_Terminate()) != GO2_OK)
	{
		cout << "Error: Go2Api_Terminate: " << status << endl;
		return;
	}

	b_connected = false;
}

sbsPolygon3D sbsGocator::GetLaserProfile()
{
	if (b_sync)
	{
		m_poly.clear();
		UpdateProfileSync();
		return m_poly;
	}
	else
	{
		WaitForData();
		return m_polyAsync;
	}
}

bool sbsGocator::StartData()
{
	if (!b_connected)
	{
		cout << "Need a connection first\n";
		return false;
	}
	if (b_started)
	{
		cout << "Already started\n";
		return true;
	}

	if ((status = Go2System_Start(m_gocator)) != GO2_OK)
	{
        cout << "Error: Go2System_Start: " << status << endl;
		StopData();
		return false;
	}
	b_started = true;
	WaitForData();
	return true;
}

bool sbsGocator::StopData()
{
	if ((status = Go2System_Stop(m_gocator)) != GO2_OK)
	{
		cout << "Error: Go2System_Stop: " << status << endl;
		return false;
	}
	b_started = false;
	return true;
}

bool sbsGocator::InitConnection()
{
	if (b_connected)
	{
		cout << "Gocator already connected\n";
		return false;
	}
	b_connected = false;
	b_started = false;

	// initialize Go2 API
	if ((status = Go2Api_Initialize()) != GO2_OK)
	{
		cout << "Error: Go2Api_Initialize: " << status << endl;
		return false;
	}

	// construct Go2 system object
	if ((status = Go2System_Construct(&m_gocator)) != GO2_OK)
	{
		cout << "Error: Go2System_Construct: " << status << endl;
		return false;
	}

	unsigned int address;
	// convert ip address string to Go2IPAddress object
	if ((status = Go2IPAddress_Parse((Go2Char*)"192.168.125.2", &address)) != GO2_OK)
	{
		cout << "Error: Go2IPAddress_Parse: " << status << endl;
		return false;
	}

	// connect to Gocator system at default address
	if ((status = Go2System_Connect(m_gocator, address)) != GO2_OK)
	{
		cout << "Error: Go2System_Connect: " << status << endl;
		return false;
	}

	// retrieve main sensor handle
	if ((m_mainSensor = Go2System_MainSensor(m_gocator)) == GO2_NULL)
	{
		cout << "Error: Go2System_MainSensor: Invalid Handle\n";
		return false;
	}

	b_connected = true;

	return true;
}

bool sbsGocator::BuildPolygonFromData( sbsPolygon3D& poly, void* data )
{
	poly.clear();

	//each result can have multiple data items
	for(Go2UInt32 j = 0; j < Go2Data_ItemCount(data); ++j)
	{
		Go2Data dataItem = Go2Data_ItemAt(data, j);
		//printf("  Type: %u\n", Go2Object_Type(dataItem));
		if (Go2Object_Type(dataItem) == GO2_TYPE_PROFILE_DATA)
		{
			unsigned int profilePointCount = Go2ProfileData_Width(dataItem);
			unsigned int profileSizeBytes = profilePointCount * sizeof(short);
			//printf("    Item[%u]: Profile data (%u points)\n", j, profilePointCount);

			size_t profileWidth = Go2ProfileData_Width(dataItem);
			double xResolution = Go2ProfileData_XResolution(dataItem);
			double zResolution = Go2ProfileData_ZResolution(dataItem);
			double xOffset = Go2ProfileData_XOffset(dataItem);
			double zOffset = Go2ProfileData_ZOffset(dataItem);
			//printf("%d\n",m_profile.m_profileWidth);

			//copy profiles to memory array
			short* memory = (short*)malloc(profileSizeBytes);
			memcpy(memory, Go2ProfileData_Ranges(dataItem), profileSizeBytes);
			poly.reserve(profileWidth);
			for (size_t k = 0; k < profileWidth; k++)
			{
				double x = xOffset + k * xResolution;
				double z = zOffset + memory[k] * zResolution;
				sbsPoint3D p(x,0,z);
				poly.push_back(p);
			}
			free(memory);
		}
	}
	return true;
}

void sbsGocator::tryAsyncConnect()
{
	if (b_connected)
	{
		return;
	}
	ConnectASync();
	if (!StartData())
	{
		StartData();
	}
}

double sbsGocator::getExposure()
{
	if (!m_mainSensor)
	{
		return 0;
	}
	return Go2Sensor_Exposure(m_mainSensor);
}

bool sbsGocator::setExposure(double exp2)
{
	bool needtostart = b_started;
	if (b_started)
	{
		StopData();
	}
	if (!m_mainSensor)
	{
		return false;
	}

	if ((status = Go2Sensor_SetExposure(m_mainSensor, exp2)) != GO2_OK)
	{
		cout << "Error: Go2System_SetExposure: " << status << endl;
		return false;
	}

	if (needtostart)
	{
		StartData();
	}

	return true;
}

bool sbsGocator::setFrameRate(double frameRate)
{
	bool needtostart = b_started;
	if (b_started)
	{
		StopData();
	}
	if (!m_mainSensor)
	{
		return false;
	}
	if ((status = Go2System_SetFrameRate(m_gocator, frameRate)) != GO2_OK)
	{
		cout << "Error: Go2System_SetFrameRate: " << status << endl;
		return false;
	}
	if (needtostart)
	{
		StartData();
	}
	return true;
}


bool sbsGocator::getExposureRange( double& minExp, double& maxExp )
{
	if (!m_mainSensor)
	{
		return false;
	}
	minExp = Go2Sensor_ExposureMin(m_mainSensor);
	maxExp = Go2Sensor_ExposureMax(m_mainSensor);

	return true;
}

bool sbsGocator::setMinimalExposure()
{
	if (!m_mainSensor)
	{
		return false;
	}
	double minExp = Go2Sensor_ExposureMin(m_mainSensor);
	return setExposure(minExp);
}

void sbsGocator::WaitForData()
{
	if(Go2Free(GO2_NULL)!=GO2_OK)
		cout << "error";
	b_profileUpdated = false;
	while(!b_profileUpdated)
	{
        boost::this_thread::sleep(boost::posix_time::microseconds(10));
	}

}

void sbsGocator::AlignmentCalibration()
{
	if (!b_connected)
	{
		tryAsyncConnect();
	}
	cout << "> Set exposure: " << m_alignmentCalibrationExposure << endl;
	setExposure(m_alignmentCalibrationExposure);
	StopData();
	Go2Data data = GO2_NULL;
	unsigned int i;

	// set alignment target to none (meaning the target is a flat reference surface)
	if ((status = Go2System_SetAlignmentTarget(m_gocator, GO2_CALIBRATION_TARGET_NONE)) != GO2_OK)
	{
		cout << "Error: Go2System_SetAlignmentTarget: " << status << endl;
 		return;
	}

	// establish a Gocator data connection
	if ((status = Go2System_ConnectData(m_gocator, GO2_NULL, GO2_NULL)) != GO2_OK)
	{
		cout << "Error: Go2System_ConnectData: " << status << endl;
 		return;
	}

	// ensure Gocator is in Alignment Calibration Mode
	if ((status = Go2System_SetMode(m_gocator, GO2_MODE_ALIGN_CAL)) != GO2_OK)
	{
		cout << "Error: Go2System_SetMode: " << status << endl;
 		return;
	}

	// Start Gocator system
	if ((status = Go2System_Start(m_gocator)) != GO2_OK)
	{
		cout << "Error: Go2System_Start: " << status << endl;
 		return;
	}

	cout << "> Collect alignment calibration data \n";

	status = Go2System_ReceiveData(m_gocator, RECEIVE_TIMEOUT, &data);

	if (status == GO2_ERROR_TIMEOUT)
	{
		cout << "Failed to collect date for calibration within timeout limit...\n";
	}
	else if (status != GO2_OK)
	{
		cout << "Error: Go2System_ReceiveData: " << status << endl;
	}
	else
	{
		//each result can have multiple data items
		for (i = 0; i < Go2Data_ItemCount(data); ++i)
		{
			Go2Data dataItem = Go2Data_ItemAt(data, i);
			if (Go2Object_Type(dataItem) == GO2_TYPE_ALIGNMENT_DATA)
			{
				if ((status = Go2AlignmentData_Status(dataItem)) == GO2_OK)
				{
					cout << "> Calibration successful!\n";
				}
				else
				{
					cout << "Calibration failed: " << status << endl;
				}
			}
		}
	}

 	if ((status = Go2Data_Destroy(data)) != GO2_OK)
	{
		cout << "Error: Go2Data_Destroy: " << status << endl;
		return;
	}

	// Stop Gocator system
	if ((status = Go2System_Stop(m_gocator)) != GO2_OK)
	{
		cout << "Error: Go2System_Stop: " << status << endl;
		return;
	}
	StartData();
}

sbsPolygon3D sbsGocator::GetCalibrationProfile()
{
	if (!b_connected)
	{
		tryAsyncConnect();
	}
	sbsPolygon3D poly = GetLaserProfile();
	size_t num = 0;

	sbsPolygon3D npoly;
	if (poly.size()==0)
	{
		return npoly;
	}

	for (size_t i = 0; i < poly.size(); i++)
	{
		if (poly[i].z <= m_threathhole)
		{
			continue;
		}
		if (!sbszeroeps(poly[i].z,1))
		{
			continue;
		}
		num++;
	}

	npoly.reserve(num);

	for (size_t i = 0; i < poly.size(); i++)
	{
		if (poly[i].z <= m_threathhole)
		{
			continue;
		}
		if (!sbszeroeps(poly[i].z,1))
		{
			continue;
		}
		npoly.push_back(poly[i]);
	}
	if (npoly.size()<2)
	{
		npoly.clear();
	}

	return npoly;
}

bool sbsGocator::GetCalibrationDiskData( sbsPoint3D& p0, sbsPoint3D& p1, sbsPoint3D& c )
{
	sbsPolygon3D poly = GetCalibrationProfile();
	if (poly.size()==0)
	{
		return false;
	}
	p0 = poly.pointFirst();
	p1 = poly.pointLast();
	sbsPoint3D cp = (p0+p1)*0.5;
	double calibrationRadius = 50;
	sbsPoint3D dp = cp-p0;
	double len = dp.length();
	double a = calibrationRadius*calibrationRadius;
	double b = len*len;
	c = cp;
	if (b>=a)
	{
		return true;
	}

	c.y = sqrt(a-b);
	return true;
}
