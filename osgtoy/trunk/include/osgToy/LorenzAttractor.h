// $Id$
// $URL$
// Copyright 2004-2011 Mike Weiblen http://mew.cx/
// OpenSceneGraph Public License (OSGPL)
//
// see: http://en.wikipedia.org/wiki/Lorenz_attractor
//      http://mathworld.wolfram.com/LorenzAttractor.html

#ifndef OSGTOY_LORENZATTRACTOR
#define OSGTOY_LORENZATTRACTOR 1

#include <osg/Geometry>
#include <osg/Vec3>

#include <osgToy/Export.h>

namespace osgToy {

/** Plot the Lorenz Attractor */

class OSGTOY_EXPORT LorenzAttractor : public osg::Geometry
{
public:
    LorenzAttractor(
        unsigned int numPoints = 10000, // some convenient defaults for demo
        float deltaT = 0.005f,
        osg::Vec3 p0 = osg::Vec3(1,0,0),
        float t0 = 0.0f,
        float a = 10.0f,
        float b = 28.0f,
        float c = 8.0f/3.0f );

    unsigned int getNumPoints() const { return _numPoints; }

protected:
    virtual ~LorenzAttractor() {}
    unsigned int _numPoints;
};

}

#endif

// vim: set sw=4 ts=8 et ic ai:
