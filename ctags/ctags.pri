# Monkey Studio 2 Ctags project include file

# include shared ctags project file
include( $${PWD}/ctags_shared.pri )

# include path
INCLUDEPATH *= $${PWD}/$${CTAGS_VERSION}
#INCLUDEPATH    *= $$getFolders( $${PWD}/$${CTAGS_VERSION} )

# dependency
PRE_TARGETDEPS  *= $${PWD}

# library integration
CTAGS_TARGET    = ctags
LIBS    *= -L$${PACKAGE_BUILD_PATH}/$${Q_TARGET_ARCH}/$$buildMode()

contains( TEMPLATE, .*app ) {
    CONFIG(debug, debug|release) {
        #Debug
        unix:LIBS   *= -l$${CTAGS_TARGET}_debug
        else:LIBS   *= -l$${CTAGS_TARGET}d
    } else {
        #Release
        LIBS    *= -l$${CTAGS_TARGET}
    }
}
