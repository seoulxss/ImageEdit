#pragma once
#include <QFileDialog>

namespace Helper
{
	QString OpenFileDialogFolder();
	QString OpenFileDialogFile();

	QStringList ScanFolder(const QString& folderPath);
	std::string UTF16ToUTF8(const std::u16string& utf16_str);

}
