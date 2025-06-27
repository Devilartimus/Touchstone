#pragma once

#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>
#include <QFont>
#include <QColor>

class PlotItem : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> points READ points WRITE setPoints NOTIFY pointsChanged)
    Q_PROPERTY(QColor gridColor MEMBER m_gridColor NOTIFY visualChanged)
    Q_PROPERTY(QColor axisColor MEMBER m_axisColor NOTIFY visualChanged)
    Q_PROPERTY(QColor textColor MEMBER m_textColor NOTIFY visualChanged)
    Q_PROPERTY(QColor lineColor MEMBER m_lineColor NOTIFY visualChanged)
    Q_PROPERTY(int numXTicks MEMBER m_numXTicks NOTIFY visualChanged)
    Q_PROPERTY(int numYTicks MEMBER m_numYTicks NOTIFY visualChanged)

public:
    explicit PlotItem(QQuickItem* parent = nullptr);

    void paint(QPainter* painter) override;

    QVector<QPointF> points() const;
    void setPoints(const QVector<QPointF>& newPoints);

signals:
    void pointsChanged();
    void visualChanged();

private:
    QVector<QPointF> m_points;
    QColor m_gridColor = Qt::lightGray;
    QColor m_axisColor = Qt::black;
    QColor m_textColor = Qt::darkGray;
    QColor m_lineColor = Qt::blue;
    int m_numXTicks = 5;
    int m_numYTicks = 5;
    QFont m_axisFont = QFont("Arial", 8);
};
