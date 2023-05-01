#include "FileIOService.h"

#include <QFile>
#include <QTextStream>

void FileIOService::save(const QString& path, const std::list<int>& dataList) const {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        for (int data : dataList) {
            stream << data << '\n';
        }
    } else {
        qWarning("Could not open file for write");
    }
}

std::list<int> FileIOService::load(const QString& path) const {
    std::list<int> dataList;

    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            dataList.push_back(stream.readLine().toInt());
        }
    }
    else {
        qWarning("Could not open file for read");
    }

    return dataList;
}
