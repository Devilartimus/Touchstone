#include "DataModel.h"
#include <QtMath>
#include <limits>

DataModel::DataModel(QObject* parent) : QObject(parent) {}

QVector<QPointF> DataModel::points() const {
    return m_points;
}

void DataModel::loadFile(const QString& path) {
    emit loadingStarted();

    QVector<MeasurementPoint> rawData;
    QString error;

    if (!TouchstoneParser::parseFile(path, rawData, error)) {
        emit errorOccurred("File parsing error", error);
        emit loadingFinished();
        return;
    }

    if (rawData.isEmpty()) {
        emit errorOccurred("Data error", "No valid data found in the file");
        emit loadingFinished();
        return;
    }

    m_points.clear();
    for (const auto& point : rawData) {
        double magnitude = std::abs(point.s11);
        double logMag;

        if (magnitude <= 0.0) {
            logMag = -300.0;
        } else {
            logMag = 20.0 * std::log10(magnitude);
        }

        m_points.append(QPointF(point.frequency, logMag));
    }

    emit dataChanged();
    emit loadingFinished();
}
