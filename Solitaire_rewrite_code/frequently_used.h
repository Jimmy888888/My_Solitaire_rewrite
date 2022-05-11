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

class WidHei
{
    public:
        int int_width;
        int int_height;
        WidHei(int w, int h);
};

class UpLow
{
    public:
        int int_upper;
        int int_lower;
};

class PosSizeUpLow
{
    public:
        UpLow uplow_ul;
        QRect qrect_posSize;
        PosSizeUpLow(int x, int y, int w, int h, int up, int low);
//        PosSizeUpLow setPosSizeUpLow(int x, int y, int w, int h, int up, int low);
};

QString merge_filepath(QString x);

bool decide_IsOverlapping(QPointF qpointf_posOne, QPointF qpointf_posTwo);

bool check_mousePosOnArea(QPointF qpointf_mousePos, QPointF qpointf_areaPos);

QList<QPointF> get_StartCardsPos();

QList<QPointF> get_StackCardsPos();

QList<QPointF> get_PlayCardsPos();

QList<PosSizeUpLow> get_CardsInitalPosSizeUpLow( QList<QPointF> qlist_startCardPos, QList<QPointF> qlist_playCardsPos, WidHei widhei_cardSize);

QList<SuitAndNumber> get_cardsSuitsAndNumber();

QList<QRect> get_cardSitePosAndSize( QList<QPointF> qlist_startCardPos, QList<QPointF> qlist_stackCardsPos, WidHei widhei_cardSize);

#endif // FREQUENTLY_USED_H

