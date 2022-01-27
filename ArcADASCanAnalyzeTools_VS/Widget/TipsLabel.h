#ifndef TIPSLABEL_H
#define TIPSLABEL_H

#include "global_header.h"

#include <QLabel>

class TipsLabel : public QLabel
{
    Q_OBJECT
public:
    TipsLabel(QWidget *parent = nullptr);
    static QString getObjNameByType(int typeId) ;
    static QColor getColorByType(int typeId);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    static QList<ObjType> objTypes;

};

#endif // TIPSLABEL_H
