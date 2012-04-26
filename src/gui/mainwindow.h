/**
 * @file mainwindow.h
 * @brief Main window for the QT GUI of PopGenLib (header)
 * @author Richard Neher, Boris Shraiman, Fabio Zanini
 * @version 
 * @date 2012-04-26
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define POPSIZE 1e3
#define MUTRATE 2e-5
#define OUTCROSSING_RATE 1e-2
#define CROSSOVER_RATE 1e-3

#define POPSIZE_MAX 5e5
#define MUTRATE_MAX 1
#define OUTCROSSING_RATE_MAX 1
#define CROSSOVER_RATE_MAX 1

#include <QApplication>
#include <QtGui/QMainWindow>
#include <QString>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QPushButton>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QMessageBox>
#include <QtGui/QIntValidator>
#include <QtGui/QDoubleValidator>

#include<string>
#include<sstream>

#include "popgen_highd.h"
#include "hivpopulation.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

	private:
		unsigned int numberPop;
		hivpopulation *pop;
		bool simContinue;

		void showResults();

		void createActions();
		void createMenus();
		void createFonts();

		void initializePopulationParameters(); 
		void createPopulationLayout();
		void createLandscapeLayout();
		void createButtonsLayout();
		void joinPanels();

		// Main Layout
		QVBoxLayout *layout;

		// Menus
		QMenu *fileMenu;
		QMenu *helpMenu;

		// Actions
		QAction *exitAct;
		QAction *aboutAct;
		QAction *aboutLibAct;
		QAction *aboutQtAct;

		// Population panel
		QGridLayout *populationLayout;
		QLabel *populationTitle;

		QLabel *popsize_l;
		QLineEdit *popsize_e;
		QString *popsize_s;
		QIntValidator *popsize_v;

		QLabel *mutrate_l;
		QLineEdit *mutrate_e;
		QString *mutrate_s;
		QDoubleValidator *mutrate_v;

		QLabel *outcrossing_rate_l;
		QLineEdit *outcrossing_rate_e;
		QString *outcrossing_rate_s;
		QDoubleValidator *outcrossing_rate_v;

		QLabel *crossover_rate_l;
		QLineEdit *crossover_rate_e;
		QString *crossover_rate_s;
		QDoubleValidator *crossover_rate_v;

		// Landscape panel
		QVBoxLayout *landscapeLayout;
		QLabel *landscapeTitle;
		QLabel *infoLabel3;
		QFont *panelsTitleFont;

		// Buttons panel
		QHBoxLayout *buttonsLayout;
		QPushButton *buttonRun;
		QPushButton *buttonPause;

		// Parameters
		int popsize;
		double mutrate, outcrossing_rate, crossover_rate;

	protected:
		void contextMenuEvent(QContextMenuEvent *event);

	public:
		MainWindow();
		virtual ~MainWindow();

	private slots:
		// Menu functions
		void about();
		void aboutLib();
		void aboutQt();
		void simStart();
		void simPause();
};

#endif
