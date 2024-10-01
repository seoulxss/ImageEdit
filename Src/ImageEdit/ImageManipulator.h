#pragma once
#include <Magick++.h>
#include <qlist.h>
#include <QMessageBox>
#include <QFile>
#include <qfileinfo.h>
#include <stdexcept>

#include "Src/Util/Helpers.h"

//All the debug librarys
#ifdef DEBUG
#pragma comment(lib, "ConfigLib.lib") //ConfigLib
//#pragma comment(lib, "Exiv2.lib") Included via vcpkg

//ImageMagick
#pragma comment(lib, "CORE_DB_aom_.lib")
#pragma comment(lib, "CORE_DB_brotli_.lib")
#pragma comment(lib, "CORE_DB_bzlib_.lib")
#pragma comment(lib, "CORE_DB_cairo_.lib")
#pragma comment(lib, "CORE_DB_coders_.lib")
#pragma comment(lib, "CORE_DB_croco_.lib")
#pragma comment(lib, "CORE_DB_de265_.lib")
#pragma comment(lib, "CORE_DB_deflate_.lib")
#pragma comment(lib, "CORE_DB_exr_.lib")
#pragma comment(lib, "CORE_DB_ffi_.lib")
#pragma comment(lib, "CORE_DB_filters_.lib")
#pragma comment(lib, "CORE_DB_freetype_.lib")
#pragma comment(lib, "CORE_DB_fribidi_.lib")
#pragma comment(lib, "CORE_DB_glib_.lib")
#pragma comment(lib, "CORE_DB_harfbuzz_.lib")
#pragma comment(lib, "CORE_DB_heif_.lib")
#pragma comment(lib, "CORE_DB_highway_.lib")
#pragma comment(lib, "CORE_DB_jpeg-turbo_.lib")
#pragma comment(lib, "CORE_DB_jpeg-turbo-12_.lib")
#pragma comment(lib, "CORE_DB_jpeg-turbo-16_.lib")
#pragma comment(lib, "CORE_DB_jpeg-xl_.lib")
#pragma comment(lib, "CORE_DB_lcms_.lib")
#pragma comment(lib, "CORE_DB_lqr_.lib")
#pragma comment(lib, "CORE_DB_lzma_.lib")
#pragma comment(lib, "CORE_DB_Magick++_.lib")
#pragma comment(lib, "CORE_DB_MagickCore_.lib")
#pragma comment(lib, "CORE_DB_MagickWand_.lib")
#pragma comment(lib, "CORE_DB_openjpeg_.lib")
#pragma comment(lib, "CORE_DB_pango_.lib")
#pragma comment(lib, "CORE_DB_pixman_.lib")
#pragma comment(lib, "CORE_DB_png_.lib")
#pragma comment(lib, "CORE_DB_raqm_.lib")
#pragma comment(lib, "CORE_DB_raw_.lib")
#pragma comment(lib, "CORE_DB_rsvg_.lib")
#pragma comment(lib, "CORE_DB_tiff_.lib")
#pragma comment(lib, "CORE_DB_webp_.lib")
#pragma comment(lib, "CORE_DB_xml_.lib")
#pragma comment(lib, "CORE_DB_zip_.lib")
#pragma comment(lib, "CORE_DB_zlib_.lib")
#else//Release version
#pragma comment(lib, "ConfigLib.lib") //ConfigLib
#pragma comment(lib, "Exiv2.lib")

