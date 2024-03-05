#include "Player.h"
#include "GameDefines.h"
#include <vector>
#include "Enemy.h"
#include <algorithm>
#include "Room.h"
#include "Character.h"
#include "Shift.h"
#include "Teleport.h"
#include "Earthquake.h"
#include "Game.h"
#include "Lightning.h"
#include "Fireball.h"
#include "Aegis.h"

Player::Player() : Character{{0,0}, 100, 15, 5}, m_inCombat{false}
{
	m_manaPoints = m_maxMP;
	m_healthPoints = m_maxHP;
	m_priority = PRIORITY_PLAYER;
}

Player::Player(Point2D position) : Character{ position, 100, 15, 5 }, m_inCombat{ false }
{
	m_manaPoints = m_maxMP;
	m_healthPoints = m_maxHP;
	m_priority = PRIORITY_PLAYER;
}

Player::~Player()
{
	for (auto iter = m_inventory.begin(); iter < m_inventory.end(); iter++) {
		delete (*iter);
	}
	m_inventory.clear();
	for (auto iter = m_spells.begin(); iter < m_spells.end(); iter++) {
		delete (*iter);
	}
	m_spells.clear();
}

void Player::AddItem(Item* item)
{
	// Have the item apply its buff
	item->OnPickup(this);

	// Don't add spellbooks to the player's inventory
	if (item->GetName().Find("Spellbook") != -1) { return; }

	// Add new Item to the inventory array and sort it alphabetically
	m_inventory.push_back(item);
	std::sort(m_inventory.begin(), m_inventory.end(), Item::Compare);
}

void Player::Draw()
{
	// Draw stats at top of screen
	std::cout << STATS_OUTPUT_POS << CSI << "1M" << CSI << "1L";
	std::cout << STATS_OUTPUT_POS << "HP: " << (int)m_healthPoints << "/" << (int)m_maxHP
		<< "    MP: " << (int)m_manaPoints << "/" << (int)m_maxMP
		<< "    Attack: " << (int)m_attackPoints << "     Defense: " << (int)m_defendPoints;

	Point2D outPos = { INDENT_X + (5 * m_mapPosition.x) + 3,  MAP_Y + (m_mapPosition.y * 2) };
	// draw the player's position on the map
	// move cursor to map pos and delete character at current position, replace it with player
	std::cout << CSI << outPos.y << ";" << outPos.x << "H";
	std::cout << MAGENTA << "\x81" << RESET_COLOR;

	
	std::cout << INVENTORY_OUTPUT_POS << CSI << "35M";

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
			std::cout << INDENT << INDENT << MAGENTA << 
				(*iter)->GetName() << RESET_COLOR << ": " << 
				(*iter)->GetDescription() << std::endl;
		}
	}

	// Draw inventory
	std::cout << std::endl << std::endl << INDENT;
	std::cout << YELLOW << "Inventory: " << RESET_COLOR << std::endl;
	for (auto iter = m_inventory.begin(); iter < m_inventory.end(); iter++) {
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
	else if (spellName == "Lightning") {
		Lightning* spell = new Lightning;
		m_spells.push_back(spell);
	}
	else if (spellName == "Fireball") {
		Fireball* spell = new Fireball;
		m_spells.push_back(spell);
	}
	else if (spellName == "Aegis") {
		Aegis* spell = new Aegis;
		m_spells.push_back(spell);
	}
	else {
		return;
	}

	// Then sort spells alphabetically
	std::sort(m_spells.begin(), m_spells.end(), Spell::Compare);
}

void Player::ExecuteCommand(int command, Room* pRoom, String spellName, int target, Game* game)
{
	std::vector<int> transitions = pRoom->GetTransitions();

	// Do the appropriate action based on the command that the user inputted
	switch (command) {
	case EAST:
		// Before moving, check if room's transitions will allow it
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
		Attack(pRoom->GetEnemies(), game, false);
		break;
	case RISKY_ATTACK:
		Attack(pRoom->GetEnemies(), game, true);
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

	// After command has resolved, wait for user input so they can read what happened
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
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You picked up a " << 
			YELLOW << Item->GetName() << RESET_COLOR << "!" << std::endl;

		// add Item to inventory
		AddItem(Item);

		// Clear Item from room
		pRoom->RemoveGameObject(Item);

		// Redraw player to update stats and stuff
		Draw();
	}
	else {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
	}
}

