#pragma once

#include <QString>
#include <QVector>
#include <complex>
#include <QRegularExpression>

struct MeasurementPoint {
    double frequency;
    std::complex<double> s11;
};

class TouchstoneParser {
public:
    static bool parseFile(const QString& path, QVector<MeasurementPoint>& outData, QString& error);
};
