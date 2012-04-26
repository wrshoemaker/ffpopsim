/**
 * @file mainwindow.cpp
 * @brief Main window for the QT GUI of PopGenLib (implementation)
 * @author Richard Neher, Boris Shraiman, Fabio Zanini
 * @version 
 * @date 2012-04-26
 */
#include "mainwindow.h"

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QPushButton>

MainWindow::MainWindow()
{
    hallo = new QLabel( this );
    hallo->setText("hey hey cowboy");
    
    QWidget *w = new QWidget(this);
    setCentralWidget(w);

    QVBoxLayout *box = new QVBoxLayout(w);
    w->setLayout(box);
    box->addWidget(hallo);

    QPushButton *b = new QPushButton(w);
    box->addWidget(b);
    b->setText("hey hey cowboy button");

    box->addStretch();
    connect(b, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    

//    QLabel* l = new QLabel( this );
//    l->setText( "Hello World!" );
//    setCentralWidget( l );
//    QAction* a = new QAction(this);
//    a->setText( "Quit" );
//    connect(a, SIGNAL(triggered()), SLOT(close()) );
//    menuBar()->addMenu( "File" )->addAction( a );
}

MainWindow::~MainWindow()
{}

void MainWindow::buttonClicked() {
	hallo->setText("this is a BETTER message!");		
}

#include "mainwindow.moc"
