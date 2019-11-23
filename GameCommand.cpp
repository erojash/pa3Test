#include <iostream>
#include "GameCommand.h"

using namespace std;
void DoMoveCommand(Model& model, int pokemon_id, Point2D p1)
{
	Pokemon* myPokemon = model.GetPokemonPtr(pokemon_id); 
	// checking for pokemon existence
	if (myPokemon == 0)
	{
		// pokemon doesn't exist
		cout << "Error: Please enter a valid command!" << endl;
	}
	else
	{	// pokemon does exist
		cout << "Moving " << myPokemon->GetName() << " to " << p1 << endl;
		myPokemon->StartMoving(p1); // call pokemon's startmoving function
	}
}
void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id)
{
	PokemonCenter* myCenter = model.GetPokemonCenterPtr(center_id);
	Pokemon* myPokemon = model.GetPokemonPtr(pokemon_id);
	// checking for pokemon and center existence
	if (myPokemon == 0)
	{
		cout << "Error: Please enter a valid command!" << endl;
	}
	else if (myCenter == 0)
	{
		cout << "Error: Please enter a valid command!" << endl;
	}
	// pokemon and center exist
	else
	{
		cout << "Moving " << myPokemon->GetName() << " to center " << myCenter->GetId() << endl;
		myPokemon->StartMovingToCenter(myCenter);
	}
}
void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id)
{
	PokemonGym* myGym = model.GetPokemonGymPtr(gym_id);
	Pokemon* myPokemon = model.GetPokemonPtr(pokemon_id);
	// checking for pokemon and gym existence
	if (myPokemon == 0)
	{
		cout << "Error: Please enter a valid command!" << endl;
	}
	else if (myGym == 0)
	{
		cout << "Error: Please enter a valid command!" << endl;
	}
	// pokemon and gym exist
	else
	{
		cout << "Moving " << myPokemon->GetName() << " to gym " << myGym->GetId() << endl;
		myPokemon->StartMovingToGym(myGym);
	}
}
void DoStopCommand(Model& model, int pokemon_id)
{
	Pokemon* myPokemon = model.GetPokemonPtr(pokemon_id);
	// checking pokemon existence
	if (myPokemon == 0)
	{
		cout << "Error: Please enter a valid command!" << endl;
	}
	// pokemon exists
	else
	{
		cout << "Stopping " << myPokemon->GetName() << endl;
		myPokemon->Stop();
	}
}
void DoTrainInGymCommand(Model& model, int pokemon_id, unsigned int training_units)
{
	Pokemon* myPokemon = model.GetPokemonPtr(pokemon_id);
	if (training_units < 0) // invalid amount of units
	{
		cout << "Error: Please enter a valid command!" << endl;
	}
	// pokemon does not exist
	else if (myPokemon == 0)
	{
		cout << "Error: Please enter a valid command!" << endl;
	}
	// pokemon exits
	else
	{
		cout << "Training " << myPokemon->GetName() << endl;
		myPokemon->StartTraining(training_units);
	}
}
void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points)
{
	Pokemon* myPokemon = model.GetPokemonPtr(pokemon_id);
	if (stamina_points < 0)
	{
		// invalid amount of stamina points
		cout << "Error: Please enter a valid command!" << endl;
	}
	// checking if pokemon exits
	else if (myPokemon == 0)
	{
		// pokemon does not exist
		cout << "Error: Please enter a valid command!" << endl;
	}
	else
	{
		// pokemon exits
		cout << "Recovering " << myPokemon->GetName() << "'s " << "stamina" << endl;
		myPokemon->StartRecoveringStamina(stamina_points);
	}
}

void DoGoCommand(Model& model, View& view)
{
	cout << "Advancing one tick." << endl;
	model.Update();
	model.Display(view);
}
void DoRunCommand(Model& model, View& view)
{
	bool updateCheck; // check is update returns true
	int count; // count how many times update was called
	cout << "Advancing to next event." << endl;
	do
	{
		updateCheck = model.Update();
		count++;
	} while (updateCheck != true || count <= 5);

	model.Display(view);
}
