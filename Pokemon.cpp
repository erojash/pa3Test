#include <iostream>
#include "Pokemon.h"
#include <ctime>
#include <cstdlib>
#include <math.h>

Pokemon::Pokemon() : GameObject('P')
{
	this->speed = 5;
	this->is_in_gym = false;
	this->is_in_center = false;
	this->name = "Pokemon Default";
	this->state = STOPPED;
	this->stamina = 20;
	this->experience_points = 0;
	this->stamina_points_to_buy = 0;
	this->current_center = 0;
	this->current_gym = 0;
	this->pokemon_dollars = 0;
	cout << "Pokemon default constructed" << endl;
}

Pokemon::Pokemon(char in_code) : GameObject('P')
{
	this->speed = 5;
	this->name = "Pokemon Default";
	this->state = STOPPED;
	this->display_code = in_code;
	this->is_in_gym = false;
	this->is_in_center = false;
	this->stamina = 20;
	this->experience_points = 0;
	this->stamina_points_to_buy = 0;
	this->current_center = 0;
	this->current_gym = 0;
	this->pokemon_dollars = 0;
	cout << "Pokemon constructed" << endl;
}

Pokemon::Pokemon(string in_name, int in_id, char in_code, double in_speed, Point2D in_loc) : GameObject('P')
{
	this->speed = in_speed;
	this->name = in_name;
	// initialize others?
	this->pokemon_dollars = 0;
	this->state = STOPPED;
	this->location.x = in_loc.x;
	this->location.y = in_loc.y;
	this->id_num = in_id;
	this->display_code = in_code;
	this->is_in_gym = false;
	this->is_in_center = false;
	this->stamina = 20;
	this->experience_points = 0;
	this->stamina_points_to_buy = 0;
	this->current_center = 0;
	this->current_gym = 0;
	cout << "Pokemon constructed" << endl;
}
Pokemon::~Pokemon()
{
	cout << "Pokemon destructed" << endl;
}
void Pokemon::StartMoving(Point2D dest)
{
	SetupDestination(dest);
	if (location.x == dest.x && location.y == dest.y) // if already at destination
	{
		cout << display_code << id_num << ": I'm already there. See?" << endl;
	}
	else if (state == EXHAUSTED) // is exhausted
	{
		cout << display_code << id_num << ": I am exhausted. I may move but you cannot see me." << endl;
	}
	else // can move
	{
		this->state = MOVING;
		cout << display_code << id_num << ": On my way." << endl;
	}
}

void Pokemon::StartMovingToCenter(PokemonCenter* center)
{
	this->current_center = center;
	SetupDestination(current_center->GetLocation());
	if (state == EXHAUSTED)
	{
		cout << display_code << id_num << ": I am exhausted so I can't move to recover stamina..." << endl;
	}
	else if (center->GetLocation().x == location.x && center->GetLocation().y == location.y) // already at center
	{
		cout << display_code << id_num << ": I am already at the PokemonCenter!" << endl;
	}
	else
	{
		this->state = MOVING_TO_CENTER;
		cout << display_code << id_num << ": on my way to center " << center->GetId() << "." << endl;
	}
}

void Pokemon::StartMovingToGym(PokemonGym* gym)
{
	this->current_gym = gym;
	SetupDestination(current_gym->GetLocation());
	if (gym->GetLocation().x == location.x && gym->GetLocation().y == location.y) // at gym
	{
		cout << display_code << id_num << ": I am already at the Pokemon Gym!" << endl;
	}
	else if (state == EXHAUSTED)
	{
		cout << display_code << id_num << ": I am exhausted so I shouldn't be going to the gym..." << endl;
	}
	else
	{
		this->state = MOVING_TO_GYM;
		cout << display_code << id_num << ": On my way to gym " << gym->GetId() << endl;
	}
}

void Pokemon::StartTraining(unsigned int num_training_units)
{
	if (is_in_gym == false)
	{
		cout << display_code << id_num << ": I can only train in a Pokemon Gym!" << endl;
	}
	else if (state == EXHAUSTED)
	{
		cout << display_code << id_num << ": I am exhausted so no more training for me..." << endl;
	}
	else if (stamina <= 0 || pokemon_dollars <= 0)
	{
		cout << display_code << id_num << ": Not enough stamina and/or money for training" << endl;
	}
	else if (current_gym->IsBeaten() == true)
	{
		cout << display_code << id_num << ": Cannot train! This Pokemon Gym is already beaten!" << endl;
	}
	else // can train
	{
		this->state = TRAINING_IN_GYM;
		cout << display_code << id_num << ": Started to train at Pokemon Gym " << current_gym->GetId();
		cout << " with " << num_training_units << " training units" << endl;
		// set to minimum of training units
		if (num_training_units > current_gym->GetNumTrainingUnitsRemaining())
		{
			this->training_units_to_buy = current_gym->GetNumTrainingUnitsRemaining();
		}
		else
		{
			this->training_units_to_buy = num_training_units;
		}
	}
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points)
{
	if (is_in_center == false)
	{
		cout << display_code << id_num << ": I can only recover stamina at a Pokemon Center!" << endl;
	}
	else if (current_center->CanAffordStaminaPoints(num_stamina_points, pokemon_dollars) == false)
	{
		cout << display_code << id_num << ": Not enough money to recover stamina." << endl;
	}
	else if (stamina <= 0)
	{
		cout << display_code << id_num << ": Cannot recover! No stamina points remaining in this Pokemon Center" << endl;
	}
	else // can recover stamina
	{
		this->state = RECOVERING_STAMINA;
		cout << display_code << id_num << ": Started recovering " << num_stamina_points << " stamina point(s) ";
		cout << "at Pokemon Center " << current_center->GetId() << endl;
		// set to minimum of stamina 
		if (num_stamina_points > current_center->GetNumStaminaPointsRemaining())
		{
			this->stamina_points_to_buy = current_gym->GetNumTrainingUnitsRemaining();
		}
		else
		{
			this->stamina_points_to_buy = num_stamina_points;
		}
	}
}

void Pokemon::Stop()
{
	this->state = STOPPED;
	cout << display_code << id_num << ": Stopping..." << endl;
}

bool Pokemon::IsExhausted()
{
	if (stamina == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Pokemon::ShouldBeVisible()
{
	if (IsExhausted() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Pokemon::ShowStatus()
{
	cout << name << " status: ";
	GameObject::ShowStatus();
	// print state specific status info
	if (this->state == STOPPED)
	{
		cout << "stopped" << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else if (this->state == MOVING)
	{
		cout << "moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else if (this->state == MOVING_TO_CENTER)
	{
		cout << "heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else if (this->state == MOVING_TO_GYM)
	{
		cout << "heading to gym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else if (this->state == IN_CENTER)
	{
		cout << "inside Pokemon Center " << current_center->GetId() << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else if (this->state == IN_GYM)
	{
		cout << "inside Pokemon Gym " << current_gym->GetId() << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else if (this->state == TRAINING_IN_GYM)
	{
		cout << "training in Pokemon Gym " << current_gym->GetId() << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else if (this->state == RECOVERING_STAMINA)
	{
		cout << "recovering stamina in Pokemon Center " << current_center->GetId() << endl;
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
	else
	{
		cout << "Stamina: " << stamina << endl;
		cout << "Pokemon Dollars: " << pokemon_dollars << endl;
		cout << "Experience Points: " << experience_points << endl;
	}
}

bool Pokemon::Update()
{
	unsigned int exp_gained; // calculated through TrainPokemon
	unsigned int stamina_gain; // calculated through DistrubteStamina
	bool hasArrived; // check if pokemon has arrived at destination
	switch (state)
	{
	case 0: return false;
		break;
	case 1:
		hasArrived = UpdateLocation();
		if (IsExhausted() == true)
		{
			this->state = EXHAUSTED;
			return true;
		}
		else if (hasArrived == true)
		{
			this->state = STOPPED;
			if (is_in_center == true)
			{
				is_in_center = false;
				current_center->RemoveOnePokemon();
				current_center = 0;
			}
			else if (is_in_gym == true)
			{
				is_in_gym = false;
				current_gym->RemoveOnePokemon();
				current_gym = 0;
			}
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 2:
		return false;
	case 3: return false;
		break;
	case 4: return false;
		break;
	case 5:
		hasArrived = UpdateLocation();
		if (IsExhausted() == true)
		{
			this->state = EXHAUSTED;
			return true;
		}
		else if (hasArrived == true)
		{
			this->state = IN_GYM;
			this->is_in_gym = true;
			current_gym->AddOnePokemon();
			if (is_in_center == true)
			{
				is_in_center = false;
				current_center->RemoveOnePokemon();
				current_center = 0;
			}
			return true;
		}
		else
		{
			return false;
		}
		break;
	case 6:
		hasArrived = UpdateLocation();
		if (IsExhausted() == true)
		{
			this->state = EXHAUSTED;
			return true;
		}
		else if (hasArrived == true)
		{
			this->state = IN_CENTER;
			this->is_in_center = true;
			current_center->AddOnePokemon();
			if (is_in_gym == true)
			{
				is_in_gym = false;
				current_gym->RemoveOnePokemon();
				current_gym = 0;
			}

			return true;
		}
		else
		{
			return false;
		}
		break;
	case 7:
		/* reduce Pokemon stamina based on total stamina cost for the current gym
	   ▪ reduce the amount of Pokemon dollars based on the dollar cost for the
	   current gym
	   ▪ increase Pokemon training experience based on experience points gain
	   for the current gym; this should be calculated using TrainPokemon()
		*/
		this->stamina = stamina - current_gym->GetStaminaCost(training_units_to_buy);
		this->pokemon_dollars = pokemon_dollars - current_gym->GetDollarCost(training_units_to_buy);
		exp_gained = current_gym->TrainPokemon(training_units_to_buy);
		this->experience_points = experience_points + exp_gained;
		cout << "** " << name << " completed " << training_units_to_buy << " training unit(s)! **" << endl;
		cout << "** " << name << " gained " << exp_gained << " experience point(s)! **" << endl;
		this->state = IN_GYM;
		return true;
		break;
	case 8:
		/*Increase Pokemon stamina; stamina should be calculated by
	DistributeStamina()
	▪ Reduce Pokemon dollars by the total cost of stamina points for the
	current center*/
		stamina_gain = current_center->DistributeStamina(stamina_points_to_buy);
		this->stamina = stamina + stamina_gain;
		this->pokemon_dollars = pokemon_dollars - current_center->GetDollarCost(stamina_points_to_buy);
		cout << "** " << name << " recovered " << stamina_gain << " stamina point(s)! ** " << endl;
		this->state = IN_CENTER;
		return true;
		break;
	default: return false;
	}
}
char Pokemon::GetCode()
{
	return display_code;
}
string Pokemon::GetName()
{
	return name;
}
bool Pokemon::UpdateLocation()
{
	double DminusLx = (destination - location).x;
	double DminusLy = (destination - location).y;
	// update object's location while moving
	if (fabs(DminusLx) <= fabs(delta.x) && fabs(DminusLy) <= fabs(delta.y))
	{
		this->location.x = destination.x;
		this->location.y = destination.y;
		cout << display_code << id_num << ": I'm there!" << endl;
		return true;
	}
	else
	{
		this->location.x = location.x + delta.x;
		this->location.y = location.y + delta.y;
		this->stamina = stamina - 1;
		this->pokemon_dollars = pokemon_dollars + GetRandomAmountOfPokemonDollars();
		cout << display_code << id_num << ": step..." << endl;
		return false;
	}
}
void Pokemon::SetupDestination(Point2D dest)
{
	this->destination.x = dest.x;
	this->destination.y = dest.y;
	this->delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

void Pokemon::GetDestination()
{
	cout << destination << endl;  // test, can take out
}

void Pokemon::GetDelta()
{
	cout << delta << endl; // test, can take out
}
double GetRandomAmountOfPokemonDollars()
{
	srand(time(0));
	double myRand = (2.0 - 0.0) * ((double)rand() / (double)RAND_MAX) + 0.0;
	return myRand;
}

