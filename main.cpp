#include <QApplication>
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>

#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto screen = QGuiApplication::primaryScreen();

    auto pixmap = screen->grabWindow();
    pixmap.save("Screenshot.bmp");

    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;
    std::this_thread::sleep_for(10ns);
    auto pixmap2 = screen->grabWindow();

    auto img1 = pixmap.toImage();
    auto img2 = pixmap2.toImage();
    for(int x = std::min(pixmap2.width(), pixmap.width()); x--;){
        for(int y = std::min(pixmap2.height(), pixmap.height()); y--;){
            auto pixel = img1.pixel(x,y) ^ img2.pixel(x,y);
            if(pixel)
                pixel = 0xff00;
            img1.setPixel(x,y, pixel);
        }
    }
    img1.save("Diff.bmp");

    return a.exec();
}
