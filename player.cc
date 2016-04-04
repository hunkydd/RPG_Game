#include <string>
#include "PRNG.h"
#include "player.h"
#include "cell.h"
#include "unoccupied.h"
#include "game.h"
#include "item.h"

using std::string;
using std::cout;
using std::endl;

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
		_attack = 50;
		_defense = 15;
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
int Player::gold() { return _gold; }

void Player::reset() {
	_stair = false;
	if ( _class == "k" ) {
		_attack = _defense = 50;
	}else if ( _class == "w" ) {
		_attack = 25;
		_defense = 0;
	}else if ( _class == "s" ) {
		_attack = 50;
		_defense = 15;
	}
}
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
	if (grid[row][col]->display() == '>') {
		_stair = true;
	}else if ( grid[row][col]->display() == '$' ) {
		grid[row][col]->itemEffect(*this);
	}else if ( (grid[row][col]->display() == ' ') ||
			  		 (grid[row][col]->display() == '-') ||
			  		 (grid[row][col]->display() == '|') ) {
		throw ( "You can't move in that direction." );
	}else {
		delete grid[row][col].getContents();
		grid[row][col].changeContents(*this, '@');
		location(grid[x()][y()]);
		Unoccupied _unoccupied = new Unoccupied(x(), y(), true, true);
		grid[x()][y()].changeContents(_unoccupied, '.');
		x(row);
		y(col);
	}
}
void Player::attack( string dir, **Cell grid ) {
	int row = x(), col = y();
	if (_job == 1) {			// wizard
		int door = 0;		// if there are two or more doors(+) on the way, you cannot attack
		while ( true ) {
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
			char c = grid[row][col]->display();
			if ( c == '+' ) door++;
			if ( (c == '|') || (c == '-') || (c == '>') || (c == ' ') || (door == 2) ) {
				throw ( "There is nothing there to attack!" );
			}else if ( (c == 'X') || (c == 'g') || (c == 'O') || (c == 'M') || (c == 'D') ) {
				int ceiling = grid[row][col]->getContents()->getDefense() == 0 ? 0 : 1;
				int dmg = -(_attack * (100 - grid[row][col]->getContents()->getDefense()) / 100 + ceiling);
				grid[row][col]->getContents()->setHealth(dmg);
				if ( !grid[row][col]->getContents()->isHostile() ) {
					grid[row][col]->getContents()->becomeHostile( grid[row][col] );
					cout << "This is an act of war to every " << grid[row][col]->getContents()->getName() << "!" << endl;
				}
				cout << "You attack the " << grid[row][col]->getContents()->getName();
				cout << "with your Inifinite Loop Laser for " << -dmg << " damage!" << endl;
				if (grid[row][col]->getContents()->getHealth() == 0) {
					grid[row][col]->getContents()->die();
				}
				break;
			}else continue;
		}
	}else {							// knight & samurai
		string skill = (_job == 0 ? "Sword of Segfault" : "Memory Corruption Katana");
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
	char c = grid[row][col]->display();
	if ( (c == '.') || (c == '|') || (c == '+') || (c == '#') || (c == '>') || (c == '-') ) {
		throw( "There is nothing there to attack!" );
	}
	int ceiling = getLocation()->getDefense() == 0 ? 0 : 1;
	int dmg = -(_attack * (100 - getLocation()->getDefense()) / 100 + ceiling);
	grid[row][col]->getContents()->setHealth(dmg);
	if ( !grid[row][col]->getContents()->isHostile() ) {
		grid[row][col]->getContents()->becomeHostile( grid[row][col] );
		cout << "This is an act of war to every " << grid[row][col]->getContents()->getName() << "!" << endl;
	}
	cout << "You attack the " << grid[row][col]->getContents()->getName();
	cout << "with your " << skill << " for " << -dmg << " damage!" << endl;
}
void Player::use( string dir, Cell **grid ) {
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
	if ( (grid[row][col]->display() == '$') || (grid[row][col]->display() == '!') ) {
		grid[row][col]->itemEffect(this);
	}else {
		throw ( "There is nothing there to use!" );
	}
}

void Player::setHealth( int h ) {
	if ( _health() + h > _maxHealth() ) { _health = _maxHealth; }
	else if ( _health() + h < 0 ) { _health = 0; }
	else { _health += h; }
}
void Player::setAttack( int a ) {
	if ( _attack() + a > 100 ) { _attack = 100; }
	else if ( _attack() + a < 0 ) { _attack = 0; }
	else { _attack += a; }
}
void Player::setDefense( int d ) {
	if ( _defense() + d > 100 ) { _defense = 100; }
	else if ( _defense() + d < 0 ) { _defense = 0; }
	else { _defense += d; }
}
void Player::setGold( int g ) { _gold += g; }
