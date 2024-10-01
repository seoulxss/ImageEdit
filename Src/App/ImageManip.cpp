#include "ImageManip.h"

#include "Src/Util/Helpers.h"

ImageManip::ImageManip(QWidget *parent)
	: QMainWindow(parent)
{
	m_UI.setupUi(this);

	//Creating the config folder
	std::wstring path = QDir::currentPath().append("/Config/").toStdWString();
	m_ConfigManager = std::make_unique<ConfigLib::ConfigManager>(path.c_str());

	//Some windows stuff
	m_UI.centralWidget->setFixedSize({1200, 650});
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);

	//Setup style & connect buttons
	SetupStyle();
	ConnectButtons();


	//ImageManipulation
	//m_UI.DateTimeEdit_Manip->setDate(QDate::currentDate());




	//Loading configs at the end
}

ImageManip::~ImageManip()
= default;

const Ui::ImageEditClass* ImageManip::GetUI() const
{
	return &m_UI;
}

void ImageManip::SetupStyle()
{
	SetFontToLabel(m_UI.Label_Converter, 18.f, true);
	SetFontToLabel(m_UI.Label_ImageEdit, 18.f, true);
	SetFontToLabel(m_UI.Label_About, 18.f, true);
	SetFontToLabel(m_UI.Label_Settings, 18.f, true);
	SetFontToLabel(m_UI.Label_Config, 18.f, true);

	//Converter
	SetFontToLabel(m_UI.Label_ConverterFiles, 15.f, false);
	SetFontToLabel(m_UI.Label_ConverterSettings, 15.f, false);

	//Manip
	SetFontToLabel(m_UI.Label_ManipFiles, 15.f, false);
	SetFontToLabel(m_UI.Label_ManipSettings, 15.f, false);

}

void ImageManip::ConnectButtons()
{
	//Left Panel buttons
	connect(m_UI.PushButton_Main, &QPushButton::clicked, this, &ImageManip::OnManip);
	connect(m_UI.PushButton_Settings, &QPushButton::clicked, this, &ImageManip::OnSettings);
	connect(m_UI.PushButton_Converter, &QPushButton::clicked, this, &ImageManip::OnConverter);
	connect(m_UI.PushButton_About, &QPushButton::clicked, this, &ImageManip::OnAbout);
	connect(m_UI.PushButton_Config, &QPushButton::clicked, this, &ImageManip::OnConfig);

	//Manip
	connect(m_UI.PushButton_ManipSelectFolder, &QPushButton::clicked, this, &ImageManip::ManipSelectFolder);
	connect(m_UI.PushButton_ManipDeleteEntry, &QPushButton::clicked, this, &ImageManip::ManipDeleteEntry);
	connect(m_UI.PushButton_ManipClear, &QPushButton::clicked, this, &ImageManip::ManipClear);
	connect(m_UI.PushButton_ManipSelectFile, &QPushButton::clicked, this, &ImageManip::ManipSelectFile);
	connect(m_UI.ListWidget_ManipImages, &QListWidget::itemClicked, this, &ImageManip::ManipSelected);

	//converter
	for (const auto& entry : g_SupportedTypes)
		m_UI.ComboBox_ConvertToType->addItem(entry);

	connect(m_UI.PushButton_DeleteCurrentConverter, &QPushButton::clicked, this, &ImageManip::ConDeleteEntry);
	connect(m_UI.PushButton_SelectFolderConverter, &QPushButton::clicked, this, &ImageManip::ConSelectFolder);
	connect(m_UI.PushButton_SelectFileConverter, &QPushButton::clicked, this, &ImageManip::ConSelectFile);
	connect(m_UI.Slider_ConverterQuality, &QSlider::valueChanged, this, &ImageManip::ConUpdateSlider);
	connect(m_UI.CheckBox_ConverterShowFileName, &QCheckBox::clicked, this, &ImageManip::ConShowFileName);
	connect(m_UI.PushButton_ClearConverter, &QPushButton::clicked, this, &ImageManip::ConClear);
	connect(m_UI.PushButton_ConvertConverter, &QPushButton::clicked, this, &ImageManip::ConConvert);
	connect(m_UI.PushButton_SelectDstFolderConverter, &QPushButton::clicked, this, &ImageManip::ConSelectOutputFolder);
	connect(m_UI.ListWidget_Converter, &QListWidget::itemDoubleClicked, this, &ImageManip::ConDoubleClickList);

}