//ImageMagick
#pragma comment(lib, "CORE_RL_aom_.lib")
#pragma comment(lib, "CORE_RL_brotli_.lib")
#pragma comment(lib, "CORE_RL_bzlib_.lib")
#pragma comment(lib, "CORE_RL_cairo_.lib")
#pragma comment(lib, "CORE_RL_coders_.lib")
#pragma comment(lib, "CORE_RL_croco_.lib")
#pragma comment(lib, "CORE_RL_de265_.lib")
#pragma comment(lib, "CORE_RL_deflate_.lib")
#pragma comment(lib, "CORE_RL_exr_.lib")
#pragma comment(lib, "CORE_RL_ffi_.lib")
#pragma comment(lib, "CORE_RL_filters_.lib")
#pragma comment(lib, "CORE_RL_freetype_.lib")
#pragma comment(lib, "CORE_RL_fribidi_.lib")
#pragma comment(lib, "CORE_RL_glib_.lib")
#pragma comment(lib, "CORE_RL_harfbuzz_.lib")
#pragma comment(lib, "CORE_RL_heif_.lib")
#pragma comment(lib, "CORE_RL_highway_.lib")
#pragma comment(lib, "CORE_RL_jpeg-turbo_.lib")
#pragma comment(lib, "CORE_RL_jpeg-turbo-12_.lib")
#pragma comment(lib, "CORE_RL_jpeg-turbo-16_.lib")
#pragma comment(lib, "CORE_RL_jpeg-xl_.lib")
#pragma comment(lib, "CORE_RL_lcms_.lib")
#pragma comment(lib, "CORE_RL_lqr_.lib")
#pragma comment(lib, "CORE_RL_lzma_.lib")
#pragma comment(lib, "CORE_RL_Magick++_.lib")
#pragma comment(lib, "CORE_RL_MagickCore_.lib")
#pragma comment(lib, "CORE_RL_MagickWand_.lib")
#pragma comment(lib, "CORE_RL_openjpeg_.lib")
#pragma comment(lib, "CORE_RL_pango_.lib")
#pragma comment(lib, "CORE_RL_pixman_.lib")
#pragma comment(lib, "CORE_RL_png_.lib")
#pragma comment(lib, "CORE_RL_raqm_.lib")
#pragma comment(lib, "CORE_RL_raw_.lib")
#pragma comment(lib, "CORE_RL_rsvg_.lib")
#pragma comment(lib, "CORE_RL_tiff_.lib")
#pragma comment(lib, "CORE_RL_webp_.lib")
#pragma comment(lib, "CORE_RL_xml_.lib")
#pragma comment(lib, "CORE_RL_zip_.lib")
#pragma comment(lib, "CORE_RL_zlib_.lib")
#endif

struct IMAGE_DATA;
inline const QStringList g_SupportedTypes = {
	".jpg",   // JPEG image
	".jpeg",  // JPEG image
	".png",   // Portable Network Graphics
	".gif",   // Graphics Interchange Format
	".bmp",   // Bitmap image
	".tiff",  // Tagged Image File Format
	".webp",  // WebP image
	".svg",   // Scalable Vector Graphics
	".pdf",   // Portable Document Format
	".tga",   // Targa image
	".pnm",   // Portable AnyMap
	".ppm",   // Portable Pixmap
	".pbm",   // Portable Bitmap
	".xbm",   // X Bitmap
	".xpm"    // X PixMap
};

