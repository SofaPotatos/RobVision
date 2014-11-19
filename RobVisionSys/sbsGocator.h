#pragma once

#include <string.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "Go2.h"
#include "../RobArm/sbsPolygon3D.h"

#define RECEIVE_TIMEOUT	30000000 // 30 second timeout for calibration to complete

int GO2_CALL OnLaserData(void* ctx, void* sys, void* data);

/// sbsGocator Class
///
/// This class handles the connection and retrieves data from the Gocator sensor.
class sbsGocator
{
    private:
        /// A private Go2System object.
        /// The object for gocator system.
        Go2System m_gocator;

        /// A private Go2Sensor object.
        /// The object for gocator sensor.
        Go2Sensor m_mainSensor;

        /// A private int variable.
        /// This variable holds the status of the Gocator.
        int status;

        /// A private int variable.
        /// This variable holds the exposure value for the Gocator sensor.
        int m_alignmentCalibrationExposure;

        /// A private bool variable.
        /// This variable holds the status of the sensor connection.
        bool b_connected;

        /// A private bool variable.
        /// This variable state if the sensor start scanning.
        bool b_started;

        /// A private bool variable.
        /// This variable indicate if the connection is Asynchronous or Synchronous.
        bool b_sync;

        /// A private Go2UInt64 object.
        /// This object holds the time out value.
        Go2UInt64 m_timeOut;

        /// A private sbsPolygon3D object.
        /// This object holds the value of the profile scanned by the laser.
        sbsPolygon3D m_poly;

    public:
        /// A public static sbsPolygon3D object.
        /// The object that holds the polygon once its constructed.
        static sbsPolygon3D m_polyAsync;

        /// A public static sbsPolygon3D object.
        /// The object uses when constructing the polygon from data.
        static sbsPolygon3D m_polyAsyncBuilding;

        /// A public static double variable.
        /// This variable holds the threshold value?.
        static double m_threathhole;

        /// A public static bool variable.
        /// This variable indicates if the profile is updated.
        static bool b_profileUpdated;

    public:
        /// A constructor.
		///
		/// This constructor creates the sbsGocator object.
        sbsGocator(void);

        /// A destructor.
		///
		/// This destructor free the resources that the object may have.
        ~sbsGocator(void);

    public:
        /// This member connect an asynchronous connection with the Gocator laser.
        ///
        ///@return true if success, false otherwise
        bool ConnectASync();

        /// This member connnect a synchronous connection with the Gocator laser.
        ///
        ///@return true if success, false otherwise
        bool ConnectSync();

        /// This member updates the profile using synchronous connection.
        ///
        ///@return true if success, false otherwise
        bool UpdateProfileSync();

        /// This member disconnect the connection with the Gocator sensor.
        void disconnect();

        /// This member get the laser profile from the sensor.
        ///
        ///@return A sbsPolygon3D object build from the laser profile
        sbsPolygon3D GetLaserProfile();

        /// This member starts the laser scanning.
        ///
        ///@return true if success, false otherwise
        bool StartData();

        /// This member stop the laser scanning.
        ///
        ///@return true if success, false otherwise
        bool StopData();

        /// This member initiate the connection with the Gocator sensor.
        ///
        ///@return true if success, false otherwise
        bool InitConnection();

        /// This member construct the polygon object from the data receive from the sensor.
        ///
        ///@param poly: The polygon to be build
        ///@param data: The data receive from laser
        static bool BuildPolygonFromData(sbsPolygon3D& poly,  void* data);

        /// This member attempt an asynchronous connection with the laser.
        void tryAsyncConnect();

        /// This member gets the exposure value from the laser.
        ///
        ///@return Exposure value
        double getExposure();

        /// This member sets the exposure value of the laser.
        ///
        ///@param exp2: The exposure value
        ///@return true if success, false otherwise
        bool setExposure(double exp2);

        /// This member sets the frame rate value of the laser.
        ///
        ///@param frameRate: The frame rate value
        ///@return true if success, false otherwise
		bool setFrameRate(double frameRate);

        /// This member gets the exposure range of the laser.
        ///
        ///@param minExp: Minimum of the exposure range
        ///@param maxExp: Maxmum of the exposure range
        ///@return true if success, false otherwise
        bool getExposureRange(double& minExp, double& maxExp);

        /// This member sets the exposure to its minimum.
        ///
        ///@return true if success, false otherwise
        bool setMinimalExposure();

        /// This member wait for the laser to get its data.
        void WaitForData();

        /// This member calibrate the laser.
        void AlignmentCalibration();

        /// This member gets the calibration profile form the laser.
        ///
        ///@return The calibration profile
        sbsPolygon3D GetCalibrationProfile();

        /// This member gets the calibration dis data from the laser.
        ///
        ///@param p0: The 3Dpoint of the edge of the disk
        ///@param p1: The 3Dpoint of the edge of the disk
        ///@param c: The 3Dpoint of the center of the disk
        ///@return true if success, false otherwise
        bool GetCalibrationDiskData( sbsPoint3D& p0, sbsPoint3D& p1, sbsPoint3D& c );
};
