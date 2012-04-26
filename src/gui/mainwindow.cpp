/**
 * @file mainwindow.cpp
 * @brief Main window for the QT GUI of PopGenLib (implementation)
 * @author Richard Neher, Boris Shraiman, Fabio Zanini
 * @version 
 * @date 2012-04-26
 */
#include "mainwindow.h"


/**
 * @brief Default constructor for the main window
 */
MainWindow::MainWindow()
{
	// Initialize number of populations
	numberPop = 0;

	// Central widget
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	// Set main layout
	layout = new QVBoxLayout;
	widget->setLayout(layout);

	// Create actions and menus
	createActions();
	createMenus();
	
	// Create fonts
	createFonts();

	// Left side vertical layout
	initializePopulationParameters();
	createPopulationLayout();

	// Right side vertical layout
	createLandscapeLayout();

	// Buttons layout
	createButtonsLayout();

	// Join panels
	joinPanels();
	
	// Show status bar
	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);
	
	// Set window title and geometry
	setWindowTitle(tr("PopGenLib GUI"));
	setMinimumSize(160, 160);
	resize(720, 320);

}

/**
 * @brief Default destructor
 */
MainWindow::~MainWindow()
{
	if(numberPop > 0)
		delete pop;
}


void MainWindow::createFonts() {
	panelsTitleFont = new QFont;
	panelsTitleFont->setPointSize(16);
	panelsTitleFont->setBold(true);
}

void MainWindow::joinPanels() {
	// Menu bar
	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Status bar
	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Central part of the window
	QHBoxLayout *centerLayout = new QHBoxLayout;
	centerLayout->setAlignment(Qt::AlignTop);
	centerLayout->addLayout(populationLayout, 1);
	centerLayout->addSpacing(15);
	centerLayout->addLayout(landscapeLayout, 1);

	// Whole window
	layout->setMargin(5);
	layout->addWidget(topFiller);
	layout->addWidget(bottomFiller);
	layout->addLayout(centerLayout, 1);
	layout->addLayout(buttonsLayout, 1);
	layout->setAlignment(Qt::AlignLeft);
}


void MainWindow::initializePopulationParameters() {
	popsize = POPSIZE;
	popsize_s = new QString;
	popsize_s->setNum(popsize);

	mutrate = MUTRATE;
	mutrate_s = new QString;
	mutrate_s->setNum(mutrate);

	outcrossing_rate = OUTCROSSING_RATE;
	outcrossing_rate_s = new QString;
	outcrossing_rate_s->setNum(outcrossing_rate);

	crossover_rate = CROSSOVER_RATE;
	crossover_rate_s = new QString;
	crossover_rate_s->setNum(crossover_rate);
}

/**
 * @brief Create the layout for the population parameters
 */
void MainWindow::createPopulationLayout() {
	populationLayout = new QGridLayout;
	populationLayout->setMargin(10);
	populationLayout->setAlignment(Qt::AlignTop);

	// Title
	populationTitle = new QLabel(tr("Population"));
	populationTitle->setFrameStyle(QFrame::Plain);
	populationTitle->setAlignment(Qt::AlignCenter);
	populationTitle->setFont(*panelsTitleFont);
	populationLayout->addWidget(populationTitle, 1, 1, 2, 2);

	// Pairs label/input form
	popsize_l = new QLabel(tr("Population Size"));
	popsize_e = new QLineEdit(*popsize_s);
	popsize_e->setAlignment(Qt::AlignRight);
	popsize_v = new QIntValidator(1, POPSIZE_MAX);
	popsize_e->setValidator(popsize_v);
	populationLayout->addWidget(popsize_l, 3, 1, 1, 1, Qt::AlignLeft);
	populationLayout->addWidget(popsize_e, 3, 2, 1, 1, Qt::AlignRight);

	mutrate_l = new QLabel(tr("Mutation Rate [1/gen/site]"));
	mutrate_e = new QLineEdit(*mutrate_s);
	mutrate_e->setAlignment(Qt::AlignRight);
	mutrate_v = new QDoubleValidator(0, MUTRATE_MAX, 6);
	mutrate_e->setValidator(mutrate_v);
	populationLayout->addWidget(mutrate_l, 4, 1, 1, 1, Qt::AlignLeft);
	populationLayout->addWidget(mutrate_e, 4, 2, 1, 1, Qt::AlignRight);

	outcrossing_rate_l = new QLabel(tr("Outcrossing rate [1/gen]"));
	outcrossing_rate_e = new QLineEdit(*outcrossing_rate_s);
	outcrossing_rate_e->setAlignment(Qt::AlignRight);
	outcrossing_rate_v = new QDoubleValidator(0, OUTCROSSING_RATE_MAX, 6);
	outcrossing_rate_e->setValidator(outcrossing_rate_v);
	populationLayout->addWidget(outcrossing_rate_l, 5, 1, 1, 1, Qt::AlignLeft);
	populationLayout->addWidget(outcrossing_rate_e, 5, 2, 1, 1, Qt::AlignRight);

	crossover_rate_l = new QLabel(tr("Crossover rate [1/sites]"));
	crossover_rate_e = new QLineEdit(*crossover_rate_s);
	crossover_rate_e->setAlignment(Qt::AlignRight);
	crossover_rate_v = new QDoubleValidator(0, CROSSOVER_RATE_MAX, 6);
	crossover_rate_e->setValidator(crossover_rate_v);
	populationLayout->addWidget(crossover_rate_l, 6, 1, 1, 1, Qt::AlignLeft);
	populationLayout->addWidget(crossover_rate_e, 6, 2, 1, 1, Qt::AlignRight);

}

