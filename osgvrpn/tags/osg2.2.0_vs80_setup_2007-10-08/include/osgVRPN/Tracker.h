/* file:        include/osgVRPN/Tracker.h
 * author:      Mike Weiblen
 * copyright:   (C) 2003-2006 Michael Weiblen http://mew.cx/
 * license:     OpenSceneGraph Public License (OSGPL)
 * $Id: Tracker.h,v 1.7 2006/07/15 17:28:35 mew Exp $
*/

#ifndef OSGVRPN_TRACKER
#define OSGVRPN_TRACKER 1

#include <osg/Quat>
#include <osg/Vec3>
#include <osg/Matrixd>
#include <osgVRPN/TrackerBase.h>

#include <osgVRPN/Export>

// fwd declarations so OSG app code doesn't need the VRPN headers
class vrpn_Tracker_Remote;
typedef struct _vrpn_TRACKERCB vrpn_TRACKERCB;

namespace osgVRPN {

/** an OSG wrapper for VRPN's vrpn_Tracker_Remote class. */

class OSGVRPN_EXPORT Tracker : public TrackerBase
{
public:
    Tracker( const char* deviceName );

    /** Update our state from the device. */
    void update();

    /** Query the tracker's transform matrix */
    const osg::Matrixd getMatrix() const;
    const osg::Matrixd getInverseMatrix() const;

protected:      // methods
    ~Tracker();

    static void s_ChangeHandler( void* userdata, const vrpn_TRACKERCB info );
    void changeHandler( const vrpn_TRACKERCB& info );

protected:      // data
    vrpn_Tracker_Remote* const  _vrpnTracker;
    osg::Vec3 _position;
    osg::Quat _rotation;

private:        // uncopyable
    Tracker(const Tracker&);
    Tracker& operator=(const Tracker&);
};

}

#endif

// vim: set sw=4 ts=8 et ic ai:
