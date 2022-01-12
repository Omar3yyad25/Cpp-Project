#pragma once
#include "Component.h"


class Switch :public Component
{
	int Cx, Cy;
	bool state_Closed;

public:
	Switch(GraphicsInfo* r_GfxInfo, string name, double value);
	virtual void Operate();	//Calculates the volt on both terminals
	virtual void Draw(UI*, bool selected = false);	//Draws the resistor
	GraphicsInfo* getC();
	void Save(ofstream& file);
	void Load(int ID);
	void Delete();
	

};

