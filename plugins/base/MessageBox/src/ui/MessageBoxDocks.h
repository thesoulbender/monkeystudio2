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
/*!
    \file MessageBoxDocks.h
    \date 2008-01-14T00:40:08
    \author Filipe AZEVEDO, Andrei KOPATS
    \brief Header of MessageBoxDocks class
    
    File also contains classes of tabs of Message Box
    MessageBox
*/

#ifndef MESSAGEBOXDOCKS_H
#define MESSAGEBOXDOCKS_H

#include "ui_UIBuildStep.h"
#include "ui_UIOutput.h"

#include <pIconManager.h>
#include <consolemanager/pConsoleManager.h>
#include <pDockWidgetTitleBar.h>
#include <coremanager/MonkeyCore.h>
#include <pMenuBar.h>

class pConsoleManagerStepModel;

/*!
    Implementation of Build Steps tab of Message box
*/
class UIBuildStep : public pDockWidget, public Ui::UIBuildStep
{
    Q_OBJECT
    
public:
    UIBuildStep( QWidget* parent = 0 )
        : pDockWidget( parent )
    {
        setObjectName( metaObject()->className() );
        
        setupUi( this );
        lvBuildSteps->setAttribute( Qt::WA_MacShowFocusRect, false );
        lvBuildSteps->setAttribute( Qt::WA_MacSmallSize );
        
        titleBar()->addAction( MonkeyCore::menuBar()->action( "mView/aShowNextErrorOrWarning" ), 0 );
        titleBar()->addAction( MonkeyCore::menuBar()->action( "mView/aShowNextWarning" ), 1 );
        titleBar()->addAction( MonkeyCore::menuBar()->action( "mView/aShowNextError" ), 2 );
        titleBar()->addSeparator( 3 );
    }
};

/*!
    Implementation of Output tab of Message box
*/
class UIOutput : public pDockWidget, public Ui::UIOutput
{
    Q_OBJECT
    
public:
    UIOutput( QWidget* parent = 0 )
        : pDockWidget( parent )
    {
        setObjectName( metaObject()->className() );
        
        setupUi( this );
        tbOutput->setAttribute( Qt::WA_MacShowFocusRect, false );
        tbOutput->setAttribute( Qt::WA_MacSmallSize );
    }
};

/*!
    Implementation of GUI of MessageBox plugin
    
    Manages tabs, implements functionality of plugin. Appends and removes 
    information from docks, according with signals from sources of information)
    Allows to show some tab of message box
*/
class MessageBoxDocks : public QObject
{
    Q_OBJECT
    friend class MessageBox;
    
public:
    MessageBoxDocks( QObject* parent = 0 );
    ~MessageBoxDocks();
    
    QString colourText( const QString&, const QColor& = Qt::black );

protected:
    UIBuildStep* mBuildStep;
    UIOutput* mOutput;
    pConsoleManagerStepModel* mStepModel;

public slots:
    void appendOutput( const QString& );
    void appendLog( const QString& );
    void appendInBox( const QString&, const QColor& = Qt::red );
    void appendStep( const pConsoleManagerStep& step );
    void appendSteps( const pConsoleManagerStepList& steps );
    void showBuild();
    void showOutput();
    void showNextErrorOrWarning();
    void showNextWarning();
    void showNextError();

protected slots:
    void lvBuildSteps_activated( const QModelIndex& index );
    void commandError( const pCommand& command, QProcess::ProcessError error );
    void commandFinished( const pCommand& command, int exitCode, QProcess::ExitStatus exitStatus );
    void commandReadyRead( const pCommand& command, const QByteArray& data );
    void commandStarted( const pCommand& command );
    void commandStateChanged( const pCommand& command, QProcess::ProcessState state );
    void commandSkipped( const pCommand& command );
};

#endif // MESSAGEBOXDOCKS_H
