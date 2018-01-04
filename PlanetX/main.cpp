#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>	/* Open GL Util APPLE */
#else
#include <GL/glut.h>	/* Open GL Util OpenGL*/
#endif

#include "RobotEx.h"
#include "RobotD.h"
#include "RobotAn.h"
#include "imageloader.h"
// gia to console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace std;
// Textures
GLuint Grass, Grass_p, Danger, Base, Options, Success, Fail;
GLuint Textures[18];
// gia to menu
bool pause = false;
bool info = false;
bool VehiclesInfo = false;
bool MapInfo = false;
bool editV = false;
bool editM = false;
// gia to pontiki
int press_x = -1, press_y = -1;
// eisodos xrhsth
int option = 0;
int busy = 0;
int input = 0;

Shmeia xartis[WIDTH][HEIGHT];	// dhmiourgia xarth
std::vector <Oxhmata *> Vehicles;	// dhmiourgia dianusmatos pou periexei ola ta oxhmata

int base_palladio = 0, base_iridio = 0, base_leukoxrusos = 0;
int pixels_w = 1024, pixels_h = 768;
// to menu xwrizetai se 8 string
char c1[64], c2[64], c3[64], c4[64], c5[64], c6[64];
char cmid[64], cmenu[8];
// function prototypes
void teleport1(int);
void teleport2(int);
void teleport3(int);
void destroy1(int);
void destroy2(int);
void destroy3(int);


