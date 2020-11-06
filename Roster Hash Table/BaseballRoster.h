#ifndef BASEBALLROSTER_H
#define BASEBALLROSTER_H
#include <string>

typedef std::string PType;
typedef int NType;

const int NUM_BUCKETS = 10;

struct PlayerNode {
	PType name;
	NType num;
	PlayerNode *next = nullptr;
};

class BaseballRoster {
private:
	//open hash table
	PlayerNode *m_roster[NUM_BUCKETS];

	//copy funciton
	void copy(const BaseballRoster& rhs);
	//deletes all dynamically allocated data and sets buckets to nullptr 
	void clearRoster();
	PlayerNode* returnPlayer(const PType player, PlayerNode *&p) const;

public:
	void dump() const;

	// Create an empty BaseballRoster map 
	BaseballRoster();

	//copy constructor
	BaseballRoster(const BaseballRoster& rhs);

	//assignement operator
	const BaseballRoster& operator=(const BaseballRoster  &rhs);

	//destructor
	~BaseballRoster();

	// Return true if the BaseballRoster map
	// is empty, otherwise false.
	bool noPlayers() const;

	// Return the number of players in
	// the BaseballRoster map.
	int numberOfPlayers() const;

	// If player is not equal to any player currently in the
	// BaseballRoster, and if the player/number pair can be added to 
	// the BaseballRoster, then do so and return true. Otherwise, 
	// make no change to the BaseballRoster and return false 
	// (indicating that the player is already in the BaseballRoster).
	bool addPlayer(const PType& player, const NType& number);

	// If player is equal to a player currently in the
	// BaseballRoster, then make that player no longer map to the
	// number it currently maps to, but instead map to the number of
	// the second parameter; return true in this case. Otherwise, 
	// make no change to the BaseballRoster and return false.
	bool updatePlayer(const PType& player, const NType& number);

	// If player is equal to a player currently in the
	// BaseballRoster, then make that player no longer map to the
	// number it currently maps to, but instead map to the number of
	// the second parameter; return true in this case. If player is
	// not equal to any player currently in the BaseballRoster, then
	// add it and return true. In fact, this function always returns true. 
	bool addOrUpdate(const PType& player, const NType& number);

	// Designate for Assignment
	// If player is equal to a player currently in the
	// BaseballRoster, remove the player/number pair with that
	// player from the map and return true.  Otherwise, make no
	// change to the BaseballRoster and return false. 
	bool dfa(const PType& player);

	// Return true if player is equal to a player currently in the
	// BaseballRoster, otherwise false.
	bool playerOnRoster(const PType& player) const;

	// If player is equal to a player currently in the
	// BaseballRoster, set number to the number in the map that that
	// key maps to, and return true.  Otherwise, make no change to
	// the number parameter of this function and return false. 
	bool findPlayer(const PType& player, NType& number) const;

	// If 0 <= i < numberOfPlayers(), copy into the player and
	// number parameters the player and number of one of the
	// player/number pairs in the map and return true.  Otherwise,
	// leave the player and number parameters unchanged and return
	// false. 
	bool findPlayer(int i, PType& player, NType& number) const;

	// Exchange the contents of this map with the other one. 
	void swapRoster(BaseballRoster& other);

};

bool combineRosters(const BaseballRoster& brOne, const BaseballRoster& brTwo, BaseballRoster& brMerged);
void outright(const BaseballRoster& brOne, const BaseballRoster& brTwo, BaseballRoster& brResult);



#endif

