#include <Magick++/Functions.h>
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include "App/ImageManip.h"

int main(int argc, char *argv[])
{
    //Image magick
    Magick::InitializeMagick(nullptr);

    //Init main app
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

	//Dark colors
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
    darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	//Setting dark color
    app.setPalette(darkPalette);

    //Widget
    ImageManip w;
    w.show();
    return app.exec();
}