void Player::Attack(std::vector<Enemy*> enemies, Game* game, bool isRisky)
{
	
	if (enemies.size() == 0) {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here to fight." << std::endl;
	}
	else {
		std::cout << EXTRA_OUTPUT_POS;

		int target = game->m_target - 1;
		if (target < 0 || target >= enemies.size()) {
			std::cout << RED << "Invalid target!" << RESET_COLOR << std::endl;
			return;
		}

		int damageDealt = 0;
		if (isRisky) {
			// risky attack (chance to miss, but deals high damage)
			if ((rand() % 100) / 100.0f < m_riskyHitChance) // normally 50% chance to hit
				damageDealt = m_attackPoints * 2 + (rand() % 8) - 4; // large variance in damage (+-4dmg)
			else
				std::cout << RED << "You missed your risky swing!" << std::endl;
		}
		else {
			// regular attack (guaranteed hit, normal damage)
			damageDealt = m_attackPoints + (rand() % 4) - 2; // small variance in damage (+-2dmg)
		}

		// Tell enemy to take damage from the attack
		if (damageDealt > 0) {
			int actualDmgDealt = enemies[target]->OnAttacked(damageDealt);
			// Report how much damage was dealt and enemy's remaining health
			std::cout << RESET_COLOR <<
				"You hit the " << enemies[target]->GetName() << ", dealing " << YELLOW << actualDmgDealt <<
				" damage." << RESET_COLOR << std::endl;
			
			if (enemies[target]->IsAlive())
				std::cout << INDENT << "The " << enemies[target]->GetName() << 
				" has " << enemies[target]->GetHP() << " health remaining." << std::endl;
		}


		// If enemy dies, tell the player
		if (enemies[target]->IsAlive() == false) {
			enemies[target]->OnDeath(game);
		}

		// Then each enemy does their chosen attack intent in retaliation
		for(Enemy* pEnemy : enemies)
			pEnemy->Attack(this, game);
	}
}

void Player::CastSpell(String spellName, Game* game)
{
	// Run binary search to check if this spell is known
	Spell* spell = SearchForSpell(spellName);

	// check if spell was not found in spellbook
	if (spell == nullptr) { 
		std::cout << EXTRA_OUTPUT_POS << RED <<
			"You don't know how to cast '" << spellName << "'." << RESET_COLOR << std::endl;
		return; 
	}

	// If program reaches here, the spell exists, therefore attempt to cast it
	// Check if spell is appropriate for the current state (combat or utility)
	if (spell->IsForCombat() != m_inCombat) {
		std::cout << EXTRA_OUTPUT_POS << RED <<
			"Now is not the time to use that spell!" << RESET_COLOR << std::endl;
		return;
	}

	// Check if player has enough mana to cast the spell
	if (m_manaPoints < spell->GetCost()) {
		// Spell failed to cast (not enough mana)
		std::cout << EXTRA_OUTPUT_POS << RED <<
			"You dont have enough MP to cast that spell!" << RESET_COLOR << std::endl;
		return;
	}

	// When casting Fireball, ensure the target is valid before casting the spell
	int target = game->m_target - 1;
	if (spellName == String("fireball") && 
		(target < 0 || target >= game->GetRoom(m_mapPosition).GetEnemies().size())) {
		std::cout << EXTRA_OUTPUT_POS << RED << "Invalid target for Fireball!" << RESET_COLOR << std::endl;
		return;
	}

	// Cast the spell and spend the mana
	spell->Cast(game, this);
	m_manaPoints -= spell->GetCost() * m_spellCostMultiplier;

	// If spell was cast in combat, each enemy then fights back
	if (m_inCombat) {
		for (Enemy* pEnemy : game->GetRoom(m_mapPosition).GetEnemies())
			pEnemy->Attack(this, game);
	}

	// Reset player's block to 0 after being attacked (from Ice Shield spell)
	m_block = 0;

	// Redraw game and player to update any changes that the spells made
	game->Draw();
	Draw(); // to update the player position and mana points

	std::cout << std::endl;
	return;
}

Spell* Player::SearchForSpell(String spellName)
{
	// Binary Search for spellName in spellbook
	int leftBound = 0;
	int rightBound = m_spells.size() - 1;

	while (leftBound <= rightBound) {
		// set mid index to be in the middle of the left and right bounds
		int mid = (int)((leftBound + rightBound) / 2);

		// check if the middle spell name is the one we are looking for
		if (spellName == m_spells[mid]->GetName().ToLower()) {
			return m_spells[mid];
		}

		// adjust left/right bounds based on if spellName comes before or after current middle value
		if (spellName > m_spells[mid]->GetName().ToLower()) {
			leftBound = mid + 1;
		}

		if (spellName < m_spells[mid]->GetName().ToLower()) {
			rightBound = mid - 1;
		}
	}

	// spell was not found, therefore return nullptr
	return nullptr;
}


