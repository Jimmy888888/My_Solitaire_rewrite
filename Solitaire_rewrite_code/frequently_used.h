#ifndef FREQUENTLY_USED_H
#define FREQUENTLY_USED_H

#include <QString>
#include <QList>
#include <iostream>
#include<fstream>
#include <string>

class CardPos
{
    public:
        int x;
        int y;
};

class SuitAndNumber
{
    public:
        QString qstring_suit;
        int int_num;
};

class PosAndSize
{
    public:
        int x;
        int y;
        int width;
        int height;
        PosAndSize(int x,int y,int w,int h);
};

QString merge_filepath(QString x);

QList<SuitAndNumber> get_cardsSuitsAndNumber();

QList<PosAndSize> get_initalPosAndSize();

QList<PosAndSize> get_cardSitePosAndSize();

#endif // FREQUENTLY_USED_H

