#include "Module.h"
#include <iostream>
#include <fstream>

Module::Module(GraphicsInfo *r_GfxInfo, string name, double val):Component(r_GfxInfo)
{
	label = name;
	value = val;
	Component_type = "MOD";
}

void Module::Draw(UI* pUI,bool selected)
{
	//Call output class and pass Module drawing info to it.
	pUI->DrawModule(*m_pGfxInfo,label,value, selected); //update to draw Module
	
}

GraphicsInfo* Module::getC()
{
	return m_pGfxInfo;
}

void Module::Operate()
{

}


void Module::Save(ofstream &file)
{
	GraphicsInfo* List = getC();
	file << Component_type << "  " << ID << "  " << label << "  " << "No Value" << "  " << List->PointsList[0].x << "  " << List->PointsList[0].y << endl;
	ID++;
	}

void Module::Load(ifstream &file)
{
	char NAME_OF_COMPONENT, LABEL;
	int ID, X, Y, Count, VALUE;
	file >> Count >> ID >> NAME_OF_COMPONENT >> LABEL >> VALUE >> X >> Y;
	
}

void Module::Delete()
{
	delete m_pGfxInfo;
}