inline const QStringList g_ExifTags = {
	"EXIF:DateTime",               // Date and time of last modification
	"EXIF:Make",                   // Camera manufacturer
	"EXIF:Model",                  // Camera model
	"EXIF:Software",               // Software/application
	"EXIF:Artist",                 // Artist/creator
	"EXIF:Copyright",              // Copyright notice
	"EXIF:ExposureTime",           // Exposure time
	"EXIF:FNumber",                // Aperture value
	"EXIF:ISOSpeedRatings",        // ISO sensitivity
	"EXIF:DateTimeOriginal",       // Date and time of original image capture
	"EXIF:DateTimeDigitized",      // Date and time of digitization
	"EXIF:ShutterSpeedValue",      // Shutter speed
	"EXIF:ApertureValue",          // Aperture
	"EXIF:BrightnessValue",        // Brightness value
	"EXIF:ExposureBiasValue",      // Exposure compensation
	"EXIF:MaxApertureValue",       // Maximum aperture
	"EXIF:SubjectDistance",        // Distance to subject
	"EXIF:MeteringMode",           // Metering mode
	"EXIF:LightSource",            // Light source
	"EXIF:Flash",                  // Flash mode
	"EXIF:FocalLength",            // Focal length
	"EXIF:FlashEnergy",            // Flash energy
	"EXIF:SpatialFrequencyResponse", // Spatial frequency response
	"EXIF:FocalPlaneXResolution",  // Focal plane X resolution
	"EXIF:FocalPlaneYResolution",  // Focal plane Y resolution
	"EXIF:SubjectLocation",        // Subject location
	"EXIF:SensingMethod",          // Sensing method
	"EXIF:FileSource",             // File source
	"EXIF:SceneType",              // Scene type
	"EXIF:CustomRendered",         // Custom processing
	"EXIF:ExposureMode",           // Exposure mode
	"EXIF:WhiteBalance",           // White balance
	"EXIF:DigitalZoomRatio",       // Digital zoom ratio
	"EXIF:FocalLengthIn35mmFilm",  // Focal length in 35mm film equivalent
	"EXIF:SceneCaptureType",       // Scene capture type
	"EXIF:GainControl",            // Gain control
	"EXIF:Contrast",               // Contrast
	"EXIF:Saturation",             // Saturation
	"EXIF:Sharpness",              // Sharpness
	"EXIF:DeviceSettingDescription", // Device settings description
	"EXIF:SubjectDistanceRange",   // Subject distance range
	"EXIF:ImageUniqueID",          // Unique image ID
	"EXIF:GPSVersionID",           // GPS version
	"EXIF:GPSLatitude",            // GPS latitude
	"EXIF:GPSLongitude",           // GPS longitude
	"EXIF:GPSAltitude",            // GPS altitude
	"EXIF:GPSSpeedRef",            // GPS speed reference
	"EXIF:GPSSpeed",               // GPS speed
	"EXIF:GPSTrackRef",            // GPS track reference
	"EXIF:GPSTrack",               // GPS track
	"EXIF:GPSImgDirectionRef",     // GPS image direction reference
	"EXIF:GPSImgDirection",        // GPS image direction
	"EXIF:GPSDestLatitude",        // GPS destination latitude
	"EXIF:GPSDestLongitude",       // GPS destination longitude
	"EXIF:GPSDestBearing",         // GPS destination bearing
	"EXIF:GPSDestDistance",        // GPS destination distance
	"EXIF:GPSProcessingMethod",    // GPS processing method
	"EXIF:GPSAreaInformation",     // GPS area information
	"EXIF:GPSDateStamp",           // GPS date stamp
	"EXIF:GPSDifferential",        // GPS differential correction
	"EXIF:Orientation",            // Image orientation
	"EXIF:ResolutionUnit",         // Resolution unit
	"EXIF:YCbCrPositioning",       // YCbCr positioning
	"EXIF:ExifVersion",            // EXIF version
	"EXIF:ComponentsConfiguration", // Components configuration
	"EXIF:CompressedBitsPerPixel", // Compressed bits per pixel
	"EXIF:MakerNote",              // Maker note
	"EXIF:UserComment",            // User comment
	"EXIF:SubSecTime",             // Sub-second time
	"EXIF:SubSecTimeOriginal",     // Sub-second time of original image capture
	"EXIF:SubSecTimeDigitized",    // Sub-second time of digitization
	"EXIF:FlashpixVersion",        // FlashPix version
	"EXIF:ColorSpace",             // Color space
	"EXIF:PixelXDimension",        // Pixel dimension in X direction
	"EXIF:PixelYDimension",        // Pixel dimension in Y direction
	"EXIF:InteroperabilityIndex",  // Interoperability index
	"EXIF:InteroperabilityVersion", // Interoperability version
	"EXIF:RelatedImageFileFormat", // Related image file format
	"EXIF:RelatedImageWidth",      // Related image width
	"EXIF:RelatedImageHeight"      // Related image height
};
inline const QStringList g_IptcTags = {
	"IPTC:ObjectName",             // Object name/Image title
	"IPTC:Urgency",                // Urgency
	"IPTC:Category",               // Category
	"IPTC:SupplementalCategories", // Supplemental categories
	"IPTC:Keywords",               // Keywords
	"IPTC:Byline",                 // Byline (Author)
	"IPTC:BylineTitle",            // Byline title
	"IPTC:Credit",                 // Credit
	"IPTC:Source",                 // Source of the image
	"IPTC:CopyrightNotice",        // Copyright notice
	"IPTC:Caption",                // Caption
	"IPTC:CaptionWriter",          // Caption writer
	"IPTC:Headline",               // Headline
	"IPTC:SpecialInstructions",    // Special instructions
	"IPTC:DateCreated",            // Date created
	"IPTC:TimeCreated",            // Time created
	"IPTC:DigitalCreationDate",    // Digital creation date
	"IPTC:DigitalCreationTime",    // Digital creation time
	"IPTC:City",                   // City
	"IPTC:SubLocation",            // Sub-location
	"IPTC:ProvinceState",          // Province/state
	"IPTC:CountryCode",            // Country code
	"IPTC:CountryName",            // Country name
	"IPTC:OriginalTransmissionReference", // Original transmission reference
	"IPTC:ContentLocationCode",    // Content location code
	"IPTC:ContentLocationName",    // Content location name
	"IPTC:ReleaseDate",            // Release date
	"IPTC:ReleaseTime",            // Release time
	"IPTC:ExpirationDate",         // Expiration date
	"IPTC:ExpirationTime",         // Expiration time
	"IPTC:Program",                // Program name
	"IPTC:ProgramVersion",         // Program version
	"IPTC:ObjectCycle",            // Object cycle (New/Repeat/Archive)
	"IPTC:SubjectReference",       // Subject reference number
	"IPTC:Scene",                  // Scene
	"IPTC:RightsUsageTerms",       // Rights usage terms
	"IPTC:ContactInfo",            // Contact information
	"IPTC:Writer",                 // Writer
	"IPTC:ImageType",              // Image type
	"IPTC:ImageOrientation",       // Image orientation
	"IPTC:JobID",                  // Job ID
	"IPTC:EnvelopeNumber",         // Envelope number
	"IPTC:ServiceID",              // Service ID
	"IPTC:EnvelopePriority",       // Envelope priority
	"IPTC:DateSent",               // Date sent
	"IPTC:TimeSent"                // Time sent
};
inline const QStringList g_XMPTags = {
	"XMP:CreateDate",             // Date and time the image was created
	"XMP:ModifyDate",             // Date and time the image was last modified
	"XMP:CreatorTool",            // Software or tool used to create the image
	"XMP:Label",                  // Label or tag assigned to the image
	"XMP:Description",            // Description of the image
	"XMP:Rights",                 // Rights or licensing information
	"XMP:Rating",                 // Rating or score given to the image
	"XMP:Subject",                // Keywords or subjects associated with the image
	"XMP:MetadataDate",           // Date and time when the metadata was created or last modified
	"XMP:RegionInfo",             // Information about regions or areas in the image
	"XMP:UsageTerms",             // Usage terms or conditions
};
inline const QStringList g_DCTags = {
	"DC:Title",                   // Title of the resource
	"DC:Creator",                 // Creator of the resource
	"DC:Subject",                 // Subject of the resource
	"DC:Description",             // Description of the resource
	"DC:Publisher",               // Publisher of the resource
	"DC:Contributor",             // Contributor to the resource
	"DC:Date",                    // Date of creation or publication
	"DC:Type",                    // Type of the resource
	"DC:Format",                  // Format of the resource
	"DC:Identifier",              // Identifier for the resource
	"DC:Source",                  // Source from which the resource was derived
	"DC:Language",                // Language of the resource
	"DC:Relation",                // Relation to other resources
	"DC:Coverage",                // Spatial or temporal coverage of the resource
	"DC:Rights",                  // Rights or permissions associated with the resource

};
inline const QStringList g_DNGTags = {
	"DNG:Version",                // Version of the DNG specification
	"DNG:UniqueCameraModel",      // Unique model name of the camera
	"DNG:RawDataUniqueID",        // Unique ID for the raw image data
	"DNG:CameraSerialNumber",     // Serial number of the camera
	"DNG:LensID",                 // ID of the lens used
	"DNG:CalibrationIlluminant1", // Calibration illuminant used
	"DNG:CalibrationIlluminant2", // Secondary calibration illuminant
	"DNG:ProfileName",            // Name of the color profile
	"DNG:ProfileHueSatMapData1",  // Hue and saturation mapping data
	"DNG:ProfileHueSatMapData2",  // Secondary hue and saturation mapping data
};
inline const QStringList g_PhotoShopTags = {
	"Photoshop:ColorMode",        // Color mode of the image (e.g., RGB, CMYK)
	"Photoshop:Compression",      // Compression type used for the image
	"Photoshop:DocumentFonts",    // Fonts used in the document
	"Photoshop:DocumentID",       // Unique ID of the Photoshop document
	"Photoshop:LayerCount",       // Number of layers in the document
	"Photoshop:LayerNames",       // Names of the layers in the document
	"Photoshop:HistoryStates",    // Number of history states in the document
	"Photoshop:Thumbnail",        // Thumbnail of the document
	"Photoshop:MetadataVersion",  // Version of the Photoshop metadata schema
	"Photoshop:Creator",          // Creator of the Photoshop document
	"Photoshop:Software"          // Software used to create or edit the document
};