void output(float x, float y, float z, float red, float green, float blue, void *font, char *string) // sunarthsh e3odou
{
	glColor3f(red, green, blue);
	glRasterPos3f(x, y + 1, z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

int finito() // sunarthsh termatismou tou programmatos
{
	bool ok = false;
	unsigned int i = 0;
	if (base_iridio + base_leukoxrusos + base_palladio >= 1500) {
		// an h posothta twn oruktwn pou exoun mazeutei einai toulaxiston 1500 
		// tote epistrefetai h timh 1 (pou shmainei termatismos me epituxia)
		return 1;
	}
	else {
		if (!Vehicles.empty()) { // elegxei an to dianusma einai adeio
			do {
				if (!Vehicles[i]->getType()) // elegxei an uparxei oxhma analushs
					ok = true;
			} while (++i < Vehicles.size() && !ok);
		}
		if (ok) {	
			return 0; // an uparxei tote epistrefei 0
		}
		else return 2; // an den uparxei epistrefei 2 (kai to programma termatizei)
	}
}

void handleKeypress(unsigned char key, int x, int y) // sunarthsh pou elegxei an path8hke kati sto plhktrologio
{
	switch (key) {
	case 'p': //an path8hke to p tote to programma kanei paush/ stamata tin paush
		if (pause) {
			info = false;
			VehiclesInfo = false;
			MapInfo = false;
			editV = false;
			editM = false;
			busy = 0;
			input = 0;
			option = 0;
		}
		pause = !pause;
		break;
	case 27: // an path8ei to escape tote kleinei to para8uro
		glutDestroyWindow(glutGetWindow());
		exit(0);
		break;
	}
	if (!finito() && !busy) { // an to programma den exei termatisei kai den einai apasxolhmeno
		switch (key) { // mia terastia switch
		case 'i':	
			if (pause && !VehiclesInfo && !MapInfo && !editV && !editM) {
				info = !info; // toggle general info
			}
			break;
		case 'v':
			if (pause && !info && !MapInfo && !editV && !editM) {
				VehiclesInfo = !VehiclesInfo; // toggle vehicles info
			}
			break;
		case 'm':
			if (pause && !info && !VehiclesInfo && !editV && !editM) {
				MapInfo = !MapInfo;	// toggle map info
			}
			break;
		case 'e':
			if (pause && !info && !VehiclesInfo && !MapInfo && !editM) {
				editV = !editV; // toggle edit vehicles
			}
			break;
		case 'z':
			if (editV) {
				// H metavlhth busy pairnei diafores times analoga me thn leitourgia pou kanei o xrhsths
				busy = 2;
			}
			break;
		case 'x':
			if (editV) {
				busy = 3;
			}
			break;
		case 'c':
			if (editV) {
				busy = 4;
			}
			break;
		case 'r':
			if (pause && !info && !VehiclesInfo && !MapInfo && !editV) {
				editM = !editM; // toggle edit map
			}
			break;
		case 'd':
			if (editM) {
				busy = 8;
			}
			break;
		case 'f':
			if (editM) {
				busy = 10;
			}
			break;
		case 'g':
			if (editM) {
				busy = 11;
			}
			break;
		case '1':
		case '2':
		case '3':
			if (editV) {
				option = key - 48; // metatrepei ton xarakthra se ari8mo 
				busy = 1;
			}
			break;
		case '4':
		case '5':
		case '6':
			if (editM) {
				option = key - 48;
				busy = 6;
			}
			break;
		}
	}
	else if (busy == 4 || busy == 6 || busy == 8) {
		if (key >= '0' && key <= '9') {
			++busy;
			input = key - 48; // eisodos xrhsth
		}
	}
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) // sunarthsh pou elegxei an path8hke kati sto pontiki
{
	unsigned int i = 0;
	bool done = false;
	// briskei tis suntetagmenes x,y opou path8hke to pontiki
	int _x = WIDTH * x / pixels_w;
	int _y = (HEIGHT + 2)* y / pixels_h;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
		if (pause) {
			press_x = _x; // to shmeio pou pataei to pontiki einai pio fwteino
			press_y = _y;
		}
		if (_y < HEIGHT) { // elegxei an to y einai ston xarth h sto menu
			if (VehiclesInfo) {	// an exoun energopoih8ei oi plhrofories gia ta oxhmata
				do {
					// h epanalhpsh elegxei an kapoio robot vrisketai stis suntetagmenes pou dw8hkan apo to pontiki
					if (Vehicles[i]->getX() == _x && Vehicles[i]->getY() == _y) { 
						done = true;
					}
				} while (++i < Vehicles.size() && !done);
				if (done) {	// an kapoio robot vre8hke emfanizei stoixeia gia to sugkekrimeno robot
					--i;
					Vehicles[i]->getInfo(c2);
					sprintf(c3, "Vehicle %d, Type: %s", i, !Vehicles[i]->getType() ? "Miner"
						: Vehicles[i]->getType() == 1 ? "Rescue" : "Exploration");
					sprintf(c4, "Moves: %d", Vehicles[i]->getMoves());
					sprintf(c5, "Mulfunctions: %d", Vehicles[i]->getFails());
					sprintf(c6, "Ability (0.1 - 1.0): %.1f", Vehicles[i]->getAbility());
				}
			}
			else if (MapInfo) { // emfanizontai plhrofories gia kapoio shmeio tou xarth
				sprintf(c2, "Palladium: %d", xartis[_x][_y].getPalladio());
				sprintf(c4, "Iridium: %d", xartis[_x][_y].getIridio());
				sprintf(c6, "Platinum: %d", xartis[_x][_y].getLeukoxriso());
				sprintf(c3, "Tile [%d] [%d]", _x, _y);
				sprintf(c5, "Danger (0.0 - 0.9): %.1f", xartis[_x][_y].getEpikind());
			}
			else if (busy == 1 && !xartis[_x][_y].isOccupied() && !xartis[_x][_y].isFlagged()) {
				if (option == 1) { // pros8etei kainourio oxhma e3ereunhshs
					RobotEx *Veh1 = new RobotEx();
					xartis[_x][_y].setOccupied(true);
					Veh1->setX(_x);
					Veh1->setY(_y);
					Vehicles.push_back(Veh1);
				}
				else if (option == 2) {
					RobotD *Veh2 = new RobotD(); // pros8etei kainourio oxhma diaswshs
					xartis[_x][_y].setOccupied(true);
					Veh2->setX(_x);
					Veh2->setY(_y);
					Vehicles.push_back(Veh2);
				}
				else if (option == 3) {	// pros8etei kainourio oxhma analushs
					RobotAn *Veh3 = new RobotAn();
					xartis[_x][_y].setOccupied(true);
					Veh3->setX(_x);
					Veh3->setY(_y);
					Vehicles.push_back(Veh3);
				}
				busy = 0;
				option = 0;
			}
			// psaxnei an uparxei kapoio robot sthn sugkekrimenh 8esh kai sthn sunexeia to diagrafei
			else if (busy == 2 && xartis[_x][_y].isOccupied()) {
				do {
					if (Vehicles[i]->getX() == _x && Vehicles[i]->getY() == _y) {
						done = true;
					}
				} while (++i < Vehicles.size() && !done);
				if (done) {
					busy = 0;
					destroy1(--i);
				}
			}
			// psaxnei an uparxei kapoio robot sthn sugkekrimenh 8esh kai antistrefei thn katastash tou
			else if (busy == 3 && xartis[_x][_y].isOccupied()) {
				do {
					if (Vehicles[i]->getX() == _x && Vehicles[i]->getY() == _y) {
						done = true;
					}
				} while (++i < Vehicles.size() && !done);
				if (done) {
					--i;
					busy = 0;
					RobotD::addSunolEpiskeues(!Vehicles[i]->isOK());
					Vehicles[i]->setState(!Vehicles[i]->isOK());
					Vehicles[i]->setDestroy(0);
				}
			}
			else if (busy == 5) { // allazei tin ikanothta tou robot sthn sugkekrimenh 8esh 
				do {
					if (Vehicles[i]->getX() == _x && Vehicles[i]->getY() == _y) {
						done = true;
					}
				} while (++i < Vehicles.size() && !done);
				if (done) {
					Vehicles[--i]->setAbility((input + 1) / 10.0f);
					input = 0;
					busy = 0;
				}
			}
			else if (busy == 7) {
				if (option == 4) { // allazei thn periekthkothta palladiou sthn sugkekrimenh 8esh
					xartis[_x][_y].setPalladio(input);
				}
				else if (option == 5) {	// allazei thn periekthkothta iridiou sthn sugkekrimenh 8esh
					xartis[_x][_y].setIridio(input);
				}
				else if (option == 6) {	// allazei thn periekthkothta leukoxrusou sthn sugkekrimenh 8esh
					xartis[_x][_y].setLeukoxriso(input);
				}
				busy = 0;
				input = 0;
			}
			else if (busy == 9) { // allazei thn epikindunothta tou shmeiou
				xartis[_x][_y].setEpikind(input / 10.0f);
				input = 0;
				busy = 0;
			}
			else if (busy == 10) { // vazei tuxaies times periekthkothtas kai epikindunothtas
				Shmeia *s = new Shmeia();
				s->setFlagged(xartis[_x][_y].isFlagged());
				xartis[_x][_y] = *s;
				busy = 0;
			}
			else if (busy == 11) { // pros8etei / afairei shmaia
				xartis[_x][_y].setFlagged(!xartis[_x][_y].isFlagged());
				RobotEx::addSunolShmaies(xartis[_x][_y].isFlagged() ? +1 : -1);
				busy = 0;
			}
		}
	}
	else if (state == GLUT_UP) {
		press_x = -1; // efe gia to pontiki
		press_y = -1;
	}
	glutPostRedisplay();
}

int getRemainingLeuk() // epistrefei thn enapomeinonta posothta leukoxrusou
{
	int leuk = 0;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			leuk += xartis[i][j].getLeukoxriso();
		}
	}
	return leuk;
}

