#PROJECT(OSGVRPN_PLUGINS)

SET(LIBRARY_OUTPUT_PATH "${LIBRARY_OUTPUT_PATH}/osgPlugins")

SET(TARGET_DEFAULT_PREFIX "osgdb_")
SET(TARGET_DEFAULT_LABEL_PREFIX "Plug osgVRPN")
SET(TARGET_COMMON_LIBRARIES 
        OpenThreads
	osg 
	osgVRPN
)

ADD_SUBDIRECTORY(tracker)

# vim: set sw=4 ts=8 et ic ai:
