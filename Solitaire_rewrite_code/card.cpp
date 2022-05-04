#include "card.h"

Card::Card(QMainWindow *parent, QString card_suit)
{
    this->setParent(parent);
    QPixmap qpixmap_cardsuit( merge_filepath( card_suit));
    this->setPixmap(qpixmap_cardsuit);
}

void Card::mousePressEvent(QMouseEvent *event)
{
    this->bool_isPressed = true;
    //record the pos when card is pressed
    CardPos_pos.x = this->pos().x();
    CardPos_pos.y = this->pos().y();
}

void Card::mouseReleaseEvent(QMouseEvent *event)
{
    this->bool_isPressed = false;
    this->bool_cardPosFixable = true;
    qDebug() << "card released";
}



