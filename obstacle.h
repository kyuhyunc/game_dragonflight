#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QLabel>
#include "dragon.h"

/**
  This class maintains the location, size, and speed of a QGraphicsRectItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class Obstacle : public QLabel{
public:
    Obstacle(QLabel *nObstacle, double nx, double ny, double w, double h, int vx, int vy, Dragon *d);
	~Obstacle();
    void setX( int nx );
    void setY( int ny );
    void setVelocityX( int vx );
    void setVelocityY( int vy );
    int getX();
    int getY();
    int getVelocityX();
    int getVelocityY();
    int move(int windowMaxX, int windowMaxY );
	int hitCheck();

private:
    int x;
    int y;
    int width;
    int height;
    int velocityX;
    int velocityY;
	QLabel *obstacle;
	Dragon *dragon;
};

#endif // OBSTACLE_H
