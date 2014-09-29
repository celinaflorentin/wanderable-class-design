// Wanderable takehome task #2: class design

/*
Approach: use the Observer Pattern (also known as the Publish/Subscribe model).
Each user can create multiple wishlists and add items to their wishlists.
Each user also publishes the contents of their wishlists.
Observers subscribe to the user's wishlists and are notified whenever a new item is added.
Observers can view a user's wishlist and choose to give any gift on the list.
Once an item is gifted, a user is notified and that item is removed from their wishlist 
(however only users are allowed to alter their own wishlists in any way)
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;


/*  
Wish class
This class holds the basic information for any wish.
*/
class Wish {
	int item_id
	string item_name;
	double item_price;
public:
	Wish (int id, string item, double price): item_id(id), item_name(item), item_price(price) {};
	~Wish ();
	void displayInfo (); // public getter to display wish details
};


/*
WishList class
This class holds methods for a vector of Wish objects
*/
class WishList {
	vector<Wish> wishes; 
public:
	WishList();
	// any class can view all the wishes in each wish list
	// printWishes calls displayInfo for each wish in each wish list
	void printWishes ();
private:
	void addWish (int item_id);
	void removeWish (int item_id);
	// only users can alter their wishlists
	// that is, only users can add or remove wishes from their wishlists
	friend class User; 
};


/* 
User class
This is our subject class.
*/
class User {
	vector<WishList> wishlists;
	vector<Observer> observers;
	string username;
public:
	User(string name): username(name) {};
	~User();
	void attach (Observer *o); // add observers
	void detach (Observer *o); // remove observers
	void notifyObservers (Wish *w); // alert observers once new wish is made
	// an Observer may call receiveGift
	// once a gift is received, the user's wishlist is automatically updated so that
	// the wish corresponding to the gift is removed from the list
	void receiveGift(Wish *w);
	// an Observer may call showWishes to view the details of a user's wishlist
	// this calls printWishes on each wishlist in wishlists
	void showWishes ();
private:
	// only users themselves can make/remove wishes or wishlists
	void makeWishList();
	void removeWishList();
	void makeWish();
	void cancelWish();
};


/* 
Observer class
*/
class Observer {
	User *giftee; // pointer to user to give gift to
	string name;
public:
	Observer (User *giftee, string name): giftee(giftee), name(name) {
		giftee->attach(this); // make this Observer subscribe to giftee's wishlists
	}
	~Observer () {
		giftee->detach(this); // make this Observer ubsubscribe from giftee's wishlists
	}
	// let this observer know of a new item added onto wishlist
	void notify(); 
	// a user calls giveGift to give a gift to the giftee
	// this calls receiveGift so that the wish may be deleted from the user's wishlist
	void giveGift(Wish *w);
};
