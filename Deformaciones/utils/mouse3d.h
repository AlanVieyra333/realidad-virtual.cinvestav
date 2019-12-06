#ifndef MOUSE3D_H
#define MOUSE3D

#ifdef __APPLE__
	#include <3DconnexionClient.framework/Headers/ConnexionClientAPI.h>
    #include <3DconnexionClient.framework/Headers/ConnexionClient.h>

    #define kConnexionClientWildcard		0x2A2A2A2A
    #define kConnexionMaskAll				0x3FFF
    #define TEST_HANDLER_DELAY_IN_MS	    0			// set to 0 to remove delay
#elif defined __linux__
    //TODO
#endif

class Mouse3d
{
private:
    short fConnexionClientID;
    double MagellanSensitivity = 1.0;

    void MessageHandlerApple(unsigned int productID, unsigned int messageType, void *messageArgument);
    void MessageHandlerLinux();
public:
    Mouse3d(/* args */);
    ~Mouse3d();

    void MessageHandler(unsigned int productID, unsigned int messageType, void *messageArgument);
};

#endif // MOUSE3D_H