//
// File: GrannyModelAOS.cpp
// Created by: Alexander Oster - tensor@ultima-iris.de
//
/*****
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*****/



#include "stdafx.h"
#include "granny/GrannyModelAOS.h"
#include "Debug.h"

#include <cassert>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

cGrannyModelAOS::cGrannyModelAOS (std::string basepath, std::string defaultanim)
{
	last_tick = 0;
	m_animset = 0;
	this->basepath = basepath;
	defaultanimname = defaultanim;

	left_hand_bone = -1;
	right_hand_bone = -1;
	hand = HAND_NONE;

	m_freebodyparts = true;

	bodyparts.assign(14,0);
}

cGrannyModelAOS::~cGrannyModelAOS ()
{
	Free ();
}

void cGrannyModelAOS::Render(int animid, int tick, float & curtime, 
							 GrnMatrix * left_matrix, GrnMatrix * right_matrix)
{
	last_tick = tick;      
	map <int, cGrannyModelTD *>::iterator iter;
	for (iter = models.begin(); iter != models.end(); iter++) 
	{
		assert (iter->second);

		// id 4 is hands part, we need hands matrix for weapon attachment.
		int id = iter->first;
		if (bodyparts.size () > (unsigned int) id)
		if (bodyparts.at (id) == 0)
			iter->second->Render(animid, tick, curtime, id==4? left_matrix: 0, id==4 ? right_matrix : 0);
		//break;
	}
}


int cGrannyModelAOS::Age(int tick)
{
	return tick - last_tick;
}

void cGrannyModelAOS::Free ()
{
	if (m_freebodyparts) 
	{
		map <int, cGrannyModelTD *>::iterator iter;
		for (iter = models.begin(); iter != models.end(); iter++) 
			delete iter->second;
	}
	models.clear();
}

void cGrannyModelAOS::AddAnimation(int animid, std::string filename)
{
	map <int, cGrannyModelTD *>::iterator iter;
	for (iter = models.begin(); iter != models.end(); iter++) 
		iter->second->AddAnimation(animid, filename);
}

cGrannyModel *cGrannyModelAOS::AddModel(int id, std::string filename)
{
	cGrannyModelTD * model = new cGrannyModelTD(filename, basepath, defaultanimname);
	
	if (id == 4) // HANDS Part
		model->SetHand(hand);
	
	models.insert(make_pair(id, model));    
	return model;
}

void cGrannyModelAOS::SetHandBones(int left, int right)
{
	left_hand_bone = left;
	right_hand_bone = right;
}

float cGrannyModelAOS::GetAnimLength(int animid)
{
	map <int, cGrannyModelTD *>::iterator iter = models.begin();
	if (iter != models.end()) 
		return iter->second->GetAnimLength(animid);
	return 0.0f;
}


cGrannyAnimation *cGrannyModelAOS::GetAnimation(int animid)
{
	map <int, cGrannyModelTD *>::iterator iter = models.begin();
	if (iter != models.end()) 
		return iter->second->GetAnimation(animid);
	return NULL;
}

void cGrannyModelAOS::SetColor(dword color)
{
	cGrannyModel::SetColor(color);

	map <int, cGrannyModelTD *>::iterator iter;
	for (iter = models.begin(); iter != models.end(); iter++) 
	{
		iter->second->SetColor(color);
	}
}

void cGrannyModelAOS::ReleaseFile()
{
	map <int, cGrannyModelTD *>::iterator iter;
	for (iter = models.begin(); iter != models.end(); iter++) 
	{
		iter->second->ReleaseFile();
	}
}
