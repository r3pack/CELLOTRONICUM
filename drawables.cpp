#include "drawables.h"
#include "effects.h"
#include "controllers.h"

int Bus::lastClicked=-1;
int Bus::lastId=0;

int ControllBus::lastClicked=-1;
int ControllBus::lastId=0;

int Slider::lastClicked=-1;
int Slider::lastId=0;

class Bus;

std::map <int, Bus*> busList;

std::map <int, ControllBus*> controllBusList;

std::map <int, Slider*> sliderList;

std::set <std::pair <Bus*, Bus*> > connections;

std::set <std::pair <Bus*, Bus*> >* getConnections() {return &connections;}

void drawConnections()
{
	setColor(COLOR_CONNECTION_LINE);
	for(auto it=connections.begin();it!=connections.end();++it)
	{
		SDL_RenderDrawLine(render, (*it).first->getPosX()+Bus::size/2, (*it).first->getPosY()+Bus::size/2,
								   (*it).second->getPosX()+Bus::size/2, (*it).second->getPosY()+Bus::size/2);
	}
}

bool Bus::setClicked()
{
	clicked=true;
	
	if(lastClicked!=-1)
	{
		auto it=busList.find(lastClicked);
		if(it==busList.end())
		{
			fprintf(stderr, "Error: bus not found\n");
			Bus::lastClicked=-1;
			return false;
		}
		
		Bus *bus1=it->second, *bus2=this;
		
		if(bus1->getType()==BT_INBUS) std::swap(bus1, bus2);
		
		if(bus1->getType()!=BT_OUTBUS || bus2->getType()!=BT_INBUS)
		{	
			fprintf(stderr, "Error: bad buses type\n");
			Bus::lastClicked=-1;
			return false;
		}
		
		
		if(bus1->getEffect() == bus2->getEffect())
		{
			fprintf(stderr, "Error: buses come from same effect\n");
			Bus::lastClicked=-1;
			return false;
		}
		
		std::pair<std::set <std::pair<Bus*, Bus*> >::iterator, bool> connIt;
		
		if(connections.find(std::pair<Bus*, Bus*>(bus1, bus2)) != connections.end())
		{
			connections.erase(std::pair<Bus*, Bus*>(bus1, bus2));
			
			bus2->getEffect()->getArgs()[bus2->getArg()].set(OSCConn::getFreeBus());
			
			bus2->used=false;
		}
		else
		{
			if(bus2->used==true) return false;
			connIt=connections.insert(std::pair<Bus*, Bus*>(bus1, bus2));
			bus2->used=true;
			
			Effect::updateTopologicalSequence();
					
			int freebus=bus1->getEffect()->getArgs()[bus1->getArg()].getIntValue();
			
			OSCConn::deleteBus(bus2->getEffect()->getArgs()[bus2->getArg()].getIntValue());
			
			bus2->getEffect()->getArgs()[bus2->getArg()].set(freebus);
			
			bus2->getEffect()->setAndSendArgument(bus2->getArg(), freebus);
			fprintf(stderr, "Connected two buses to %d\n", freebus);
		}
		
		Bus::lastClicked=-1;
		
		return true;
	}
	else
	lastClicked=id;
	
	return false;
}

bool Bus::receiveSecondClick(int X, int Y, MouseEvent me)
{
	X-=posX;
	Y-=posY;
	if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
	{
		used=false;
		if(getType()==BT_OUTBUS)
		{
			used=false;
			for(auto it=connections.begin();it!=connections.end();)
			{
				if((*it).first==this)
				{
					(*it).second->used=false;
					it=connections.erase(it);
				}
				else ++it;
			}
		}
			
		if(getType()==BT_INBUS)
		{
			used=false;
			for(auto it=connections.begin();it!=connections.end();++it)
			{
				if((*it).second==this)
				{
					(*it).first->used=false;
					connections.erase(it);
					break;
				}
			}
		}
		return true;
	}
	return false;
}

