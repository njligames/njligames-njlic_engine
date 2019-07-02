//
//  Path.cpp
//  NJLIC
//
//  Created by James Folk on 12/11/18.
//

#include "Path.h"

//#include "Path.h"
//#include "misc/utils.h"
//#include "misc/Cgdi.h"
//#include "2d/transformations.h"

#include "Pi.h"
#include "World.h"
#include "btMatrix3x3.h"

#define FORMATSTRING "{\"njli::Path\":[]}"
namespace njli
{
    const double Pi = PI_NJLIC;
    const double TwoPi = Pi * 2;

    inline double RandFloat() { return ((rand()) / (RAND_MAX + 1.0)); }

    inline double RandInRange(double x, double y)
    {
        return x + RandFloat() * (y - x);
    }

    inline void Vec3DRotateAroundOrigin(btVector3 &v, double ang)
    {
        //    //create a transformation matrix
        //    C2DMatrix mat;
        //
        //    //rotate
        //    mat.Rotate(ang);
        //
        //    //now transform the object's vertices
        //    mat.TransformVector2Ds(v);

        btQuaternion rotation(btVector3(1.0, 1.0, 1.0).normalized(), ang);
        v = quatRotate(rotation, v);
    }

    Path::Path() : m_bLooped(true) {}

    Path::Path(const Path &copy) : m_bLooped(copy.m_bLooped)
    {
        m_WayPoints = copy.m_WayPoints;
        curWaypoint = m_WayPoints.begin();
    }

    const Path &Path::operator=(const Path &rhs)
    {
        if (this != &rhs)
        {
            m_bLooped = rhs.m_bLooped;
            m_WayPoints = rhs.m_WayPoints;

            curWaypoint = m_WayPoints.begin();
        }
        return *this;
    }

    // constructor for creating a path with initial random waypoints. MinX/Y
    //& MaxX/Y define the bounding box of the path.
    Path::Path(int NumWaypoints, double MinX, double MinY, double MinZ,
               double MaxX, double MaxY, double MaxZ, bool looped)
        : m_bLooped(looped)
    {
        createRandomPath(NumWaypoints, MinX, MinY, MinZ, MaxX, MaxY, MaxZ);

        curWaypoint = m_WayPoints.begin();
    }

    btVector3 Path::currentWaypoint() const
    {
        if (m_WayPoints.size() > 0)
        {
            return *curWaypoint;
        }
        return btVector3(0, 0, 0);
    }

    std::list<btVector3> Path::createRandomPath(int NumWaypoints, double MinX,
                                                double MinY, double MinZ,
                                                double MaxX, double MaxY,
                                                double MaxZ)
    {
        m_WayPoints.clear();

        double midX = (MaxX + MinX) / 2.0;
        double midY = (MaxY + MinY) / 2.0;
        double midZ = (MaxZ + MinZ) / 2.0;

        double smaller = fmin(midX, midY);
        smaller = fmin(smaller, midZ);

        double spacing = TwoPi / (double)NumWaypoints;

        for (int i = 0; i < NumWaypoints; ++i)
        {
            double RadialDist = RandInRange(smaller * 0.2f, smaller);

            btVector3 temp(RadialDist, RadialDist, RadialDist);

            Vec3DRotateAroundOrigin(temp, i * spacing);

            //        temp.x += midX;
            temp.setX(temp.x() + midX);
            //        temp.y += midY;
            temp.setY(temp.y() + midY);
            temp.setZ(temp.z() + midZ);

            m_WayPoints.push_back(temp);
        }

        curWaypoint = m_WayPoints.begin();

        return m_WayPoints;
    }

    void Path::addWayPoint(const btVector3 &new_point)
    {
        m_WayPoints.push_back(new_point);

        if (m_WayPoints.size() == 1)
        {
            curWaypoint = m_WayPoints.begin();
        }
    }

    void Path::debugDraw() const
    {
        //    gdi->OrangePen();
        btVector4 color(1.0, 1.0, 1.0, 1.0);

        std::list<btVector3>::const_iterator it = m_WayPoints.begin();

        btVector3 wp = *it++;
        njli::World::getInstance()->getDebugDrawer()->point(wp, color);

        while (it != m_WayPoints.end())
        {
            njli::World::getInstance()->getDebugDrawer()->drawLine(wp, *it,
                                                                   color);

            wp = *it++;
            njli::World::getInstance()->getDebugDrawer()->point(wp, color);
        }

        if (m_bLooped)
            njli::World::getInstance()->getDebugDrawer()->drawLine(
                *(--it), *m_WayPoints.begin(), color);
    }

    Path::operator std::string() const
    {
        std::string temp(string_format(FORMATSTRING));
        return temp;
    }

    btScalar Path::averageDistanceBetweenPoints() const
    {
        btScalar distance(0);

        if (m_WayPoints.size())
        {

            std::list<btVector3>::const_iterator i = m_WayPoints.begin();
            btVector3 previousPoint(*i);
            i++;

            for (; i != m_WayPoints.end(); i++)
            {
                distance += previousPoint.distance(*i);
                previousPoint = *i;
            }
            if (m_bLooped)
            {
                i = m_WayPoints.begin();
                distance += previousPoint.distance(*i);

                distance /= (m_WayPoints.size() + 1);
            }
            else
            {
                distance /= m_WayPoints.size();
            }
        }
        return distance;
    }
} // namespace njli
