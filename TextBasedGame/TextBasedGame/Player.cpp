#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"
#include "String.h"
#include <vector>
#include "Enemy.h"
#include <algorithm>
#include "Room.h"
#include "Character.h"
#include "Shift.h"
#include "Teleport.h"
#include "Earthquake.h"
#include "Game.h"
#include "LightningBolt.h"
#include "Fireball.h"

Player::Player() : Character{{0,0}, m_maxHP, 15, 5}, m_inCombat{false}
{
	m_manaPoints = m_maxMP;
	m_healthPoints = m_maxHP;
	m_priority = PRIORITY_PLAYER;
}

Player::Player(Point2D position) : Character{ position, m_maxHP, 15, 5 }, m_inCombat{ false }
{
	m_manaPoints = m_maxMP;
	m_healthPoints = m_maxHP;
	m_priority = PRIORITY_PLAYER;
}

Player::~Player()
{
	for (auto iter = m_Items.begin(); iter < m_Items.end(); iter++) {
		delete (*iter);
	}
	m_Items.clear();
}

void Player::AddItem(Item* item)
{
	// Have the item apply its buff
	item->OnPickup(this);

	// Add new Item to the array and sort it alphabetically
	m_Items.push_back(item);
	std::sort(m_Items.begin(), m_Items.end(), Item::Compare);
}

void Player::Draw()
{
	// Draw stats at top of screen
	std::cout << STATS_OUTPUT_POS << "HP: " << (int)m_healthPoints << "/" << (int)m_maxHP 
		<< "    MP: " << (int)m_manaPoints << "/" << (int)m_maxMP
		<< "    Attack: " << (int)m_attackPoints << "     Defense: " << (int)m_defendPoints;

	Point2D outPos = { INDENT_X + (5 * m_mapPosition.x) + 3,  MAP_Y + (m_mapPosition.y * 2) };
	// draw the player's position on the map
	// move cursor to map pos and delete character at current position, replace it with player
	std::cout << CSI << outPos.y << ";" << outPos.x << "H";
	std::cout << MAGENTA << "\x81" << RESET_COLOR;

	
	std::cout << INVENTORY_OUTPUT_POS << CSI << "15M";

	// Draw spellbook
	std::cout << INVENTORY_OUTPUT_POS << YELLOW;
	if (m_inCombat)
		std::cout << "Known Combat Spells:";
	else
		std::cout << "Known Utility Spells:";
	std::cout << RESET_COLOR << std::endl;

	for (auto iter = m_spells.begin(); iter < m_spells.end(); iter++) {
		// display utility or combat spells based on whether player is in combat
		if ((*iter)->IsForCombat() == m_inCombat) { 
			std::cout << INDENT << INDENT <<
				(*iter)->GetName() << ": " << (*iter)->GetDescription() << std::endl;
		}
	}

	// Draw inventory
	std::cout << std::endl << std::endl << INDENT;
	std::cout << YELLOW << "Inventory: " << RESET_COLOR << std::endl;
	for (auto iter = m_Items.begin(); iter < m_Items.end(); iter++) {
		std::cout << INDENT << INDENT <<
			(*iter)->GetName() << ": " << (*iter)->GetDescription() << std::endl;
	}
}

void Player::DrawDescription()
{
}

void Player::LearnSpell(String spellName)
{
	// Add the specified spell to player's known spells
	if (spellName == "Shift") {
		Shift* spell = new Shift;
		m_spells.push_back(spell);
	}
	else if (spellName == "Teleport") {
		Teleport* spell = new Teleport;
		m_spells.push_back(spell);
	}
	else if (spellName == "Earthquake") {
		Earthquake* spell = new Earthquake;
		m_spells.push_back(spell);
	}
	else if (spellName == "Lightning Bolt") {
		LightningBolt* spell = new LightningBolt;
		m_spells.push_back(spell);
	}
	else if (spellName == "Fireball") {
		Fireball* spell = new Fireball;
		m_spells.push_back(spell);
	}
	else {
		return;
	}

	// Then sort spells alphabetically
	std::sort(m_spells.begin(), m_spells.end(), Spell::Compare);
}

void Player::ExecuteCommand(int command, Room* pRoom, String spellName, Game* game)
{
	std::vector<int> transitions = pRoom->GetTransitions();

	switch (command) {
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1 && std::find(transitions.begin(), transitions.end(), command) != transitions.end()) {
			m_mapPosition.x++;
		}
		return;
	case WEST:
		if (m_mapPosition.x > 0 && std::find(transitions.begin(), transitions.end(), command) != transitions.end()) {
			m_mapPosition.x--;
		}
		return;
	case NORTH:
		if (m_mapPosition.y > 0 && std::find(transitions.begin(), transitions.end(), command) != transitions.end()) {
			m_mapPosition.y--;
		}
		return;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1 && std::find(transitions.begin(), transitions.end(), command) != transitions.end()) {
			m_mapPosition.y++;
		}
		return;
	case NORMAL_ATTACK:
		Attack(pRoom->GetEnemy(), game, false);
		break;
	case RISKY_ATTACK:
		Attack(pRoom->GetEnemy(), game, true);
		break;
	case PICKUP:
		Pickup(pRoom);
		break;
	case CAST:
		CastSpell(spellName, game);
		break;
	case COMBAT_FAIL:
		std::cout << EXTRA_OUTPUT_POS << RED << "You're in combat, you can't do that right now!" << RESET_COLOR << std::endl;
		break;
	default:
		// the command was not valid so do nothing
		std::cout << EXTRA_OUTPUT_POS << RED << "You try, but you just can't do it." << RESET_COLOR << std::endl;
		break;
	}

	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}

