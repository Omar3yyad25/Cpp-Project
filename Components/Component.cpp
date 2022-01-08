#include "Component.h"

int Component::ID = 1;

string Component::getLabel()
{
	return label;
}

void Component::setLabel(string ll) {
	label = ll;
}

double Component::getValue()
{
	return value;
}

void Component::setValue(double v)
{
	value = v;
}

string Component::getType()
{
	return Component_type;
}

bool Component::CheckSelection()
{
	return Selected;
}

void Component::Select() {
	if (Selected == false) Selected = true;
	else Selected = false;
}
void Component::DeleteGraphic()
{
	delete m_pGfxInfo;
}


Component::Component(GraphicsInfo *r_GfxInfo)
{
	m_pGfxInfo = r_GfxInfo;	
}

Component::Component()
{
	m_pGfxInfo = nullptr;
	term1_volt = term2_volt = 0;
	term1_conn_count = term2_conn_count = 0;

}

 
GraphicsInfo* Component::getC()
{
	return m_pGfxInfo;
}

void Component::setC(GraphicsInfo* c)
{
	m_pGfxInfo = c;
}



Component::~Component()
{}

