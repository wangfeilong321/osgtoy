/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2005 Robert Osfield 
 *
 * This application is open source and may be redistributed and/or modified   
 * freely and without restriction, both in commericial and non commericial applications,
 * as long as this copyright notice is maintained.
 * 
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/* file:      examples/osgVRPNviewer/osgVRPNviewer.cpp
 * author:    Mike Weiblen
 * copyright: (C) 2003-2007 Michael Weiblen http://mew.cx/
 * license:   OpenSceneGraph Public License (OSGPL)
 * $Id$
*/

#include <iostream>

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Vec3>
#include <osg/io_utils>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgVRPN/TrackerBase.h>
#include <osgVRPN/Tracker.h>
#include <osgVRPN/AnalogTracker.h>
#include <osgVRPN/TrackerTransform.h>
#include <osgVRPN/TrackerManipulator.h>

///////////////////////////////////////////////////////////////////////////

static bool gUseAnalogTracker(false);

static osgVRPN::TrackerBase* myTrackerFactory( osgViewer::Viewer* viewer )
{
    if( ! gUseAnalogTracker )
        return new osgVRPN::Tracker( "Tracker0@localhost" );

    const char* deviceName( "Spaceball0@localhost" );
    osgVRPN::AnalogTracker* trk( new osgVRPN::AnalogTracker() );
    trk->setViewer( viewer );
    trk->setAnalogDevice( new osgVRPN::Analog( deviceName ) );
    trk->setTranslateChannelX(0);
    trk->setTranslateChannelY(1);
    trk->setTranslateChannelZ(2);
    trk->setRotateChannelX(3);
    trk->setRotateChannelY(4);
    trk->setRotateChannelZ(5);
    trk->setTranslationScale(osg::Vec3(50,50,50));
    trk->setRotationScale(osg::Vec3(5,5,5));
    trk->setButtonDevice( new osgVRPN::Button( deviceName ) );
    trk->setResetButton(0);
    return trk;
}

///////////////////////////////////////////////////////////////////////////
// camera manipulator's ui event handler (for keypresses etc)

class AppKeyHandler : public osgGA::GUIEventHandler
{
public:
    AppKeyHandler( osg::ref_ptr<osgVRPN::TrackerBase> tracker ) : _tracker( tracker ) {}

    bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& )
    {
        if( ea.getEventType() != osgGA::GUIEventAdapter::KEYDOWN ) return false;

        switch( ea.getKey() )
        {
            case osgGA::GUIEventAdapter::KEY_Up:
                adjustScale( 1.1f );
                return true;

            case osgGA::GUIEventAdapter::KEY_Down:
                adjustScale( 1.0f / 1.1f );
                return true;

            default: break;
        }
        return false;
    }

private:
    void adjustScale( float multiplier )
    {
        if( ! _tracker.valid() ) return;
        osg::Vec3 scale = _tracker->getTranslationScale() * multiplier;
        _tracker->setTranslationScale( scale );
        osg::notify(osg::INFO) << "Tracker scale = " << scale << std::endl;
    }

    osg::ref_ptr<osgVRPN::TrackerBase> _tracker;
};

///////////////////////////////////////////////////////////////////////////

osg::Node* buildTestScene( osgVRPN::TrackerBase* tracker, bool useTrackerTransform )
{
    osg::Group* scene( new osg::Group );
    osg::Geode* geode(0);

    geode = new osg::Geode;
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0,0,-2),100,100,0.1)));
    osg::Texture2D* tex0( new osg::Texture2D );
    tex0->setImage( osgDB::readImageFile( "Images/lz.rgb" ) );
    geode->getOrCreateStateSet()->setTextureAttributeAndModes( 0, tex0, osg::StateAttribute::ON );
    scene->addChild( geode );

    geode = new osg::Geode;
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0,0,0),3,3,0.1)));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(40,0,0),5)));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(0,40,0),2,9)));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(-40,0,0),3,7)));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0,-40,0),7,7,7)));
    scene->addChild( geode );

    geode = new osg::Geode;
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(0,0,0),1,2)));
    if( useTrackerTransform )
    {
        osgVRPN::TrackerTransform* xform( new osgVRPN::TrackerTransform(tracker) );
        xform->addChild( geode );
        scene->addChild( xform );
    }
    else
    {
        scene->addChild( geode );
    }

    return scene;
}

///////////////////////////////////////////////////////////////////////////

static bool gUseTrackerManipulator(true);
static bool gUseTrackerTransform( !gUseTrackerManipulator );

int main( int argc, char *argv[] )
{
    osg::ArgumentParser args( &argc, argv );
    args.getApplicationUsage()->setApplicationName( args.getApplicationName() );
    args.getApplicationUsage()->setDescription(args.getApplicationName()+" demonstrates osgVRPN");
    args.getApplicationUsage()->setCommandLineUsage(args.getApplicationName()+" [options]");
    args.getApplicationUsage()->addCommandLineOption("-h or --help","Display this information");
    args.getApplicationUsage()->addKeyboardMouseBinding( "upArrow", "increase tracker scale" );
    args.getApplicationUsage()->addKeyboardMouseBinding( "downArrow", "decrease tracker scale" );

    osgViewer::Viewer viewer;

    viewer.getUsage( *args.getApplicationUsage() );
    if (args.read("-h") || args.read("--help"))
    {
        args.getApplicationUsage()->write(std::cout);
        return 1;
    }

    osgVRPN::TrackerBase* tracker( myTrackerFactory( 0 /*&viewer*/ ) );
    viewer.getEventHandlerList().push_front( new AppKeyHandler( tracker ) );

    osg::Node* theScene(0);
    if( args.argc() > 1 )
    {
        theScene = osgDB::readNodeFiles(args);
        if( !theScene ) 
        {
            std::cout << args.getApplicationName() <<": No data loaded" << std::endl;
            return 1;
        }

        //osgUtil::Optimizer optimizer;
        //optimizer.optimize( theScene );
    }
    else
    {
        theScene = buildTestScene( tracker, gUseTrackerTransform );
    }

    if( gUseTrackerManipulator )
    {
        osgVRPN::TrackerManipulator* manip( new osgVRPN::TrackerManipulator(tracker) );
        unsigned int pos( viewer.addCameraManipulator(manip) );
        viewer.selectCameraManipulator( pos );

        manip->setAutoComputeHomePosition(false);
        //manip->setHomeMatrix( osg::Matrix::translate(0,0,10) * osg::Matrixd::rotate(1.2,1,0,0) );
{
    const osg::BoundingSphere& bs = theScene->getBound();
    manip->setHomeMatrix( osg::Matrix::translate(0,0,1.5*bs._radius) * osg::Matrixd::rotate(1.2,1,0,0) );
}

    }

    viewer.setSceneData( theScene );
    viewer.realize();
    while( !viewer.done() )
    {
        viewer.sync();
        viewer.update();

        if( 1 )
        {   // set clearcolor based on view orientation
            osg::Vec3 eye, center, up;
            viewer.getViewMatrix().getLookAt( eye, center, up );
            osg::Vec3 dirColor( center - eye );
            dirColor.normalize();
            dirColor += osg::Vec3(1,1,1);
            dirColor *= 0.5f;
            viewer.setClearColor( osg::Vec4(dirColor,1) );
        }

        viewer.frame();
    }
    viewer.sync();
    return 0;
}

// vim: set sw=4 ts=8 et ic ai:
