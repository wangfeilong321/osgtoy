// $Id$
// $URL$
// Copyright 2005-2011 Mike Weiblen http://mew.cx/
// 3Dlabs_license.txt

/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2005 Robert Osfield 
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/


#ifndef OSGTOY_GLSLLINTVISITOR
#define OSGTOY_GLSLLINTVISITOR 1

#include <osg/NodeVisitor>
#include <osg/Node>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Program>
#include <osg/Shader>
#include <osg/Uniform>

#include <osgToy/Export.h>
#include <osgToy/GlslLint.h>

namespace osgToy {

/** A visitor to traverse an OSG scenegraph, find osg::Shaders containing
  * GLSL code, and test for portability and conformance with the GLSL
  * specification using the open-source GLSL parser front-end.
  */
class OSGTOY_EXPORT GlslLintVisitor : public osg::NodeVisitor
{
public:
    GlslLintVisitor( osgToy::GlslLint::Options options = osgToy::GlslLint::NONE );
    virtual ~GlslLintVisitor();

    virtual void apply( osg::Geode& geode );
    virtual void apply( osg::Node& node );

    virtual void apply( const osg::StateSet* stateset );
    virtual void apply( const osg::Program* program );
    virtual void apply( const osg::Uniform* uniform );

protected:
    void pushState();
    void popState();

    osgToy::GlslLint::Options _options;
};

}

#endif

// vim: set sw=4 ts=8 et ic ai:
