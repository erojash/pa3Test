#include <iostream>
#include "PokemonGym.h"

using namespace std;

PokemonGym::PokemonGym(): Building()
{
	this->display_code = 'G';
	this->id_num = 1;
	this->state = NOT_BEATEN;
	this->max_number_of_training_units = 10;
	this->num_training_units_remaining = max_number_of_training_units;
	this->stamina_cost_per_training_unit = 1;
	this->dollar_cost_per_training_unit = 1.0;
	this->experience_points_per_training_unit = 2;
	cout << "PokemonGym default constructed" << endl;
}
PokemonGym::PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, double dollar_cost, unsigned int exp_points_per_unit, int in_id, Point2D in_loc): Building()
{
	this->id_num = in_id;
	this->max_number_of_training_units = max_training_units;
	this->stamina_cost_per_training_unit = stamina_cost;
	this->experience_points_per_training_unit = exp_points_per_unit;
	this->dollar_cost_per_training_unit = dollar_cost;
	this->location = in_loc;
	// default for rest
	this->display_code = 'G';
	this->state = NOT_BEATEN;
	this->num_training_units_remaining = max_number_of_training_units;
	cout << "PokemonGym constructed" << endl;
}
PokemonGym::~PokemonGym()
{
	cout << "PokemonGym destructed" << endl;
}
double PokemonGym::GetDollarCost(unsigned int unit_qty)
{
	double cost = (double) unit_qty * dollar_cost_per_training_unit;
	return cost;
}
unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty)
{
	unsigned int cost = unit_qty * stamina_cost_per_training_unit;
	return cost;
}
unsigned int PokemonGym::GetNumTrainingUnitsRemaining()
{
	return num_training_units_remaining;
}
bool PokemonGym::IsAbleToTrain(unsigned int unit_qty, double budget, unsigned int stamina)
{
	// Returns true if a Pokemon with a given budget and stamina can request to train unit_qty training units 
	if (GetStaminaCost(unit_qty) <= stamina && GetDollarCost(unit_qty) <= budget) // ??
	{
		return true;
	}
	else
	{
		return false;
	}
}
unsigned int PokemonGym::TrainPokemon(unsigned int training_units)
{
	unsigned int exp_points;
	if (training_units > num_training_units_remaining)
	{
		// use num_training_units_remaining;
		exp_points = num_training_units_remaining * experience_points_per_training_unit;
		this->num_training_units_remaining = 0;
		return exp_points;
	}
	else
	{
		// use num_training_units_remaining - training_units;
		exp_points = (num_training_units_remaining - training_units) * experience_points_per_training_unit;
		return exp_points;
		
	}

}
bool PokemonGym::Update()
{
	if (num_training_units_remaining == 0)
	{
		this->state = BEATEN;
		this->display_code = 'g';
		cout << display_code << id_num << " has been beaten" << endl;
		return true;
	}
	else
	{
		return false;
	}
}
bool PokemonGym::IsBeaten()
{
	if (num_training_units_remaining == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void PokemonGym::ShowStatus()
{
	cout << "Pokemon Gym status: ";
	Building::ShowStatus();
	cout << "Max number of training units: " << max_number_of_training_units << endl;
	cout << "Stamina cost per training unit: " << stamina_cost_per_training_unit << endl;
	cout << "Pokemon dollar per training unit: " << dollar_cost_per_training_unit << endl;
	cout << "Experience points per training unit: " << experience_points_per_training_unit << endl;
	cout << num_training_units_remaining << " training unit(s) are remaining for this gym" << endl;
}
