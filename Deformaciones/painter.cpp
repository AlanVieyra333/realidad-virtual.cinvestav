#include "painter.h"

#define RESOLUTION_LEVEL 3

Painter::Painter( QWidget *parent )
        : QWidget( parent )
{
    setMinimumSize( 500, 355 );

    canvas = new Canvas( this );
	connect( canvas, SIGNAL(changePos()), SLOT(newPosition( )) );

    quit = new QPushButton( tr("Quit") );
    quit->setFont( QFont( "Times", 14, QFont::Bold ) );
    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    reset = new QPushButton( tr("Reset")  );
    reset->setFont( QFont( "Times", 14, QFont::Bold ) );
    connect( reset, SIGNAL(clicked()), canvas, SLOT(reset()) );

    myinit = new QPushButton( tr("Apply") );
    myinit->setFont( QFont( "Times", 14, QFont::Bold ) );
    connect( myinit, SIGNAL(clicked()), canvas, SLOT(initscreen()) );

    stop = new QPushButton( tr("Remove")  );
    stop->setFont( QFont( "Times", 14, QFont::Bold ) );
    connect( stop, SIGNAL(clicked()), canvas, SLOT(stop()) );

    forceText = new QLabel(  );
    forceText->setText("Fuerza:");
    forceText->setAlignment( Qt::AlignCenter );

    forceValue = new QDoubleSpinBox( );
	forceValue->setDecimals( 2 );
	forceValue->setRange( 0.0, 0.2 );
	forceValue->setSingleStep( 0.01 );
    forceValue->setValue( 0.2 );
    connect( forceValue, SIGNAL(valueChanged(double)), canvas, SLOT( set_force(double) ) );
	
    textoAngulo = new QLabel(  );
    textoAngulo->setText("Ángulo alpha");
    textoAngulo->setAlignment( Qt::AlignCenter );

    angulo = new QDoubleSpinBox( );
	angulo->setDecimals( 1 );
	angulo->setRange( -90.0, 90.0 );
	angulo->setSingleStep( 1.0 );
    angulo->setValue( 0.0 );
    connect( angulo, SIGNAL(valueChanged(double)), canvas, SLOT( set_angle_alpha(double) ) );

    textoAngulo2 = new QLabel(  );
    textoAngulo2->setText("Ángulo beta");
    textoAngulo2->setAlignment( Qt::AlignCenter );

    angulo2 = new QDoubleSpinBox( );
	angulo2->setDecimals( 1 );
	angulo2->setRange( -90.0, 90.0 );
	angulo2->setSingleStep( 1.0 );
    angulo2->setValue( 90.0 );
    connect( angulo2, SIGNAL(valueChanged(double)), canvas, SLOT( set_angle_beta(double) ) );

    textoResolucion = new QLabel(  );
    textoResolucion->setText("Resolucion:");
    textoResolucion->setAlignment( Qt::AlignCenter );

	resolucion = new QSpinBox( );
	resolucion->setRange( 1, RESOLUTION_LEVEL );
	resolucion->setSingleStep( 1 );
    connect( resolucion, SIGNAL(valueChanged(int)), canvas, SLOT( set_resolution(int) ) );

    // QGridLayout *grid = new QGridLayout( this, 1, 2, 5 ); //2x2, 5 pixel border
    QGridLayout *grid = new QGridLayout( ); //2x2, 5 pixel border
    grid->addWidget( canvas, 0, 1 );
    grid->setColumnStretch( 1, 10 );

    messpos = new QLabel(  );
    messpos->setMaximumHeight( 20 );
    messpos->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );
    // messpos->setBackgroundColor( messpos->colorGroup().base() );
    messpos->setAlignment( Qt::AlignCenter );

    // Labels for the new displays...
    visorMouse = new QLabel(this );
    visorMouse->setMaximumHeight( 20 );
    visorMouse->setText("Mouse:");
    visorMouse->setAlignment( Qt::AlignCenter );

	QVBoxLayout *leftBox = new QVBoxLayout;
	grid->addLayout( leftBox, 0, 0 );
	leftBox->addWidget( quit );
    leftBox->addWidget( reset );

    leftBox->addWidget( forceText );
	leftBox->addWidget( forceValue );
	leftBox->addWidget( textoAngulo );
	leftBox->addWidget( angulo );
    leftBox->addWidget( textoAngulo2 );
	leftBox->addWidget( angulo2 );
    leftBox->addWidget( textoResolucion );
	leftBox->addWidget( resolucion );

    leftBox->addWidget( myinit );
	leftBox->addWidget( stop );
	leftBox->addWidget(visorMouse);
	leftBox->addWidget( messpos );

	setLayout( grid );
}

void Painter::newPosition( )
{
	int mx, my;

	canvas->getPosition( &mx, &my );

    QString s;
	messpos->setText( s.sprintf("%d,%d", mx, my ) );
}

void Painter::addShape(Figura *figura) {
    canvas->addShape(figura);
}

void Painter::setEye(float x, float y, float z) {
    canvas->setEye(x, y, z);
}

void Painter::setCenter(float x, float y, float z) {
    canvas->setCenter(x, y, z);
}

void Painter::setCenterDegree(float degree) {
    canvas->setCenterDegree(degree);
}