//My data struct, which holds all the Image
struct _Metadata
{
	std::map<std::string, std::string> Exif;
	std::map<std::string, std::string> IPTC;
	std::map<std::string, std::string> XMP;
	std::map<std::string, std::string> DublinCore;
	std::map<std::string, std::string> DNG;
	std::map<std::string, std::string> Photoshop;
};

struct IMAGE_METADATA
{
    IMAGE_METADATA(Magick::Image& Image, bool ScanMetadata, IMAGE_DATA* data)
	{
        if (ScanMetadata)
            Set(Image, data);

	}


	IMAGE_METADATA() = default;

	void Set(Magick::Image& Image, IMAGE_DATA* Data)
	{
        ProcessMetadata(Image, m_Metadata.Exif,
                        {
	                        "EXIF:DateTime",               // Datum und Uhrzeit der letzten Änderung
	                        "EXIF:Make",                   // Kamerahersteller
	                        "EXIF:Model",                  // Kameramodell
	                        "EXIF:Software",               // Software/Anwendung
	                        "EXIF:Artist",                 // Künstler/Urheber
	                        "EXIF:Copyright",              // Copyright-Hinweis
	                        "EXIF:ExposureTime",           // Belichtungszeit
	                        "EXIF:FNumber",                // Blendenwert
	                        "EXIF:ISOSpeedRatings",        // ISO-Empfindlichkeit
	                        "EXIF:DateTimeOriginal",       // Datum und Uhrzeit der Aufnahme
	                        "EXIF:DateTimeDigitized",      // Datum und Uhrzeit der Digitalisierung
	                        "EXIF:ShutterSpeedValue",      // Verschlusszeit (Shutter Speed)
	                        "EXIF:ApertureValue",          // Blendenöffnung (Aperture)
	                        "EXIF:BrightnessValue",        // Helligkeitswert
	                        "EXIF:ExposureBiasValue",      // Belichtungskorrektur
	                        "EXIF:MaxApertureValue",       // Maximalöffnung (Max Aperture)
	                        "EXIF:SubjectDistance",        // Entfernung zum Motiv
	                        "EXIF:MeteringMode",           // Belichtungsmessmodus
	                        "EXIF:LightSource",            // Lichtquelle
	                        "EXIF:Flash",                  // Blitzmodus
	                        "EXIF:FocalLength",            // Brennweite
	                        "EXIF:FlashEnergy",            // Blitzenergie
	                        "EXIF:SpatialFrequencyResponse", // Räumliche Frequenzantwort
	                        "EXIF:FocalPlaneXResolution",  // Fokusebene X-Auflösung
	                        "EXIF:FocalPlaneYResolution",  // Fokusebene Y-Auflösung
	                        "EXIF:SubjectLocation",        // Position des Motivs
	                        "EXIF:SensingMethod",          // Sensormethode
	                        "EXIF:FileSource",             // Datenquelle (File Source)
	                        "EXIF:SceneType",              // Szenentyp
	                        "EXIF:CustomRendered",         // Benutzerdefinierte Verarbeitung
	                        "EXIF:ExposureMode",           // Belichtungsmodus
	                        "EXIF:WhiteBalance",           // Weißabgleich
	                        "EXIF:DigitalZoomRatio",       // Digitaler Zoomfaktor
	                        "EXIF:FocalLengthIn35mmFilm",  // Brennweite in 35mm-Äquivalent
	                        "EXIF:SceneCaptureType",       // Art der Szenenaufnahme
	                        "EXIF:GainControl",            // Verstärkungssteuerung
	                        "EXIF:Contrast",               // Kontrast
	                        "EXIF:Saturation",             // Sättigung
	                        "EXIF:Sharpness",              // Schärfe
	                        "EXIF:DeviceSettingDescription", // Geräteeinstellungen
	                        "EXIF:SubjectDistanceRange",   // Entfernungsbereich zum Motiv
	                        "EXIF:ImageUniqueID",          // Eindeutige Bild-ID
	                        "EXIF:GPSVersionID",           // GPS-Version
	                        "EXIF:GPSLatitude",            // GPS-Breitengrad
	                        "EXIF:GPSLongitude",           // GPS-Längengrad
	                        "EXIF:GPSAltitude",            // GPS-Höhe
	                        "EXIF:GPSSpeedRef",            // Referenz für GPS-Geschwindigkeit
	                        "EXIF:GPSSpeed",               // GPS-Geschwindigkeit
	                        "EXIF:GPSTrackRef",            // Referenz für GPS-Richtung
	                        "EXIF:GPSTrack",               // GPS-Richtung
	                        "EXIF:GPSImgDirectionRef",     // Referenz für Bildrichtung
	                        "EXIF:GPSImgDirection",        // Bildrichtung
	                        "EXIF:GPSDestLatitude",        // GPS-Zielbreitengrad
	                        "EXIF:GPSDestLongitude",       // GPS-Ziellängengrad
	                        "EXIF:GPSDestBearing",         // GPS-Zielrichtung
	                        "EXIF:GPSDestDistance",        // GPS-Zieldistanz
	                        "EXIF:GPSProcessingMethod",    // GPS-Verarbeitungsmethode
	                        "EXIF:GPSAreaInformation",     // GPS-Ortsinformation
	                        "EXIF:GPSDateStamp",           // GPS-Datumsstempel
	                        "EXIF:GPSDifferential",        // GPS-Differenzialkorrektur
	                        "EXIF:Orientation",            // Bildorientierung
	                        "EXIF:ResolutionUnit",         // Auflösungseinheit
	                        "EXIF:YCbCrPositioning",       // YCbCr-Positionierung
	                        "EXIF:ExifVersion",            // EXIF-Version
	                        "EXIF:ComponentsConfiguration", // Komponenten-Konfiguration
	                        "EXIF:CompressedBitsPerPixel", // Komprimierte Bits pro Pixel
	                        "EXIF:MakerNote",              // Herstellerhinweis
	                        "EXIF:UserComment",            // Benutzerkommentar
	                        "EXIF:SubSecTime",             // Untersekundenzeit (Subsekunden)
	                        "EXIF:SubSecTimeOriginal",     // Untersekundenzeit der Originalaufnahme
	                        "EXIF:SubSecTimeDigitized",    // Untersekundenzeit der Digitalisierung
	                        "EXIF:FlashpixVersion",        // FlashPix-Version
	                        "EXIF:ColorSpace",             // Farbraum
	                        "EXIF:PixelXDimension",        // Pixelanzahl in X-Richtung
	                        "EXIF:PixelYDimension",        // Pixelanzahl in Y-Richtung
	                        "EXIF:InteroperabilityIndex",  // Interoperabilitätsindex
	                        "EXIF:InteroperabilityVersion", // Interoperabilitätsversion
	                        "EXIF:RelatedImageFileFormat", // Dateiformat des zugehörigen Bildes
	                        "EXIF:RelatedImageWidth",      // Breite des zugehörigen Bildes
	                        "EXIF:RelatedImageHeight"      // Höhe des zugehörigen Bildes
                        }, Data);
        
        
        ProcessMetadata(Image, m_Metadata.IPTC,
                        {
	                        "IPTC:ObjectName",             // Object name/Image title
	                        "IPTC:Urgency",                // Urgency
	                        "IPTC:Category",               // Category
	                        "IPTC:SupplementalCategories", // Supplemental categories
	                        "IPTC:Keywords",               // Keywords
	                        "IPTC:Byline",                 // Byline (Author)
	                        "IPTC:BylineTitle",            // Byline title
	                        "IPTC:Credit",                 // Credit
	                        "IPTC:Source",                 // Source of the image
	                        "IPTC:CopyrightNotice",        // Copyright notice
	                        "IPTC:Caption",                // Caption
	                        "IPTC:CaptionWriter",          // Caption writer
	                        "IPTC:Headline",               // Headline
	                        "IPTC:SpecialInstructions",    // Special instructions
	                        "IPTC:DateCreated",            // Date created
	                        "IPTC:TimeCreated",            // Time created
	                        "IPTC:DigitalCreationDate",    // Digital creation date
	                        "IPTC:DigitalCreationTime",    // Digital creation time
	                        "IPTC:City",                   // City
	                        "IPTC:SubLocation",            // Sub-location
	                        "IPTC:ProvinceState",          // Province/state
	                        "IPTC:CountryCode",            // Country code
	                        "IPTC:CountryName",            // Country name
	                        "IPTC:OriginalTransmissionReference", // Original transmission reference
	                        "IPTC:ContentLocationCode",    // Content location code
	                        "IPTC:ContentLocationName",    // Content location name
	                        "IPTC:ReleaseDate",            // Release date
	                        "IPTC:ReleaseTime",            // Release time
	                        "IPTC:ExpirationDate",         // Expiration date
	                        "IPTC:ExpirationTime",         // Expiration time
	                        "IPTC:Program",                // Program name
	                        "IPTC:ProgramVersion",         // Program version
	                        "IPTC:ObjectCycle",            // Object cycle (New/Repeat/Archive)
	                        "IPTC:SubjectReference",       // Subject reference number
	                        "IPTC:Scene",                  // Scene
	                        "IPTC:RightsUsageTerms",       // Rights usage terms
	                        "IPTC:ContactInfo",            // Contact information
	                        "IPTC:Writer",                 // Writer
	                        "IPTC:ImageType",              // Image type
	                        "IPTC:ImageOrientation",       // Image orientation
	                        "IPTC:JobID",                  // Job ID
	                        "IPTC:EnvelopeNumber",         // Envelope number
	                        "IPTC:ServiceID",              // Service ID
	                        "IPTC:EnvelopePriority",       // Envelope priority
	                        "IPTC:DateSent",               // Date sent
	                        "IPTC:TimeSent"                // Time sent
                        }, Data);
        
        ProcessMetadata(Image, m_Metadata.XMP,
                        {
	                        "XMP:CreateDate",             // Date and time the image was created
	                        "XMP:ModifyDate",             // Date and time the image was last modified
	                        "XMP:CreatorTool",            // Software or tool used to create the image
	                        "XMP:Label",                  // Label or tag assigned to the image
	                        "XMP:Description",            // Description of the image
	                        "XMP:Rights",                 // Rights or licensing information
	                        "XMP:Rating",                 // Rating or score given to the image
	                        "XMP:Subject",                // Keywords or subjects associated with the image
	                        "XMP:MetadataDate",           // Date and time when the metadata was created or last modified
	                        "XMP:RegionInfo",             // Information about regions or areas in the image
	                        "XMP:UsageTerms",             // Usage terms or conditions
                        }, Data);
        
        ProcessMetadata(Image, m_Metadata.DublinCore,
                        {
	                        "DC:Title",                   // Title of the resource
	                        "DC:Creator",                 // Creator of the resource
	                        "DC:Subject",                 // Subject of the resource
	                        "DC:Description",             // Description of the resource
	                        "DC:Publisher",               // Publisher of the resource
	                        "DC:Contributor",             // Contributor to the resource
	                        "DC:Date",                    // Date of creation or publication
	                        "DC:Type",                    // Type of the resource
	                        "DC:Format",                  // Format of the resource
	                        "DC:Identifier",              // Identifier for the resource
	                        "DC:Source",                  // Source from which the resource was derived
	                        "DC:Language",                // Language of the resource
	                        "DC:Relation",                // Relation to other resources
	                        "DC:Coverage",                // Spatial or temporal coverage of the resource
	                        "DC:Rights",                  // Rights or permissions associated with the resource
                        }, Data);
        
        ProcessMetadata(Image, m_Metadata.DNG,
                        {
	                        "DNG:Version",                // Version of the DNG specification
	                        "DNG:UniqueCameraModel",      // Unique model name of the camera
	                        "DNG:RawDataUniqueID",        // Unique ID for the raw image data
	                        "DNG:CameraSerialNumber",     // Serial number of the camera
	                        "DNG:LensID",                 // ID of the lens used
	                        "DNG:CalibrationIlluminant1", // Calibration illuminant used
	                        "DNG:CalibrationIlluminant2", // Secondary calibration illuminant
	                        "DNG:ProfileName",            // Name of the color profile
	                        "DNG:ProfileHueSatMapData1",  // Hue and saturation mapping data
	                        "DNG:ProfileHueSatMapData2",  // Secondary hue and saturation mapping data
                        }, Data);
        
        ProcessMetadata(Image, m_Metadata.Photoshop,
                        {
	                        "Photoshop:ColorMode",        // Color mode of the image (e.g., RGB, CMYK)
	                        "Photoshop:Compression",      // Compression type used for the image
	                        "Photoshop:DocumentFonts",    // Fonts used in the document
	                        "Photoshop:DocumentID",       // Unique ID of the Photoshop document
	                        "Photoshop:LayerCount",       // Number of layers in the document
	                        "Photoshop:LayerNames",       // Names of the layers in the document
	                        "Photoshop:HistoryStates",    // Number of history states in the document
	                        "Photoshop:Thumbnail",        // Thumbnail of the document
	                        "Photoshop:MetadataVersion",  // Version of the Photoshop metadata schema
	                        "Photoshop:Creator",          // Creator of the Photoshop document
	                        "Photoshop:Software",         // Software used to create or edit the document
                        }, Data);
	}

