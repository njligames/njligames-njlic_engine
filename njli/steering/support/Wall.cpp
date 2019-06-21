//
//  Wall.cpp
//  NJLIC
//
//  Created by James Folk on 6/20/19.
//

#include "Wall.h"

//#include "Wall.h"
//#include "misc/utils.h"
//#include "misc/Cgdi.h"
//#include "2d/transformations.h"

#include "Pi.h"
#include "World.h"
#include "btMatrix3x3.h"

#define FORMATSTRING "{\"njli::Wall\":[]}"
namespace njli
{

  Wall::Wall() : m_planePoint(new btVector3()), m_planeNormal(new btVector3())
  {
  }
  Wall::Wall(const Wall &copy)
      : m_planePoint(new btVector3(*(copy.m_planePoint))),
        m_planeNormal(new btVector3(*(copy.m_planeNormal)))
  {
  }

  const Wall &Wall::operator=(const Wall &copy)
  {
    if (this != &copy)
      {
        *m_planePoint = *(copy.m_planePoint);
        *m_planeNormal = *(copy.m_planeNormal);
      }
    return *this;
  }

  Wall::~Wall()
  {
    delete m_planeNormal;
    delete m_planePoint;
  }

  // constructor for creating a path with initial random waypoints. MinX/Y
  //& MaxX/Y define the bounding box of the path.
  Wall::Wall(const btVector3 &planePoint, const btVector3 &planeNormal)
      : m_planePoint(new btVector3(planePoint)),
        m_planeNormal(new btVector3(planeNormal))
  {
    *m_planeNormal = planeNormal;
    *m_planePoint = planePoint;
  }

  // renders the path in orange
  void Wall::debugDraw() const
  {
    btVector3 color(1.0, 1.0, 1.0);
    btVector3 ncolor(1.0, 0.0, 0.0);
    float planeScale(1.0);
    float normalVecScale(1.0);

    njli::World::getInstance()->getDebugDrawer()->plane(
        *m_planePoint, *m_planeNormal, color, ncolor, planeScale,
        normalVecScale);
  }

  Wall::operator std::string() const { return std::string(""); }

  bool Wall::lineIntersection(const btVector3 &linePoint,
                              const btVector3 &lineDirection) const
  {
    if (m_planeNormal->dot(lineDirection.normalized()) == 0)
      {
        return false;
      }
    return true;
  }
  // http://geomalgorithms.com/a05-_intersect-1.html
  // intersect3D_SegmentPlane(): find the 3D intersection of a segment and a
  // plane
  //    Input:  S = a segment, and Pn = a plane = {Point V0;  Vector n;}
  //    Output: *I0 = the intersect point (when it exists)
  //    Return: 0 = disjoint (no intersection)
  //            1 =  intersection in the unique point *I0
  //            2 = the  segment lies in the plane
  //    int
  //    intersect3D_SegmentPlane( Segment S, Plane Pn, Point* I )
  //    {
  //        Vector    u = S.P1 - S.P0;
  //        Vector    w = S.P0 - Pn.V0;
  //
  //        float     D = dot(Pn.n, u);
  //        float     N = -dot(Pn.n, w);
  //
  //        if (fabs(D) < SMALL_NUM) {           // segment is parallel to plane
  //            if (N == 0)                      // segment lies in plane
  //                return 2;
  //            else
  //                return 0;                    // no intersection
  //        }
  //        // they are not parallel
  //        // compute intersect param
  //        float sI = N / D;
  //        if (sI < 0 || sI > 1)
  //            return 0;                        // no intersection
  //
  //        *I = S.P0 + sI * u;                  // compute segment intersect
  //        point return 1;
  //    }
  btVector3 Wall::lineIntersectionPoint(const btVector3 &linePoint,
                                        const btVector3 &lineDirection) const
  {
    if (lineIntersection(linePoint, lineDirection))
      {
        btScalar t = (m_planeNormal->dot(*m_planePoint) -
                      m_planeNormal->dot(linePoint)) /
                     m_planeNormal->dot(lineDirection.normalized());

        return linePoint + btVector3(lineDirection.normalized() * t);
      }
    return linePoint;
  }

  int Wall::segmentIntersection(const btVector3 &p0, const btVector3 &p1,
                                btVector3 &intersectionPoint) const
  {
    btVector3 u(p1 - p0);
    btVector3 w(p0 - *m_planePoint);

    float D(m_planeNormal->dot(u));
    float N(-m_planeNormal->dot(w));
    float smallest = std::numeric_limits<float>::min();
    if (fabs(D) < 0.00001)
      {
        if (N == 0)
          return 2;
        else
          return 0;
      }

    // they are not parallel
    // compute intersect param
    float sI = N / D;
    if (sI < 0 || sI > 1)
      return 0; // no intersection

    intersectionPoint = (p0 + sI * u); // compute segment intersect point
    return 1;
  }

  btVector3 Wall::segmentIntersectionPoint(const btVector3 &p0,
                                           const btVector3 &p1) const
  {
    btVector3 intersectionPoint;
    if (segmentIntersection(p0, p1, intersectionPoint) > 0)
      {
        return intersectionPoint;
      }
    return btVector3(0, 0, 0);
  }

  const btVector3 &Wall::normal() const { return *m_planeNormal; }

  const btVector3 &Wall::distance() const { return *m_planePoint; }

  //    public static Vector lineIntersection(Vector planePoint, Vector
  //    planeNormal, Vector linePoint, Vector lineDirection) {
  //        if (planeNormal.dot(lineDirection.normalize()) == 0) {
  //            return null;
  //        }
  //
  //        double t = (planeNormal.dot(planePoint) -
  //        planeNormal.dot(linePoint)) /
  //        planeNormal.dot(lineDirection.normalize()); return
  //        linePoint.plus(lineDirection.normalize().scale(t));
  //    }
} // namespace njli