/**
 * @brief Create the layout for the landscape parameters
 */
void MainWindow::createLandscapeLayout() {
	landscapeLayout = new QVBoxLayout;
	landscapeLayout->setMargin(10);
	landscapeLayout->setAlignment(Qt::AlignTop);

	// Title
	landscapeTitle = new QLabel(tr("Landscape"));
	landscapeTitle->setFrameStyle(QFrame::Plain);
	landscapeTitle->setAlignment(Qt::AlignCenter);
	landscapeTitle->setFont(*panelsTitleFont);
	landscapeLayout->addWidget(landscapeTitle);
	
	// TODO: remove this manual spacing
	landscapeLayout->addSpacing(15);

	// Pairs label/input form (TODO)
	infoLabel3 = new QLabel(tr("<i>Third label</i>"));
	infoLabel3->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	infoLabel3->setAlignment(Qt::AlignCenter);
	landscapeLayout->addWidget(infoLabel3);

}


void MainWindow::createButtonsLayout() {
	buttonsLayout = new QHBoxLayout;
	buttonsLayout->setMargin(10);
	buttonsLayout->setAlignment(Qt::AlignCenter);

	buttonRun = new QPushButton("&Run");
	buttonRun->setDefault(1);
	connect(buttonRun, SIGNAL(clicked()), this, SLOT(simStart()));

	buttonPause = new QPushButton("&Pause");
	buttonPause->setDisabled(1);
	connect(buttonPause, SIGNAL(clicked()), this, SLOT(simPause()));

	buttonsLayout->addWidget(buttonRun, 1);
	buttonsLayout->addWidget(buttonPause, 1);
}


/**
 * @brief Describe context menu
 *
 * @param event
 */
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
	QMenu menu(this);
	menu.addAction(aboutAct);
	menu.addAction(aboutLibAct);
	menu.exec(event->globalPos());
}


/**
 * @brief About box for PopGenLib GUI
 */
void MainWindow::about() {
	QMessageBox::about(this, tr("About PopGenLib GUI"),
	        tr("<b>PopGenLib GUI</b> is a graphical user interface to simulate evolution "
		   "of populations with many loci. "
		   "In the current version, an HIV-like population with 10000 sites is modeled."));
}

/**
 * @brief About box for PopGenLib
 */
void MainWindow::aboutLib() {
	QMessageBox::about(this, tr("About PopGenLib"),
	        tr("<b>PopGenLib</b> is a C/C++ library to simulate multilocus evolution "
		   "of populations. See the documentation for further information."));
}


void MainWindow::showResults() {
	
	std::stringstream ss;
	ss<<"Generation: "<<pop->get_generation()<<endl;
	ss<<"Number of clones: "<<pop->get_number_of_clones()<<".";

	QMessageBox::about(this, tr("Results of the simulation"), tr(ss.str().c_str()));
		
}

/**
 * @brief About box for QT
 */
void MainWindow::aboutQt() {
}

/**
 * @brief Create and connect (re)actions
 */
void MainWindow::createActions()
{
	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	
	aboutLibAct = new QAction(tr("&About PopGenLib"), this);
	aboutLibAct->setStatusTip(tr("Show the PopGenLib library's About box"));
	connect(aboutLibAct, SIGNAL(triggered()), this, SLOT(aboutLib()));
	
	aboutQtAct = new QAction(tr("About &Qt"), this);
	aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}

/**
 * @brief Create menus and connect them to the right actions
 */
void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAct);
		
	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutLibAct);
	helpMenu->addAction(aboutQtAct);
}

void MainWindow::simStart() {
	buttonRun->setDisabled(1);
	buttonPause->setDisabled(0);

	popsize_e->setReadOnly(1);
	mutrate_e->setReadOnly(1);
	outcrossing_rate_e->setReadOnly(1);
	crossover_rate_e->setReadOnly(1);

	popsize = (popsize_e->text()).toUInt();
	mutrate = (mutrate_e->text()).toDouble();
	outcrossing_rate = (outcrossing_rate_e->text()).toDouble();
	crossover_rate = (crossover_rate_e->text()).toDouble();

	if(numberPop == 0) {
		pop = new hivpopulation;
		numberPop += 1;
	}

	pop->set_up(popsize, 0, mutrate, outcrossing_rate, crossover_rate);
	
	simContinue = 1;
	unsigned int totalgen = 1000;
	size_t i=0;
	while(simContinue && (i < totalgen)) {
		pop->evolve(1);
		i++;
	}

	simPause();
}


void MainWindow::simPause() {
	simContinue = 0;

	buttonRun->setDisabled(0);
	buttonPause->setDisabled(1);

	popsize_e->setReadOnly(0);
	mutrate_e->setReadOnly(0);
	outcrossing_rate_e->setReadOnly(0);
	crossover_rate_e->setReadOnly(0);

	showResults();
}

// This is some QT magic
#include "mainwindow.moc"
