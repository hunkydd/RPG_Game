#include <string>
#include "PRNG.h"
#include "player.h"
#include "cell.h"
#include "unoccupied.h"
#include "game.h"

using std::string;

Player::Player( char _class )
	: gold(0) {
	if ( _class == "k" ) {
		_job = 0;
		_maxHealth = _health = 100;
		_attack = _defense = 50;
	}else if ( _class == "w" ) {
		_job = 1;
		_maxHealth = _health = 60;
		_attack = 25;
		_defense = 0;
	}else if ( _class == "s" ) {
		_job = 2;
		_maxHealth = _health = 80;
		_atk = 50;
		_def = 15;
	}
}

string Player::getType() {
	switch ( _job ) {
		case 0:
			return "Knight";
		case 1:
			return "Wizard";
		case 2:
			return "Samurai";
	}
}
int Player::health() { return _health; }
int Player::maxHealth() { return _maxHealth; }
int Player::attack() { return _attack; }
int Player::defense() { return _defense; }
int Player::gold() { return _gold; }

void Player::move( string dir, **Cell grid ) {		// should return a GameObject
	int row = x(), col = y();
	switch ( dir ) {
		case "nw":
			row--; col--; break;
		case "no":
			row--; break;
		case "ne":
			row--; col++; break;
		case "wo":
			col--; break;
		case "eo":
			col++; break;
		case "sw":
			row++; col--; break;
		case "so":
			row++; break;
		case "se":
			row++; col++; break;
	}
	if ( !grid[row][col]->getContents()->canWalk() ) {
		throw ( "There is something in the way" );
	}
	Unoccupied *_unoccupied = new Unoccupied(x(), y(), true, true);
	grid[x()][y()].changeContents(_unoccupied);
	x(row);
	y(col);
	grid[x()][y()].changeContents(this);
}
void Player::attack( string dir, **Cell grid ) {
	int row = x(), col = y();
	if (job == 1) {			// wizard
		switch ( dir ) {
			case "nw":
				for (;grid[row][col]->getContents()->;row--, col--) {

				}
				break;
			case "no":
				break;
			case "ne":
				break;
			case "wo":
				break;
			case "eo":
				break;
			case "sw":
				break;
			case "so":
				break;
			case "se":
				break;
		}
	}else {							// knight & samurai
		switch ( dir ) {
			case "nw":
				row--; col--; break;
			case "no":
				row--; break;
			case "ne":
				row--; col++;
				break;
			case "wo":
				col--; break;
			case "eo":
				col++; break;
			case "sw":
				row++; col--; break;
			case "so":
				row++; break;
			case "se":
				row++; col++; break;
		}
	}
	if ( grid[row][col]->canWalk() ) {
		throw( "There is nothing there!" );
	}
	int ceiling = getLocation()->getDefense() == 0 ? 0 : 1;
	int dmg = -(atk * (100 - getLocation()->getDefense()) / 100 + ceiling);
	grid[row][col]->getContents()->setHealth(dmg);
	// char _type = grid[row][col].getContents().getType();
	// if ( _class == 's' ) {
	// 	extern int MAX_COLS, MAX_ROWS;
	// 	for (int i = 0; i <= MAX_ROWS; i++) {
	// 		for (int j = 0; j <= MAX_COLS; j++) {
	// 			if (grid[i][j].getContents().getType() == _type) {
	// 				grid[i][j].getContents().becomeHostile();
	// 			}
	// 		}
	// 	}
	// }
}
void Player::setHealth( int h ) {
	if ( _health() + h > _maxHealth() ) { _health = _maxHealth; }
	else if ( _health() + h < 0 ) { _health = 0; }
	else { _health += h; }
}
