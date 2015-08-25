#include "utils.h"
namespace Utils
{

    std::wstring GetSaveFileNameFromDialog()
    {
        QString selfilter = "CHDATA (*.chdata)";
        QString filePath = QFileDialog::getSaveFileName(0, "ChessGame", QDir::homePath(), ("All files (*.*);;CHDATA (*.chdata);;TXT (*.txt)"), &selfilter);
        return filePath.toStdWString();
    }
    std::wstring GetOpenFileNameFromDialog()
    {
        QString selfilter = "CHDATA (*.chdata)";
        QString filePath = QFileDialog::getOpenFileName(0, "ChessGame", QDir::homePath(), ("All files (*.*);;CHDATA (*.chdata);;TXT (*.txt)"), &selfilter);
        return filePath.toStdWString();
    }
}

