#ifndef DRAGON_H
#define DRAGON_H
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>

/**
  This class maintains the location, size, and speed of a dragon
  */
class Dragon : public QLabel{
	Q_OBJECT
public:
	/**  Default constructor		 
	 *  @param nDragon QLabel that has pixmap data of dragon
	 *  @param nx left top location of the tile(x-location)
	 *  @param ny left top location of the tile(y-location)
	 *  @param w width of the tile
	 *  @param h height of the tile
	 */
    Dragon(QLabel *nDragon, double nx, double ny, double w, double h);
	/**  Default destructor */
	~Dragon();

	/** Set x-location 
 	 *	@param nx x location of left top of the tile
	 */
    void setX( int nx );

	/** Set y-location 
	 *	@param ny y location of left top of the tile
     */
    void setY( int ny );

	/** Get x-location 
     * @return x-location 
     */
    int getX();

	/** Get y-location 
     * @return y-location
     */    
    int getY();

	/** Get size(either width or height) of a dragon
     * @return size(either width or height)
     */    
	double getSize();

	/** Move the tile in proper direction
	 *	@param windowMaxX width of window
	 *	@param windowMaxY height of window
	 */
    void move(int windowMaxX, int windowMaxY);

	/** reset the keyvalue that will make a dragon stop */
	void keyReset();

	/** function that will emit signal when space is pressed */
	void magicPotion();

	/** function that will emit signal when left shift key is pressed */
	void pause();

protected:
	/** Inherited function for key press event */
	void keyPressEvent(QKeyEvent *event);
	/** Inherited function for key release event */
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
	void myPressSignal2 ();
	

};

#endif // OBSTACLE_H
