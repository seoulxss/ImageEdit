#pragma once
#include "Src/ImageEdit/ImageManipulator.h"
#include <QListWidget>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QImageReader>
#include <QDragEnterEvent>
#include <QDropEvent>

class ImageManip;

//My converter class
class ImageConverter
{
public:
	ImageConverter();

	//Converts the images, it's a wrapper
	bool Convert(const ImageManip* const UI);

	//Gets all images from a list
	void GetAllImages(const QStringList& list);

	//Gets the image from a path
	void GetImage(const QString& file);


	//We need to access it
	QList<IMAGE_DATA> m_ImageList = { };
	QString m_OutputFolder = {};
private:
	//Logic to convert
	void ProcessImage(const QString& Type, const ImageManip* UI);

};