int getRemainingIr() // epistrefei thn enapomeinonta posothta irdiou
{
	int ir = 0;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			ir += xartis[i][j].getIridio();
		}
	}
	return ir;
}

int getRemainingPal() // epistrefei thn enapomeinonta posothta palladiou
{
	int pal = 0;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			pal += xartis[i][j].getPalladio();
		}
	}
	return pal;
}

float getDanger() // epistrefei ton meso oro kindunou ana shmeio
{
	float danger = 0;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			danger += xartis[i][j].getEpikind();
		}
	}
	return danger / (WIDTH*HEIGHT);
}

bool canMove(int i)	// elegxei an to oxhma mporei na kinh8ei se kapoio geitoniko tou tetragwno
{
	int dx = -1, dy = -1, X = Vehicles[i]->getX(), Y = Vehicles[i]->getY();
	bool ok = false;
	do {
		do {
			if (X + dx >= 0 && X + dx < WIDTH && Y + dy >= 0 && Y + dy < HEIGHT &&
				!xartis[X + dx][Y + dy].isOccupied() && !xartis[X + dx][Y + dy].isFlagged()) {
				ok = true;
			}
		} while (!ok && ++dy < 2);
		dy = -1;
	} while (!ok && ++dx < 2);
	return ok;
}

void clearVehicles(int value) // diagrafei ena oxhma apo to dianusma
{
	// 3ekinaw apo to telos tou vector gia na mhn upar3oun 8emata kata thn diagrafh
	for (int i = Vehicles.size() - 1; i >= 0; i--) {
		if (Vehicles[i]->getDestroy() < -3) {
			Vehicles.erase(Vehicles.begin() + i);
		}
	}
}

