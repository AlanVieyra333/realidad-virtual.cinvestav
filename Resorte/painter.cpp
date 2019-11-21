#include "painter.h"
#include "spring.h"


Painter::Painter( QWidget *parent )
        : QWidget( parent )
{
    setMinimumSize( 500, 160 );

    quit = new QPushButton( tr("Quit") );
    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );

    spring = new Spring( this );

    reset = new QPushButton( tr("Reset") );
    connect( reset, SIGNAL(clicked()), spring, SLOT( resetea() ) );

    apply = new QPushButton( tr("Apply")  );
    connect( apply, SIGNAL(clicked()), spring, SLOT( deforma() ) );

    remove = new QPushButton( tr("Remove")  );
    connect( remove, SIGNAL(clicked()), this, SLOT( doRemove() ) );
    connect( this, SIGNAL(sendRemove()), spring, SLOT( quitaFuerza() ) );

    forceText = new QLabel(  );
    forceText->setText("Fuerza:");
    forceText->setAlignment( Qt::AlignCenter );

    forceValue = new QDoubleSpinBox( );
	forceValue->setDecimals( 2 );
	forceValue->setRange( 0.0, 0.2 );
	forceValue->setSingleStep( 0.01 );
    connect( forceValue, SIGNAL(valueChanged(double)), spring, SLOT( poneFuerza(double) ) );
	forceValue->setValue( 0.2 );
	
    textoAngulo = new QLabel(  );
    textoAngulo->setText("Ángulo a");
    textoAngulo->setAlignment( Qt::AlignCenter );

    angulo = new QDoubleSpinBox( );
	angulo->setDecimals( 1 );
	angulo->setRange( -90.0, 90.0 );
	angulo->setSingleStep( 1.0 );
    connect( angulo, SIGNAL(valueChanged(double)), spring, SLOT( poneAngulo2(double) ) );
	angulo->setValue( 0.0 );

    textoAngulo2 = new QLabel(  );
    textoAngulo2->setText("Ángulo b");
    textoAngulo2->setAlignment( Qt::AlignCenter );

    angulo2 = new QDoubleSpinBox( );
	angulo2->setDecimals( 1 );
	angulo2->setRange( -90.0, 90.0 );
	angulo2->setSingleStep( 1.0 );
    connect( angulo2, SIGNAL(valueChanged(double)), spring, SLOT( poneAngulo(double) ) );
	angulo2->setValue( 90.0 );

    textoNodo = new QLabel(  );
    textoNodo->setText("Nodo:");
    textoNodo->setAlignment( Qt::AlignCenter );

    int max_nodos = (NODOS_BASE*4) - 3;
	nodo = new QSpinBox( );
	nodo->setRange( 0, max_nodos - 1 );
	nodo->setSingleStep( 1 );
    connect( nodo, SIGNAL(valueChanged(int)), spring, SLOT( poneNodo(int) ) );
	nodo->setValue( ((spring->r.nodos - 1) / 2) );

    textoResolucion = new QLabel(  );
    textoResolucion->setText("Resolucion:");
    textoResolucion->setAlignment( Qt::AlignCenter );

	resolucion = new QSpinBox( );
	resolucion->setRange( 1, 3 );
	resolucion->setSingleStep( 1 );
    connect( resolucion, SIGNAL(valueChanged(int)), spring, SLOT( poneResolucion(int) ) );
    //resolucion->setValue( 1 );

    QGridLayout *grid = new QGridLayout( ); //2x2, 5 pixel border
    grid->addWidget( spring, 0, 1 );
    // grid->setColumnStretch( 1, 10 );

	QBoxLayout *leftBox = new QBoxLayout ( QBoxLayout::TopToBottom );
	leftBox->addWidget( quit );
	leftBox->addWidget( reset );
	leftBox->addWidget( forceText );
	leftBox->addWidget( forceValue );
	leftBox->addWidget( textoAngulo );
	leftBox->addWidget( angulo );
    leftBox->addWidget( textoAngulo2 );
	leftBox->addWidget( angulo2 );
	leftBox->addWidget( textoNodo );
	leftBox->addWidget( nodo );
    leftBox->addWidget( textoResolucion );
	leftBox->addWidget( resolucion );
	leftBox->addWidget( apply );
	leftBox->addWidget( remove );
	leftBox->addStretch( );
	grid->addLayout( leftBox, 0, 0 );

	setLayout( grid );
}