void ImageManip::OnManip() const
{
	m_UI.stackedWidget->setCurrentWidget(m_UI.ImageManipulation);
}

void ImageManip::OnSettings() const
{
	m_UI.stackedWidget->setCurrentWidget(m_UI.Settings);
}

void ImageManip::OnConverter() const
{
	m_UI.stackedWidget->setCurrentWidget(m_UI.Converter);
}

void ImageManip::OnConfig() const
{
	m_UI.stackedWidget->setCurrentWidget(m_UI.Config);
}

void ImageManip::OnAbout() const
{
	m_UI.stackedWidget->setCurrentWidget(m_UI.About);
}

void ImageManip::ManipSelectFolder()
{
	auto folder = Helper::OpenFileDialogFolder();
	if (folder.isEmpty())
		return;

	auto images = Helper::ScanFolder(folder);
	m_Manipulator.GetAllImages(images);

	//add it to the widget
	m_UI.ListWidget_ManipImages->addItems(images);
	m_UI.ListWidget_ManipImages->update();
}

void ImageManip::ManipSelectFile()
{
	auto file = Helper::OpenFileDialogFile();
	if (file.isEmpty())
		return;

	m_Manipulator.GetImage(file);

	QStringList filenames;
	for (const auto& entry : m_Manipulator.m_Images)
	{
		filenames.append(entry.m_ImageNameEx);
	}
	m_UI.ListWidget_ManipImages->addItems(filenames);
	m_UI.ListWidget_ManipImages->update();

}

void ImageManip::ManipDeleteEntry()
{
	if (m_Manipulator.m_OutputFolder.isEmpty())
		return;

	auto item = m_UI.ListWidget_ManipImages->selectedItems();

	QStringList toDelete;
	for (const auto& items : item)
	{
		toDelete.append(items->text());
	}



}

void ImageManip::ManipClear()
{
	m_Manipulator.m_Images.clear();
	m_UI.ListWidget_ManipImages->clear();
}

void ImageManip::ManipNext()
{
}

void ImageManip::ManipPrev()
{
}

void ImageManip::ManipSelected()
{
	// QPointer<QWidget> dummyWidget = new QWidget;
	// QVBoxLayout* dummyLayout = new QVBoxLayout(dummyWidget);
	//
	// for (const auto& entry : g_ExifTags)
	// {
	// 	QLabel* label = new QLabel(entry);
	// 	QLineEdit* edit = new QLineEdit("");
	// 	dummyLayout->addWidget(label);
	// 	dummyLayout->addWidget(edit);
	//
	// 	//Creating a vertical layout
	// 	QVBoxLayout* vLayout = new QVBoxLayout;
	// 	vLayout->addWidget(label);
	// 	vLayout->addWidget(edit);
	//
	// 	//Container for the layout
	// 	QWidget* vContainer = new QWidget;
	// 	vContainer->setLayout(vLayout);
	// 	dummyLayout->addWidget(vContainer);
	//
	// 	//spacing
	// 	dummyLayout->addSpacing(5);
	// }
	//
	// dummyWidget->setLayout(dummyLayout);
	// m_UI.ScrollArea_ManipTags->setWidget(dummyWidget);
	// m_UI.ScrollArea_ManipTags->setWidgetResizable(true);

}

void ImageManip::ConSelectFolder()
{
	auto folder = Helper::OpenFileDialogFolder();
	if (folder.isEmpty())
		return;

	auto images = Helper::ScanFolder(folder);
	m_Converter.GetAllImages(images);


	//Check the checkbox & add it to the widget
	ConShowFileName();
}

void ImageManip::ConSelectFile()
{
	auto file = Helper::OpenFileDialogFile();
	if (file.isEmpty())
		return;

	m_Converter.GetImage(file);

	//Check the checkbox & add it to the widget
	ConShowFileName();
}

