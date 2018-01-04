#include "RobotEx.h"

RobotEx::RobotEx()
{
	shmaies = 0; // oi shmaies tou robot arxikopoiountai sto 0
}

int RobotEx::sunol_shmaies = 0; // oi sunolikes shmaies arxikopoiountai sto 0

int RobotEx::getType() const
{
	return 2; // ola ta robot e3ereunhshs exoun ari8mo oxhmatos 2
}

void RobotEx::getInfo(char *c) const
{
	sprintf(c, "Flags : %d", shmaies); // apo8hkeuetai stin metavlhth c o ari8mos twn shmaiwn
}

void RobotEx::action(Shmeia map[WIDTH][HEIGHT], std::vector<Oxhmata*> veh)
{
	int X = this->getX(), Y = this->getY(), dx = -1, dy = -1;
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
			// elegxei gia ta oria tou xarth, gia thn epikindunothta twn shmeiwn kai gia to an uparxei shmaia
			// an h syn8hkh isxuei tote topo8etei shmaia sto shmeio
			if ((dx || dy) && X + dx >= 0 && X + dx < WIDTH && Y + dy >= 0 && Y + dy < HEIGHT		
				&& map[X + dx][Y + dy].getEpikind() > 0.5 && !map[X + dx][Y + dy].isFlagged()) {	
				map[X + dx][Y + dy].setFlagged(true);												 	
				done = true; // enhmerwnei oti topo8eth8hke shmaia
				++shmaies;
				++sunol_shmaies;
				this->setActive(this->isActive() + 1); // gia enan guro akoma 8a einai active
			}
		} while (++dy < 2 && !done); // oi 2 brogxoi while exoun dhmiourgh8ei gia ton elegxo olwn twn tetragwnwn pou briskontai 
		dy = -1; // gurw apo to oxhma. Au3anontas katallhla ta dx kai dy prospelaunontai ola ta shmeia plhsion tou robot										
	} while (++dx < 2 && !done);
}

// epistrofh tou sunolikou ari8mou twn shmaiwn pou exei valei to sugkekrimeno robot 
int RobotEx::getShmaies() const
{
	return shmaies;
}

// epistrofh tou sunolikou ari8mou twn shmaiwn pou exoun topo8eth8ei apo ola ta oxhmata
int RobotEx::getSunolShmaies()
{
	return sunol_shmaies;
}
// pros8etei stis sunolikes shmaies
void RobotEx::addSunolShmaies(int shm)
{
	sunol_shmaies += shm;
}
