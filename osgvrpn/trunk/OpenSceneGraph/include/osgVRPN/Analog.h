/* file:        include/osgVRPN/Analog.h
 * author:      Mike Weiblen mew@mew.cx
 * copyright:   (C) 2003-2006 Michael Weiblen
 * license:     OpenSceneGraph Public License (OSGPL)
 * $Id: Analog.h,v 1.2 2006/06/23 17:22:37 mew Exp $
 *
 * references:  http://www.openscenegraph.org/
 *              http://www.vrpn.org/
 *              http://mew.cx/
*/

#ifndef OSGVRPN_ANALOG
#define OSGVRPN_ANALOG 1

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Array>

#include <osgVRPN/Export>

// fwd declarations so OSG app code doesn't need the VRPN headers
class vrpn_Analog_Remote;
typedef struct _vrpn_ANALOGCB vrpn_ANALOGCB;

namespace osgVRPN {

/** an OSG wrapper for VRPN's vrpn_Analog_Remote class. */

class OSGVRPN_EXPORT Analog : public osg::Referenced
{
public:
    Analog( const char* deviceName );

    /** Update our state from the device. */
    void update();

    /** Query a channel value from the Analog */
    unsigned int getNumChannels() const { return _data->getNumElements(); }
    float getValue(unsigned int channel) const { return (*_data)[channel]; }

protected:      // methods
    Analog();
    Analog(const Analog&);
    virtual ~Analog();
    const Analog& operator=(const Analog&);

    static void s_ChangeHandler( void* userdata, const vrpn_ANALOGCB info );
    void changeHandler( const vrpn_ANALOGCB& info );

protected:      // data
    vrpn_Analog_Remote* const     _vrpnAnalog;
    osg::ref_ptr<osg::FloatArray> _data;
};

}

#endif

// vim: set sw=4 ts=8 et ic ai:
