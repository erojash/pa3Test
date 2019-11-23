#include <iostream>
#include "Model.h"

Model::Model()
{
  this->time = 0;
  this->num_objects = 6;
  this->num_pokemon = 2;
  this->num_centers = 2;
  this->num_gyms = 2;
  Pokemon* pokemon1Ptr = new Pokemon("Pikachu", 1, 'P', 2, Point2D(5, 1));
  Pokemon* pokemon2Ptr = new Pokemon("Bulbasaur", 2, 'P', 1, Point2D(10, 1));
  PokemonCenter* center1Ptr = new PokemonCenter(1, Point2D(1, 20));
  PokemonCenter* center2Ptr = new PokemonCenter(2, Point2D(10, 20));
  PokemonGym* gym1Ptr = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
  PokemonGym* gym2Ptr = new PokemonGym(20, 5, 7.5, 8, 2, Point2D(5, 5));
  // putting object pointers into arrays
  this->object_ptrs[0] = pokemon1Ptr;
  this->object_ptrs[1] = pokemon2Ptr;
  this->object_ptrs[2] = center1Ptr;
  this->object_ptrs[3] = center2Ptr;
  this->object_ptrs[4] = gym1Ptr;
  this->object_ptrs[5] = gym2Ptr;
  this->pokemon_ptrs[0] = pokemon1Ptr;
  this->pokemon_ptrs[1] = pokemon2Ptr;
  this->center_ptrs[0] = center1Ptr;
  this->center_ptrs[1] = center2Ptr;
  this->gym_ptrs[0] = gym1Ptr;
  this->gym_ptrs[1] = gym2Ptr;
  cout << "Model default constructed" << endl;
}
Model::~Model()
{
  cout << "Model destructed" << endl;
}
Pokemon* Model::GetPokemonPtr(int id)
{
  if (pokemon_ptrs[0]->GetId() == id)
    {
      return pokemon_ptrs[0];
    }
  else if (pokemon_ptrs[1]->GetId() == id)
    {
      return pokemon_ptrs[1];
    }
  else
    {
      return 0;
    }
}
PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
  if (center_ptrs[0]->GetId() == id)
    {
      return center_ptrs[0];
    }
  else if (center_ptrs[1]->GetId() == id)
    {
      return center_ptrs[1];
    }
  else
    {
      return 0;
    }
}
PokemonGym* Model::GetPokemonGymPtr(int id)
{
  if (gym_ptrs[0]->GetId() == id)
    {
      return gym_ptrs[0];
    }
  else if (gym_ptrs[1]->GetId() == id)
    {
      return gym_ptrs[1];
    }
  else
    {
      return 0;
    }
}
bool Model::Update()
{
  int count = 0; // keep track of times update returned true
  time++; // incrementing time
  for (int i = 0; i < 6; i++)
    {
      bool checkUpdate = object_ptrs[i]->Update();
      if (checkUpdate == true)
	  {
	  count++;
	  }
    }
  if (gym_ptrs[0]->IsBeaten() == true && gym_ptrs[1]->IsBeaten() == true)
    {
      cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
      exit(EXIT_SUCCESS);
    }
  else if (pokemon_ptrs[0]->IsExhausted() == true && pokemon_ptrs[1]->IsExhausted() == true)
    {
      cout << "GAME OVER: You lose! All of your pokemon are tired!" << endl;
      exit(EXIT_FAILURE);
    }
  else if (count >= 1)
    {
      return true;
    }
  else
    {
      return false;
    }
}
	
void Model::Display(View& view)
{
	cout << "Time: " << time << endl;
	// view.Clear();
	// for loop for plot
	for (int i = 0; i < 6; i++)
	{
		view.Plot(object_ptrs[i]);
	}
	view.Draw();
}
void Model::ShowStatus()
{
  pokemon_ptrs[0]->ShowStatus();
  pokemon_ptrs[1]->ShowStatus();
  center_ptrs[0]->ShowStatus();
  center_ptrs[1]->ShowStatus();
  gym_ptrs[0]->ShowStatus();
  gym_ptrs[1]->ShowStatus();
}
