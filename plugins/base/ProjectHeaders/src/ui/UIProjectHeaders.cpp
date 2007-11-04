/****************************************************************************
**
** 		Created using Monkey Studio v1.8.0.0
** Author    : Azevedo Filipe aka Nox P@sNox <pasnox@gmail.com>
** Project   : UIProjectHeaders
** FileName  : UIProjectHeaders.cpp
** Date      : 2007-11-04T02:21:34
** License   : GPL
** Comment   : Your comment here
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "UIProjectHeaders.h"
#include "pMonkeyStudio.h"

#include <QDir>
#include <QFileInfoList>
#include <QTextCodec>
#include <QHash>
#include <QStringList>

using namespace pMonkeyStudio;

UIProjectHeaders::UIProjectHeaders( QWidget* p )
	: QDialog( p )
{
	setupUi( this );
	cbLanguages->addItems( availableLanguages() );
}

UIProjectHeaders::~UIProjectHeaders()
{}

const QStringList getRecursiveFiles( QDir d, const QStringList& l )
{
	QStringList ll;
	foreach ( QFileInfo f, d.entryInfoList( QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst | QDir::Name ) )
	{
		if ( f.isFile() && ( l.isEmpty() || ( !l.isEmpty() && QDir::match( l, f.fileName() ) ) ) )
			ll << f.absoluteFilePath();
		else if ( f.isDir() )
		{
			d.cd( f.filePath() );
			ll << getRecursiveFiles( d, l );
			d.cdUp();
		}
	}
	return ll;
}

void UIProjectHeaders::accept()
{
	// get filters for this language
	QStringList filters;
	QHash<QString, QStringList> l = availableLanguagesSuffixes();
	foreach ( QString k, l.keys() )
		if ( k == cbLanguages->currentText() )
			foreach ( QString e, l.value( k ) )
				if ( !filters.contains( e ) )
					filters << e;
	
	// regexp
	QRegExp rx( "^(/\\*.*\\*/).*$" );
	rx.setMinimal( true );
	
	// get recursive files
	foreach ( QString fn, getRecursiveFiles( QDir( leDirectory->text() ), filters ) )
	{
		QFile f( fn );
		f.open( QIODevice::ReadWrite | QIODevice::Text );
		QString b = QTextCodec::codecForLocale()->toUnicode( f.readAll() );
		
		int i;
		if ( ( i = rx.indexIn( b ) ) != -1 )
		{
			if ( !question( tr( "Replace Licensing..." ), tr( "There already is a licensing, replace it ?\n\n%1" ).arg( rx.cap( 1 ) ), window() ) )
				continue;
			b.remove( 0, rx.cap( 1 ).length() );
		}
		b.prepend( teLicensing->toPlainText().trimmed() );
		
		f.resize( 0 );
		f.write( qPrintable( b ) );
		f.close();
	}
}