void draw(GLuint texture, float x, float y, float z) { // zwgrafizei ta panta
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// to fonto ginetai pio skoteino an pathseis to p(pause) kai akoma pio skoteino an pathseis to i(info)
	glColor3f(1.0f - (pause + info) * 0.25f + (press_x == x && press_y == y) *0.25,
		1.0f - (pause + info) * 0.25f + (press_x == x && press_y == y) *0.25,
		1.0f - (pause + info) * 0.25f + (press_x == x && press_y == y) *0.25);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y + 1, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + 1, y + 1, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + 1, y, z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y, z);

	glEnd();
}

void goToBase(int i) // 3ekina tin diadikasia thlemetaforas enos robot sthn bash
{
	// to animation gia to teleport einai: teleport1 -> teleport2 -> teleport3 -> teleport2 -> teleport1
	glutTimerFunc(70, teleport1, i);
}

void teleport1(int i)
{
	if (((RobotAn*)Vehicles[i])->isFull()) {	// an to robot einai full tote 
		Vehicles[i]->setTeleport(1);			// 8etei thn timh 1 sto teleport 
		glutTimerFunc(70, teleport2, i);		// kai meta apo 70 ms kalei tin sunartish teleport 2
	}
	else {
		Vehicles[i]->setTeleport(0);			// teleiwnei to animation
	}
	glutPostRedisplay();
}

void teleport2(int i)
{
	Vehicles[i]->setTeleport(2);
	if (((RobotAn*)Vehicles[i])->isFull()) {
		glutTimerFunc(70, teleport3, i);	// an einai full meta apo 70ms kalei tin sunarthsh teleport3
	}
	else {
		glutTimerFunc(70, teleport1, i);	// alliws kalei thn sunarthsh teleport1
	}
	glutPostRedisplay();
}

void teleport3(int i)
{
	RobotAn* r = (RobotAn*)Vehicles[i];
	int _ir, _leuk, _pal;
	Vehicles[i]->setTeleport(3);
	// dinei tis posothtes pou exei e3oru3ei sthn vash
	_ir = r->getIr() + base_iridio > 500 ? 500 - base_iridio : r->getIr();
	_leuk = r->getLeuk() + base_leukoxrusos > 500 ? 500 - base_leukoxrusos : r->getLeuk();
	_pal = r->getPal() + base_palladio > 500 ? 500 - base_palladio : r->getPal();

	base_iridio += _ir;
	base_leukoxrusos += _leuk;
	base_palladio += _pal;
	// adeiazei
	r->setIr(0);
	r->setLeuk(0);
	r->setPal(0);
	// antistrofo animation
	glutTimerFunc(70, teleport2, i);
	glutPostRedisplay();
}

void destroy(int i) // 8etei to oxhma se katastash katastrofhs (destroy = -4)
{
	xartis[Vehicles[i]->getX()][Vehicles[i]->getY()].setOccupied(false);
	Vehicles[i]->setDestroy(-4);
	glutPostRedisplay();
}

void destroy1(int i)
{
	// to animation einai: destroy1 -> destroy2 -> destroy3
	Vehicles[i]->setDestroy(-1);
	glutTimerFunc(70, destroy2, i);
	glutPostRedisplay();
}

void destroy2(int i)
{
	Vehicles[i]->setDestroy(-2);
	glutTimerFunc(70, destroy3, i);
	glutPostRedisplay();
}

void destroy3(int i)
{
	// teleiwnei to animation
	Vehicles[i]->setDestroy(-3);
	glutTimerFunc(70, destroy, i);
	glutPostRedisplay();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,			//Always GL_TEXTURE_2D
		0,								//0 for now
		GL_RGB,							//Format OpenGL uses for image
		image->width, image->height,	//Width and height
		0,								//The border of the image
		GL_RGB,							//GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,				//GL_UNSIGNED_BYTE, because pixels are stored
										//as unsigned numbers
		image->pixels);					//The actual pixel data
	return textureId; //Returns the id of the texture
}

