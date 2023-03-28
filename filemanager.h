#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QTextDocument>



class FileManager
{
public:
    FileManager();
    void printPDF(QTextDocument *doc, QString filePath);
    QString readFile(QString filePath);
    void saveToFile(QString filePath, QString resultString);
};

#endif // FILEMANAGER_H
