#ifndef RobotAn_h
#define RobotAn_h
#include "Oxhmata.h"

class RobotAn : public Oxhmata {

public:

	RobotAn();

	int getPal() const;
	int getIr() const;
	int getLeuk() const;
	bool isFull() const;

	int getType() const; // epistrefei ton tupo tou oxhmatos
	void getInfo(char *) const; // epistrefei plhrofories gia to oxhma
	void action(Shmeia[WIDTH][HEIGHT], std::vector<Oxhmata*>); // sunarthsh leitourgias gia to oxhma

	static int getSunolPal(); // epistrefei sunolikh posothta palladiou
	static int getSunolIr(); // epistrefei sunolikh posothta iridiou
	static int getSunolLeuk(); // epistrefei sunolikh posothta leukoxrusou

	void setPal(int);
	void setIr(int);
	void setLeuk(int);

	void addPal(int);
	void addIr(int);
	void addLeuk(int);

private:
	int palladio, iridio, leukoxrusos, total_pal, total_ir, total_leuk;
	static const int max_fortio = 50;
	static int sunol_pal, sunol_ir, sunol_leuk;
};

#endif