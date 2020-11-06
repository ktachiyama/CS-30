#include "BaseballRoster.h"
#include <iostream>
#include <cctype>
using namespace std;

//prints the roster
void BaseballRoster::dump() const {
	cout << "ROSTER" << endl << "------------------------" << endl;
	PlayerNode *p;
	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		p = m_roster[bucket];
		while (p != nullptr) {
			cout << p->num << "  " << p->name << endl;
			p = p->next;
		}
	}
}

int Convert_Key(std::string key) {
	int i, total = 0;

	for (i = 0; i < key.length(); i++) {
		total = total + (i + 1) * key[i];
	}
	total = total % 10;

	return total;
}

int Convert_Key(int key) {
	return key % 10;
}

BaseballRoster::BaseballRoster() {
	//initializes all buckets to nullptr
	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		m_roster[bucket] = nullptr;
	}
}

//copy constructor
BaseballRoster::BaseballRoster(const BaseballRoster& rhs) {
	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++)
		m_roster[bucket] = nullptr;	//initializes all buckets to nullptr

	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		if (rhs.m_roster[bucket] != nullptr) {
			PlayerNode *rhs_p = rhs.m_roster[bucket];

			m_roster[bucket] = new PlayerNode;
			PlayerNode *copy_p = m_roster[bucket];

			while (rhs_p->next != nullptr) {
				copy_p->name = rhs_p->name;
				copy_p->num = rhs_p->num;
				copy_p->next = new PlayerNode;
				copy_p = copy_p->next;
				rhs_p = rhs_p->next;
			}
			copy_p->name = rhs_p->name;
			copy_p->num = rhs_p->num;
		}
	}
}

void BaseballRoster::copy(const BaseballRoster& rhs) {
	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++)
		m_roster[bucket] = nullptr;	//initializes all buckets to nullptr

	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		if (rhs.m_roster[bucket] != nullptr) {
			PlayerNode *rhs_p = rhs.m_roster[bucket];

			m_roster[bucket] = new PlayerNode;
			PlayerNode *copy_p = m_roster[bucket];

			while (rhs_p->next != nullptr) {
				copy_p->name = rhs_p->name;
				copy_p->num = rhs_p->num;
				copy_p->next = new PlayerNode;
				copy_p = copy_p->next;
				rhs_p = rhs_p->next;
			}
			copy_p->name = rhs_p->name;
			copy_p->num = rhs_p->num;
		}
	}
}

//assignment operator
const BaseballRoster &BaseballRoster :: operator=(const BaseballRoster &rhs) {
	if (this == &rhs)
		return *this;
	clearRoster();
	(*this).copy(rhs);
	return *this;
}

//destructor
BaseballRoster::~BaseballRoster() {
	clearRoster();
}

void BaseballRoster::clearRoster() {
	PlayerNode *p;
	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		p = m_roster[bucket];
		while (p != nullptr) {
			m_roster[bucket] = p;
			p = p->next;
			delete m_roster[bucket];
		}
	}
}

PlayerNode* BaseballRoster::returnPlayer(const PType player, PlayerNode *&p) const {
	p = m_roster[Convert_Key(player)];

	while (p != nullptr) { //traverse through linked list
		if (p->name == player) {
			return p;
		}
		p = p->next;
	}
	//player not found
	return nullptr;
}

////////////////////////////////////////////////////////////////////////

bool BaseballRoster::noPlayers() const {
	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		if (m_roster[bucket] != nullptr)
			return false;
	}
	//roster is empty
	return true;
}

int BaseballRoster::numberOfPlayers() const {
	int count = 0;
	PlayerNode *p;
	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		p = m_roster[bucket];
		while (p != nullptr) {
			count++;
			p = p->next;
		}
	}
	return count;
}

bool BaseballRoster::addPlayer(const PType& player, const NType& number) {
	//if the player already exists, return false
	if (playerOnRoster(player))
		return false;

	int bucket = Convert_Key(player);

	PlayerNode *p;
	p = m_roster[bucket];
	if (m_roster[bucket] == nullptr) {
		m_roster[bucket] = new PlayerNode;
		p = m_roster[bucket];
		p->name = player;
		p->num = number;
		return true;
	}

	else {
		while (p->next != nullptr)
			p = p->next;	//traverse to the end of the linked list
		p->next = new PlayerNode;
		p->next->name = player;
		p->next->num = number;
		return true;
	}
}

