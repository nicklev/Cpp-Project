#include "RobotD.h"

RobotD::RobotD()
{
	episkeues = 0; // arxikopoiei tis episkeues sto 0
}

int RobotD::sunol_episkeues = 0; // arxikopoiei tis sunolikes episkeues sto 0

int RobotD::getType() const
{
	return 1; // epistrefei ton arithmo 1 pou antistoixei sta robot diaswshs
}

void RobotD::getInfo(char *c) const
{
	sprintf(c, "Rescues : %d", episkeues); // apo8hkeuei sto c ton ari8mo twn episkeuwn tou ka8e robot
}

void RobotD::action(Shmeia map[WIDTH][HEIGHT], std::vector<Oxhmata*> veh)
{
	int unsigned i = 0, dx = -1, dy = -1, X = this->getX(), Y = this->getY();
	bool done = false;			

	if (this->isActive() != this->getSpeed()) {
		this->setActive(this->isActive() - 1);
	}
	else {
		this->setActive(0);
	}
	do {
		do {
			// sun8hkh pou elegxei thn perioxh gurw apo to robot
			// elegxei gia ta oria tou xarth kai gia to an uparxei kapoio oxhma
			if ((dx || dy) && X + dx >= 0 && X + dx < WIDTH && Y + dy >= 0 && Y + dy < HEIGHT
				&& map[X + dx][Y + dy].isOccupied()) {
				do {
					// elegxei an kapoio oxhma gurw apo to robot diaswshs xreiazetai episkeuh
					if (veh[i]->getDestroy() > 0 && veh[i]->getX() == X + dx && veh[i]->getY() == Y + dy) {
						veh[i]->setState(true); // 8etei thn katastash tou oxhmatos true
						this->setActive(this->isActive() + 1); // gia enan guro akoma 8a einai active
						veh[i]->setActive(veh[i]->isActive() + 1); // gia enan guro akoma to oxhma pou epidior8w8hke 8a einai active
						veh[i]->setDestroy(0); // 8etei to destroy tou oxhmatos pou episkeuazetai sto 0
						++episkeues; // au3anei tis episkeues tou robot diaswshs kata 1
						++sunol_episkeues; // au3anei tis sunolikes episkeues kata 1
						done = true; // enhmerwnei oti egine episkeuh
					}
				} while (++i < veh.size() && !done);
				i = 0;
			}
		} while (++dy < 2 && !done);
		dy = -1;
	} while (++dx < 2 && !done); // stous 2 parapanw brogxous do-while au3anontas katallhla tis metablites
}								// dx, dy prospelaunontai ta geitonika shmeia ston xarth

int RobotD::getEpiskeues() const
{
	return episkeues;
}

int RobotD::getSunolEpiskeues()
{
	return sunol_episkeues;
}

void RobotD::addSunolEpiskeues(int ep)
{
	sunol_episkeues += ep;
}
