#include "filedialogex.h"

#include <QSettings>
#include <QFileDialog>
#include "fileformat.h"
#include "pencildef.h"

FileDialog::FileDialog( QWidget* parent ) : QObject( parent )
{
    mRoot = parent;
}

FileDialog::~FileDialog()
{
}

QString FileDialog::openFile(FileType fileType)
{
    QString strTitle = openDialogTitle( fileType );
    QString strInitialFilePath = getLastOpenPath( fileType );
    QString strFilter = saveFileFilters( fileType );

    QString filePath = QFileDialog::getOpenFileName( mRoot,
                                                     strTitle,
                                                     strInitialFilePath,
                                                     strFilter );
    if ( !filePath.isEmpty() )
    {
        setLastOpenPath( fileType, filePath );
    }

    return filePath;
}

QString FileDialog::saveFile( FileType fileType )
{
    QString strTitle = saveDialogTitle( fileType );
    QString strInitialFilePath = getLastSavePath( fileType );
    QString strFilter = saveFileFilters( fileType );

    QString filePath = QFileDialog::getSaveFileName( mRoot,
                                                     strTitle,
                                                     strInitialFilePath,
                                                     strFilter );
    if ( !filePath.isEmpty() )
    {
        setLastSavePath( fileType, filePath );
    }

    return filePath;
}

QString FileDialog::getLastOpenPath( FileType fileType )
{
    QSettings setting( PENCIL2D, PENCIL2D );
    setting.beginGroup( "LastOpenPath" );

    return setting.value( toSettingKey( fileType ), QDir::homePath() ).toString();
}

void FileDialog::setLastOpenPath( FileType fileType, QString openPath )
{
    QSettings setting( PENCIL2D, PENCIL2D );
    setting.beginGroup( "LastOpenPath" );

    setting.setValue( toSettingKey( fileType ), openPath );
}

QString FileDialog::getLastSavePath( FileType fileType )
{
    QSettings setting( PENCIL2D, PENCIL2D );
    setting.beginGroup( "LastSavePath" );

    return setting.value( toSettingKey( fileType ), QDir::homePath() ).toString();
}

void FileDialog::setLastSavePath( FileType fileType, QString savePath )
{
    QSettings setting( PENCIL2D, PENCIL2D );
    setting.beginGroup( "LastSavePath" );

    setting.setValue( toSettingKey( fileType ), savePath );
}

QString FileDialog::openDialogTitle( FileType fileType )
{
    switch ( fileType )
    {
        case FileType::DOCUMENT: return tr( "Open document" );
        case FileType::IMAGE: return tr( "Import image" );
        case FileType::IMAGE_SEQUENCE: return tr( "Import image sequence" );
        case FileType::MOVIE: return tr( "Import movie" );
        case FileType::SOUND: return tr( "Import sound" );
        case FileType::PALETTE: return tr( "Import palette" );
        default: Q_ASSERT( false );
    }
    return "";
}

QString FileDialog::saveDialogTitle( FileType fileType )
{
    switch ( fileType )
    {
        case FileType::DOCUMENT: return tr( "Save document" );
        case FileType::IMAGE: return tr( "Export image" );
        case FileType::IMAGE_SEQUENCE: return tr( "Export image sequence" );
        case FileType::MOVIE: return tr( "Export movie" );
        case FileType::SOUND: return tr( "Export sound" );
        case FileType::PALETTE: return tr( "Export palette" );
        default: Q_ASSERT( false );
    }
    return "";
}

QString FileDialog::openFileFilters( FileType fileType )
{
    switch ( fileType )
    {
        case FileType::DOCUMENT: return tr( PFF_OPEN_ALL_FILE_FILTER );
        case FileType::IMAGE: return PENCIL_IMAGE_FILTER;
        case FileType::IMAGE_SEQUENCE: return tr( "Images (*.png *.jpg *.jpeg *.tif *.tiff *.bmp)" );
        case FileType::MOVIE: return PENCIL_MOVIE_EXT;
        case FileType::SOUND: return tr( "Sounds (*.wav *.mp3);;WAV (*.wav);;MP3 (*.mp3)" );
        case FileType::PALETTE: return QString();
        default: Q_ASSERT( false );
    }
    return "";
}

QString FileDialog::saveFileFilters( FileType fileType )
{
    switch ( fileType )
    {
        case FileType::DOCUMENT: return tr( PFF_SAVE_ALL_FILE_FILTER );
        case FileType::IMAGE: return QString();
        case FileType::IMAGE_SEQUENCE: return QString();
        case FileType::MOVIE: return tr( "MP4 (*.mp4);;AVI (*.avi);;GIF (*.gif)" );
        case FileType::SOUND: return QString();
        case FileType::PALETTE: return QString();
        default: Q_ASSERT( false );
    }
    return "";
}

QString FileDialog::toSettingKey( FileType fileType )
{
    switch ( fileType )
    {
        case FileType::DOCUMENT: return "Document";
        case FileType::IMAGE: return "Image";
        case FileType::IMAGE_SEQUENCE: return "ImageSequence";
        case FileType::MOVIE: return "Movie";
        case FileType::SOUND: return "Sound";
        case FileType::PALETTE: return "Palette";
        default: Q_ASSERT( false );
    }
    return "";
}
