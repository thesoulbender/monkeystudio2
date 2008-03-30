#ifndef UIXUPMANAGER_H
#define UIXUPMANAGER_H

#include <fresh.h>

#include "ui_UIXUPManager.h"
#include "../../consolemanager/pCommand.h"

#include <QHash>

class ProjectItemModel;
class XUPItem;
class QAction;

class Q_MONKEY_EXPORT UIXUPManager : public QDockWidget, public Ui::UIXUPManager
{
	Q_OBJECT
	
public:
	enum Actions
	{
		New = 0, // new project
		Open, // open project
		SaveCurrent, // save current project
		SaveAll, // save all projects
		CloseCurrent, // close current proejct
		CloseAll, // close all projects
		Add, // add file to current project
		Remove, // remove items/files from current project
		Settings, // open settings dialog for current project
		Source, // show xup source of current project
		Filtered, // view filtered tree
		UserAction // enum for adding custom action to project manager, ie : setAction( UIXUPManager::UserAction +1, ... );
	};
	
	UIXUPManager( QWidget* = 0 );
	~UIXUPManager();

	void initGui();
	
	ProjectItemModel* model() const;

	void registerItem( XUPItem* item );
	void unRegisterItem( XUPItem* item );
	QStringList projectsFilters() const;

	QList<XUPItem*> topLevelProjects() const;
	XUPItem* currentProject() const;
	void setCurrentProject( const XUPItem* );

	XUPItem* currentValue() const;
	XUPItem* currentItem() const;

	QAction* action( UIXUPManager::Actions ) const;
	void setAction( UIXUPManager::Actions, QAction* );

protected:
	ProjectItemModel* mModel;
	QHash<QString, XUPItem*> mRegisteredItems;
	QHash<UIXUPManager::Actions, QAction*> mActions;

	void initializeProject( XUPItem* );

public slots:
	bool openProject( const QString& );
	bool saveProject( XUPItem*, const QString& );

protected slots:
	void actionNewTriggered();
	void actionOpenTriggered();
	void actionSaveCurrentTriggered();
	void actionSaveAllTriggered();
	void actionCloseCurrentTriggered();
	void actionCloseAllTriggered();
	void actionAddTriggered();
	void actionRemoveTriggered();
	void actionSettingsTriggered();
	void actionSourceTriggered();
	void actionFilteredToggled( bool toggled );
	void currentChanged( const QModelIndex&, const QModelIndex& );
	void on_tvProxiedProjects_collapsed( const QModelIndex& );
	void on_tvProxiedProjects_expanded( const QModelIndex& );
	void on_tvProxiedProjects_doubleClicked( const QModelIndex& );
	void internal_projectOpen( XUPItem* );
	void internal_projectAboutToClose( XUPItem* );
	void internal_projectClosed( XUPItem* );
	void internal_projectModifiedChanged( XUPItem*, bool );
	void internal_currentProjectChanged( XUPItem*, XUPItem* );
	void internal_projectDoubleClicked( XUPItem* );
	void internal_fileDoubleClicked( XUPItem*, const QString& );

signals:
	void projectOpen( XUPItem* project );
	void projectAboutToClose( XUPItem* project );
	void projectClosed( XUPItem* project );
	void projectModifiedChanged( XUPItem* project, bool modified );
	void currentProjectChanged( XUPItem* currentProject, XUPItem* previousProject );
	void currentProjectChanged( XUPItem* currentProject );
	void projectDoubleClicked( XUPItem* project );
	void fileDoubleClicked( XUPItem* project, const QString& fileName );
	void fileDoubleClicked( const QString& fileName );
	void projectCustomContextMenuRequested( const QPoint& pos );
	void projectInstallCommandRequested( const pCommand& cmd, const QString& mnu );
	void projectUninstallCommandRequested( const pCommand& cmd, const QString& mnu );
};

#endif // UIXUPMANAGER_H