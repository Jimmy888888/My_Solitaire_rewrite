#include "card.h"

Card::Card(QMainWindow *parent, QString card_suit, int int_cardNum, int int_initalX, int int_initalY, int int_initalZ, int int_upper, int int_lower)
{
    this->setParent(parent);
    qpixmap_cardFront = QPixmap( merge_filepath( card_suit));
    qpixmap_cardBack = QPixmap( merge_filepath( "pictures/card/red_back.png"));
    int_cardNumber = int_cardNum;
    qpointf_bePressedPos = QPointF(int_initalX, int_initalY);
    qpointf_MoveFixPos = QPointF(0,0);
    int_Zorder = int_initalZ;
    int_upperCardNum = int_upper;
    int_lowerCardNum = int_lower;
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





