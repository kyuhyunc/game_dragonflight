#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include <QLabel>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QLCDNumber>
#include <QPixmap>

#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>

#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

using namespace std;

class MainWindow : public QWidget {
    Q_OBJECT
    
public:
	/**  Default constructor  \n
	 *	QWidget, window, will be the biggest screen that will save Gridlayout. \n
	 *  This Gridlayout contains all top layout, heuristic layout, solution layout, QGraphicscene etc.
	 */
	explicit MainWindow();
	/**  Default destructor */
	~MainWindow();

	/** Create the top layout that will be contained in Gridlayout 
	 * 	@return QHBoxLayout that has boxes for input
	 */
	QHBoxLayout *createTopLayout();

	void show();
    
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
	QPixmap *backGround;

    QWidget *window;

	// layouts
	QGridLayout *layout; // main layout    
    QHBoxLayout *topLayout; // top input text board layout
    
	// buttons
	QPushButton *reStart;	
	QPushButton *pause_resumeGame;	
	QPushButton *exitGame;	
	
	// text boxes
	QLCDNumber *score;
	
	// labels for topLayout 
	QLabel *scoreLabel;

	// vector for saving obstacles
	QVector<QLabel*> obstacles;

	double scoreNum; // for score
	QTimer *mainTimer; // main timer
	QTimer *timer1; // for rock
	QTimer *timer2; // for arrow
	QTimer *timer3; // for fireball
	QTimer *timer4; // for red potion
	QTimer *timer5; // for white potion

		 
public slots:
	void startGame();
	void PRGame();
	void cntScore();
	void obs_rock();
	void obs_arrow();
	void obs_fireball();
};

#endif // MAINWINDOW_H