bool ControllBus::connectControllBusWithSlider()
{
	if(Slider::lastClicked != -1 && ControllBus::lastClicked != -1)
	{
		auto it=sliderList.find(Slider::lastClicked);
		if(it==sliderList.end())
		{
			fprintf(stderr, "Error: slider not found\n");
			Slider::lastClicked=-1;
			ControllBus::lastClicked=-1;
			return false;
		}
		
		auto it2=controllBusList.find(ControllBus::lastClicked);
		if(it2==controllBusList.end())
		{
			fprintf(stderr, "Error: controllbus not found\n");
			Slider::lastClicked=-1;
			ControllBus::lastClicked=-1;
			return false;
		}
		
		Slider *slider=it->second;
		ControllBus *controllBus=it2->second;
		Controller* controller=controllBus->controller;
		
		if(slider->controlledBy!=NULL)
		{
			bool fromThisController=false;
			
			int busCount=controller->getBusCount();
			
			int whichBus=0;
			for(;whichBus<controller->outBuses.size();++whichBus)
			{
				if(controller->outBuses[whichBus].bus==controllBus) break;
			}
			
			for(auto it=controller->controlledSliders.begin();it!=controller->controlledSliders.end();++it)
			{
				if(it->second==slider && whichBus==it->first)
				{
					controller->controlledSliders.erase(it);
					slider->controlledBy=NULL;
					break;
				}
			}
			
			fprintf(stderr, "Error: slider is already controlled\n");
			Slider::lastClicked=-1;
			ControllBus::lastClicked=-1;
			return false;
		}
		
		int size=controller->outBuses.size();
		
		int i=0;
		for(;i<size;++i)
		{
			if(controller->outBuses[i].bus==controllBus) break;
		}
		
		if(i==size)
		{
			fprintf(stderr, "Error: controllbus not found on controller\n");
			Slider::lastClicked=-1;
			ControllBus::lastClicked=-1;
			return false;
		}
		
		controller->controlledSliders.push_back(std::pair<int, Slider*>(i, slider));
		
		ControllBus::lastClicked=-1;
		Slider::lastClicked=-1;
		slider->controlledBy=controller;
		
		return true;
	}
	return false;
}

bool ControllBus::setClicked()
{
	if(clicked==true && lastClicked==id) {clicked=false; lastClicked=-1;}
	else
	{
		clicked=true;
		lastClicked=id;
		
		return ControllBus::connectControllBusWithSlider();
	}
}

bool ControllBus::receiveSecondClick(int X, int Y, MouseEvent me)
{
	X-=posX;
	Y-=posY;
	if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
	{
		for(auto it=controller->controlledSliders.begin();it!=controller->controlledSliders.end();)
		{
			if(controller->outBuses[it->first].bus==this)
			{
				it->second->controlledBy=NULL;
				it=controller->controlledSliders.erase(it);
			}
			else
			++it;
		}
		return true;
	}
	return false;
}

void Slider::setClicked()
{
	if(clicked==true && lastClicked==id) {clicked=false; lastClicked=-1;}
	else
	{
		if(controlledBy!=NULL)
		{
			removeConnections();
			return;
		}
		clicked=true;
		lastClicked=id;
		
		ControllBus::connectControllBusWithSlider();
	}
}

void Slider::removeConnections()
{
	if(controlledBy!=NULL)
	{
		for(auto it=controlledBy->controlledSliders.begin();it!=controlledBy->controlledSliders.end();++it)
		{
			if(it->second==this) {controlledBy->controlledSliders.erase(it); break;}
		}
	}
	controlledBy=NULL;
}

Slider::~Slider() 
{
	removeConnections();
	SDL_DestroyTexture(valueTex);
	sliderList.erase(id);
}

void Slider::setValue(float v)
{
	value=v;
	
	if(!(lastValue>=(value-0.001) && lastValue<=(value+0.001)))
	{
		effect->setAndSendArgument(argument, value);
		SDL_DestroyTexture(valueTex);
		std::ostringstream buff;
		buff.setf(std::ios::fixed, std:: ios::floatfield);
		if(value>=10.0f || value<=-10.0f)
		buff.precision(1);
		else
		buff.precision(2);
		buff<<value;
		
		valueTex=generateText(buff.str().c_str());
		lastValue=value;
		
		level=height-int((value-rangeBegin)/(rangeEnd-rangeBegin)*float(height));
	}
}