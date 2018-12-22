//
//  Path.h
//  NJLIC
//
//  Created by James Folk on 12/11/18.
//

#ifndef Path_hpp
#define Path_hpp


//------------------------------------------------------------------------
//
//  Name:   Path.h
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
class Path
{
private:
    
    std::list<btVector3>            m_WayPoints;
    
    //points to the current waypoint
    std::list<btVector3>::iterator  curWaypoint;
    
    //flag to indicate if the path should be looped
    //(The last waypoint connected to the first)
    bool                           m_bLooped;
    
public:
    
    Path();
    Path(const Path &copy);
    const Path &operator=(const Path &copy);
    
    //constructor for creating a path with initial random waypoints. MinX/Y
    //& MaxX/Y define the bounding box of the path.
    Path(int    NumWaypoints,
         double MinX,
         double MinY,
         double MinZ,
         double MaxX,
         double MaxY,
         double MaxZ,
         bool   looped);
    
    
    //returns the current waypoint
    btVector3    currentWaypoint()const;
    
    //returns true if the end of the list has been reached
    bool        finished(){return !(curWaypoint != m_WayPoints.end());}
    
    //moves the iterator on to the next waypoint in the list
    inline void setNextWaypoint();
    
    //creates a random path which is bound by rectangle described by
    //the min/max values
    std::list<btVector3> createRandomPath(int   NumWaypoints,
                                          double MinX,
                                          double MinY,
                                          double MinZ,
                                          double MaxX,
                                          double MaxY,
                                          double MaxZ);
    
    
    void enableLoopOn(bool enable = true){m_bLooped = enable;}
    
    //adds a waypoint to the end of the path
    void addWayPoint(const btVector3 &new_point);
    
    //methods for setting the path with either another Path or a list of vectors
    void set(std::list<btVector3> new_path){m_WayPoints = new_path;curWaypoint = m_WayPoints.begin();}
    void set(const Path& path){m_WayPoints=path.getPath(); curWaypoint = m_WayPoints.begin();}
    
    
    void clear(){m_WayPoints.clear();}
    size_t size(){return m_WayPoints.size();}
    
    std::list<btVector3> getPath()const{return m_WayPoints;}
    
    //renders the path in orange
    void debugDraw()const;
    
    operator std::string() const;
    
    btScalar averageDistanceBetweenPoints()const;
};




//-------------------- Methods -------------------------------------------

inline void Path::setNextWaypoint()
{
    assert (m_WayPoints.size() > 0);
    
    if (++curWaypoint == m_WayPoints.end())
    {
        if (m_bLooped)
        {
            curWaypoint = m_WayPoints.begin();
        }
    }
}
}


#endif
