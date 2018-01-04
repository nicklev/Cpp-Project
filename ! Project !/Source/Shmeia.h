#ifndef Shmeia_h
#define Shmeia_h
#include <cstdlib>

class Shmeia {

public:

	Shmeia(); // Constructor

	bool isOccupied() const; // epistrefei true an to shmeio einai kateillhmeno
	bool isFlagged() const;	// epistrefei true an to shmeio exei shmaia

	void setPalladio(int); // 8etei thn posothta tou palladiou
	void setIridio(int); // 8etei thn posothta tou iridiou
	void setLeukoxriso(int); // 8etei thn posothta tou leukoxrusou
	void setEpikind(float);	// 8etei thn epikindunotita tou shmeiou
	void setOccupied(bool);	// 8etei me true ta shmeia pou einai kateillhmena
	void setFlagged(bool); // 8etei thn shmaia

	int getPalladio() const; // epistrefei thn timh tou palladiou
	int getIridio() const; // epistrefei thn timh tou iridiou
	int getLeukoxriso() const; // epistrefei thn timh tou leukoxrusou

	int getPeriek() const; // epistrefei thn periektikothta tou shmeiou
	float getEpikind() const; // epistrefei thn epikindunothta

private:
	bool shmaia, occupied;
	float epikind;
	int palladio, iridio, leukoxriso;
};

#endif