	_Metadata m_Metadata;
private:

	//We use an initializer list to make it faster
    void ProcessMetadata(const Magick::Image& Image, std::map<std::string, std::string>& map, const std::initializer_list<std::string>& list, const
                         IMAGE_DATA* pData);


};

struct IMAGE_DATA
{
	IMAGE_DATA(const QString& absolutePath, bool ScanMetaData) : m_Path(absolutePath)
	{
		try
		{
			//Reading the file
			m_Image.read(absolutePath.toStdString());
			m_ImageInfo = *m_Image.imageInfo();

			//Setting the Image name
			QFileInfo file(absolutePath);
			m_ImageNameEx = file.fileName();
			m_ImageName = file.completeBaseName();

			//Scan metadata
			m_Metadata = IMAGE_METADATA(m_Image, ScanMetaData, this);
			
		}
		catch (const Magick::Exception& e)
		{
			QMessageBox box;
			QString error = "Could not load the image! Is it really a image file?";
			error.append(" <ImageMagick Error>: ");
			error.append(e.what());
			box.setWindowTitle("ImageMagick Error");
			box.setText(error);
			box.exec();
		}
	}

	QString m_ImageName = {};
	QString m_ImageNameEx = {};
	QString m_Path = {};
	Magick::Image m_Image;
	Magick::ImageInfo m_ImageInfo;
	IMAGE_METADATA m_Metadata;
};

//The basic editor class
class ImageManipulator
{
public:
	ImageManipulator();

	void GetAllImages(const QStringList& list);
	void GetImage(const QString& file);
    void LoadAsync(const QStringList& List);

	QString m_OutputFolder = {};
	QList<IMAGE_DATA> m_Images = {};
};