void drawMap() // emfanizei ton xarth
{
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (xartis[i][j].getPeriek() > 3) {
				draw(Grass_p, i, j, 0.0f); // texture me upsulh periekthkothta
			}
			else {
				draw(Grass, i, j, 0.0f); // texture me xamhlh periekthkothta
			}
		}
	}

}

void drawVehicles() // emfanizei ta robot
{
	for (unsigned int i = 0; i < Vehicles.size(); i++) {
		if (Vehicles[i]->getDestroy() < -3) {} // etoimo gia katastrofh
		else if (Vehicles[i]->getTeleport()) { // animation gia teleport
			draw(Textures[5 + (Vehicles[i]->getTeleport())],
				Vehicles[i]->getX(), Vehicles[i]->getY(), 0.5f);
		}
		else if (Vehicles[i]->getDestroy() < 0) { // animation gia katastrofh
			draw(Textures[12 + 3 * Vehicles[i]->getType() + Vehicles[i]->getDestroy()],
				Vehicles[i]->getX(), Vehicles[i]->getY(), 0.5f);
		}
		else { // texture gia oxhma me/xwris vlavh
			draw(Textures[Vehicles[i]->getType() + 3 * (!Vehicles[i]->isOK())],
				Vehicles[i]->getX(), Vehicles[i]->getY(), 0.5f);
		}
	}
};

void drawFlags() { // emfanizei tis shmaies
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (xartis[i][j].isFlagged()) {
				draw(Danger, i, j, 0.5f); // texture gia shmaia kindunou
			}
		}
	}
}

