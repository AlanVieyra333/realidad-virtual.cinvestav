#include "mouse3d.h"

Mouse3d::Mouse3d(/* args */)
{
#ifdef __APPLE__
	if(SetConnexionHandlers(&MyMessageHandler, NULL, NULL, false) != 0 ) {
		fprintf(stderr, "Error al intentar leer el mouse 3D.\n");
		exit(1);
	}
	fConnexionClientID = RegisterConnexionClient(kConnexionClientWildcard, NULL, 1, kConnexionMaskAll);
#endif
}

Mouse3d::~Mouse3d()
{
}

void Mouse3d::MessageHandler(unsigned int productID, unsigned int messageType, void *messageArgument)
{
#ifdef __APPLE__
	MessageHandlerApple(productID, messageType, messageArgument);
#elif defined __linux__
	//TODO
#endif
}

void Mouse3d::MessageHandlerApple(unsigned int productID, unsigned int messageType, void *messageArgument) {
#ifdef __APPLE__
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
#endif
}