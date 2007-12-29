#ifndef FILTEREDPROJECTITEMMODEL_H
#define FILTEREDPROJECTITEMMODEL_H

#include <QStandardItemModel>
#include <QHash>

#include "ProjectItem.h"

class ProjectItemModel;

class FilteredProjectItem : public QStandardItem
{
public:
	FilteredProjectItem( ProjectItem* it )
	{
		mItem = it;
		Q_ASSERT( mItem );
	}
	
	virtual QVariant data( int r = Qt::UserRole +1 ) const
	{ return mItem->data( r ); }
	
	virtual FilteredProjectItem* child( int r, int c = 0 ) const
	{ return dynamic_cast<FilteredProjectItem*>( QStandardItem::child( r, c ) ); }
	
	virtual void appendRow( FilteredProjectItem* it )
	{ insertRow( rowCount(), it ); }
	
	virtual void insertRow( int i, FilteredProjectItem* it )
	{ QStandardItem::insertRow( i, it ); }
	
	ProjectItem* item() const
	{ return mItem; }
	
protected:
	ProjectItem* mItem;
};

class FilteredProjectItemModel : public QStandardItemModel
{
	Q_OBJECT
	
public:
	FilteredProjectItemModel( ProjectItemModel* = 0 );
	~FilteredProjectItemModel();

	// return item for row / column
	FilteredProjectItem* item( int, int = 0 ) const;
	// return item from index
	FilteredProjectItem* itemFromIndex( const QModelIndex& ) const;
	// append row item
	void appendRow( FilteredProjectItem* );

	void setSourceModel( ProjectItemModel* );
	ProjectItemModel* sourceModel() const;
	QModelIndex mapFromSource( const QModelIndex& ) const;
	QModelIndex mapToSource( const QModelIndex& ) const;

private:
	FilteredProjectItem* getFolder( ProjectItem*, FilteredProjectItem* = 0 );
	FilteredProjectItem* getVariable( ProjectItem* );
	void addVariable( ProjectItem* );
	void projectInserted( ProjectItem* );
	ProjectItemModel* mSourceModel;
	QHash<ProjectItem*, FilteredProjectItem*> mItems;

private slots:
	//void columnsAboutToBeInserted( const QModelIndex& parent, int start, int end );
	//void columnsAboutToBeRemoved( const QModelIndex& parent, int start, int end );
	//void columnsInserted( const QModelIndex& parent, int start, int end );
	//void columnsRemoved( const QModelIndex& parent, int start, int end );
	//void dataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight );
	void headerDataChanged( Qt::Orientation orientation, int first, int last );
	void layoutAboutToBeChanged();
	void layoutChanged();
	void modelAboutToBeReset();
	void modelReset();
	//void rowsAboutToBeInserted( const QModelIndex& parent, int start, int end );
	void rowsAboutToBeRemoved( const QModelIndex& parent, int start, int end );
	void rowsInserted( const QModelIndex& parent, int start, int end );
	//void rowsRemoved( const QModelIndex& parent, int start, int end );
};

#endif // FILTEREDPROJECTITEMMODEL_H