void drawInfo() // emfanizei genikes plhrofories kai thn vash
{
	char ch[256];
	// emfanizei th vash
	glBindTexture(GL_TEXTURE_2D, Base);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, HEIGHT - 1.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(WIDTH - 2.5f, HEIGHT - 1.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(WIDTH - 2.5f, 1.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5f, 1.5f, 0.5f);

	glEnd();

	glPushMatrix();
	glLoadIdentity();
	// emfanizw tis posothtes pou exoun sullex8ei sth vash
	sprintf(ch, "Iridium [%d / 500]", base_iridio);
	output(3.5f, HEIGHT / 2.0f + 2.4f, 1.0f, 0.5f, 0.3f, 0.2f, GLUT_BITMAP_HELVETICA_18, ch);

	sprintf(ch, "Platinum [%d / 500]", base_leukoxrusos);
	output(3.5f, HEIGHT / 2.0f + 3.4f, 1.0f, 0.2f, 0.5f, 0.3f, GLUT_BITMAP_HELVETICA_18, ch);

	sprintf(ch, "Palladium [%d / 500]", base_palladio);
	output(3.5f, HEIGHT / 2.0f + 4.4f, 1.0f, 0.3f, 0.2f, 0.5f, GLUT_BITMAP_HELVETICA_18, ch);

	glPopMatrix();
	// emfanizw mpares gia ta orukta
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex3f(7.5f, HEIGHT / 2.0f + 3.0f, 1.0f);
	glVertex3f(7.5f, HEIGHT / 2.0f + 3.6f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(7.6 + 8.5*base_iridio / 500.0f, HEIGHT / 2.0f + 3.6f, 1.0);
	glVertex3f(7.6 + 8.5*base_iridio / 500.0f, HEIGHT / 2.0f + 3.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);

	glVertex3f(7.5f, HEIGHT / 2.0f + 4.0f, 1.0f);
	glVertex3f(7.5f, HEIGHT / 2.0f + 4.6f, 1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(7.6 + 8.5*base_leukoxrusos / 500.0f, HEIGHT / 2.0f + 4.6f, 1.0);
	glVertex3f(7.6 + 8.5*base_leukoxrusos / 500.0f, HEIGHT / 2.0f + 4.0f, 1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);

	glVertex3f(7.5f, HEIGHT / 2.0f + 5.0f, 1.0f);
	glVertex3f(7.5f, HEIGHT / 2.0f + 5.6f, 1.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(7.6 + 8.5*base_palladio / 500.0f, HEIGHT / 2.0f + 5.6f, 1.0);
	glVertex3f(7.6 + 8.5*base_palladio / 500.0f, HEIGHT / 2.0f + 5.0f, 1.0f);

	glEnd();
}

void drawOptions() // menu
{
	glBindTexture(GL_TEXTURE_2D, Options);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	// emfanizei to menu
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, HEIGHT + 2, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(WIDTH, HEIGHT + 2, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(WIDTH, HEIGHT, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, HEIGHT, 0.0f);

	glEnd();
	// emfanizw ola ta string sto menu
	output(8.0f, HEIGHT + 0.1f, 0.5f, 0, 1, 1, GLUT_BITMAP_9_BY_15, cmid);
	output(0.2f, HEIGHT - 0.4f, 0.5f, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, c1);
	output(0.2f, HEIGHT + 0.6f, 0.5f, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, c2);
	output(WIDTH / 2.5f, HEIGHT - 0.4f, 0.5f, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, c3);
	output(WIDTH / 2.5f, HEIGHT + 0.6f, 0.5f, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, c4);
	output(2.1 * WIDTH / 3.0f, HEIGHT - 0.4f, 0.5f, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, c5);
	output(2.1 * WIDTH / 3.0f, HEIGHT + 0.6f, 0.5f, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, c6);
	output(WIDTH - 1, HEIGHT + 0.6f, 0.5f, 0, 1, 1, GLUT_BITMAP_9_BY_15, cmenu);
}

void drawSuccess() // emfanizei mhnuma epituxias!
{
	pause = true;

	glBindTexture(GL_TEXTURE_2D, Success);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, HEIGHT - 1.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(WIDTH - 2.5f, HEIGHT - 1.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(WIDTH - 2.5f, 1.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5f, 1.5f, 0.5f);

	glEnd();
}

void drawFail() // emfanizei mhnuma apotuxias..
{
	pause = true;

	glBindTexture(GL_TEXTURE_2D, Fail);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, HEIGHT - 1.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(WIDTH - 2.5f, HEIGHT - 1.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(WIDTH - 2.5f, 1.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2.5f, 1.5f, 0.5f);

	glEnd();
}

void drawScene() // display function
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// xwrizw to para8uro se WIDTH * HEIGHT merh (+2 gia to menu)
	glOrtho(0, WIDTH, HEIGHT + 2, 0, -1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);

	if (info) {
		drawInfo();
	}
	else if (finito() == 1) {
		drawSuccess();
	}
	else if (finito() == 2) {
		drawFail();
	}
	// dinw times sta string tou menu
	if (finito() || busy) { // adeio menu
		fill(c1, c1 + 64, 0); fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0); fill(c4, c4 + 64, 0);
		fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmid, cmid + 64, 0); fill(cmenu, cmenu + 8, 0);
	}
	else if (!pause) { // default
		sprintf(cmid, "Press 'p' to pause");
		fill(c1, c1 + 64, 0); fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0);
		fill(c4, c4 + 64, 0); fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmenu, cmenu + 8, 0);
	}
	else if (!VehiclesInfo && !info && !MapInfo && !editV && !editM) { // pause menu
		sprintf(c1, "Press 'i' to view general info");
		sprintf(c2, "Press 'v' to view vehicles info");
		sprintf(c3, "Press 'm' to view map info");
		sprintf(c4, "Press 'e' to edit the vehicles");
		sprintf(c5, "Press 'r' to edit the map");
		sprintf(c6, "Press 'p' to resume");
		sprintf(cmenu, "\'p\'");
		fill(cmid, cmid + 64, 0);
	}
	else if (VehiclesInfo) { // Vehicles info
		if (strcmp(c1, "Click a vehicle to view info!")) {
			fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0); fill(c4, c4 + 64, 0);
			fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmid, cmid + 64, 0); fill(cmenu, cmenu + 8, 0);
		}
		sprintf(c1, "Click a vehicle to view info!");
		sprintf(cmenu, "\'v\'");
	}
	else if (MapInfo) { // Map info
		if (strcmp(c1, "Click somewhere to view info!")) {
			fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0); fill(c4, c4 + 64, 0);
			fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmid, cmid + 64, 0); fill(cmenu, cmenu + 8, 0);
		}
		sprintf(c1, "Click somewhere to view info!");
		sprintf(cmenu, "\'m\'");
	}
	else if (info) { // General info
		sprintf(c1, "Plat / Irid / Pallad mined: %d / %d / %d",
			RobotAn::getSunolLeuk(), RobotAn::getSunolIr(), RobotAn::getSunolPal());
		sprintf(c2, "Plat / Irid / Pallad remaining: %d / %d / %d",
			getRemainingLeuk(), getRemainingIr(), getRemainingPal());
		sprintf(c3, "Total Mulfunctions: %d", Oxhmata::getTotalFails());
		sprintf(c4, "Total Rescues: %d", RobotD::getSunolEpiskeues());
		sprintf(c5, "Average Danger (0.0-0.9): %.1f", getDanger());
		sprintf(c6, "Total Flags: %d", RobotEx::getSunolShmaies());
		sprintf(cmenu, "\'i\'");
	}
	else if (editV) { // Edit vehicles
		fill(cmid, cmid + 64, 0);
		sprintf(c1, "Press '1' to insert Exploration unit");
		sprintf(c3, "Press '2' to insert Rescue unit");
		sprintf(c5, "Press '3' to insert Miner unit");
		sprintf(c2, "Press 'z' to remove a vehicle");
		sprintf(c4, "Press 'x' to repair/break");
		sprintf(c6, "Press 'c' to edit ability");
		sprintf(cmenu, "\'e\'");
	}
	else if (editM) { // Edit Map
		fill(cmid, cmid + 64, 0);
		sprintf(c1, "Press '4' to change Palladium levels");
		sprintf(c3, "Press '5' to change Iridium levels");
		sprintf(c5, "Press '6' to change Platinum levels");
		sprintf(c2, "Press 'd' to change danger levels");
		sprintf(c4, "Press 'f' to randomize!");
		sprintf(c6, "Press 'g' to put/remove flag");
		sprintf(cmenu, "\'r\'");
	}
	// H metavlhth busy pairnei diafores times analoga me thn leitourgia pou kanei o xrhsths
	if (busy == 1) {
		sprintf(cmid, "Click on an empty tile");
		fill(c1, c1 + 64, 0); fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0);
		fill(c4, c4 + 64, 0); fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmenu, cmenu + 8, 0);
	}
	else if (busy == 2 || busy == 3 || busy == 5) {
		sprintf(cmid, "Click on a vehicle");
		fill(c1, c1 + 64, 0); fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0);
		fill(c4, c4 + 64, 0); fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmenu, cmenu + 8, 0);
	}
	else if (busy == 4 || busy == 6 || busy == 8) {
		sprintf(cmid, "Enter a number (0-9)");
		fill(c1, c1 + 64, 0); fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0);
		fill(c4, c4 + 64, 0); fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmenu, cmenu + 8, 0);
	}
	else if (busy == 7 || busy >= 9) {
		sprintf(cmid, "Click on a tile");
		fill(c1, c1 + 64, 0); fill(c2, c2 + 64, 0); fill(c3, c3 + 64, 0);
		fill(c4, c4 + 64, 0); fill(c5, c5 + 64, 0); fill(c6, c6 + 64, 0); fill(cmenu, cmenu + 8, 0);
	}

	// zwgrafizei to para8uro
	drawOptions();
	drawMap();
	drawVehicles();
	drawFlags();



	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