void Player::Pickup(Room* pRoom)
{
	// check if Item exists in room
	if (pRoom->GetItem() != nullptr) {
		Item* Item = pRoom->GetItem();

		// Tell user what Item was picked up
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You picked up the " << 
			YELLOW << Item->GetName() << RESET_COLOR << "." << std::endl;

		// add Item to inventory
		AddItem(Item);

		// Clear Item from room
		pRoom->RemoveGameObject(Item);
	}
	else {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
	}
}

void Player::Attack(Enemy* pEnemy, Game* game, bool isRisky)
{

	if (pEnemy == nullptr) {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here to fight." << std::endl;
	}
	else {
		std::cout << EXTRA_OUTPUT_POS;

		int damageDealt = 0;
		if (isRisky) {
			if (rand() % 10 < 5) // 50% chance to hit
				damageDealt = m_attackPoints * 2 + (rand() % 8) - 4; // large variance in damage (+-4dmg)
			else
				std::cout << RED << "You missed your risky swing!" << std::endl;
		}
		else {
			// regular attack (guaranteed hit)
			damageDealt = m_attackPoints + (rand() % 4) - 2; // small variance in damage (+-2dmg)
		}

		// Tell enemy to take damage from the attack
		if (damageDealt > 0) {
			int actualDmgDealt = pEnemy->OnAttacked(damageDealt);
			// Report how much damage was dealt and enemy's remaining health
			std::cout << RESET_COLOR <<
				"You hit the enemy, dealing " << YELLOW << actualDmgDealt <<
				" damage." << RESET_COLOR << std::endl;
			
			if (pEnemy->IsAlive())
				std::cout << INDENT << "The enemy has " << pEnemy->GetHP() <<
				" health remaining." << std::endl;
		}


		// If enemy dies, tell the player
		if (pEnemy->IsAlive() == false) {
			pEnemy->OnDeath(game);
		}
		else {
			// Otherwise the enemy does their chosen attack intent
			int damageTaken = pEnemy->Attack(this);
			if (damageTaken != -1){
				// if the attack involves taking damage, take the damage
				m_healthPoints -= damageTaken;
			}
		}
	}
}

void Player::CastSpell(String spellName, Game* game)
{
	// Binary Search for spellName in spellbook
	int leftBound = 0;
	int rightBound = m_spells.size() - 1;
	Spell* spell = nullptr;
	
	while (leftBound <= rightBound) {
		// set mid index to be in the middle of the left and right bounds
		int mid = (int)((leftBound + rightBound) / 2);

		// check if the middle spell name is the one we are looking for
		if (spellName == m_spells[mid]->GetName().ToLower()) {
			spell = m_spells[mid];
			break;
		}

		// adjust left/right bounds based on if spellName comes before or after current middle value
		if (spellName > m_spells[mid]->GetName().ToLower()) {
			leftBound = mid + 1;
		}

		if (spellName < m_spells[mid]->GetName().ToLower()) {
			rightBound = mid - 1;
		}
	}

	// check if spell was not found in spellbook
	if (spell == nullptr) { 
		std::cout << EXTRA_OUTPUT_POS << RED <<
			"You don't know how to cast '" << spellName << "'." << RESET_COLOR << std::endl;
		return; 
	}

	// If program reaches here, the spell exists, therefore attempt to cast it
	// Check if spell is for the current state (combat or utility)
	if (spell->IsForCombat() != m_inCombat) {
		std::cout << EXTRA_OUTPUT_POS << RED <<
			"Now is not the time to use that spell!" << RESET_COLOR << std::endl;
		return;
	}
	// Check if player has enough mana first
	if (m_manaPoints < spell->GetCost()) {
		// Spell failed to cast (not enough mana)
		std::cout << EXTRA_OUTPUT_POS << RED <<
			"You dont have enough MP to cast that spell!" << RESET_COLOR << std::endl;
		return;
	}
	// Cast the spell and spend the mana
	spell->Cast(game, this);
	m_manaPoints -= spell->GetCost();

	// If spell was cast in combat, enemy then fights back
	if (m_inCombat) {
		game->GetRoom(m_mapPosition).GetEnemy()->Attack(this);
	}

	// Redraw game and player to update any changes that the spells made
	game->Draw();
	Draw(); // to update the player position and mana points

	std::cout << std::endl;
	return;
}


