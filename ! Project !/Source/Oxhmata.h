#ifndef Oxhmata_h
#define Oxhmata_h
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Shmeia.h"
#define WIDTH 20
#define HEIGHT 15
using namespace std;

class Oxhmata{
public:

	Oxhmata(); // Constructor

	virtual int getType() const; // epistrefei ton tupo tou oxhmatos
								// 0 -> robot analushs
							   // 1 -> robot diaswshs
							  // 2 -> robot e3ereunhshs
	virtual void getInfo(char *) const;	// epistrefei plhrofories gia to oxhma
	virtual void action(Shmeia[WIDTH][HEIGHT], std::vector<Oxhmata*>); // sunarthsh metakinhshs tou oxhmatos
	void move(Shmeia[WIDTH][HEIGHT]); // metakinei ta oxhmata
	void failure(Shmeia[WIDTH][HEIGHT]); // upologizei thn pi8anothta na pa8ei vlavh kata th metakinhsh

	int getSpeed() const; // epistrefei thn taxuthta tou oxhmatos
	float getAbility() const; // epistrefei thn ikanothta tou oxhmatos
	bool isOK() const; // epistrefei true an den exei kapoia vlavh
	int isActive() const; // elegxei an to oxhma kanei kati

	void setX(int);	// 8etoun tis suntetagmenes x, y
	void setY(int);

	int getX() const; // epistrefoun tis suntetagmenes x, y
	int getY() const;
	int getFails() const; // epistrefei ton ari8mo twn vlavwn tou ka8e oxhmatos
	static int getTotalFails();	// epistrefei ton ari8mo twn vlavwn olwn twn oxhmatwn
	int getMoves() const; // epistrefei ton ari8mo twn metakinhsewn
	int getTeleport() const; // gia to teleport animation
	int getDestroy() const;	// timer gia thn katastrofh, times -1, -2, -3 gia to animation, timh -4 gia katastrofh

	void setSpeed(int);	// 8etei thn taxuthta tou oxhmatos
	void setAbility(float);	// 8etei thn ikanothta tou oxhmatos
	void setState(bool); // 8etei thn katastash tou oxhmatos
	void setActive(int); // active > taxuthta shmainei oti den mporei na kounh8ei
	void setTeleport(int); // orizei to teleport
	void setDestroy(int); // orizei to destroy

private:
	float ikanothta;
	static int total_fails;
	int taxuthta, active, x_8esh, y_8esh, moves, fails, teleport, destroy;
	bool katastash;

};


#endif
