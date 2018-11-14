#include <vector>
#include "carte.h"

std::vector<std::vector<state::TerrainTypeId>> map1() {
	std::vector<std::vector<state::TerrainTypeId>> carte1;
	carte1 = {{state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine},
	{state::routev,state::routev,state::routev,state::routedu,state::plaine,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::plaine,state::routedd,state::routev,state::routev,state::routev},
	{state::montagne,state::plaine,state::plaine,state::routeh,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::routeh,state::plaine,state::plaine,state::montagne},
	{state::montagne,state::montagne,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::montagne,state::montagne},
	{state::plaine,state::foret,state::plaine,state::routeh,state::routev,state::routedu,state::plaine,state::plaine,state::montagne,state::foret,state::foret,state::montagne,state::plaine,state::plaine,state::routedd,state::routev,state::routeh,state::plaine,state::foret,state::plaine},
	{state::plaine,state::foret,state::foret,state::routeh,state::plaine,state::routegd,state::routev,state::routev,state::routev,state::routev,state::routev,state::routev,state::routev,state::routev,state::routegu,state::plaine,state::routeh,state::foret,state::foret,state::plaine},
	{state::plaine,state::plaine,state::routedd,state::routegu,state::montagne,state::montagne,state::plaine,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::plaine,state::montagne,state::montagne,state::routegd,state::routedu,state::plaine,state::plaine},
	{state::plaine,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::montagne,state::montagne,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::plaine},
	{state::plaine,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::montagne,state::montagne,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::plaine},
	{state::plaine,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::montagne,state::montagne,state::montagne,state::montagne,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::plaine},
	{state::plaine,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::montagne,state::montagne,state::montagne,state::montagne,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::plaine},
	{state::plaine,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::montagne,state::montagne,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::plaine},
	{state::plaine,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::montagne,state::montagne,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::plaine},
	{state::plaine,state::plaine,state::routegd,state::routedu,state::montagne,state::montagne,state::plaine,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::plaine,state::montagne,state::montagne,state::routedd,state::routegu,state::plaine,state::plaine},
	{state::plaine,state::foret,state::foret,state::routeh,state::plaine,state::routedd,state::routev,state::routev,state::routev,state::routev,state::routev,state::routev,state::routev,state::routev,state::routedu,state::plaine,state::routeh,state::foret,state::foret,state::plaine},
	{state::plaine,state::foret,state::plaine,state::routeh,state::routev,state::routegu,state::plaine,state::plaine,state::montagne,state::foret,state::foret,state::montagne,state::plaine,state::plaine,state::routegd,state::routev,state::routeh,state::plaine,state::foret,state::plaine},
	{state::montagne,state::montagne,state::plaine,state::routeh,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::routeh,state::plaine,state::montagne,state::montagne},
	{state::montagne,state::plaine,state::plaine,state::routeh,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::plaine,state::foret,state::foret,state::foret,state::foret,state::plaine,state::routeh,state::plaine,state::plaine,state::montagne},
	{state::routev,state::routev,state::routev,state::routegu,state::plaine,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::plaine,state::routegd,state::routev,state::routev,state::routev},
	{state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine,state::foret,state::foret,state::plaine,state::plaine,state::plaine,state::plaine,state::plaine}};
	return(carte1);
};
