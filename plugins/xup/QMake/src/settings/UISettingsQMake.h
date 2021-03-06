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
#ifndef UISETTINGSQMAKE_H
#define UISETTINGSQMAKE_H

#include <QWidget>
#include <QModelIndex>
#include <QItemSelection>

class Ui_UISettingsQMake;
class QtVersionManager;
class pGenericTableModel;

class QPlainTextEdit;
class QAbstractButton;

class UISettingsQMake : public QWidget
{
    Q_OBJECT
    
public:
    UISettingsQMake( QWidget* parent = 0 );
    ~UISettingsQMake();

protected:
    Ui_UISettingsQMake* ui;
    QBrush mBackground;
    QBrush mForeground;
    QtVersionManager* mQtManager;
    pGenericTableModel* mQtVersionsModel;
    pGenericTableModel* mQtModulesModel;
    pGenericTableModel* mQtConfigurationsModel;
    
    void loadSettings();
    void goAtDocumentStart( QPlainTextEdit* pte );
    
    // qt versions
    void setQtVersion( const QModelIndex& index );
    void getQtVersion( const QModelIndex& index );
    void updateQtVersionState();
    
    // qt modules
    void setQtModule( const QModelIndex& index );
    void getQtModule( const QModelIndex& index );
    void updateQtModuleState();
    
    // qt configuration
    void setQtConfiguration( const QModelIndex& index );
    void getQtConfiguration( const QModelIndex& index );
    void updateQtConfigurationState();

protected slots:
    void on_lwPages_currentRowChanged( int row );
    void updateMkSpecsEntries( const QString& currentMkSpec = QString( "#null" ) );
    
    // qt versions
    void lvQtVersions_selectionModel_selectionChanged( const QItemSelection& selected, const QItemSelection& deselected );
    void on_tbAddQtVersion_clicked();
    void on_tbRemoveQtVersion_clicked();
    void on_tbClearQtVersions_clicked();
    void on_tbUpQtVersion_clicked();
    void on_tbDownQtVersion_clicked();
    void on_tbDefaultQtVersion_clicked();
    void on_tbQtVersionPath_clicked();
    void on_tbQtVersionQMakeSpec_clicked();
    
    // qt modules
    void lvQtModules_selectionModel_selectionChanged( const QItemSelection& selected, const QItemSelection& deselected );
    void on_tbAddQtModule_clicked();
    void on_tbRemoveQtModule_clicked();
    void on_tbClearQtModules_clicked();
    void on_tbUpQtModule_clicked();
    void on_tbDownQtModule_clicked();
    
    // qt modules
    void lvQtConfigurations_selectionModel_selectionChanged( const QItemSelection& selected, const QItemSelection& deselected );
    void on_tbAddQtConfiguration_clicked();
    void on_tbRemoveQtConfiguration_clicked();
    void on_tbClearQtConfigurations_clicked();
    void on_tbUpQtConfiguration_clicked();
    void on_tbDownQtConfiguration_clicked();
    
    void on_dbbButtons_clicked( QAbstractButton* button );
};

#endif // UISETTINGSQMAKE_H
