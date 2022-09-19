#include <QApplication>
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto screen = QGuiApplication::primaryScreen();
    if(screen){
        auto pixmap = screen->grabWindow();
        pixmap.save("Screenshot.bmp");
    } else {
    }
    return a.exec();
}
