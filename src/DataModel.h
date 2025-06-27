#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>

#include "TouchstoneParser.h"

class DataModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> points READ points NOTIFY dataChanged)

public:
    explicit DataModel(QObject* parent = nullptr);

    Q_INVOKABLE void loadFile(const QString& path);
    QVector<QPointF> points() const;

signals:
    void errorOccurred(const QString& title, const QString& message);
    void dataChanged();
    void loadingStarted();
    void loadingFinished();

private:
    QVector<QPointF> m_points;
};
