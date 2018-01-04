#ifndef RobotD_h
#define RobotD_h
#include "Oxhmata.h"

class RobotD : public Oxhmata {

public:

	RobotD(); // Constructor

	int getType() const; // epistrefei ton tupo tou oxhmatos
	void getInfo(char *) const; // epistrefei plhrofories gia to oxhma
	void action(Shmeia[WIDTH][HEIGHT], std::vector<Oxhmata*>); // sunarthsh leitourgias gia to oxhma

	int getEpiskeues() const; // epistrefei to atomiko ari8mo episkeuwn

	static int getSunolEpiskeues(); // epistrefei ton sunoliko ari8mo episkeuwn
	static void addSunolEpiskeues(int); // epistrefei sunoliko ari8mo episkeuwn olwn twn robot

private:
	int episkeues;
	static int sunol_episkeues;

};

#endif