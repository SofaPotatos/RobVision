#pragma once

#include "sbsPoint3D.h"

/// sbsPolygon3D Class
///
/// This class is a polygon class which contain an vector of 3DPoint class
class sbsPolygon3D
{
    public:
        /// A public sbsPoint3D vector.
        /// This variable 3D points of the polygon.
        sbsPoint3DVector m_points;

    public:
		/// A constructor.
		///
		/// This constructor a polygon.
        sbsPolygon3D();

		/// A destructor.
		///
		/// This destructor free the resources that the object may have.
        ~sbsPolygon3D();

    public:
        sbsPoint3D& operator()(size_t i);
        sbsPoint3D& operator[](size_t i);

    public:
        /// This member clear all vector.
        void clear();

        /// This member push the 3D point onto the back of the vector.
        ///
        ///@param p: The 3Dpoint to be added at the end of the vector
        void push_back(sbsPoint3D& p);

        /// This member remove the last element of the vector.
        void pop_back();

        /// This member reserve the memory for the vector.
        void reserve(size_t num);

        /// This member return the vector size.
        ///
        ///@return Size of vector
        size_t size();

        /// This member return the first element of the vector.
        ///
        ///@return First 3D point
        sbsPoint3D pointFirst();

        /// This member return the last element of the vector.
        ///
        ///@return Last 3D point
        sbsPoint3D pointLast();
};

#define sbsPolygon3DVector vector<sbsPolygon3D>
