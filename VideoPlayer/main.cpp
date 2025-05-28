
#include <QApplication>
#include "VideoPlayer.h"


int main(int argc, char *argv[])
{
    //create Qt Application
    QApplication a(argc, argv);
    //class VideoPlayer shows the principal windows
    VideoPlayer player;
    player.show();
    //Start the event loop from Qt, with out this the windows will open and close immediately
    return a.exec();
}
