#ifndef DRAGON_H
#define DRAGON_H
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

/**
  This class maintains the location, size, and speed of a QGraphicsRectItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class Dragon : public QLabel{
	Q_OBJECT
public:
    Dragon(QLabel *nDragon, double nx, double ny, double w, double h);
	~Dragon();
    void setX( int nx );
    void setY( int ny );
    int getX();
    int getY();
	double getSize();
    void move(int windowMaxX, int windowMaxY);
	void keyReset();
	void magicPotion();

protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
    int x;
    int y;
    int width;
    int height;
	QLabel *dragon;
	
	bool up_key;
	bool down_key;
	bool left_key;
	bool right_key;

signals:
	void myPressSignal();
	

};

#endif // OBSTACLE_H
