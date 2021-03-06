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
    \file pTabbedMainWindow.h
    \date 2008-01-14T00:27:51
    \author Filipe AZEVEDO aka Nox P\@sNox <pasnox@gmail.com>
    \brief An extended QMainWindow
*/
#ifndef PTABBEDMAINWINDOW_H
#define PTABBEDMAINWINDOW_H

#include "../objects/MonkeyExport.h"
#include "pMainWindow.h"

class pTabbedWorkspace;

/*!
    \brief An extended QMainWindow
    \details that internally handle a pTabbedWorkspace as central widget
*/
class Q_MONKEY_EXPORT pTabbedMainWindow : public pMainWindow
{
    Q_OBJECT

public:
    pTabbedMainWindow( QWidget* parent = 0, Qt::WindowFlags windowFlags = 0 );

    pTabbedWorkspace* tabbedWorkspace();

private:
    pTabbedWorkspace* mWorkspace;

public slots:
    virtual void saveState();
    virtual void restoreState();
};

#endif // PTABBEDMAINWINDOW_H
