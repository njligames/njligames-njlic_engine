//
//  Wall.h
//  NJLIC
//
//  Created by James Folk on 6/20/19.
//

#ifndef Wall_hpp
#define Wall_hpp


//------------------------------------------------------------------------
//
//  Name:   Wall.h
//
//  Desc:   class to define, manage, and traverse a path (defined by a series of 2D vectors)
//
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <list>
#include <cassert>
#include <string>

#include "btVector3.h"



namespace njli
{
class Wall
{
private:
    
    btVector3 *m_planePoint;
    btVector3 *m_planeNormal;
    
public:
    
    Wall();
    Wall(const Wall &copy);
    const Wall &operator=(const Wall &copy);
    virtual ~Wall();
    
    //constructor for creating a path with initial random waypoints. MinX/Y
    //& MaxX/Y define the bounding box of the path.
    Wall(const btVector3 &planePoint, const btVector3 &planeNormal);
    
    //renders the path in orange
    void debugDraw()const;
    
    operator std::string() const;
    
    bool lineIntersection(const btVector3 &linePoint, const btVector3 &lineDirection)const;
    btVector3 lineIntersectionPoint(const btVector3 &linePoint, const btVector3 &lineDirection)const;
    
    int segmentIntersection(const btVector3 &p0, const btVector3 &p1, btVector3 &intersectionPoint)const;
    btVector3 segmentIntersectionPoint(const btVector3 &p0, const btVector3 &p1)const;
    
    const btVector3 &normal()const;
    const btVector3 &distance()const;
};

}


#endif
