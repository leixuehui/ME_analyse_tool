#ifndef MYLABEL_H
#define MYLABEL_H

#include "global_header.h"

#include <QLabel>
#include <QList>
#include <QTextStream>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent = nullptr);
    ~MyLabel();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
   void signalObstacleInfoChanged(const QString& info,const QString& otherInfo);

public slots:
    void slotDisplayObj(const ME_DeviceData& drawObjData);
    void slotCoordinateChanged(int xIndex,int yIndex);

private:
    void drawObject(QPainter* painter, const Position *info, ObstacleData_B mapObstacleData);
    void genObstacleInfo(QString &obsInfo, const ObjInfo &obj);
    void tranferDrawObjData(const ME_DeviceData &drawObjData, QString& obsInfo,QString& otherInfo);
    void paintCoordinateSystem(QPainter* painter);

private:
	ME_DeviceData drawObjData_;
    int xRangeIndex = 0;
    int yRangeIndex = 0;
	
};

#endif // MYLABEL_H
