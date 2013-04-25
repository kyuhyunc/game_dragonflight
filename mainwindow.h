#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QApplication>
#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QLabel>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QLCDNumber>
#include <QPixmap>
#include <QTextEdit>
#include <QLineEdit>

#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <ctime>

#include "obstacle.h"
#include "dragon.h"

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
	QVBoxLayout *createRightLayout();

	void allTimerStop();
	void allTimerDelete();

	void show();

	void obs_potions(int type);
    
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
	QPixmap *backGround;

    QWidget *window;

	// layouts
	QGridLayout *layout; // main layout    
    QHBoxLayout *topLayout; // top input text board layout
    QVBoxLayout *rightLayout; // top input text board layout
    
	// buttons
	QPushButton *reStart;	
	QPushButton *pause_resumeGame;	
	QPushButton *exitGame;	
	
	// text boxes
	QLCDNumber *score;
	QLCDNumber *QgameLevel;
	int gameLevel;
	double scoreNum; // for score
	QTextEdit *errMsg; // get error message
	QLabel *instruction1;
	QLabel *instruction2;
	QLineEdit *usrName;

	// labels for layouts
	QLabel *scoreLabel;
	QLabel *usrNameLabel;
	QLabel *gameLevelLabel;
	
	// vector for saving obstacles
	QVector<Obstacle*> obstacles;
	QVector<QLabel*> Qhearts;
	int num_hearts;
	QVector<QLabel*> magic_potions;
	Dragon *dragon;

	QTimer *mainTimer; // main timer
	QTimer *timer1; // for rock
	QTimer *timer2; // for arrow
	QTimer *timer3; // for fireball
	//QTimer *timer4; // for red potion
	//QTimer *timer5; // for white potion
		 
protected:

public slots:
	void startGame();
	void PRGame();
	void cntScore();
	void obs_rock();
	void obs_arrow();
	void obs_fireball();
	void useMagic();
};

#endif // MAINWINDOW_H
