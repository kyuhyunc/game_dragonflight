#include "obstacle.h"

Obstacle::Obstacle(QLabel *nObstacle, double nx, double ny, double w, double h, int vx, int vy, Dragon *d )
{
    x = nx;
    y = ny;
    width = w;
    height = h;
    velocityX = vx;
    velocityY = vy;
	obstacle = nObstacle;
	dragon = d;
	obstacle->setAttribute(Qt::WA_TranslucentBackground);
}

Obstacle::~Obstacle()
{
	delete obstacle;
	//obstacle->setPixmap(NULL);
}

int Obstacle::getVelocityX() {
    return velocityX;
}

int Obstacle::getVelocityY() {
    return velocityY;
}

void Obstacle::setVelocityX( int vx ) {
    velocityX = vx;
}

void Obstacle::setVelocityY( int vy ) {
    velocityY = vy;
}

int Obstacle::move( int windowMaxX, int windowMaxY ) {
	// 0: obstacle+no hit, 1: obstacle+hit, 2: red_potion, 3: magic_potion
    x += velocityX;
    y += velocityY;
	
    if ( x < 0 ) {
		//delete obstacle;
		return 0;
    }

    if ( y < 0 ) {
		//delete obstacle;
		return 0;
    }

    if ( (x+width) > windowMaxX *2.49 ) {
		//delete obstacle;
   		return 0; 
	}

    if ( (y+height) > windowMaxY *2.49 ) {
		//delete obstacle;
   		return 0;
	}

    obstacle->move(x,y);

	if(hitCheck() == 1) // Obstacle
		return 1;
	else if(hitCheck() == 2) // red_potion
		return 2;
	else if(hitCheck() == 3) // magic_potion
		return 3;

	return 4;
}

int Obstacle::hitCheck()
{
	double dx = dragon->getX();
	double dy = dragon->getY();
	int dsize = dragon->getSize();
	int buffer = 34;

	if( x + width > dx + buffer  && x + buffer < dx + dsize){
		if( y + height > dy + buffer && y + buffer < dy + dsize){
			// 77:R, 78:W
			if(width == 77)
				return 2;
			else if(width == 78)
				return 3;
			else
				return 1;
		}
	}

	return 0;
}

int Obstacle::getX() {
    return x;
}

int Obstacle::getY() {
    return y;
}

void Obstacle::setX(int nx) {
    x = nx;
}

void Obstacle::setY(int ny) {
    y = ny;
}

