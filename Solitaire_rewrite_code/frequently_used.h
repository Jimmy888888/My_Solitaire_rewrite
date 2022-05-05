#ifndef FREQUENTLY_USED_H
#define FREQUENTLY_USED_H

#include <QString>
#include <QList>
#include <QRect>
#include <QPointF>
#include <iostream>
#include<fstream>
#include <string>


class SuitAndNumber
{
    public:
        QString qstring_suit;
        int int_num;
};

QString merge_filepath(QString x);

QList<QRect> get_cardSitePosAndSize();

QList<SuitAndNumber> get_cardsSuitsAndNumber();

QList<QRect> get_initalPosAndSize();

QList<QPointF> get_cardSitePos();

#endif // FREQUENTLY_USED_H

