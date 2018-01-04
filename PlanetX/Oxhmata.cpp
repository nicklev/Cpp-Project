#include "Oxhmata.h"

Oxhmata::Oxhmata()
{
	//arxikopoihsh timwn
	ikanothta = (rand() % 15 + 1) / 10.0f;
	if (ikanothta > 1) {
		ikanothta -= 0.5;
	}
	katastash = true;	
	// taxuthta:
	// 0 -> grhgoro
	// -1 -> metrio
	// -2 -> argo
	taxuthta = rand() % 3 - 2;
	active = 0;	
	moves = 0;
	fails = 0;
	teleport = 0;
	destroy = 0;
}

int Oxhmata::total_fails = 0;

int Oxhmata::getType() const { return -1; }
void Oxhmata::getInfo(char *) const { }
void Oxhmata::action(Shmeia map[WIDTH][HEIGHT], std::vector<Oxhmata*> veh) { std::cout << "ERROR"; }

void Oxhmata::move(Shmeia map[WIDTH][HEIGHT])
{
	int X = this->getX(), Y = this->getY(), dX, dY;
	++moves; // au3anontai oi metakinhseis tou oxhmatos kata 1
	do {
		dX = (rand() % 3) - 1; // upologizontai tuxaies times gia ta dx, dy apo to -1 mexri to 1
		dY = (rand() % 3) - 1;
	} while (X + dX < 0 || X + dX >= WIDTH || Y + dY < 0 || Y + dY >= HEIGHT ||	// elegxei an oi suntetagmenes pou upologisthkan pio panw 
		map[X + dX][Y + dY].isOccupied() || map[X + dX][Y + dY].isFlagged());  // den vgainoun ektos oriwn tou xarth kai elegxei an sto
																			  // shmeio auto den uparxei allo oxhma kai den uparxei shmaia				
	map[X][Y].setOccupied(false); // 8etei thn arxikh 8esh tou robot ws mh kateilhmmenh
	map[X + dX][Y + dY].setOccupied(true); // 8etei thn kainouria 8esh ws kateilhmmenh
	this->setX(X + dX);	// 8etei tis kainouries suntetagmenes 
	this->setY(Y + dY);
}

void Oxhmata::failure(Shmeia map[WIDTH][HEIGHT])
{
	int X = this->getX(), Y = this->getY();
	int prob = rand() % 10;	// upologizei thn pi8anotita na pa8ei vlavh kata tin metakinhsh
	if (prob < 10 * map[X][Y].getEpikind() * (1 - this->getAbility())) {
		this->setState(false); // to oxhma pa8ainei vlavh
		map[X][Y].setEpikind(map[X][Y].getEpikind() / 2); // meiwnei thn epikindunothta tou shmeiou sto miso
	}
}

void Oxhmata::setX(int x)
{
	x_8esh = x;
}

void Oxhmata::setY(int y)
{
	y_8esh = y;
}

int Oxhmata::getSpeed() const
{
	return taxuthta;
}

float Oxhmata::getAbility() const
{
	return ikanothta;
}

bool Oxhmata::isOK() const
{
	return katastash;
}

int Oxhmata::isActive() const
{
	return active;
}

int Oxhmata::getX() const
{
	return x_8esh;
}

int Oxhmata::getY() const
{
	return y_8esh;
}

int Oxhmata::getFails() const
{
	return fails;
}

int Oxhmata::getTotalFails()
{
	return total_fails;
}

int Oxhmata::getMoves() const
{
	return moves;
}

int Oxhmata::getTeleport() const
{
	return teleport;
}

int Oxhmata::getDestroy() const
{
	return destroy;
}

void Oxhmata::setSpeed(int sp)
{
	taxuthta = sp;
}

void Oxhmata::setAbility(float ab)
{
	ikanothta = ab;
}

void Oxhmata::setState(bool st)
{
	katastash = st;
	if (st == false) {
		++fails;
		++total_fails;
	}
}

void Oxhmata::setActive(int ac)
{
	active = ac;
}

void Oxhmata::setTeleport(int tel)
{
	teleport = tel;
}

void Oxhmata::setDestroy(int des)
{
	destroy = des;
}