void changeSize(int w, int h) // sunarthsh gia resize tou para8urou
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	pixels_h = h;
	pixels_w = w;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	gluPerspective(45, ratio, 0.1f, 1000);
	glLoadIdentity();

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void theGame(int value) // sunarthsh pou kanei ta panta
{
	if (finito() == 1) {
		drawSuccess(); // mhnuma epituxias
	}
	else if (finito() == 2) {
		drawFail(); // mhnuma apotuxias
	}
	else if (!pause) {
		for (unsigned int i = 0; i < Vehicles.size(); i++) {
			if (Vehicles[i]->getDestroy() < -3) {} // etoimo gia katastrofh
			else if (!Vehicles[i]->getType() && ((RobotAn*)Vehicles[i])->isFull()) {
				goToBase(i); // teleport sthn vash
			}
			else if (!Vehicles[i]->isOK()) {
				Vehicles[i]->setDestroy(Vehicles[i]->getDestroy() + 1); // timer gia katastrofh
			}
			else if (!(Vehicles[i]->isActive() - Vehicles[i]->getSpeed()) && canMove(i)) {
				Vehicles[i]->move(xartis); // metakinhsh
				Vehicles[i]->failure(xartis); // pi8anothta vlavhs kata th metakinhsh
			}
			if (Vehicles[i]->getDestroy() == 25) {
				destroy1(i); // katastrofh meta apo 25 gurous vlavhs
			}
			else if (!Vehicles[i]->getDestroy()) {
				Vehicles[i]->action(xartis, Vehicles); // leitourgia
			}
		}
		glutTimerFunc(420, clearVehicles, 0); // diagrafh twn robot pou exoun destroy = -4
	}
	glutTimerFunc(500, theGame, 0); // ektelesh ths sunarthshs se 0.5 deuterolepta
	glutPostRedisplay(); // display
}

