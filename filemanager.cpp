#include "filemanager.h"

#include <QFile>
#include <QPrinter>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextStream>

FileManager::FileManager()
{

}

void FileManager::printPDF(QTextDocument* doc, QString filePath)
{
    QTextCursor cursor(doc);
    cursor.movePosition(QTextCursor::End);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName(filePath);
    doc->print(&printer);
}

QString FileManager::readFile(QString filePath)
{
    QString text;
    QFile in(filePath);
    if( in.open( QIODevice::ReadOnly ) ) {
        QTextStream stream( &in );
        text = stream.readAll();
        in.close();
    }
    return text;
}

void FileManager::saveToFile(QString filePath, QString resultString)
{
    QFile out(filePath);
    if( out.open( QIODevice::WriteOnly ) ) {
        QTextStream stream( &out );
        stream << resultString;
        out.close();
    }
}
