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
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QString qstring_cardBack = "pictures/card/red_back.png";


public:
    QString qstring_cardSuit;
    bool bool_isFront = false;
    bool bool_isPressed = false;
    bool bool_cardPosFixable = true;
    CardPos CardPos_pos;

};

#endif // CARD_H


//card status:back front
//zvalue
//place
