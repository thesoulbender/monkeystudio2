
include( ../../plugins.pri )

DESTDIR	= $$MONKEY_PLUGINS_DIR/GNUdbg2
TARGET	= GNUDebugger2
RESOURCES	= src/resources/GNUDebugger.qrc

SOURCES	= src/GNUDebugger.cpp \
	src/DockGNUDebugger.cpp \
	src/kernel/gdbProcess.1.3.cpp \
	src/ui/UIGNUDebuggerSetting.cpp \
	src/kernel/gdbPatternFile.1.3.cpp \
	src/kernel/gdbInterpreter.1.3.cpp \
	src/kernel/gdbRestoreLine.1.3.cpp \
	src/kernel/gdbParser.1.3.cpp \
	src/kernel/gdbConnectTemplate.cpp \
	src/kernel/gdbBridgeEditor.cpp \
	src/kernel/gdbKernelDispatcher.cpp \
	src/kernel/gdbCore.cpp \
	src/addon/gdbBreakpoint.cpp \
	src/addon/gdbBacktrace.cpp


FORMS	= src/ui/UIGNUDebuggerSetting.ui

OPENEDFILES	= src/ui/UIsetting.h \
	src/ui/UIsetting.cpp \
	src/GNUDebugger.h \
	src/GNUDebugger.cpp

HEADERS	= src/GNUDebugger.h \
	src/DockGNUDebugger.h \
	src/kernel/gdbProcess.1.3.h \
	src/ui/UIGNUDebuggerSetting.h \
	src/kernel/gdbPatternFile.1.3.h \
	src/kernel/gdbInterpreter.1.3.h \
	src/kernel/gdbRestoreLine.1.3.h \
	src/kernel/gdbParser.1.3.h \
	src/kernel/gdbConnectTemplate.h \
	src/kernel/gdbBridgeEditor.h \
	src/kernel/gdbKernelDispatcher.h \
	src/kernel/gdbCore.h \
	src/addon/gdbBreakpoint.h \
	src/addon/gdbBacktrace.h

