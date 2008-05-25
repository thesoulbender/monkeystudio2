//==========================================

/*
	Class GdbControl
*/

#include "gdbControl.h"

#include <QFileDialog>
#include <QIcon>
#include <QToolTip>

GdbControl::GdbControl(GdbParser *p) :  GdbCore( p),
	interpreterEndSteppingRange(NULL)
{
	mWidget = new QFrame();
	QVBoxLayout *h = new QVBoxLayout(mWidget);
	
	bStepOver = new QPushButton();
	bRun = new QPushButton();
	bStepInto = new QPushButton();
	bContinue = new QPushButton();
	bStop = new QPushButton();
	bLoadTarget = new QPushButton();
	bExitGdb = new QPushButton();

	bExitGdb->setIcon(QIcon(":/icons/close.png"));
	bExitGdb-> setIconSize (QSize(13,13));
	bExitGdb->setEnabled(false);
	bExitGdb->setToolTip("Exit debugging mode");

	bRun->setIcon(QIcon(":/icons/update.png"));
	bRun-> setIconSize (QSize(13,13));
	bRun->setEnabled(false);
	bRun->setToolTip("Start or restart");

	bStop->setIcon(QIcon(":/icons/stop.png"));
	bStop-> setIconSize (QSize(13,13));
	bStop->setEnabled(false);
	bStop->setToolTip("Stop debugging");

	bLoadTarget->setIcon(QIcon(":/icons/file.png"));
	bLoadTarget-> setIconSize (QSize(13,13));
	bLoadTarget->setToolTip("Load target");

	bContinue->setIcon(QIcon(":/icons/play.png"));
	bContinue-> setIconSize (QSize(13,13));
	bContinue->setEnabled(false);
	bContinue->setToolTip("Run to next breakpoint");

	bStepOver->setIcon(QIcon(":/icons/stepover.png"));
	bStepOver-> setIconSize (QSize(13,13));
	bStepOver->setEnabled(false);
	bStepOver->setToolTip("Execute step over");

	bStepInto->setIcon(QIcon(":/icons/stepinto.png"));
	bStepInto-> setIconSize (QSize(13,13));
	bStepInto->setEnabled(false);
	bStepInto->setToolTip("Execute step into");


	h->setSpacing(0);
	h->addWidget(bLoadTarget);
	h->addWidget(bRun);
	h->addWidget(bContinue);
	h->addWidget(bStepOver);
	h->addWidget(bStepInto);
	h->addWidget(bStop);
	h->addWidget(bExitGdb);

//	getContainer()->setWidget(mWidget);
//	getContainer()->setWindowTitle(name());

	connect (bLoadTarget, SIGNAL(clicked()), this, SLOT(onLoadTarget()));
	connect (bStepOver, SIGNAL(clicked()), this, SLOT(onStepOver()));
	connect (bStepInto, SIGNAL(clicked()), this, SLOT(onStepInto()));
	connect (bRun, SIGNAL(clicked()), this, SLOT(onRun()));
	connect (bContinue, SIGNAL(clicked()), this, SLOT(onContinue()));
	connect (bStop, SIGNAL(clicked()), this, SLOT(onStop()));
	connect (bExitGdb, SIGNAL(clicked()), this,SLOT(onExit()));

	cmd.setClass(this);
	
	cmd.connectEventNotify("notify-question", &GdbControl::processQuestion);

	start();
} 
//
GdbControl::~GdbControl()
{
	delete bRun;
	delete bStop;
	delete bExitGdb;
	delete bStepInto;
	delete bStepOver;
	delete bLoadTarget;
	delete bContinue;
	//delete h;
	delete mWidget;
	
//	delete getContainer();
} 
//
void GdbControl::setAction(QHash<QString, QAction *> *a)
{
	mActionList = a;
}


