/****************************************************************************
    Copyright (C) 2005 - 2011  Filipe AZEVEDO & The Monkey Studio Team
    http://monkeystudio.org licensing under the GNU GPL.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
****************************************************************************/
#include "AppDebug.h"
#include "DebugDockWidget.h"

#include <coremanager/MonkeyCore.h>
#include <maininterface/UIMain.h>
#include <pDockToolBar.h>

QWeakPointer<DebugDockWidget> AppDebug::mDock;

void AppDebug::fillPluginInfos()
{
    mPluginInfos.Caption = tr( "Application Debug View" );
    mPluginInfos.Description = tr( "A plugin that help to debug Mks itself" );
    mPluginInfos.Author = "Filipe AZEVEDO aka Nox P@sNox <pasnox@gmail.com>";
    mPluginInfos.Type = BasePlugin::iBase;
    mPluginInfos.Name = PLUGIN_NAME;
    mPluginInfos.Version = "0.5.0";
    mPluginInfos.FirstStartEnabled = false;
    mPluginInfos.HaveSettingsWidget = false;
    mPluginInfos.Pixmap = pIconManager::pixmap( "AppDebug.png", ":/icons" );
}

bool AppDebug::install()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    mDock = QSharedPointer<DebugDockWidget>( new DebugDockWidget );
    qInstallMessageHandler( AppDebug::qtMessageHandler );
#else
    mDock = new DebugDockWidget;
    qInstallMsgHandler( AppDebug::qtMessageHandler );
#endif
    MonkeyCore::mainWindow()->dockToolBar( Qt::LeftToolBarArea )->addDock( mDock.data(), infos().Caption, pIconManager::icon( "AppDebug.png", ":/icons" ) );

    return true;
}

bool AppDebug::uninstall()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    qInstallMessageHandler( 0 );
#else
    qInstallMsgHandler( 0 );
#endif
    mDock.data()->deleteLater();

    return true;
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
void AppDebug::qtMessageHandler( QtMsgType type, const QMessageLogContext& context, const QString& msg )
#else
void AppDebug::qtMessageHandler( QtMsgType type, const char* msg )
#endif
{
    if ( mDock ) {
        mDock.data()->qtMessageHandler( type,
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
                                        msg
#else
                                        QString::fromLocal8Bit( msg )
#endif
                                        );
    }
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( BaseAppDebug, AppDebug )
#endif
