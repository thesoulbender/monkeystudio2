/****************************************************************************
**
** 		Created using Monkey Studio v1.7.0
** Author    : Nox P@sNox <pasnox@gmail.com>
** Project   : ConsoleManager
** FileName  : ConsoleManager.h
** Date      : mar. août 21 20:52:27 2007
** License   : GPL
** Comment   : Your comment here
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef PCONSOLEMANAGER_H
#define PCONSOLEMANAGER_H

#include "MonkeyExport.h"
#include "QSingleton.h"
#include "pCommand.h"

#include <QApplication>
#include <QProcess>

class pCommandParser;

class Q_MONKEY_EXPORT pConsoleManager : public QProcess, public QSingleton<pConsoleManager>
{
	Q_OBJECT
	friend class QSingleton<pConsoleManager>;
	
public:
	enum StepType { stUnknown = -1, stError, stWarning, stGood, stBad, stCompiling, stState };
	
	struct Step
	{
		QString mFileName;
		QPoint mPosition;
		StepType mType;
		QString mText;
		QString mFullText;
	};
	
	pCommand currentCommand() const { return mCommands.value( 0 ); }
	QStringList parsersName() const
	{ return mParsers.keys(); }
	
	void addParser( pCommandParser* );
	void removeParser( pCommandParser* );
	void removeParser( const QString& );

protected:
	int mTimerId;
	pCommandList mCommands;
	QHash<QString, pCommandParser*> mParsers;
	void timerEvent( QTimerEvent* );

private:
	pConsoleManager( QObject* = QApplication::instance() );
	~pConsoleManager();

public slots:
	void sendRawCommand( const QString& );
	void sendRawData( const QByteArray& );
	void stopCurrentCommand( bool = false );
	void addCommand( const pCommand& );
	void addCommands( const pCommandList& );
	void removeCommand( const pCommand& );
	void removeCommands( const pCommandList& );

private slots:
	void executeProcess();
	void error( QProcess::ProcessError );
	void finished( int, QProcess::ExitStatus );
	void readyRead();
	void started();
	void stateChanged( QProcess::ProcessState );

signals:
	void commandError( const pCommand&, QProcess::ProcessError );
	void commandFinished( const pCommand&, int, QProcess::ExitStatus );
	void commandReadyRead( const pCommand&, const QByteArray& );
	void commandStarted( const pCommand& );
	void commandStateChanged( const pCommand&, QProcess::ProcessState );
	void commandSkipped( const pCommand& );
	void newStepAvailable( const pConsoleManager::Step& );

};

#endif // PCONSOLEMANAGER_H
