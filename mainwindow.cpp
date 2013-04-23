#include "mainwindow.h"

QBrush redBrush(Qt::red);
QBrush blueBrush(Qt::blue);
QBrush blkBrush(Qt::black);
QBrush greenBrush(Qt::green);
QBrush whiteBrush(Qt::white);
	
MainWindow::MainWindow()  {
	//Biggest layout that will include every other layout and widget	
	layout = new QGridLayout;
	//We need a scene and a view to do graphics in QT
	scene = new QGraphicsScene();
	view = new QGraphicsView( scene );
	scoreNum = 0;	

	//This sets the size of the window and gives it a title.
	view->setFixedSize( WINDOW_MAX_X*2.5, WINDOW_MAX_Y*2.5 );
	
	backGround = new QPixmap("./pics/back_ground.jpg");
	
	scene->addPixmap(backGround->scaled(WINDOW_MAX_X*2.49,WINDOW_MAX_Y*2.49,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

	// topLayout for text input board	
	topLayout = createTopLayout();
	
	// placing layouts and widgets in the main layout by using gridlayout
	layout->addLayout(topLayout,0,0);
	layout->addWidget(view,3,0);

	// window that will get layout that has every thing
	window = new QWidget;
	window->setWindowTitle("Dragon Flight");

	// setting layout in the main window
	// window > layout(Gridlayout) = other layouts + widgets
	window->setLayout(layout);		

	// setting a timer
	mainTimer = new QTimer(this);
	timer1 = new QTimer(this);
	timer2 = new QTimer(this);
	timer3 = new QTimer(this);
	timer4 = new QTimer(this);
	timer5 = new QTimer(this);

	mainTimer->setInterval(10);
	timer1->setInterval(100);
	timer2->setInterval(200);
	timer3->setInterval(300);
	

	// mainTimer
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(cntScore()));

	// rock
	connect(timer1, SIGNAL(timeout()), this, SLOT(obs_rock()));
	connect(timer2, SIGNAL(timeout()), this, SLOT(obs_arrow()));
	connect(timer3, SIGNAL(timeout()), this, SLOT(obs_fireball()));


	// connecting buttons
	connect(reStart, SIGNAL(clicked()), this, SLOT(startGame()));

	connect(pause_resumeGame, SIGNAL(clicked()), this, SLOT(PRGame()));
	// connecting quit button to terminate the program
	connect(exitGame, SIGNAL(clicked()), qApp, SLOT(quit()));	
}

QHBoxLayout *MainWindow::createTopLayout() 
{	
	// top layout for three inputs, size, moves and seed value.
	QHBoxLayout *topLayout = new QHBoxLayout;
	
	// score, resume and exit button
	score = new QLCDNumber(10);
	reStart = new QPushButton("Start/Restart");
	pause_resumeGame = new QPushButton("Pause/Resume");
	exitGame = new QPushButton("Quit");	

	// set the size of text boxes
	score->setMaximumWidth(250);

	// label for the box
	scoreLabel = new QLabel(tr("Score"));
	scoreLabel->setMaximumWidth(50);

	topLayout->addWidget(scoreLabel);
	topLayout->addWidget(score);
	topLayout->addWidget(reStart);
	topLayout->addWidget(pause_resumeGame);
	topLayout->addWidget(exitGame);
	
	return topLayout;
}
 
void MainWindow::startGame()
{
	std::cout << "Start Game" << std::endl;
	mainTimer->start();
}

void MainWindow::show() 
{
	window->show();
}

void MainWindow::PRGame()
{
	std::cout << "Pause or Resume Game" << std::endl;
	if (timer1->isActive() == true){
		mainTimer->stop();
		timer1->stop(); 
		timer2->stop();
		timer3->stop();
		timer4->stop();
		timer5->stop();
		// disconnect keys
	}
	else{
		mainTimer->start();
		timer1->start(); 
		timer2->start(); 
		timer3->start(); 
		timer4->start(); 
		timer5->start();
		// connect keys
	}
}
void MainWindow::cntScore()
{
	scoreNum ++;
	score->display(scoreNum);

	// as scoreNum goes higer set interval again

	// after 2sec, start rock
	if(scoreNum == 20)
		timer1->start();
	// after 15sec, start arrow
	if(scoreNum == 150)
		timer2->start();
	// after 30sec, start fireball
	if(scoreNum == 300)
		timer3->start();
	// potions
}

void MainWindow::obs_rock()
{
	std::cout << "rock" << std::endl;
}

void MainWindow::obs_arrow()
{
	
	std::cout << "obs_arrow" << std::endl;
}

void MainWindow::obs_fireball()
{
	
	std::cout << "fireball" << std::endl;
}

MainWindow::~MainWindow()
{
	if(mainTimer->isActive() == false){
		mainTimer->stop();
		timer1->stop();
		timer2->stop();
		timer3->stop();
		timer4->stop();
		timer5->stop();
	}

	// buttons
	delete pause_resumeGame;	
	delete exitGame;	

	// text boxes
	delete score;
	
	// labels for topLayout 
	delete scoreLabel;

	delete topLayout; // top input te
	delete layout; // main layout    
    delete scene;
    delete view;
    delete window;
}

