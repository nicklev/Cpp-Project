#include "Shmeia.h"

Shmeia::Shmeia()
{
	shmaia = false;
	palladio = rand() % 10; // arxikopoiei thn posothta palladiou sto shmeio
	iridio = rand() % 10; // arxikopoiei thn posothta iridiou sto shmeio
	leukoxriso = rand() % 10; // arxikopoiei thn posothta leukoxrusou sto shmeio
	epikind = rand() % 15 / 10.0f; // arxikopoiei thn epikindunothta tou shmeiou
	if (epikind > 0.9) {
		epikind -= 1;
	}
	occupied = false;
}

bool Shmeia::isOccupied() const
{
	return occupied;
}

bool Shmeia::isFlagged() const
{
	return shmaia;
}

void Shmeia::setPalladio(int pal)
{
	palladio = pal;
}

void Shmeia::setIridio(int ir)
{
	iridio = ir;
}

void Shmeia::setLeukoxriso(int leuk)
{
	leukoxriso = leuk;
}

void Shmeia::setEpikind(float ep)
{
	epikind = ep;
}

void Shmeia::setOccupied(bool oc)
{
	occupied = oc;
}

void Shmeia::setFlagged(bool fl)
{
	shmaia = fl;
}

int Shmeia::getPalladio() const
{
	return palladio;
}

int Shmeia::getIridio() const
{
	return iridio;
}

int Shmeia::getLeukoxriso() const
{
	return leukoxriso;
}

int Shmeia::getPeriek() const
{
	return palladio + iridio + leukoxriso;
}

float Shmeia::getEpikind() const
{
	return epikind;
}
