#include "sbsProfile.h"

/*******************************************************************************
* Global Declaration
********************************************************************************/

int sbsProfile::m_numProfileScan = 10;

/*******************************************************************************
* Constructor & Destructor
********************************************************************************/

sbsProfile::sbsProfile()
{
	m_profileType = 0;
	m_robotPolys.reserve(sbsProfile::m_numProfileScan);
}

sbsProfile::sbsProfile(boost::shared_ptr<sbsPolygon3D> poly )
{
	m_robotPoly = *poly;
	m_profileType = 0;
}

sbsProfile::~sbsProfile()
{
}

/*******************************************************************************
* Public Method
********************************************************************************/

void sbsProfile::finalizePolygon()
{
	m_robotPoly = m_robotPolys[0];
	m_laserPoly = m_laserPolys[0];
}

void sbsProfile::saveScans(string file)
{
}

void sbsProfile::loadScans(string profileFile)
{
}
