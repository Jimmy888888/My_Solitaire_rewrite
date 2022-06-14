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
#include <QThread>
#include <QDebug>
#include <QLabel>


class SuitAndNumber
{
    public:
        QString qstring_suit;
        int int_num;
};

class CardBePressed
{
    public:
        int int_Zorder = -1;
        //card order number in qlist_cards
        int int_CardONum = -1;
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
};

class PosNum
{
    public:
        QPointF qpointf_pos = QPointF(0,0);
        //card order number in qlist_cards
        int int_cardONum=0;
};
//card order num and move fix pos
class ONumFixPos
{
    public:
        QPointF qpointf_fixpos = QPointF(0,0);
        //card order number in qlist_cards
        int int_cardONum=0;
};

QString merge_filepath(QString x);

bool decide_IsOverlapping(QPointF qpointf_posOne, QPointF qpointf_posTwo);

bool check_mousePosOnArea(QPointF qpointf_mousePos, QPointF qpointf_areaPos);

QList<QPointF> get_StartCardsArea ();

QList<QPointF> get_StackCardsArea ();

QList<QPointF> get_PlayCardsArea ();

QList<PosSizeUpLow> get_CardsInitalPosAndSizeAndUpperCardONumAndLowerCardONum( QList<QPointF> qlist_StartCardsArea, QList<QPointF> qlist_PlayCardsArea, WidHei widhei_cardSize);

QList<SuitAndNumber> get_cardsSuitsAndNumber();

QList<QRect> get_cardSitePosAndSize( QList<QPointF> qlist_StartCardsArea, QList<QPointF> qlist_StackCardsArea, WidHei widhei_cardSize);

QList<PosNum> get_PlayCardPosAndNum( QList<QPointF> qlist_allCardPos, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_PlayCardsArea );

#endif // FREQUENTLY_USED_H

