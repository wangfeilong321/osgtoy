/* file:      src/osgPlugins/hpp/Image.h
 * copyright: (C) 2007 Michael Weiblen http://mew.cx/
 * license:   OpenSceneGraph Public License (OSGPL)
 * $Id$
*/

#ifndef OSGPLUGIN_HPP_IMAGE_H
#define OSGPLUGIN_HPP_IMAGE_H

#include <iostream>
#include <osg/Image>

namespace hpp
{

std::ostream& operator << (std::ostream& fout, const osg::Image& img );

}

#endif

// vim: set sw=4 ts=8 et ic ai:
