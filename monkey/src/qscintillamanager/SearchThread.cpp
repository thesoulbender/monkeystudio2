#include "SearchThread.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QList>
#include <QDir>

#include <QDebug>

class DirWalkIterator
{
protected:
	QList<QStringList> mDirStack;
	QStringList mFilesList;
	QStringList mDirList;
	QString currentDir;
	
	void enterDirrectory (QString dir)
	{
		QStringList dirs = QDir(dir).entryList (QDir::Dirs | QDir::NoDotAndDotDot);
		currentDir = dir;
		for (int i = 0; i < dirs.size (); i++)
			dirs[i] = currentDir +'/'+ dirs[i];
		mDirStack.prepend (dirs);
		mFilesList = QDir(dir).entryList (QDir::Files);
	}
	
	bool findDirWithFiles ()
	{
		while (!mDirStack.isEmpty() && mFilesList.isEmpty())
		{
			if (!mDirStack.first().isEmpty()) // 1 level down
			{
				enterDirrectory (mDirStack.first().takeFirst());
			}
			else // one level up. Will enter next dir on next WHILE iteration
				mDirStack.takeFirst ();
		}
		return !mFilesList.isEmpty();
	}

public:
	DirWalkIterator (QString dir)
	{
		enterDirrectory (dir);
	}
	
	QString next()
	{
		// Find dirrectory with files, return "", if finished search
		if (!findDirWithFiles ())
		{
			return QString::null;
		}
		
		return currentDir + '/' + mFilesList.takeFirst();
	}
};

SearchThread::SearchThread(const QString &_dir, const QString &_text, bool _isWhole, bool _isMatch, bool _isReg, QObject* parent)
    : QThread(parent)/*, mTerm(false)*/
{
    dir = _dir;
    text = _text;
    isWhole = _isWhole;
    isMatch = _isMatch;
    isReg = _isReg;
    qWarning () << "Created thread with dir " << dir;
    qWarning () << "Searching " << text;
}

SearchThread::~SearchThread()
{
}

void SearchThread::run()
{
    qWarning () << "Thread started";
	DirWalkIterator dirWalker (dir);
    int files_count = 0;
    QString fileName = dirWalker.next();
    while (!fileName.isNull())
    {
        emit changeProgress(++files_count);
        QFile file(fileName);
        qWarning () << "Processing file " << fileName;
        if (file.open(QIODevice::ReadOnly)) 
        {
            QString line;
            QTextStream in(&file);
            int i = 0;
            while (!in.atEnd() /*&& !isTermEnabled()*/) 
            {
                ++i;
                line = in.readLine();
                //qWarning () << "Readed line " << line;
                
                bool ifContains = false;
                if (isReg)
                    ifContains = line.contains(QRegExp(text));
                else
                {
                        ifContains = line.contains(QRegExp("\\b"+text+"\\b"));
                }
                if (ifContains) 
                {
                    pConsoleManager::Step step;
                    step.mFileName = file.fileName();
                    step.mPosition = QPoint (0,i);
                    step.mText = line.simplified();
                    emit appendSearchResult (step);
                }
            }
        }
        if (isTermEnabled())
        {
            quit();
            break;
        }
        fileName = dirWalker.next();
    }
    qWarning () << "Thread finished";
}
