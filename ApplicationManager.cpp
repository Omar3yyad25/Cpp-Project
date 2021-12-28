#include <fstream>
#include <iostream>
#include "ApplicationManager.h"
#include "Actions\ActionAddRes.h"
#include "Actions\ActionAddLamp.h"
#include "Actions\ActionAddBattery.h"
#include "Actions\ActionAddSwitch.h"
#include "Actions\ActionAddBuzzer.h"
#include "Actions\ActionAddFuse.h"
#include "Actions\ActionAddGround.h"
#include "Actions\ActionConnect.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionEditL.h"
#include "Actions\ActionEditV.h"
#include "Actions\ActionSaveCircut.h"
#include "Actions\ActionLoadCircut.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = nullptr;

	ConnCount = 0;
	for (int i = 0; i < MaxConnCount; i++)
		ConnList[i] = nullptr;


	//Creates the UI Object & Initialize the UI
	pUI = new UI;
}
/////////////////////////////////////////////////////////////////////
bool ApplicationManager::isConflict(int xx, int yy, int ww, int hh) const
{


	if (yy > pUI->gB().height - pUI->gB().StatusBarHeight - hh / 2 -1 ||
		yy < pUI->gB().ToolBarHeight + hh ||
		xx > pUI->gB().widthTD - pUI->gB().EditBarWidth - ww/2
		
		) return true;


	for (int i = 0; i < CompCount; i++) {
		if (
			(xx >= CompList[i]->getC()->PointsList[0].x - ww / 2 &&
				yy >= CompList[i]->getC()->PointsList[0].y - hh &&
				xx <= CompList[i]->getC()->PointsList[1].x + ww / 2 &&
				yy <= CompList[i]->getC()->PointsList[1].y + hh)
			)	return true;

	}

	return false;
}





////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}
void ApplicationManager::AddConnection(Connection* pConn)
{
	ConnList[ConnCount++] = pConn;

}
Component** ApplicationManager::getCompList()
{
	return CompList;
}
int ApplicationManager::getCompCount() const
{
	return CompCount;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return pUI->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = nullptr;
	switch (ActType)
	{
		case ADD_RESISTOR:
			pAct= new ActionAddRes(this);
			break;

		case ADD_LAMP:
			pAct = new ActionAddLamp(this);
			break;

		case ADD_BATTERY:
			pAct = new ActionAddBat(this);
			break;

		case ADD_SWITCH:
			pAct = new ActionAddSwitch(this);
			break;
			///////////////////555555555555555555555555555555555555555
		case ADD_BUZZER:
			pAct = new ActionAddBuzzer(this);
			break;
		case ADD_FUSE:
			pAct = new ActionAddFuse(this);
			break;
		case ADD_GROUND:
			pAct = new ActionAddGround(this);
			break;

		case ADD_CONNECTION:
			pAct = new ActionConnect(this);
			break;
	
		case SELECT:
			pAct = new ActionSelect(this);
			break;

		case EDIT_L:
			pAct = new ActionEditL(this);
			break;

		case EDIT_V:
			pAct = new ActionEditV(this);
			break;

		case SAVE:
			pAct = new ActionSaveCircut(this);
			break;

		case LOAD:
			pAct = new ActionLoadCircut(this);
			break;

		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = nullptr;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(pUI);
		for (int i = 0; i < ConnCount; i++)
			ConnList[i]->Draw(pUI);

}

////////////////////////////////////////////////////////////////////
UI* ApplicationManager::GetUI()
{
	return pUI;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete pUI;
	
}
//////////////////////////////////////////////////////////

void ApplicationManager::SaveCircut(ofstream& file) {

	for (int i = 0; i < CompCount; i++) {
		file << i + 1 << "  ";
		CompList[i]->Save(file);
	}
}

/////////////////////////////////////////////////////////////////

void ApplicationManager::LoadCircut(ifstream& file) {
	for (int i = 0; i < getCompCount(); i++) {
		CompList[i]->Load(file);

		Action* pAct = nullptr;
		if (CompList[i]->Component_type == "RES") pAct = new ActionAddRes(this);

		else if (CompList[i]->Component_type == "LMP") pAct = new ActionAddLamp(this);

		else if (CompList[i]->Component_type == "BAT") pAct = new ActionAddBat(this);

		else if (CompList[i]->Component_type == "SWT") pAct = new ActionAddSwitch(this);

		else if (CompList[i]->Component_type == "BUZ") pAct = new ActionAddBuzzer(this);

		else if (CompList[i]->Component_type == "FUS") pAct = new ActionAddFuse(this);

		else if (CompList[i]->Component_type == "GND")pAct = new ActionAddGround(this);

		else if (CompList[i]->Component_type == "CON") pAct = new ActionConnect(this);

		if (pAct)
		{
			pAct->Execute();
			delete pAct;
			pAct = nullptr;
		}
	}
}
