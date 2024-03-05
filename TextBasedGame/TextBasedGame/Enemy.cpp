#include "Enemy.h"
#include "Character.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

Enemy::Enemy() : Character{ {0,0}, 40, 15, 5 }, m_nextAttack{ ESCAPE }, m_seqIndex{ 0 }, m_itemDropChance{0}
{
	m_priority = PRIORITY_ENEMY;
}

Enemy::Enemy(Point2D pos, int HP, int AT, int DF, String name, float chance) :
	Character{ pos, HP, AT, DF }, m_name{ name }, m_nextAttack{ESCAPE}, m_seqIndex{ 0 }, m_itemDropChance{chance}
{
	m_priority = PRIORITY_ENEMY;
}

int Enemy::OnAttacked(int damageDealt)
{
	int damage = damageDealt - m_defendPoints;
	if (damage <= 0) damage = rand() % 10 + 1; // if DF was too high, take small random dmg

	SetHP(m_healthPoints - damage);
	return damage;
}

void Enemy::Attack(Player* pPlayer, Game* game)
{
	// Make sure a dead enemy doesn't attack!
	if (!IsAlive()) { return; }

	int damage = 0;
	int index = 0;

	// Every message starts with "The <enemyname>"
	std::cout << INDENT << "The " << YELLOW << m_name << " " << RESET_COLOR;
	
	// Act on attack intent
	switch (m_nextAttack)
	{
	case WEAK:
		// deal low amount of damage
		damage = CalculateDamage(0.75f, pPlayer);
		pPlayer->SetHP(pPlayer->GetHP() - damage);

		// print result of attack
		std::cout << "hit you with a weak attack, dealing " <<
			RED << damage << " damage, " << RESET_COLOR <<
			"and leaving you with " << GREEN << pPlayer->GetHP() << "HP remaining." << RESET_COLOR << std::endl;
		break;

	case MED:
		// deal normal amount of damage
		damage = CalculateDamage(1.0f, pPlayer);
		pPlayer->SetHP(pPlayer->GetHP() - damage);
		
		// print result of attack
		std::cout << "hit you with a normal attack, dealing " <<
			RED << damage << " damage, " << RESET_COLOR << 
			"and leaving you with " << GREEN << pPlayer->GetHP() << "HP remaining." << RESET_COLOR << std::endl;
		break;

	case STRONG:
		// deal high amount of damage
		damage = CalculateDamage(1.5f, pPlayer);
		pPlayer->SetHP(pPlayer->GetHP() - damage);

		// print result of attack
		std::cout << "hit you with a strong attack, dealing " << 
			RED << damage << " damage, " << RESET_COLOR <<
			"and leaving you with " << GREEN << pPlayer->GetHP() << "HP remaining." << RESET_COLOR << std::endl;
		break;

	case DEBUFF:
		break;

	case HEAL:
		// heal this enemy a large amount
		break;

	case STEAL:
		// pick a random item from player's inventory
		if (pPlayer->m_inventory.size() == 0) { std::cout << "found nothing to steal!" << std::endl; break; }
		index = rand() % pPlayer->m_inventory.size();
		// notify player of what item was stolen
		std::cout << "stole your " << YELLOW
			<< pPlayer->m_inventory[index]->GetName() << RESET_COLOR << " from you!" << std::endl;
		// Add it to enemy's inventory
		m_inventory.push_back(pPlayer->m_inventory[index]);
		// Make player lose the benefit of the item
		pPlayer->m_inventory[index]->OnStolen(pPlayer);
		// Remove it from player's inventory
		pPlayer->m_inventory.erase(pPlayer->m_inventory.begin() + index);
		break;

	case ESCAPE:
		// Remove this enemy from its room
		game->GetRoom(m_mapPosition).RemoveGameObject(this);
		std::cout << "ran away, taking all its stolen items with it!" << std::endl;
		break;

	default:
		break;
	}

	// If player was killed as a result of this attack, print lose message
	if (!pPlayer->IsAlive()) {
		std::cout << INDENT << RED << "YOU HAVE BEEN KILLED. GAME OVER." << std::endl;
		exit(0);
	}

	// Switch intent to the next attack in the sequence
	m_seqIndex = (m_seqIndex + 1) % m_attackSequence.size();
	m_nextAttack = m_attackSequence[m_seqIndex];
}

void Enemy::OnDeath(Game* game)
{
	// Let player know that the enemy died
	std::cout << INDENT << GREEN << "You killed the " << m_name << "!" << RESET_COLOR << std::endl << INDENT;
	
	// Either drop an item or some MP
	if ((rand() % 100) / 100.0f < m_itemDropChance) {
		std::cout << YELLOW << "The enemy dropped an item! (use the 'pickup' command to grab it!)" << RESET_COLOR << std::endl;
		game->AddStatItem(m_mapPosition);
	}
	else {
		Player* player = game->GetPlayer();

		// Increase players MP by random amount (capping it at max MP)
		int MPGain = rand() % 5 + 3;
		player->SetMP(player->GetMP() + MPGain);
		std::cout << "You gained " << BLUE << MPGain << "MP!" << RESET_COLOR;
	}
	std::cout << std::endl;

	// check for possible HP gain from harvester's scythe item
	if (game->GetPlayer()->m_gainHPOnKill) {
		int HPGain = rand() % 5 + 1;
		game->GetPlayer()->SetHP(game->GetPlayer()->GetHP() + HPGain);
		std::cout << INDENT << GREEN << "You gained " << HPGain <<
			"HP from the Harvester's Scythe!" << RESET_COLOR << std::endl;
	}

	// Return any stolen items
	if (m_inventory.size() > 0) {

		std::cout << SAVE_CURSOR_POS << INDENT << YELLOW <<
			"Your stolen items are now returned to you:" << RESET_COLOR << std::endl;
		for (Item* item : m_inventory) {
			game->GetPlayer()->m_inventory.push_back(item);
			std::cout << INDENT;
			item->OnPickup(game->GetPlayer());
		}

		// Go back to the output area
		std::cout << RESTORE_CURSOR_POS << CSI << m_inventory.size() + 1 << "B";

	}
}


void Enemy::DrawDescription()
{
	// Print summarised description of enemy's stats
	
	std::cout << m_name << ")  " << GREEN << m_healthPoints << "HP" 
		<< RESET_COLOR << "  Intent: " << YELLOW;

	switch (m_nextAttack) {
	case WEAK:
		std::cout << "weak attack";
		break;
	case MED:
		std::cout << "average attack";
		break;
	case STRONG:
		std::cout << "strong attack";
		break;
	case DEBUFF:
		std::cout << "weaken player";
		break;
	case STEAL:
		std::cout << "steal item";
		break;
	case ESCAPE:
		std::cout << "run away";
		break;
	default:
		std::cout << "error";
		break;
	}
		
	std::cout << RESET_COLOR << "     ";
}

float Enemy::CalculateDamage(float multiplier, Player* pPlayer)
{
	// Calculate damage, multipled by multiplier, with a bit of variance, minus player's defence
	float damage = m_attackPoints * multiplier + (rand() % 4) - 2 - pPlayer->GetDF();
	if (damage <= 0) damage = rand() % 5 + 1; // if player's DF was too high, deal small random dmg
	damage -= pPlayer->GetBlock();
	
	if (damage <= 0) {
		// reduce block by blocked amount
		pPlayer->SetBlock(-damage);
		damage = 0;
	}
	else {
		pPlayer->SetBlock(0);
	}
	return damage;
}

