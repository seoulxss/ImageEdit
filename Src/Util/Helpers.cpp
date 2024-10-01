#include "Helpers.h"
#include <windows.h>

#include "Src/ImageEdit/ImageManipulator.h"

QString Helper::OpenFileDialogFolder()
{
	QString dir = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Select Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    return dir;
}

QString Helper::OpenFileDialogFile()
{
	QString filter = "Image Files (*.jpg *.jpeg *.png *.gif *.bmp *.tiff *.webp *.heic *.heif *.svg *.ico *.tga *.pnm *.ppm *.pbm *.xbm *.xpm);;PDF Files (*.pdf);;All Files (*)";
    QString file = QFileDialog::getOpenFileName(nullptr, QObject::tr("Select File"), "", filter, nullptr, QFileDialog::ReadOnly);
    return file;
}

QStringList Helper::ScanFolder(const QString& folderPath)
{
    QDir dir(folderPath);
    QStringList images;

    if (dir.exists())
    {
        dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        QStringList fileList = dir.entryList();

        //Loop over the files
        for (auto& file : fileList)
        {
            QString filePath = dir.absoluteFilePath(file);
            QFileInfo fileInfo(filePath);

            for (const auto& entry : g_SupportedTypes)
            {
                if (entry.contains(fileInfo.suffix().toLower()))
                {
                    images.append(filePath);
                    break;
                }
            }

        }

        return images;
    }

    return {};
}

std::string Helper::UTF16ToUTF8(const std::u16string& utf16_str)
{
    if (utf16_str.empty()) return std::string();

    int utf8_len = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(utf16_str.data()), utf16_str.length(), nullptr, 0, nullptr, nullptr);
    if (utf8_len <= 0) {
        return {};
    }

    std::string utf8_str(utf8_len, 0);
    WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<const wchar_t*>(utf16_str.data()), utf16_str.length(), &utf8_str[0], utf8_len, nullptr, nullptr);

    return utf8_str;
}
