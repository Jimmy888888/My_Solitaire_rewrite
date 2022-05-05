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
    Card(QMainWindow *parent, QString card_suit);
    void turnfront();
    void turnback();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


public:
    QString qstring_cardSuit;
    bool bool_isFront = false;
    bool bool_isPressed = false;
    bool bool_cardPosFixable = true;
    int int_cardNumber;
    CardPos CardPos_pos;
    QPixmap qpixmap_cardFront;
    QPixmap qpixmap_cardBack;
};

#endif // CARD_H


//card status:back front
//zvalue
//place
