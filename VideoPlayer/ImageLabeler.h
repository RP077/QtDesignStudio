
#pragma once
#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <vector>
#include <unordered_map>
#include <string>

enum class LabelType { RECTANGLE, PIXELS };

struct LabelData {
    LabelType type;
    std::vector<int> data;
    std::string imagePath;
};

class ImageLabeler : public QWidget {
    Q_OBJECT

public:
    explicit ImageLabeler(const QString& imagePath);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    QPixmap image;
    QString path;
    bool drawing = false;
    bool useRectangle = true;

    QPoint startPoint;
    QPoint endPoint;
    std::vector<QPoint> paintedPoints;

    void saveLabel();

    static std::unordered_map<std::string, LabelData> labelMap;
};
