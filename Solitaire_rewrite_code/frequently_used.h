#ifndef FREQUENTLY_USED_H
#define FREQUENTLY_USED_H

#include <QString>
#include <QList>
#include <QRect>
#include <QPointF>
#include <QtGlobal>
#include <iostream>
#include<fstream>
#include <string>


class SuitAndNumber
{
    public:
        QString qstring_suit;
        int int_num;
};

class CardBePressed
{
    public:
        int int_Zorder;
        int int_NumInCardList;
};

QString merge_filepath(QString x);

bool decide_IsOverlapping(QPointF qpointf_posOne, QPointF qpointf_posTwo);

bool check_mousePosOnArea(QPointF qpointf_mousePos, QPointF qpointf_areaPos);

QList<QRect> get_cardSitePosAndSize();

QList<SuitAndNumber> get_cardsSuitsAndNumber();

QList<QRect> get_initalPosAndSize();

QList<QPointF> get_cardSitePos();

#endif // FREQUENTLY_USED_H