void ImageManip::ConDeleteEntry()
{
	if (m_Converter.m_ImageList.isEmpty())
		return;

	//Get the selected items
	auto itemsToDelete = m_UI.ListWidget_Converter->selectedItems();

	//Loop over it and delete it in the converter list
	for (auto& item : itemsToDelete)
	{
		//If the checkbox is checked (Only filenames)
		if (m_UI.CheckBox_ConverterShowFileName->isChecked())
		{
			auto it = std::ranges::find_if(m_Converter.m_ImageList,[&item](const IMAGE_DATA& image) 
				{
				return image.m_ImageName == item->text();
				});

			if (it != m_Converter.m_ImageList.end())
			{
				m_Converter.m_ImageList.erase(it);
			}
		}

		//If not
		else
		{
			auto it = std::ranges::find_if(m_Converter.m_ImageList, [&item](const IMAGE_DATA& image)
				{
					return image.m_Path == item->text();
				});

			if (it != m_Converter.m_ImageList.end())
			{
				m_Converter.m_ImageList.erase(it);
			}
		}

	}

	//delete the strings in thr widget
	for (auto& item : itemsToDelete)
	{

		delete m_UI.ListWidget_Converter->takeItem(m_UI.ListWidget_Converter->row(item));
	}
}

void ImageManip::ConUpdateSlider() const
{
	//Display the quality number
	int val = m_UI.Slider_ConverterQuality->value();
	m_UI.Label_SliderValue->setText(QString::number(val));
}

void ImageManip::ConShowFileName()
{
	//The handler to show the filenames instead of paths
	if (m_UI.CheckBox_ConverterShowFileName->isChecked())
	{
		m_UI.ListWidget_Converter->clear();
		QStringList filenames;

		for (const auto& entry : m_Converter.m_ImageList)
		{
			filenames.append(entry.m_ImageNameEx);
		}
		m_UI.ListWidget_Converter->addItems(filenames);
		m_UI.ListWidget_Converter->update();
	}

	//Path
	else
	{
		m_UI.ListWidget_Converter->clear();
		QStringList filenames;

		for (const auto& entry : m_Converter.m_ImageList)
		{
			filenames.append(entry.m_Path);
		}
		m_UI.ListWidget_Converter->addItems(filenames);
		m_UI.ListWidget_Converter->update();

	}
}

void ImageManip::ConClear()
{
	m_UI.ListWidget_Converter->clear();
	m_Converter.m_ImageList.clear();
}

void ImageManip::ConConvert()
{
	if (!m_Converter.Convert(this))
		return;


	//We clear the list afterward
	if (m_UI.CheckBox_ConverterClearListAfter->isChecked())
	{
		m_UI.ListWidget_Converter->clear();
		m_Converter.m_ImageList.clear();
	}

}

void ImageManip::ConSelectOutputFolder()
{
	auto path = Helper::OpenFileDialogFolder();
	if (path.isEmpty())
		return;

	m_Converter.m_OutputFolder = path;
	m_UI.Label_OutputFolderConverter->setStyleSheet("color: green;");
	m_UI.Label_OutputFolderConverter->setWordWrap(true);
	m_UI.Label_OutputFolderConverter->setText(path);
}

void ImageManip::ConDoubleClickList()
{
	m_pLastImage.clear();
	auto item = m_UI.ListWidget_Converter->selectedItems();
	QString path;

	for (const auto& entry : m_Converter.m_ImageList)
	{
		if (item.at(0)->text() == entry.m_ImageNameEx)
		{
			path = entry.m_Path;
			break;
		}

		if (item.at(0)->text() == entry.m_Path)
		{
			path = entry.m_Path;
			break;
		}
	}

	m_pLastImage= new ImageWindow(path);
	m_pLastImage->show();
}

void ImageManip::SetFontToLabel(QLabel* label, float size, bool bold)
{
	QFont font;
	font.setFamily("Exo2");
	font.setPointSizeF(size);
	font.setBold(bold);

	label->setFont(font);
}