QString GdbControl::name()
{
	 return "GdbControl"; 
}
//
int GdbControl::process(QGdbMessageCore m)
{
	return cmd.dispatchProcess(m);
}
//
int GdbControl::processError(QGdbMessageCore m)
{
	// TODO
	QMessageBox::warning(NULL, "Error in GDB Control", m.msg);
 
	return PROCESS_TERMINED;
}
//
void GdbControl::processPrompt()
{
}
//
void GdbControl::onLoadTarget()
{
	QFileDialog *d = new QFileDialog(NULL,"Select target");
	 if (d->exec())
	 {
		QStringList fileNames = d->selectedFiles(); 
		QString file = fileNames.at(0);
		file.replace('\\','/');
		emit wantStart(file);

//		emit sendRawData(this,"file " + file.toLocal8Bit());
	 }
	d->close();
	delete d;
}
// step over or into
int GdbControl::processSteps(QGdbMessageCore m)
{
// no warning
m=m;

		mActionList->value("aRestart")->setEnabled(true);

		mActionList->value("aStepOver")->setEnabled(true);
		mActionList->value("aStepInto")->setEnabled(true);
		mActionList->value("aContinue")->setEnabled(true);
		mActionList->value("aStop")->setEnabled(true);
		mActionList->value("aExitGdb")->setEnabled(true);

		bRun->setEnabled(true);
		bStepOver->setEnabled(true);
		bStepInto->setEnabled(true);
		bContinue->setEnabled(true);
		bStop->setEnabled(true);
		bExitGdb->setEnabled(true);

		cmd.disconnectEventInterpreter(interpreterEndSteppingRange);
		cmd.leaveEventInterpreter(&interpreterEndSteppingRange);
		return PROCESS_TERMINED;
}
//
int GdbControl::processQuestion(QGdbMessageCore m)
{
	QByteArray currentQuestion = getParametre("currentQuestion=", m.msg);

	// questions pris en charges
	QRegExp kill("^Kill the program being debugged\\? \\(y or n\\) $");
	QRegExp restart("^Start it from the beginning\\? \\(y or n\\) $");

	if(kill.exactMatch( currentQuestion))
	{
		mActionList->value("aRestart")->setEnabled(true);
		mActionList->value("aStepOver")->setEnabled(false);
		mActionList->value("aStepInto")->setEnabled(false);
		mActionList->value("aContinue")->setEnabled(false);
		mActionList->value("aStop")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(false);

		bRun->setEnabled(true);
		bStop->setEnabled(false);
		bStepOver->setEnabled(false);
		bStepInto->setEnabled(false);
		bContinue->setEnabled(false);
		bExitGdb->setEnabled(false);
	}

	if(restart.exactMatch( currentQuestion))
	{
		mActionList->value("aRestart")->setEnabled(false);
		mActionList->value("aStepOver")->setEnabled(false);
		mActionList->value("aStepInto")->setEnabled(false);
		mActionList->value("aContinue")->setEnabled(false);
		mActionList->value("aStop")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(false);

		bRun->setEnabled(false);
		bStop->setEnabled(false);
		bStepOver->setEnabled(false);
		bStepInto->setEnabled(false);
		bContinue->setEnabled(false);
		bExitGdb->setEnabled(false);
	}

	return PROCESS_TERMINED;
}
//
void GdbControl::onStepOver()
{
		mActionList->value("aRestart")->setEnabled(false);
		mActionList->value("aStepOver")->setEnabled(false);
		mActionList->value("aStepInto")->setEnabled(false);
		mActionList->value("aContinue")->setEnabled(false);
		mActionList->value("aStop")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(false);

		bRun->setEnabled(false);
	bStepOver->setEnabled(false);
	bStepInto->setEnabled(false);
	bContinue->setEnabled(false);
	bStop->setEnabled(false);
	bExitGdb->setEnabled(false);

	interpreterEndSteppingRange = new QGdbInterpreter("end-stepping-range",
	"n",
	QRegExp("^n"), 
	QRegExp("^\\d+\\s+.*"),
	"");
	
	cmd.connectEventInterpreter(interpreterEndSteppingRange, &GdbControl::processSteps);
	cmd.forceProcess();
}
//
void GdbControl::onStepInto()
{
		mActionList->value("aRestart")->setEnabled(false);
		mActionList->value("aStepOver")->setEnabled(false);
		mActionList->value("aStepInto")->setEnabled(false);
		mActionList->value("aContinue")->setEnabled(false);
		mActionList->value("aStop")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(false);

		bRun->setEnabled(false);

	bStepOver->setEnabled(false);
	bStepInto->setEnabled(false);
	bContinue->setEnabled(false);
	bStop->setEnabled(false);
	bExitGdb->setEnabled(false);

	interpreterEndSteppingRange = new QGdbInterpreter("end-stepping-range",
	"s",
	QRegExp("^s"), 
	QRegExp("^\\d+\\s+.*"),
	"");
	cmd.connectEventInterpreter(interpreterEndSteppingRange, &GdbControl::processSteps);
	cmd.forceProcess();
}
//
void GdbControl::onRun()
{
//	bRun->setEnabled(false);
	emit sendRawData(this,"r");
}
//
void GdbControl::onContinue()
{
	emit sendRawData(this,"c");
}
//
void GdbControl::onStop()
{
	emit sendRawData(this,"kill");
}
//
void GdbControl::onExit()
{
	emit wantExit();
}
//
void GdbControl::gdbStarted()
{
	GdbCore::gdbStarted();
	bExitGdb->setEnabled(true);
		mActionList->value("aExitGdb")->setEnabled(true);
}
//
void GdbControl::gdbFinished()
{
	GdbCore::gdbFinished();

		mActionList->value("aLoadTarget")->setEnabled(true);
		mActionList->value("aRestart")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(false);

	bLoadTarget->setEnabled(true);
	bExitGdb->setEnabled(false);
	bRun->setEnabled(false);
}
//
void GdbControl::targetLoaded()
{
	GdbCore::targetLoaded();
	bRun->setEnabled(true);
	bExitGdb->setEnabled(true);
	bLoadTarget->setEnabled(false);

		mActionList->value("aRestart")->setEnabled(true);
		mActionList->value("aLoadTarget")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(true);
}
//
void GdbControl::targetRunning()
{
	GdbCore::targetRunning();

	bRun->setEnabled(false);
	bStepOver->setEnabled(false);
	bStepInto->setEnabled(false);
	bContinue->setEnabled(false);
	bStop->setEnabled(false);
	bExitGdb->setEnabled(false);

		mActionList->value("aRestart")->setEnabled(false);
		mActionList->value("aStepOver")->setEnabled(false);
		mActionList->value("aStepInto")->setEnabled(false);
		mActionList->value("aContinue")->setEnabled(false);
		mActionList->value("aStop")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(false);
}
//
void GdbControl::targetStopped()
{
	GdbCore::targetStopped();

	bRun->setEnabled(true);
	bStepOver->setEnabled(true);
	bStepInto->setEnabled(true);
	bContinue->setEnabled(true);
	bStop->setEnabled(true);
	bExitGdb->setEnabled(true);

		mActionList->value("aRestart")->setEnabled(true);
		mActionList->value("aStepOver")->setEnabled(true);
		mActionList->value("aStepInto")->setEnabled(true);
		mActionList->value("aContinue")->setEnabled(true);
		mActionList->value("aStop")->setEnabled(true);
		mActionList->value("aExitGdb")->setEnabled(true);

}
//
void GdbControl::targetExited()
{
	GdbCore::targetExited();

	bRun->setEnabled(true);
	bStepOver->setEnabled(false);
	bStepInto->setEnabled(false);
	bContinue->setEnabled(false);
	bStop->setEnabled(false);
	bExitGdb->setEnabled(true);

		mActionList->value("aRestart")->setEnabled(true);
		mActionList->value("aStepOver")->setEnabled(false);
		mActionList->value("aStepInto")->setEnabled(false);
		mActionList->value("aContinue")->setEnabled(false);
		mActionList->value("aStop")->setEnabled(false);
		mActionList->value("aExitGdb")->setEnabled(true);
}
//
