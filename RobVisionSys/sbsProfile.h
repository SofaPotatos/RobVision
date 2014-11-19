#pragma once

#include "../RobArm/sbsPolygon3D.h"

/// sbsProfile Class
///
/// This class contains profiles of robot coordinates and laser coordinates.
class sbsProfile
{
    public:
        /// A public sbsPolygon3D object.
        /// This object stores the robot coordinates for 1 profile.
        sbsPolygon3D m_robotPoly;

        /// A public sbsPolygon3D object.
        /// This object stores the laser coordinates for 1 profile.
        sbsPolygon3D m_laserPoly;

        /// A public sbsPolygon3D vector.
        /// This vector stores the robot profiles.
        vector<sbsPolygon3D> m_robotPolys;

        /// A public sbsPolygon3D vector.
        /// This vector stores the laser profiles.
        vector<sbsPolygon3D> m_laserPolys;

        /// A public int.
        /// This variable acts as a flag, 0 = undefined, 1 = empty, and 2 = has data.
        int m_profileType;

        /// A public static int.
        /// This variable store numbers of profiles.
        static int m_numProfileScan;

    public:
        /// A constructor.
		///
		/// This constructor creates a sbsProfile object.
        sbsProfile();

        /// A constructor.
		///
		/// This constructor creates a sbsProfile object identical to sbsProfile in the shared_ptr.
		///@param poly: A shared_ptr that points to a sbsProfile object
        sbsProfile(boost::shared_ptr<sbsPolygon3D> poly);

		/// A destructor.
		///
		/// This destructor free the resources that the object may have.
        ~sbsProfile();

    public:
        /// This members set the sbsPolygon3D object first object in the vector
        void finalizePolygon();

        /// Not implemented
        void saveScans(string profileFile);

        /// Not implemented
        void loadScans(string profileFile);
};