bool BaseballRoster::playerOnRoster(const PType& player) const {

	int bucket = Convert_Key(player);
	PlayerNode *p = m_roster[bucket];

	while (p != nullptr) { //traverse through linked list
		if (p->name == player) {
			return true;
		}
		p = p->next;
	}
	//player not found
	return false;
}

bool BaseballRoster::updatePlayer(const PType& player, const NType& number) {
	PlayerNode *p = returnPlayer(player, p);
	if (p != nullptr) {
		p->num = number;
		return true;
	}
	return false;
}

bool BaseballRoster::addOrUpdate(const PType& player, const NType& number) {
	if (updatePlayer(player, number))
		return true;
	else {
		addPlayer(player, number);
		return true;
	}
}

bool BaseballRoster::dfa(const PType& player) {
	int bucket = Convert_Key(player);
	PlayerNode *p = m_roster[bucket];

	if (p == nullptr)
		return false;

	if (p->name == player) {
		if (p->next != nullptr) {
			m_roster[bucket] = p->next;
		}
		delete p;
		m_roster[bucket] = nullptr;
		return true;
	}
	PlayerNode *q = p;
	p = p->next;

	while (p != nullptr) {
		if (p->name == player) {
			q->next = p->next;
			delete p;
			return true;
		}
		q = p;
		p = p->next;
	}//player not found
	return false;
}

bool BaseballRoster::findPlayer(const PType& player, NType& number) const {
	PlayerNode *p = returnPlayer(player, p);

	if (p == nullptr) //player not found
		return false;

	number = p->num;
	return true;
}

bool BaseballRoster::findPlayer(int i, PType& player, NType& number) const {
	if (i < 0 || i >= numberOfPlayers()) //if not 0 <= i < numberOfPlayers(), 
		return false;				   	 //i is invalid

	int player_count = 0;
	PlayerNode *p;

	for (int bucket = 0; bucket < NUM_BUCKETS; bucket++) {
		p = m_roster[bucket];
		while (p != nullptr) {
			if (player_count == i) { // once player_count = i, then assign
				player = p->name;	 //the player's info and return
				number = p->num;
				return true;
			}
			p = p->next;
			player_count++;
		}
	}
	return false;
}

void BaseballRoster::swapRoster(BaseballRoster& other) {
	BaseballRoster temp = other;
	other = *this;
	*this = temp;
}

bool combineRosters(const BaseballRoster& brOne, const BaseballRoster& brTwo, BaseballRoster& brMerged) {
	BaseballRoster mergedRoster;

	bool combine = true;
	PType player;
	NType r1_num;
	NType r2_num;

	for (int i = 0; i < brOne.numberOfPlayers(); i++) {
		brOne.findPlayer(i, player, r1_num);

		//if a player in brOne also exists in br2 (same 
		//NType and PType), then add it to mergedRoster
		if (brTwo.findPlayer(player, r2_num)) {
			if (r1_num == r2_num) {
				mergedRoster.addPlayer(player, r1_num);
			}
			//if a player in brOne has the same PType as a
			//player in brTwo, but their NType is different,
			//then bool combine becomes false and the player
			//is not added to mergedRoster.
			else {
				combine = false;
			}
		}
		else
			mergedRoster.addPlayer(player, r1_num);
	}

	//if a player in brTwo does not exist in brOne, add it
	//to mergedRoster
	for (int i = 0; i < brTwo.numberOfPlayers(); i++) {
		brTwo.findPlayer(i, player, r2_num);

		if (!brOne.findPlayer(player, r1_num)) {
			mergedRoster.addPlayer(player, r2_num);
		}
	}

	//set brMerged to mergedRoster
	brMerged = mergedRoster;

	return combine;
}

void outright(const BaseballRoster& brOne, const BaseballRoster& brTwo, BaseballRoster& brResult) {
	BaseballRoster outrightRoster;

	PType player;
	NType num;

	//if a player in brOne does not exist in brTwo, add
	//the player to outrightRoster.
	for (int i = 0; i < brOne.numberOfPlayers(); i++) {
		brOne.findPlayer(i, player, num);

		if (!brTwo.findPlayer(player, num)) {
			outrightRoster.addPlayer(player, num);
		}
	}
	
	//if a player in brTwo does not exist in brOne, add
	//the player to outrightRoster.
	for (int i = 0; i < brTwo.numberOfPlayers(); i++) {
		brTwo.findPlayer(i, player, num);

		if (!brOne.findPlayer(player, num)) {
			outrightRoster.addPlayer(player, num);
		}
	}

	brResult = outrightRoster;

}
