/**
	A example for drawing crated primitives

	Fraga 11/09/2000
**/

#include <QApplication>
#include <vector>

#include "painter.h"
#include "figuras/mesh.h"

#include <3DconnexionClient.framework/Headers/ConnexionClientAPI.h>
#include <3DconnexionClient.framework/Headers/ConnexionClient.h>

#define kConnexionClientWildcard		0x2A2A2A2A
#define kConnexionMaskAll				0x3FFF
#define TEST_HANDLER_DELAY_IN_MS	    0			// set to 0 to remove delay

Painter *w;
int16_t fConnexionClientID;

void addShapes(Painter *);
void MyMessageHandler(unsigned int productID, unsigned int messageType, void *messageArgument);

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    w = new Painter();
    w->setGeometry( 100, 100, 1000, 540 );		//355 );

    addShapes(w);
    w->setEye(2.1, 5.5, 4.0);
    w->setCenter(0.0, 0.0, 0.0);

    if(SetConnexionHandlers(&MyMessageHandler, NULL, NULL, false) != 0 ) {
		fprintf(stderr, "Error al intentar leer el mouse 3D.\n");
		exit(1);
	}
	fConnexionClientID = RegisterConnexionClient(kConnexionClientWildcard, NULL, 1, kConnexionMaskAll);

    w->show();         // Show widget
    return a.exec();  // go!
}

/*	Add shapes into canvas	*/
void addShapes(Painter *w) {
	vector<float> v1, v2;
    
    // Malla
    v1 = {-1.0, 0.0, -1.0};
    v2 = {v1[0] + 2, v1[1], v1[2] + 2};
    w->addShape(new Mesh(v1, v2));
}

void MyMessageHandler(unsigned int productID, unsigned int messageType, void *messageArgument)
{
	ConnexionDeviceState *state;
	uint16_t rx, ry;

	switch (messageType) {
		case kConnexionMsgDeviceState:
			state = (ConnexionDeviceState*)messageArgument;
			
			if (state->client == fConnexionClientID)
			{
				// decipher what command/event is being reported by the driver
				switch (state->command) {
					case kConnexionCmdHandleAxis:
						// state->axis will contain values for the 6 axis
						// printf("x: %d, y: %d, z: %d, rx: %d, ry: %d, rz: %d\n", state->axis[0], state->axis[1],
						//  	state->axis[2], state->axis[3], state->axis[4], state->axis[5]);
						rx = state->axis[3];
                        ry = state->axis[4];
                        w->set_3dMouse(rx, ry);
						break;
					case kConnexionCmdHandleButtons:
						// state->buttons reports the buttons that are pressed
						// printf("Button: %d\n", state->buttons);
						if (state->buttons == 2)
						{
							//w->applyForce();
						}
						
						break;
				}
			}
			break;
		
		default:
		// other messageTypes can happen and should be ignored
			break;
	}

#if TEST_HANDLER_DELAY_IN_MS
	usleep(TEST_HANDLER_DELAY_IN_MS * 1000);
#endif
}