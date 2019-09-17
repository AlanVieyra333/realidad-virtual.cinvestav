#include "painter.h"

Painter::Painter( QWidget *parent )
        : QWidget( parent )
{
    setMinimumSize( 500, 355 );

    QPushButton *quit = new QPushButton( tr("Quit") );
    quit->setFont( QFont( "Times", 14, QFont::Bold ) );
    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    canvas = new Canvas( this );
	connect( canvas, SIGNAL(changePos()), SLOT(newPosition( )) );
	connect( canvas, SIGNAL(changeSize()), SLOT(newSize( )) );

    myinit = new QPushButton( tr("Init") );
    myinit->setFont( QFont( "Times", 14, QFont::Bold ) );
    connect( myinit, SIGNAL(clicked()), canvas, SLOT(initscreen()) );

    stop = new QPushButton( tr("Stop")  );
    stop->setFont( QFont( "Times", 14, QFont::Bold ) );
    connect( stop, SIGNAL(clicked()), canvas, SLOT(stop()) );

    // QGridLayout *grid = new QGridLayout( this, 1, 2, 5 ); //2x2, 5 pixel border
    QGridLayout *grid = new QGridLayout( ); //2x2, 5 pixel border
    grid->addWidget( canvas, 0, 1 );
    grid->setColumnStretch( 1, 10 );

    messpos = new QLabel(  );
    messpos->setMaximumHeight( 20 );
    messpos->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );
    // messpos->setBackgroundColor( messpos->colorGroup().base() );
    messpos->setAlignment( Qt::AlignCenter );

    messize = new QLabel(  );
    messize->setMaximumHeight( 20 );
    messize->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );
    // messize->setBackgroundColor( messpos->colorGroup().base() );
    messize->setAlignment( Qt::AlignCenter );

    // Labels for the new displays...
    visorMouse = new QLabel(this );
    visorMouse->setMaximumHeight( 20 );
    visorMouse->setText("Mouse:");
    visorMouse->setAlignment( Qt::AlignCenter );

    // Labels for the new displays...
    visorTama = new QLabel(this );
    visorTama->setMaximumHeight( 20 );
    visorTama->setText("Tamaño:");
    visorTama->setAlignment( Qt::AlignCenter );

	QVBoxLayout *leftBox = new QVBoxLayout;
	grid->addLayout( leftBox, 0, 0 );
	leftBox->addWidget( quit );
	leftBox->addWidget( myinit );
	leftBox->addWidget( stop );
	leftBox->addWidget(visorMouse);
	leftBox->addWidget( messpos );
	leftBox->addWidget(visorTama);
	leftBox->addWidget( messize );

	setLayout( grid );
}

void Painter::newPosition( )
{
	int mx, my;

	canvas->getPosition( &mx, &my );

    QString s;
	messpos->setText( s.sprintf("%d,%d", mx, my ) );
}

void Painter::newSize( )
{
	int mx, my;

	canvas->getSize( &mx, &my );

    QString s;
	messize->setText( s.sprintf("%d,%d", mx, my ) );
}

