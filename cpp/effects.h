#ifndef EFFECTS_H
#define EFFECTS_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <stdarg.h>
#include <queue>
#include "osc.h"
#include "graphics.h"
#include "drawables.h"

	///Komparator porównujący 2 cstringi
	struct cmpCStr
	{
	   bool operator()(char const *a, char const *b)
	   {
		  return std::strcmp(a, b) < 0;
	   }
	};

	///Enum przechowujący typ argumentu
	enum VarType{
		TYPE_UNKNOWN,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_STRING,
		TYPE_BLOB,
		TYPES_SIZE
	};
	
	///Klasa z informacjami o argumęcie efektu
	class EffectArgument{
		friend class Effect;
		private:
		
			VarType type; ///typ argumentu
			const char* name; ///nazwa
			void* value; ///aktualna wartość
			
			///Metoda wrzucająca dane do struktury danych OSC z oscptk
			void addArgumentToMessage(Message* msg); 
			
			///Wysyła argument przez OSC. 'id' jest identyfikatorem efektu 
			void sendArgument(int id);	
			
		public:
		
			///Ustawia wartość argumentu na podaną wartość (ale nie wysyłe jej)
			void set(int var);
			
			///Ustawia wartość argumentu na podaną wartość (ale nie wysyłe jej)
			void set(float var);
			
			///Ustawia wartość argumentu na podaną wartość (ale nie wysyłe jej)
			void set(std::string var);
		
			///Zwraca nazwę argumentu
			const char* getName() {return name;}
			
			///Zwraca wartość przy typu float (Jeżeli to nie jest float to zwróci 0.0f)
			float getFloatValue() {if(type==TYPE_FLOAT) return *(float*)value; else return 0.0f;}
			
			///Zwraca wartość przy typu int (Jeżeli to nie jest int to zwróci 0)
			int getIntValue() {if(type==TYPE_INT) return *(int*)value; else return 0;}
		
			EffectArgument(const char* n, int var): name(n) {set(var);}
			EffectArgument(const char* n, float var): name(n) {set(var);}
			EffectArgument(const char* n, std::string var): name(n) {set(var);}
			
			~EffectArgument();
	};
		
	///Klasa efektu - jest to najbardziej podstawowa klasa dla efektu - nie zawiera ona implementacji GUI (ta jest w EffectGUI)
	class Effect{
	
		private:
			static int lastId; ///ostatnio przyznany indentyfikator dla efektu +1
		
		protected:
			static std::set <std::pair<int, int> > effectTree; ///drzewo połączeń efektów - budowane w metodzie updateTopologicalSequence()
			int id; ///identyfikator instancji efektu
			bool paused; ///instancja efektu zpauzowana lub nie
		public:
		
			///buduje drzewo połączeń i sortuje topologicznie efekty, a następnie wysyła tę kolejność do SC
			static void updateTopologicalSequence(); 
		
			//Zwraca czy instancja efektu jest zpauzowany
			bool isPaused() {return paused;}
			///Pauzuje instancje efektu
			void pauseInstance();
			///Odpauzuje instancje efektu
			void unpauseInstance();
			///Wysyła instancje efektu na serwer (może być zpauzowany)
			void sendInstance(bool paused=false);
			///Usuwa instancję z serwera
			void deleteInstance();
			///Ustawia efekt w kolejności wykonywania przed efektem podanym w parametrze (nieużywane)
			void moveBefore(Effect* effect);
			///Ustawia efekt w kolejności wykonywania za efektem podanym w parametrze
			void moveAfter(Effect* effect);
			///Ustawia efekt w kolejności wykonywania na początek kolejki
			void moveToHead();
			
			///Metoda zapisująca swoje dane do strumienia pliku (do implementacji przez konkretne efekty, lub gotowej implementacji z EfektGUI, wykorzystywane przy zapisie do pliku)
			virtual void saveData(FILE* file) {}
			///Metoda czytająca swoje dane z cstringa (są to dane zapisane wcześniej przez saveData, wykorzystywane przy wczytywaniu z pliku)
			virtual void loadData(char* data) {}
		
			Effect();
			
			virtual ~Effect();
			
			///zwraca identyfikator
			int getId() {return id;}
			
			///zwraca nazwe taką samą jak nazwa efektu w SC (do implementacji przez konkretne efekty)
			virtual const char* getName() = 0;
			///zwraca nazwę do wyświetlenia w GUI - używana jest także do identyfikacji więc nie można powtarzać tych samych nazw! (do implementacji przez konkretne efekty)
			virtual const char* getFullName() = 0;
			///Zwraca tablice z argumentami efektu (do implementacji przez konkretne efekty)
			virtual EffectArgument* getArgs() = 0;
			///Zwraca ilość argumentów (do implementacji przez konkretne efekty)
			virtual const int getArgsCount() = 0;
			
			///metoda rysująca efekt (do implementacji przez konkretne efekty, lub gotowa implementacja w EfektGUI)
			virtual void draw(){}
			///odbieranie pirwszego przycisku myszy paramety do współżędna kliknięcia oraz typ (do implementacji przez konkretne efekty, lub gotowa implementacja w EfektGUI)
			virtual bool receiveClick(int X, int Y, MouseEvent me){return false;}
			///odbieranie drugiego przycisku myszy paramety do współżędna kliknięcia oraz typ (do implementacji przez konkretne efekty, lub gotowa implementacja w EfektGUI)
			virtual bool receiveSecondClick(int X, int Y, MouseEvent me){return false;}
			///odbieranie trzeciego przycisku myszy paramety do współżędna kliknięcia oraz typ (do implementacji przez konkretne efekty, lub gotowa implementacja w EfektGUI)
			virtual bool receiveThridClick(int X, int Y, MouseEvent me){return false;}
			///odbieranie naciśnięć klawiszy (do implementacji przez konkretne efekty, lub gotowa implementacja w EfektGUI)
			virtual bool receiveKeyboardEvent(SDL_Scancode scancode){return false;}
			
			///metoda która może być wykonywania przez konkretne efekty co każdą klatkę programu (np. żeby pilnować odpowiednich wartości argumentów efektów) - nie musi być implementowana 
			virtual void doSomething() {}
			
			///Ustawia argument o podanym id (kolejności w tablicy) na zadaną wartość (ale nie wysyła do SC)
 			void setArgument(int argId, int value);
			///Ustawia argument o podanym id (kolejności w tablicy) na zadaną wartość (ale nie wysyła do SC)
			void setArgument(int argId, float value);
			///Ustawia argument o podanym id (kolejności w tablicy) na zadaną wartość (ale nie wysyła do SC)
			void setArgument(int argId, std::string value);
			
			///Wysyła argument o podanym id (kolejności w tablicy) do SC
			void sendArgument(int argId);
			
			///Ustawia argument o podanym id (kolejności w tablicy) na zadaną wartość i wysyła go do SC
			void setAndSendArgument(int argId, int value);
			///Ustawia argument o podanym id (kolejności w tablicy) na zadaną wartość i wysyła go do SC
			void setAndSendArgument(int argId, float value);
			///Ustawia argument o podanym id (kolejności w tablicy) na zadaną wartość i wysyła go do SC
			void setAndSendArgument(int argId, std::string value);
			
			///Zapisuje wszystkie efekty oraz resztę rzeczy w sesji do pliku (wgrywa też wszystko do SC)
			static void saveToFile(const char* filename);
			
			///Wczytuje wszystkie efekty oraz resztę rzeczy w sesji z pliku
			static void loadFromFile(const char* filename);
			
			///Czyści całą sesję (także po stronie SC), oraz tworzy kopię zapasową
			static void clearAll();
	};
	
	///Struktura wykorzystywana w EffectCreator - jest to wierzchołek w drzewie menu
	struct EffectCreatorMenuEntry
	{
		std::vector <EffectCreatorMenuEntry*>* submenuEntries=NULL; ///wierzchołki wychodzące
		const char* name; ///nazwa wpisu
		SDL_Texture* nameTex; ///tekstura w wyrenderowaną nazwą
		SDL_Texture* nameTexRed; ///tekstura w wyrenderowaną nazwa (wersja zaznaczona)
		EffectCreatorMenuEntry* parent=NULL; ///wierzchołek z którego wychodzi ten wierzchołek
		int width=0; ///obliczona szerokość menu
		
		///rekurencyjnie oblicza wszerokość menu (ten wierzchołek + jego dzieci)
		void calculateWidth() 
		{
			if(submenuEntries==NULL) return;
			for(auto it=submenuEntries->begin();it!=submenuEntries->end();++it)
			{
				int w;
				SDL_QueryTexture((*it)->nameTex, NULL, NULL, &w, NULL);
				width=std::max(width, w);
			}
			
			for(auto it=submenuEntries->begin();it!=submenuEntries->end();++it)
			{
				(*it)->calculateWidth();
			}
		}
		
		///Konstruktor. Parametry kolejno: nazwa, wierzchołek ojciec, czy jest elementem (jeżeli jest to jego nazwa musi pokrywać się z jakimś efektem lub kontrolerem)
		EffectCreatorMenuEntry(const char* n, EffectCreatorMenuEntry* p, bool isElement)
		{
			name=n;
			parent=p;
			if(!isElement) submenuEntries=new std::vector <EffectCreatorMenuEntry*>;
			if(isElement)
			{
				nameTex=generateText(name, COLOR_ELEMENT_TEXT);
				nameTexRed=generateText(name, COLOR_SELECTED_ELEMENT_TEXT);
			}
			else
			{
				nameTex=generateText(name);
				nameTexRed=generateText(name, COLOR_SELECTED_TEXT);
			}
		}
		
	};
	
	class EffectCreator{
		private:
			EffectCreatorMenuEntry* chosenEffect; ///Aktualny wierzchołek
		
		public:	
			static const int menu_period=30; ///odstęp pomiędzy poziomami menu
			
			///przechodzi pozycję wyżej
			void moveUp(); 
			
			///przechodzi pozycję niżej
			void moveDown(); 
			
			///wchodzi w podmenu lub tworzy efekt/kontroler jeżeli to element
			void enter();
			
			///wraca poziom wyżej
			void back(); 
			
			///obliera klawisze
			void receiveKeyboardEvent(SDL_Scancode scancode); 
			
			///inicializuje menu
			void init(); 
			
			///rusuje menu
			void draw(int X, int Y); 
	};
	
	///Funkcja sprawdzająca czy wszystkie efekty zarejestowane po stronie tego programu mają swoje odpowiedniki po stronie SC
	bool checkEffectsList();
	
	///Zwraca listę wsztstkich instancji efektów
	std::map <int, Effect*>* getEffectInstanceList();
	
	///rejestruje efekty na liście (efekty, a nie ich instancję). Jako paramentry podaję się nazwę z SC, pełną nazwę
	void registerEffect(const char* name, const char* fullName, const char* group, const char* subgroup=NULL);

#endif