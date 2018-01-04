#ifndef RobotEx_h
#define RobotEx_h
#include "Oxhmata.h"

class RobotEx : public Oxhmata {

public:

	RobotEx(); // Constructor

	int getType() const; // epistrefei to eidos tou oxhmatos
	void getInfo(char *) const;	// epistrefei plhrofories gia to oxhma
	void action(Shmeia[WIDTH][HEIGHT], std::vector<Oxhmata*>); // sunartish leitourgias tou oxhmatos

	int getShmaies() const; // epistrefei ton atomiko ari8mo shmaiwn

	static int getSunolShmaies(); // epistrefei ton sunoliko ari8mo shmaiwn
	static void addSunolShmaies(int); // pros8etei tis sunolikes shmaies

private:
	int shmaies;
	static int sunol_shmaies;

};

#endif