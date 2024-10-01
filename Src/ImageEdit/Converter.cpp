#include "Converter.h"

#include "Src/App/ImageManip.h"


ImageConverter::ImageConverter()
{
	m_ImageList.reserve(100);
}

bool ImageConverter::Convert(const ImageManip* const UI)
{
    try
    {
        if (m_OutputFolder.isEmpty())
        {
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setText("Please set a output folder first!");
            msg.exec();
            return false;
        }

        QString selectedType = UI->GetUI()->ComboBox_ConvertToType->currentText();
        ProcessImage(selectedType, UI);
        return true;
    }

    catch (Magick::Exception& e)
    {
        QMessageBox msg;
        msg.setWindowTitle("Error Magick");
        msg.setText(e.what());
        msg.exec();
    }

    return false;
}

void ImageConverter::GetAllImages(const QStringList& list)
{
	for (const auto& entry : list)
	{
        m_ImageList.emplaceBack(entry, false);
	}
}

void ImageConverter::GetImage(const QString& file)
{
    m_ImageList.emplaceBack(file, false);
}

void ImageConverter::ProcessImage(const QString& Type, const ImageManip* const UI)
{
    QString folder = m_OutputFolder;

    //remove dot
    QString TypeNoDot = Type;
    if (TypeNoDot.startsWith('.')) {
        TypeNoDot.remove(0, 1);
    }

    for (auto& Image : m_ImageList)
    {
        Image.m_Image.magick(TypeNoDot.toStdString());
        Image.m_Image.quality(static_cast<size_t>(UI->GetUI()->Slider_ConverterQuality->value()));

        QString baseName = Image.m_ImageName + "_Converted";
        QString dst = folder + "/" + baseName + "." + TypeNoDot;

        int count = 0;
        while (QFile::exists(dst))
        {
            count++;
            dst = folder + "/" + baseName + QString::number(count) + "." + TypeNoDot;
        }

        //Metadata
        if (UI->GetUI()->CheckBox_ConverterMetadata->isChecked())
            Image.m_Image.strip();

        Image.m_Image.write(dst.toStdString());
    }

    m_OutputFolder = folder;
}
