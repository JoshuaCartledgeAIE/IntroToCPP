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
#include "Game.h"

Player::Player() : Character{{0,0}, m_maxHP, BASE_AT, BASE_DF}, m_inCombat{false}
{
	m_manaPoints = m_maxMP;
	m_healthPoints = m_maxHP;
	m_attackPoints = BASE_AT;
	m_defendPoints = BASE_DF;
	m_priority = PRIORITY_PLAYER;
}

Player::Player(Point2D position) : Character{ position, m_maxHP, BASE_AT, BASE_DF }, m_inCombat{ false }
{
	m_manaPoints = m_maxMP;
	m_healthPoints = m_maxHP;
	m_attackPoints = BASE_AT;
	m_defendPoints = BASE_DF;
	m_priority = PRIORITY_PLAYER;
}

Player::~Player()
{
	for (auto iter = m_Items.begin(); iter < m_Items.end(); iter++) {
		delete (*iter);
	}
	m_Items.clear();
}

void Player::AddItem(Item* pUp)
{
	// Add new Item to the array and sort it alphabetically
	m_Items.push_back(pUp);
	std::sort(m_Items.begin(), m_Items.end(), Item::Compare);

	// Apply the stat buffs from the Item
	float healthChange = m_maxHP * pUp->GetHealthMultiplier() - m_maxHP;
	m_healthPoints += healthChange;
	m_maxHP *= pUp->GetHealthMultiplier();

	m_attackPoints *= pUp->GetAttackMultiplier();

	m_defendPoints *= pUp->GetDefenceMultiplier();
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

	// Draw inventory
	std::cout << INVENTORY_OUTPUT_POS << CSI << "15M"; 
	std::cout << INVENTORY_OUTPUT_POS << YELLOW << "Inventory: " << RESET_COLOR;
	for (auto iter = m_Items.begin(); iter < m_Items.end(); iter++) {
		std::cout << (*iter)->GetName() << "\t";
	}

	// Draw spellbook
	std::cout << std::endl << std::endl << INDENT << YELLOW;
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
		Attack(pRoom->GetEnemy(), false);
		break;
	case RISKY_ATTACK:
		Attack(pRoom->GetEnemy(), true);
		break;
	case PICKUP:
		Pickup(pRoom);
		break;
	case CAST:
		CastSpell(spellName, game);
		break;
	default:
		// the command was not valid so do nothing
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << std::endl;
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
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You picked up the " << Item->GetName() << std::endl;

		// add Item to inventory
		AddItem(Item);

		// Clear Item from room
		pRoom->RemoveGameObject(Item);
	}
	else {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
	}
}

void Player::Attack(Enemy* pEnemy, bool isRisky)
{
	if (pEnemy == nullptr) {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here to fight." << std::endl;
	}
	else {
		std::cout << EXTRA_OUTPUT_POS;

		int damageDealt = 0;
		if (isRisky) {
			if (rand() % 10 < 5) // 50% chance to hit
				damageDealt = m_attackPoints * 2 + (rand() % 8) - 4;
			else
				std::cout << RED << "You missed your risky swing!" << std::endl;
		}
		else {
			// regular attack (guaranteed hit)
			damageDealt = m_attackPoints + (rand() % 4) - 2;
		}
		
		// Tell enemy to take damage from the attack
		if (damageDealt > 0)
			pEnemy->OnAttacked(damageDealt);

		// If enemy dies, tell the player
		if (pEnemy->IsAlive() == false) {
			std::cout << GREEN << "You have killed the enemy!" << RESET_COLOR << std::endl;
		}
		else {
			// Otherwise the enemy fights back
			int damage = pEnemy->GetAT() - m_defendPoints;
			if (damage < 0) damage = 1 + rand() % 10;
			m_healthPoints -= damage;

			std::cout << RESET_COLOR <<
				"You fight the enemy and take " << damage <<
				" damage. Your health is now at " << m_healthPoints <<
				std::endl;
			std::cout << INDENT << "The enemy has " << pEnemy->GetHP() <<
				" health remaining." << std::endl;
		}
	}
}

void Player::CastSpell(String spellName, Game* game)
{
	// Search for spell in spellbook (Replace with binary search later???)
	for (Spell* spell : m_spells) {
		if (spellName == spell->GetName().ToLower()) {
			// Spell exists, therefore attempt to cast it
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
			spell->Cast(game, game->GetPlayer());
			m_manaPoints -= spell->GetCost();

			// Redraw game and player to update any changes that the spells made
			game->Draw();
			Draw(); // to update the player position and mana points

			std::cout << std::endl;
			return;
		}
	}

	// If program reaches here, the spell was not found in the player's known spells
	std::cout << EXTRA_OUTPUT_POS << RED << 
		"You don't know how to cast '" << spellName << "'."  << RESET_COLOR << std::endl;
}


