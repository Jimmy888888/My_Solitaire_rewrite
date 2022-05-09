#ifndef CARD_H
#define CARD_H
#include <QMainWindow>
#include <QLabel>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QString>
#include <QPixmap>

#include "frequently_used.h"

class Card: public QLabel
{
public:
    Card(QMainWindow *parent, QString card_suit, int int_cardNum, int int_initalX, int int_initalY, int int_initalZ);
    void turnfront();
    void turnback();
//    void mousePressEvent(QMouseEvent *event);


public:
//    QString qstring_cardSuit;
    bool bool_isFront = false;
    bool bool_isPressed = false;
    bool bool_PosFixable = true;
    bool bool_moveabel = false;
    int int_cardNumber;
    int int_Zorder;
    int int_upperCardNum = -1;
    int int_lowerCardNum = -1;
    QPointF qpointf_bePressedPos;
    QPixmap qpixmap_cardFront;
    QPixmap qpixmap_cardBack;

};

#endif // CARD_H


//card status:back front
//zvalue
//place
