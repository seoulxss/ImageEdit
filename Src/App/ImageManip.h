#pragma once

#include <QtWidgets/QMainWindow>
#include <QPointer>
#include <QScrollArea>
#include <QLineEdit>
#include "ui_ImageEdit.h"
#include "Ext/ConfigLib/Include/ConfigLib.h"
#include "Src/ImageEdit/ImageManipulator.h"
#include "Src/ImageEdit/Converter.h"

class ImageWindow : public QMainWindow {
public:
    ImageWindow(const QString& imagePath, QWidget* parent = nullptr) : QMainWindow(parent) {
        QLabel* label = new QLabel(this);
        QPixmap pixmap(imagePath);

        if (pixmap.isNull())
            return;


        label->setPixmap(pixmap);
        label->setScaledContents(true);


        QScrollArea* scrollArea = new QScrollArea(this);
        scrollArea->setWidget(label);
        setCentralWidget(scrollArea);

        // + 10 because it doesnt fit completely (Fix this later?)
        resize(pixmap.width() + 10, pixmap.height() + 10);
        setWindowTitle("Image-view");
    }
};

class ImageManip : public QMainWindow
{
    Q_OBJECT

public:
    ImageManip(QWidget* parent = nullptr);
    ~ImageManip() override;


    const Ui::ImageEditClass* GetUI() const;

private:
    Ui::ImageEditClass m_UI;
    std::unique_ptr<ConfigLib::ConfigManager> m_ConfigManager = nullptr;
    ImageManipulator m_Manipulator = {};
    ImageConverter m_Converter = {};

    void SetupStyle();
    void ConnectButtons();

private slots:
    void OnManip() const;
    void OnSettings() const;
    void OnConverter() const;
    void OnConfig() const;
    void OnAbout() const;


    //Manipulation
    void ManipSelectFolder();
    void ManipSelectFile();
    void ManipDeleteEntry();
    void ManipClear();
    void ManipNext();
    void ManipPrev();
    void ManipSelected();

    //Converter
    void ConSelectFolder();
    void ConSelectFile();
    void ConDeleteEntry();
    void ConUpdateSlider() const;
    void ConShowFileName();
    void ConClear();
    void ConConvert();
    void ConSelectOutputFolder();
    void ConDoubleClickList();


private:
    void SetFontToLabel(QLabel* label, float size, bool bold);

    QPointer<ImageWindow> m_pLastImage = nullptr;
};

