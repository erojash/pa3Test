#include <iostream>
#include "PokemonCenter.h"

PokemonCenter::PokemonCenter(): Building()
{
	this->display_code = 'C';
	// this->pokemon_count = 0;
	this->stamina_capacity = 100;
	this->num_stamina_points_remaining = stamina_capacity;
	this->dollar_cost_per_stamina_point = 5;
	this->state = STAMINA_POINTS_AVAILABLE;
	cout << "PokemonCenter default constructed" << endl;
}

PokemonCenter::PokemonCenter(int in_Id, Point2D in_loc): Building()
{
	this->id_num = in_Id;
	this->location = in_loc;
	// remainder of of member varibales to their initial values
	this->stamina_capacity = 100;
	this->num_stamina_points_remaining = stamina_capacity;
	this->dollar_cost_per_stamina_point = 5;
	this->display_code = 'C';
	cout << "PokemonCenter constructed" << endl;
	this->state = STAMINA_POINTS_AVAILABLE;
}
PokemonCenter::~PokemonCenter()
{
	cout << "PokemonCenter destructed" << endl;
}
bool PokemonCenter::HasStaminaPoints()
{
	if (this->num_stamina_points_remaining >= 1)
	{
		return true;
	}
	else
	{
		return 0;
	}
}

unsigned int PokemonCenter::GetNumStaminaPointsRemaining()
{
	return this->num_stamina_points_remaining;
}

bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points, double budget)
{
	if (budget >= GetDollarCost(stamina_points))
	{
		return true;
	}
	else
	{
		return false;
	}
}

double PokemonCenter::GetDollarCost(unsigned int stamina_points)
{
	double cost = this->num_stamina_points_remaining * this->dollar_cost_per_stamina_point;
	return cost;
}

unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed)
{
	if (this->num_stamina_points_remaining >= points_needed)
	{
		this->num_stamina_points_remaining = num_stamina_points_remaining - points_needed;
		return points_needed;
	}
	else
	{
	  this->num_stamina_points_remaining = 0;
		return num_stamina_points_remaining;
	}
} 

bool PokemonCenter::Update()
{
	if (this->num_stamina_points_remaining == 0)
	{
		this->state = NO_STAMINA_POINTS_AVAILABLE;
		this->display_code = 'c';
		cout << "PokemonCenter " << this->id_num << " has run out of stamina points" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

void PokemonCenter::ShowStatus()
{
	cout << "Pokemon Center Status: ";
	Building::ShowStatus();
	cout << "Pokemon dollar cost per stamina point: " << this->dollar_cost_per_stamina_point << endl;
	cout << "has " << this->num_stamina_points_remaining << " stamina point(s) remaining" << endl;
}
