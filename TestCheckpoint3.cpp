#include <iostream>
#include "Building.h"
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Pokemon.h"

using namespace std;

int main()
{
	// test pokemon constructors
	Point2D myLocation(10, 1);
	Pokemon myPoke("Bulbasaur", 1, 'B', 2, myLocation);
	myPoke.ShowStatus();

	// testing set up  destination and start moving
	Point2D mydest(10,20);
	myPoke.StartMoving(mydest);
	myPoke.GetDelta();
	myPoke.GetDestination();

	// test update
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	cout << endl;
	  cout << endl;
        myPoke.ShowStatus();
	cout << endl;

	// test StartMovingToCenter and recovering stamina
	Point2D centerLoc(1,5);
	PokemonCenter myCenter(2,centerLoc);
	PokemonCenter* myCenterPtr = &myCenter;
	myCenter.ShowStatus();
	myPoke.StartMovingToCenter(myCenterPtr);
	myPoke.GetDestination();
	myPoke.ShowStatus();
	cout << endl;
	myPoke.StartRecoveringStamina(1);
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.Update();
	myPoke.StartRecoveringStamina(2);
	myPoke.ShowStatus();
	myPoke.Update();
	myPoke.ShowStatus();
	// test StartMovingToGym and start training 
	Point2D myGymloc(2, 3);
	PokemonGym myGym(40, 2, 3.5, 2, 9, myGymloc);
    myPoke.StartMovingToGym(&myGym);
	myPoke.Update();
	myPoke.Update();
	myPoke.StartTraining(1);
	myPoke.Update();
	myPoke.ShowStatus();
	cout << endl;
	cout << endl;
	myCenter.ShowStatus();
	cout << endl;
	myGym.ShowStatus();
	cout << endl;
 
	return 0;
}