void init() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
	int i, X, Y;
	// fortwsh textures
	Image* image = loadBMP("Grass.bmp");
	Grass = loadTexture(image);
	image = loadBMP("Grass_p.bmp");
	Grass_p = loadTexture(image);
	image = loadBMP("Danger.bmp");
	Danger = loadTexture(image);
	image = loadBMP("Base.bmp");
	Base = loadTexture(image);
	image = loadBMP("Options.bmp");
	Options = loadTexture(image);
	image = loadBMP("Success.bmp");
	Success = loadTexture(image);
	image = loadBMP("Fail.bmp");
	Fail = loadTexture(image);
	image = loadBMP("V1.bmp");
	Textures[0] = loadTexture(image);
	image = loadBMP("V2.bmp");
	Textures[1] = loadTexture(image);
	image = loadBMP("V3.bmp");
	Textures[2] = loadTexture(image);
	image = loadBMP("V1_c.bmp");
	Textures[3] = loadTexture(image);
	image = loadBMP("V2_c.bmp");
	Textures[4] = loadTexture(image);
	image = loadBMP("V3_c.bmp");
	Textures[5] = loadTexture(image);
	image = loadBMP("V1_t1.bmp");
	Textures[6] = loadTexture(image);
	image = loadBMP("V1_t2.bmp");
	Textures[7] = loadTexture(image);
	image = loadBMP("V1_t3.bmp");
	Textures[8] = loadTexture(image);
	image = loadBMP("V1_d3.bmp");
	Textures[9] = loadTexture(image);
	image = loadBMP("V1_d2.bmp");
	Textures[10] = loadTexture(image);
	image = loadBMP("V1_d1.bmp");
	Textures[11] = loadTexture(image);
	image = loadBMP("V2_d3.bmp");
	Textures[12] = loadTexture(image);
	image = loadBMP("V2_d2.bmp");
	Textures[13] = loadTexture(image);
	image = loadBMP("V2_d1.bmp");
	Textures[14] = loadTexture(image);
	image = loadBMP("V3_d3.bmp");
	Textures[15] = loadTexture(image);
	image = loadBMP("V3_d2.bmp");
	Textures[16] = loadTexture(image);
	image = loadBMP("V3_d1.bmp");
	Textures[17] = loadTexture(image);
	delete image;
	// tuxaies suntetagmenes gia ola ta oxhmata
	for (i = 0; i < 10; i++) {
		do {
			X = rand() % WIDTH;
			Y = rand() % HEIGHT;
		} while (xartis[X][Y].isOccupied());

		RobotAn *Veh1 = new RobotAn();
		xartis[X][Y].setOccupied(true);
		Veh1->setX(X);
		Veh1->setY(Y);
		Vehicles.push_back(Veh1);
	}
	for (int i = 0; i < 10; i++) {
		do {
			X = rand() % WIDTH;
			Y = rand() % HEIGHT;
		} while (xartis[X][Y].isOccupied());

		RobotEx *Veh2 = new RobotEx();
		xartis[X][Y].setOccupied(true);
		Veh2->setX(X);
		Veh2->setY(Y);
		Vehicles.push_back(Veh2);
	}
	for (int i = 0; i < 15; i++) {
		do {
			X = rand() % WIDTH;
			Y = rand() % HEIGHT;
		} while (xartis[X][Y].isOccupied());

		RobotD *Veh3 = new RobotD();
		xartis[X][Y].setOccupied(true);
		Veh3->setX(X);
		Veh3->setY(Y);
		Vehicles.push_back(Veh3);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(500, 100);
	srand(time(NULL)); // arxikopoihsh seed gia tuxaious ari8mous

	glutCreateWindow("PlanetX"); // onoma!
	init(); // arxikopoihsh textures kai oxhmatwn


	// Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutIgnoreKeyRepeat(1); // agnoei to sunexomeno pathma enos plhktrou
	glutMouseFunc(mouseClick);
	glutReshapeFunc(changeSize);
	glutTimerFunc(500, theGame, 0);


	glutMainLoop();
	return 0;
}