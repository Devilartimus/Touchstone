#include "TouchstoneParser.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

bool TouchstoneParser::parseFile(const QString& path, QVector<MeasurementPoint>& outData, QString& error) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = "Cannot open file: " + path;
        return false;
    }

    QTextStream in(&file);
    outData.clear();
    int lineCount = 0;
    bool dataSectionStarted = false;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        lineCount++;

        if (line.isEmpty() || line.startsWith("#") || line.startsWith("!")) {
            continue;
        }

        if (!dataSectionStarted && (line.startsWith("I") || line.contains("Freq"))) {
            dataSectionStarted = true;
            continue;
        }

        if (line.startsWith("I")) {
            continue;
        }

        QRegularExpression re("[-+]?\\d*\\.?\\d+([eE][-+]?\\d+)?");
        QRegularExpressionMatchIterator matches = re.globalMatch(line);
        QVector<double> numbers;

        while (matches.hasNext()) {
            QRegularExpressionMatch match = matches.next();
            bool ok;
            double num = match.captured().toDouble(&ok);
            if (ok) numbers.append(num);
        }

        if (numbers.size() < 3) {
            error = QString("Invalid data format at line %1: %2").arg(lineCount).arg(line);
            return false;
        }

        outData.append({numbers[0], std::complex<double>(numbers[1], numbers[2])});
    }

    if (outData.isEmpty()) {
        error = "No valid data points found in the file";
        return false;
    }

    return true;
}
