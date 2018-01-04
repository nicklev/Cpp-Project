#include "RobotAn.h"

RobotAn::RobotAn()
{
	// arxikopoiountai ola me 0
	palladio = 0;
	iridio = 0;
	leukoxrusos = 0;
	total_ir = 0;
	total_leuk = 0;
	total_pal = 0;
}

int RobotAn::sunol_pal = 0, RobotAn::sunol_ir = 0, RobotAn::sunol_leuk = 0;

int RobotAn::getType() const
{
	return 0; // o tupos twn oxhmatwn analushs einai 0
}

void RobotAn::getInfo(char *c) const
{
	// to c pairnei plhrofories gia to oxhma analushs
	sprintf(c, "Plat / Irid / Pallad : %d / %d / %d", total_leuk, total_ir, total_pal);
}

void RobotAn::action(Shmeia map[WIDTH][HEIGHT], std::vector<Oxhmata*> veh)
{
	int X = this->getX(), Y = this->getY(); // suntetagmenes tou oxhmatos
	// to active 8a meiwnetai mexri na ftasei thn taxuthta
	// to active au3anetai otan kanei kati to oxhma
	if (this->isActive() != this->getSpeed()) {
		this->setActive(this->isActive() - 1);
	}
	else {
		this->setActive(0);
	}
	if (map[X][Y].getPeriek() > 3) // an to shmeio exei upshlh periekthkothta
	{
		// kanei e3oru3h
		this->addIr(map[X][Y].getIridio());
		this->addLeuk(map[X][Y].getLeukoxriso());
		this->addPal(map[X][Y].getPalladio());
		// to shmeio adeiazei
		map[X][Y].setLeukoxriso(0);
		map[X][Y].setIridio(0);
		map[X][Y].setPalladio(0);
		this->setActive(this->isActive() + 1);
	}
}

int RobotAn::getSunolPal()
{
	return sunol_pal;
}

int RobotAn::getSunolIr()
{
	return sunol_ir;
}

int RobotAn::getSunolLeuk()
{
	return sunol_leuk;
}

int RobotAn::getPal() const
{
	return palladio;
}

int RobotAn::getIr() const
{
	return iridio;
}

int RobotAn::getLeuk() const
{
	return leukoxrusos;
}

bool RobotAn::isFull() const
{
	return (palladio + iridio + leukoxrusos >= max_fortio);
}

void RobotAn::setPal(int pal)
{
	palladio = pal;
}

void RobotAn::setIr(int ir)
{
	iridio = ir;
}

void RobotAn::setLeuk(int leuk)
{
	leukoxrusos = leuk;
}

void RobotAn::addPal(int pal)
{
	int _pal = palladio + pal > max_fortio ? max_fortio - palladio : pal;
	palladio += _pal;
	total_pal += _pal;
	sunol_pal += _pal;
}

void RobotAn::addIr(int ir)
{
	int _ir = iridio + ir > max_fortio ? max_fortio - iridio : ir;
	iridio += _ir;
	total_ir += _ir;
	sunol_ir += _ir;
}

void RobotAn::addLeuk(int leuk)
{
	int _leuk = leukoxrusos + leuk > max_fortio ? max_fortio - leukoxrusos : leuk;
	leukoxrusos += _leuk;
	total_leuk += _leuk;
	sunol_leuk += _leuk;
}
