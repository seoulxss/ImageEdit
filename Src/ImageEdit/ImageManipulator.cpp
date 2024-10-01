#include "ImageManipulator.h"
#include <QtConcurrent/QtConcurrent>
#define NOMINMAX
#include <Windows.h>
#include <Psapi.h>
#include <exiv2/exiv2.hpp>
#pragma comment(lib, "psapi.lib")

void IMAGE_METADATA::ProcessMetadata(const Magick::Image& Image, std::map<std::string, std::string>& map,
                                     const std::initializer_list<std::string>& list, const IMAGE_DATA* pData)
{
    for (const auto& tag : list)
    {
        std::string value = Image.attribute(tag);

		if (!value.empty())
			map[tag] = value;

		//This one can be weird, so I do that one manually with Exiv2
		if (tag == "EXIF:UserComment")
		{
			try
			{
				Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(pData->m_Path.toStdString());
				image->readMetadata();
				Exiv2::ExifData& exifData = image->exifData();
				Exiv2::ExifKey key("Exif.Photo.UserComment");
				Exiv2::ExifData::iterator pos = exifData.findKey(key);

				if (pos != exifData.end())
				{
					std::string comment = pos->print(&exifData);
					map[tag] = comment;
				}

			}

			catch (Exiv2::Error& e)
			{
				map[tag] = "Error reading chars";
			}
			
		}
    }
}

ImageManipulator::ImageManipulator()
{
	m_Images.reserve(100);
}

void ImageManipulator::GetAllImages(const QStringList& list)
{
	for (const auto& entry : list)
	{
		m_Images.emplaceBack(entry, true);
	}
}

void ImageManipulator::GetImage(const QString& file)
{
	m_Images.emplaceBack(file, true);
}

void ImageManipulator::LoadAsync(const QStringList& List)
{
	QtConcurrent::run([this, List]() 
		{
		GetAllImages(List);
		});
}
