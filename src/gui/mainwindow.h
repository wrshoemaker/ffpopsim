/**
 * @file mainwindow.h
 * @brief Main window for the QT GUI of PopGenLib (header)
 * @author Richard Neher, Boris Shraiman, Fabio Zanini
 * @version 
 * @date 2012-04-26
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow();
		virtual ~MainWindow();
	private:
		QLabel *hallo;
	private slots:
		void buttonClicked();
};

#endif
