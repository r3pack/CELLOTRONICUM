#include "drawables.h"
#include "effects.h"
#include "controllers.h"

int Bus::lastClicked=-1;
int Bus::lastId=0;

int ControllBus::lastClicked=-1;
int ControllBus::lastId=0;

int ValueGifter::lastClicked=-1;
int ValueGifter::lastId=0;

class Bus;

std::map <int, Bus*> busList;

std::map <int, ControllBus*> controllBusList;

std::map <int, ValueGifter*> valueGifterList;

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

void Bus::removeBus()
{
	for(auto it=getConnections()->begin();it!=getConnections()->end();)
	{
		if((*it).first==this || (*it).second==this)
		{
			(*it).first->used=false;
			(*it).second->used=false;
			(*it).second->getEffect()->setAndSendArgument((*it).second->getArg(), OSCConn::getFreeBus());
			it=getConnections()->erase(it);
		}
		else
		++it;
	}
	busList.erase(id);
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
		
		if(bus1->getType()%2==0) std::swap(bus1, bus2);
		
		if(!((bus1->getType()==BT_OUTBUS && bus2->getType()==BT_INBUS) ||
		     (bus1->getType()==BT_FREQ_OUTBUS && bus2->getType()==BT_FREQ_INBUS) ||
		     (bus1->getType()==BT_AMP_OUTBUS && bus2->getType()==BT_AMP_INBUS)))
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
			
			bus2->getEffect()->setAndSendArgument(bus2->getArg(), OSCConn::getFreeBus());
			
			bus2->used=false;
		}
		else
		{
			if(bus2->used==true) return false;
			connIt=connections.insert(std::pair<Bus*, Bus*>(bus1, bus2));
			bus2->used=true;
			
			int freebus=bus1->getEffect()->getArgs()[bus1->getArg()].getIntValue();
			
			OSCConn::deleteBus(bus2->getEffect()->getArgs()[bus2->getArg()].getIntValue());
			
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

bool Bus::receiveClick(int X, int Y, MouseEvent me)
{
	X-=posX;
	Y-=posY;
	if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
	{
		if(setClicked())
		{
			Effect::updateTopologicalSequence();
		}
		return true;
	}
	return false;
}

bool Bus::receiveSecondClick(int X, int Y, MouseEvent me)
{
	X-=posX;
	Y-=posY;
	if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
	{
		used=false;
		if(getType()%2==1)
		{
			used=false;
			for(auto it=connections.begin();it!=connections.end();)
			{
				if((*it).first==this)
				{	
					(*it).second->getEffect()->setAndSendArgument((*it).second->getArg(), OSCConn::getFreeBus());
			
					(*it).second->used=false;
					it=connections.erase(it);
				}
				else ++it;
			}
		}
			
		if(getType()%2==0)
		{
			used=false;
			for(auto it=connections.begin();it!=connections.end();++it)
			{
				if((*it).second==this)
				{
					(*it).second->getEffect()->setAndSendArgument((*it).second->getArg(), OSCConn::getFreeBus());
				
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

bool ControllBus::connectControllBusWithValueGifter()
{
	if(ValueGifter::lastClicked != -1 && ControllBus::lastClicked != -1)
	{
		auto it=valueGifterList.find(ValueGifter::lastClicked);
		if(it==valueGifterList.end())
		{
			fprintf(stderr, "Error: slider not found\n");
			ValueGifter::lastClicked=-1;
			ControllBus::lastClicked=-1;
			return false;
		}
		
		auto it2=controllBusList.find(ControllBus::lastClicked);
		if(it2==controllBusList.end())
		{
			fprintf(stderr, "Error: controllbus not found\n");
			ValueGifter::lastClicked=-1;
			ControllBus::lastClicked=-1;
			return false;
		}
		
		ValueGifter *valueGifter=it->second;
		ControllBus *controllBus=it2->second;
		Controller* controller=controllBus->controller;
		
		if(valueGifter->controlledBy!=NULL)
		{
			bool fromThisController=false;
			
			int busCount=controller->getBusCount();
			
			int whichBus=0;
			for(;whichBus<controller->outBuses.size();++whichBus)
			{
				if(controller->outBuses[whichBus].bus==controllBus) break;
			}
			
			for(auto it=controller->controlledValueGifters.begin();it!=controller->controlledValueGifters.end();++it)
			{
				if(it->second==valueGifter && whichBus==it->first)
				{
					controller->controlledValueGifters.erase(it);
					valueGifter->controlledBy=NULL;
					break;
				}
			}
			
			fprintf(stderr, "Error: value gifter is already controlled\n");
			ValueGifter::lastClicked=-1;
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
			ValueGifter::lastClicked=-1;
			ControllBus::lastClicked=-1;
			return false;
		}
		
		controller->controlledValueGifters.push_back(std::pair<int, ValueGifter*>(i, valueGifter));
		
		ControllBus::lastClicked=-1;
		ValueGifter::lastClicked=-1;
		valueGifter->controlledBy=controller;
		
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
		
		return ControllBus::connectControllBusWithValueGifter();
	}
}

bool ControllBus::receiveSecondClick(int X, int Y, MouseEvent me)
{
	X-=posX;
	Y-=posY;
	if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
	{
		for(auto it=controller->controlledValueGifters.begin();it!=controller->controlledValueGifters.end();)
		{
			if(controller->outBuses[it->first].bus==this)
			{
				it->second->controlledBy=NULL;
				it=controller->controlledValueGifters.erase(it);
			}
			else
			++it;
		}
		return true;
	}
	return false;
}

void ValueGifter::setClicked()
{
	if(clicked==true && lastClicked==id) {clicked=false; lastClicked=-1;}
	else
	{
		clicked=true;
		lastClicked=id;
		
		ControllBus::connectControllBusWithValueGifter();
	}
}

void ValueGifter::removeConnections()
{
	ValueGifter* dis=valueGifterList[id];
	if(controlledBy!=NULL)
	{
		for(auto it=controlledBy->controlledValueGifters.begin();it!=controlledBy->controlledValueGifters.end();++it)
		{
			if(it->second==this) {controlledBy->controlledValueGifters.erase(it); break;}
		}
	}
	controlledBy=NULL;
}

Slider::~Slider() 
{
	removeConnections();
	SDL_DestroyTexture(valueTex);
	valueGifterList.erase(id);
}

void Slider::setValue(float v)
{
	value=v;
	
	if(!(lastValue>=(value-0.001) && lastValue<=(value+0.001)))
	{
		effect->setAndSendArgument(argument, value);
		SDL_DestroyTexture(valueTex);
		std::ostringstream buff;
		buff.setf(std::ios::fixed, std::ios::floatfield);
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

void GradualSlider::setValue(int v)
{
	value=v;
	
	if(value!=lastValue)
	{
		effect->setAndSendArgument(argument, graduals[value]);
		SDL_DestroyTexture(valueTex);
		std::ostringstream buff;
		//buff.setf(std::ios::fixed, std::ios::floatfield);
		if(graduals[value]>=10.0f || graduals[value]<=-10.0f)
		buff.precision(1);
		else
		buff.precision(2);
		buff<<graduals[value];
		
		valueTex=generateText(buff.str().c_str());
		lastValue=value;
	}
}

GradualSlider::~GradualSlider() 
{
	removeConnections();
	SDL_DestroyTexture(valueTex);
	valueGifterList.erase(id);
}