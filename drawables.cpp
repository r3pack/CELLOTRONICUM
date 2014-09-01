#include "drawables.h"
#include "effects.h"
#include "controllers.h"

int Bus::lastClicked=-1;
int Bus::lastId=0;

int ControllBus::lastClicked=-1;
int ControllBus::lastId=0;

int ValueGifter::lastClicked=-1;
int ValueGifter::lastId=0;

int EntryBox::lastClicked=-1;
int EntryBox::lastId=0;

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
	
	if(Bus::lastClicked!=-1 && (ControllBus::lastClicked!=-1 || ValueGifter::lastClicked!=-1))
	{
		Bus::lastClicked=-1;
		ControllBus::lastClicked=-1;
		ValueGifter::lastClicked=-1;
	}
	
	if(Bus::lastClicked!=-1)
	{
		Bus* bus=busList[Bus::lastClicked];
		int x, y;
		SDL_GetMouseState(&x, &y);
		setColor(COLOR_CONNECTION_LINE);
		SDL_RenderDrawLine(render, bus->getPosX()+Bus::size/2, bus->getPosY()+Bus::size/2, x, y);
	}
	
	if(ControllBus::lastClicked!=-1)
	{
		ControllBus* controllBus=controllBusList[ControllBus::lastClicked];
		int x, y;
		SDL_GetMouseState(&x, &y);
		setColor(COLOR_CONNECTION_LINE);
		SDL_RenderDrawLine(render, controllBus->getPosX()+ControllBus::size/2, controllBus->getPosY()+ControllBus::size/2, x, y);
	}
	
	if(ValueGifter::lastClicked!=-1)
	{
		ValueGifter* valueGifter=valueGifterList[ValueGifter::lastClicked];
		int x, y;
		SDL_GetMouseState(&x, &y);
		setColor(COLOR_CONNECTION_LINE);
		SDL_RenderDrawLine(render, valueGifter->getPosX()+valueGifter->getWidth()/2, valueGifter->getPosY()-Slider::slider_bus_height/2, x, y);
	}
}

void setOptimalPrecision(float value, std::stringstream& ss)
{
	ss.setf(std::ios::fixed);
	if(value>=1000.0f || value<=-1000.0f)
	ss.precision(0);
	else
	if(value>=10.0f || value<=-10.0f)
	ss.precision(1);
	else
	if(value>=1.0f || value<=-1.0f)
	ss.precision(2);
	else
	if(int(value*1000.0)%10!=0)
	ss.precision(3);
	else
	ss.precision(2);
}

void SwitchButton::setStatus(bool s) 
{
	status=s;
	if(status==false)
	{
		effect->setAndSendArgument(argument, value1);
		symbol=symbol1;
	}
	else
	{
		effect->setAndSendArgument(argument, value2);
		symbol=symbol2;
	}
}

bool SwitchButton::receiveClick(int X, int Y, MouseEvent me)
{
	if(isTrigger && status && me==ME_RELEASE)
	{
		status=false;
		effect->setAndSendArgument(argument, value1);
		symbol=symbol1;
		return true;
	}
	if(Button::receiveClick(X, Y, me))
	{
		setStatus(!status);
		return true;
	}
	return false;
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
			if(bus2->used==true) 
			{	
				bus2->removeConnections();
				printf("Bus is already used - removing existing connections\n");
			}
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

void Bus::removeConnections()
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
}

bool Bus::receiveSecondClick(int X, int Y, MouseEvent me)
{
	lastClicked=-1;
	X-=posX;
	Y-=posY;
	if(X>=0 && X<=size && Y>=0 && Y<=size && me==ME_PRESS)
	{
		removeConnections();
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
				if(it->second==valueGifter)
				{
					controller->controlledValueGifters.erase(it);
					valueGifter->controlledBy=NULL;
					break;
				}
			}
			
			fprintf(stderr, "Error: value gifter is already controlled - removing existing controller\n");
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
	lastClicked=-1;
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
	valueGifterList.erase(id);
}

void Slider::setValue(float v, bool skipEntryBox, bool forceSet)
{
	value=v;
	
	if((!(lastValue>=(value-0.001) && lastValue<=(value+0.001))) || forceSet)
	{
		effect->setAndSendArgument(argument, value);

		lastValue=value;
		
		level=height-int((value-rangeBegin)/(rangeEnd-rangeBegin)*float(height));
		
		if(!skipEntryBox) 
		{
			entryBox.setValue(value);
			entryBox.setPos(posX+width/2-entryBox.getWidth()/2, posY+height);
		}
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
		
		buff.unsetf(std::ios::scientific);
		
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

void EntryBox::sendValue()
{
	if(effect!=NULL)
	effect->setAndSendArgument(argument, value);
}