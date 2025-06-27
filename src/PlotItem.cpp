#include "PlotItem.h"
#include <QPainter>
#include <QtMath>
#include <algorithm>
#include <cmath>

PlotItem::PlotItem(QQuickItem* parent) : QQuickPaintedItem(parent) {
    setAntialiasing(true);
}

QVector<QPointF> PlotItem::points() const {
    return m_points;
}

void PlotItem::setPoints(const QVector<QPointF>& newPoints) {
    m_points = newPoints;
    update();
    emit pointsChanged();
}

void PlotItem::paint(QPainter* painter) {
    if (m_points.isEmpty())
        return;

    const int leftPadding = 60;
    const int rightPadding = 20;
    const int topPadding = 20;
    const int bottomPadding = 50;

    const double plotWidth = width() - leftPadding - rightPadding;
    const double plotHeight = height() - topPadding - bottomPadding;

    if (plotWidth <= 0 || plotHeight <= 0)
        return;

    double minX = m_points.first().x();
    double maxX = m_points.last().x();
    double minY = m_points.first().y();
    double maxY = m_points.first().y();

    for (const auto& point : m_points) {
        minX = qMin(minX, point.x());
        maxX = qMax(maxX, point.x());
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }

    if (qFuzzyCompare(maxX, minX)) maxX = minX + 1;
    if (qFuzzyCompare(maxY, minY)) maxY = minY + 1;

    auto scaleX = [=](double x) {
        return leftPadding + (x - minX) / (maxX - minX) * plotWidth;
    };

    auto scaleY = [=](double y) {
        return topPadding + plotHeight - (y - minY) / (maxY - minY) * plotHeight;
    };

    painter->fillRect(QRectF(leftPadding, topPadding, plotWidth, plotHeight), Qt::white);

    painter->setFont(m_axisFont);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    painter->setPen(QPen(m_gridColor, 1, Qt::DotLine));
    for (int i = 0; i <= m_numXTicks; i++) {
        double value = minX + i * (maxX - minX) / m_numXTicks;
        double x = scaleX(value);

        painter->drawLine(QPointF(x, topPadding), QPointF(x, topPadding + plotHeight));

        painter->setPen(m_textColor);
        QString label;
        if (value >= 1e9) {
            label = QString("%1 GHz").arg(value / 1e9, 0, 'f', 2);
        } else if (value >= 1e6) {
            label = QString("%1 MHz").arg(value / 1e6, 0, 'f', 2);
        } else if (value >= 1e3) {
            label = QString("%1 kHz").arg(value / 1e3, 0, 'f', 2);
        } else {
            label = QString("%1 Hz").arg(value, 0, 'f', 2);
        }

        painter->drawText(QRectF(x - 50, topPadding + plotHeight + 15, 100, 20),
                          Qt::AlignHCenter | Qt::AlignTop, label);
        painter->setPen(QPen(m_gridColor, 1, Qt::DotLine));
    }

    for (int i = 0; i <= m_numYTicks; i++) {
        double value = minY + i * (maxY - minY) / m_numYTicks;
        double y = scaleY(value);

        painter->drawLine(QPointF(leftPadding, y), QPointF(leftPadding + plotWidth, y));

        painter->setPen(m_textColor);
        QString label = QString("%1 dB").arg(value, 0, 'f', 2);

        painter->drawText(QRectF(5, y - 10, leftPadding - 10, 20),
                          Qt::AlignRight | Qt::AlignVCenter, label);
        painter->setPen(QPen(m_gridColor, 1, Qt::DotLine));
    }

    painter->setPen(QPen(m_axisColor, 2));
    painter->drawLine(QPointF(leftPadding, topPadding), QPointF(leftPadding, topPadding + plotHeight));
    painter->drawLine(QPointF(leftPadding, topPadding + plotHeight),
                      QPointF(leftPadding + plotWidth, topPadding + plotHeight));

    painter->setPen(m_textColor);

    painter->drawText(QRectF(leftPadding + plotWidth / 2 - 50, topPadding + plotHeight + 35, 100, 20),
                      Qt::AlignHCenter | Qt::AlignTop, "Frequency");

    painter->save();
    painter->translate(20, topPadding + plotHeight / 2 + 50);
    painter->rotate(-90);
    painter->drawText(QRectF(-100, 0, 200, 20), Qt::AlignHCenter | Qt::AlignTop, "S11 (dB)");
    painter->restore();

    painter->setPen(QPen(m_lineColor, 2));
    QPointF prev(scaleX(m_points[0].x()), scaleY(m_points[0].y()));
    for (int i = 1; i < m_points.size(); ++i) {
        QPointF curr(scaleX(m_points[i].x()), scaleY(m_points[i].y()));
        painter->drawLine(prev, curr);
        prev = curr;
    }
}
