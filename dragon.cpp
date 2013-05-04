#include "dragon.h"
#include <iostream>

#define Key_Left 16777234
#define Key_Up 16777235
#define Key_Right 16777236
#define Key_Down 16777237
#define spacebar 32
#define shift 16777248

Dragon::Dragon(QLabel *nDragon, double nx, double ny, double w, double h) : QLabel(nDragon)
{
	x = nx;
	y = ny;
	width = w;
	height = h;
	dragon = nDragon;
	nDragon->setAttribute(Qt::WA_TranslucentBackground);

	up_key = false;
	down_key = false;
	left_key = false;
	right_key = false;
	
	this->setFocus();
}

Dragon::~Dragon()
{
	dragon->setPixmap(NULL);
	//delete dragon;
}

double Dragon::getSize()
{
	return width;
}

void Dragon::keyReset()
{
	up_key = false;
	down_key = false;
	left_key = false;
	right_key = false;
}

void Dragon::move( int windowMaxX, int windowMaxY) {
	int speed = 2;	

	if(up_key == true){
		if(y-speed > 0)	y-=speed; //y--; 
	}
	if(left_key == true){
		if(x-speed > 0)	x-=speed; //x--;
	}
	if(down_key == true){
		if(y+height+speed < windowMaxY*2.49) y+=speed;//y++;
	}
	if(right_key == true){
		if(x+width+speed < windowMaxX*2.49) x+=speed;//x++;
	}
	
	dragon->move(x,y);
	this->setFocus();
	//QLabel dragon ( 
}

void Dragon::magicPotion()
{
	emit myPressSignal();
}

void Dragon::pause()
{
	emit myPressSignal2();
}

int Dragon::getX() {
    return x;
}

int Dragon::getY() {
    return y;
}

void Dragon::setX(int nx) {
    x = nx;
}

void Dragon::setY(int ny) {
    y = ny;
}

void Dragon::keyPressEvent(QKeyEvent *event)
{
	//std::cout << "keyevent: ";
	//std::cout << event->key() << std::endl;

	switch(event->key()){
		case Key_Up: // 0
			up_key = true;
			break;
		case Key_Left: // 1
			left_key = true;
			break;
		case Key_Down: // 2
			down_key = true;
			break;
		case Key_Right: // 3
			right_key = true;
			break;
		case spacebar:
			magicPotion();
			break;
		case shift:
			pause();
			break;
	}
}

void Dragon::keyReleaseEvent(QKeyEvent *event)
{
	//std::cout << "keyevent: ";
	//std::cout << event->key() << std::endl;

	switch(event->key()){
		case Key_Up: // 0
			up_key = false;
			break;
		case Key_Left: // 1
			left_key = false;
			break;
		case Key_Down: // 2
			down_key = false;
			break;
		case Key_Right: // 3
			right_key = false;
			break;
	}
}