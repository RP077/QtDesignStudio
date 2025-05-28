#include "ImageLabeler.h"
#include <QPainter>
#include <QFileInfo>

std::unordered_map<std::string, LabelData> ImageLabeler::labelMap;

ImageLabeler::ImageLabeler(const QString& imagePath)
    : path(imagePath), image(imagePath) {
    setFixedSize(image.size());
}

void ImageLabeler::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, image);
    painter.setPen(Qt::red);

    if (useRectangle && drawing) {
        QRect rect(startPoint, endPoint);
        painter.drawRect(rect);
    } else {
        for (const auto& p : paintedPoints)
            painter.drawPoint(p);
    }
}

void ImageLabeler::mousePressEvent(QMouseEvent* event) {
    if (useRectangle) {
        startPoint = event->pos();
        drawing = true;
    } else {
        paintedPoints.clear();
        paintedPoints.push_back(event->pos());
        drawing = true;
    }
}

void ImageLabeler::mouseMoveEvent(QMouseEvent* event) {
    if (drawing) {
        if (useRectangle) {
            endPoint = event->pos();
        } else {
            paintedPoints.push_back(event->pos());
        }
        update();
    }
}

void ImageLabeler::mouseReleaseEvent(QMouseEvent* event) {
    drawing = false;

    QFileInfo fi(path);
    std::string key = fi.fileName().toStdString();

    if (useRectangle) {
        QRect rect(startPoint, endPoint);
        labelMap[key] = {
            LabelType::RECTANGLE,
            { rect.x(), rect.y(), rect.width(), rect.height() },
            path.toStdString()
        };
    } else {
        std::vector<int> coords;
        for (const auto& pt : paintedPoints) {
            coords.push_back(pt.x());
            coords.push_back(pt.y());
        }
        labelMap[key] = {
            LabelType::PIXELS,
            coords,
            path.toStdString()
        };
    }
}
