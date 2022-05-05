#include "card.h"

Card::Card(QMainWindow *parent, QString card_suit)
{
    this->setParent(parent);
    qpixmap_cardFront = QPixmap( merge_filepath( card_suit));
    qpixmap_cardBack = QPixmap( merge_filepath( "pictures/card/red_back.png"));
    this->setPixmap(qpixmap_cardBack);
}

void Card::turnfront()
{
    this->setPixmap(qpixmap_cardFront);
}

void Card::turnback()
{
    this->setPixmap(qpixmap_cardBack);
}

void Card::mousePressEvent(QMouseEvent *event)
{
    this->turnfront();
    this->bool_isPressed = true;
    //record the pos when card is pressed
    qpointf_bePressedPos.setX(this->pos().x());
    qpointf_bePressedPos.setY(this->pos().y());
}

void Card::mouseReleaseEvent(QMouseEvent *event)
{
    this->bool_isPressed = false;
    this->bool_cardPosFixable = true;
//    qDebug() << "card released";
}

