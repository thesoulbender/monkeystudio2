/****************************************************************************
**
** Authors   : Andrei KOPATS aka hlamer <hlamer@tut.by>
** Project   : Beaver Debugger plugin
** FileName  : BeaverDebugger.h
** Date      : 
** License   : GPL
** Comment   : 
** Home Page : http://www.monkeystudio.org
**
	Copyright (C) 2005 - 2008  Andrei KOPATS & The Monkey Studio Team

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
**
****************************************************************************/
/*!
	\file BeaverDebugger.h
	\date 2008-01-14T00:40:08
	\author Filipe AZEVEDO, Andrei KOPATS
	\brief Header file for BeaverDebugger plugin
*/
#ifndef BEAVER_DEBUGGER
#define BEAVER_DEBUGGER

#include <BasePlugin.h>

#include <QPointer>

/*!
	Main class of BeaverDebugger plugin
	
	Plugin allows to use Beaver Debugger with MkS
*/
class BeaverDebugger : public BasePlugin
{
	Q_OBJECT
	Q_INTERFACES( BasePlugin )

public:
	PluginInfos infos() const;
	virtual bool setEnabled( bool );
	virtual QWidget* settingsWidget();
protected slots:
	void explainWhyCannot() const;
};

#endif
