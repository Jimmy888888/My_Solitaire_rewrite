#include "table.h"

Table::Table(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Game Start");
    this->setWindowIcon( QIcon( merge_filepath("pictures/icon.png")));
    this->setMinimumSize(1200,900);
    this->setMaximumSize(1200,900);
    this->setStyleSheet("QMainWindow {background: 'green';}");

    //access three kinds cards pos
    qlist_StartCardsPos = get_StartCardsPos();
    qlist_StackCardsPos = get_StackCardsPos();
    qlist_PlayCardsPos = get_PlayCardsPos();
    //access cardSize
    WidHei widhei_cardSize = WidHei(110, 160);


    //access card site's pos and size, and make 6 card sites on table, and save card sites in qlabel_cardSite
    qlist_setCardSitePosAndsize = get_cardSitePosAndSize(qlist_StartCardsPos, qlist_StackCardsPos, widhei_cardSize);
    QPixmap qpixmap_cardSite(merge_filepath("pictures/card_site.png"));
    for(int i=0; i < qlist_setCardSitePosAndsize.length(); i++)
    {
        qlabel_cardSite = new QLabel(this);
        qlabel_cardSite->setGeometry(qlist_setCardSitePosAndsize[i]);
        qlabel_cardSite->setPixmap(qpixmap_cardSite);
        qlist_cardSite << qlabel_cardSite;
    }


    //access card's suit filename, and card's number
    qlist_cardSuitsAndNumber = get_cardsSuitsAndNumber();
    //access card's inital pos and size and upper card num and lower card num
    qlist_setPosSizeUpLow = get_CardsInitalPosSizeUpLow(qlist_StartCardsPos, qlist_PlayCardsPos, widhei_cardSize);

    int int_initialZorder = 0;
    //generate 52 cards, and save cards in qlist_cards
    for(int i=0; i< qlist_cardSuitsAndNumber.length(); i++)
    {
        int_initialZorder = i;

        card_cardMake =
            new Card(this,
                     qlist_cardSuitsAndNumber[i].qstring_suit,
                     qlist_cardSuitsAndNumber[i].int_num,
                     qlist_setPosSizeUpLow[i].qrect_posSize.x(),
                     qlist_setPosSizeUpLow[i].qrect_posSize.y(),
                     int_initialZorder,
                     qlist_setPosSizeUpLow[i].uplow_ul.int_upper,
                     qlist_setPosSizeUpLow[i].uplow_ul.int_lower);

        card_cardMake->setGeometry(qlist_setPosSizeUpLow[i].qrect_posSize);
        card_cardMake->show();
        qlist_cards << (card_cardMake);
        //qDebug() << card_cardMake->qpointf_bePressedPos << " " << i  << " " <<card_cardMake->int_cardNumber << " " <<
        //            card_cardMake->int_upperCardNum<< " " << card_cardMake->int_lowerCardNum << card_cardMake->bool_isFront;
    }

}

void Table::mousePressEvent(QMouseEvent *event)
{
    //check is any card be pressed, if there is, record its card zorder and card order number in qlist_cards with CardBePressed
    CardBePressed_PressedCard = get_thePressedCard(qlist_cards, event);

    //StackCardPos : up=-1 low=-1 zorder, check cardNum

    if(check_mousePosOnArea(event->pos(), qlist_StartCardsPos[0]) == true)
    {
        //
    }
    else
    {
        //
    }

    //CardBePressed_PressedCard.int_Zorder >=0 means card is be pressed, set card state
    if(CardBePressed_PressedCard.int_Zorder >= 0 )
    {
        int int_numCardList = CardBePressed_PressedCard.int_NumInCardList;
        int int_tempUpCardNum = int_numCardList;
        //the pressed card and its upper cards will be record in qlist_MoveAbelCards, int_tempUpCardNum == -1 means no upper card
        while(int_tempUpCardNum > -1)
        {
            qlist_MoveAbelCards << int_tempUpCardNum;
            int_tempUpCardNum = qlist_cards[ int_tempUpCardNum ]->int_upperCardNum;
        }
        //if qlist_MoveAbelCards.length()=0 this for loop wont run
        for(int i=0; i < qlist_MoveAbelCards.length(); i++)
        {
            //set card state
            int_maxZorder++;
            qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos = qlist_cards[ qlist_MoveAbelCards[i] ]->pos();
            //qlist_cardMoveFixPos is used on void Table::mouseMoveEvent(QMouseEvent *event)
            qlist_cardMoveFixPos << ( event->pos() - qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos );
            qlist_cards[ qlist_MoveAbelCards[i] ]->bool_isPressed = true;
            qlist_cards[ qlist_MoveAbelCards[i] ]->bool_moveabel = true;
            qlist_cards[ qlist_MoveAbelCards[i] ]->bool_isFront = true;
            qlist_cards[ qlist_MoveAbelCards[i] ]->int_Zorder = int_maxZorder;
            qlist_cards[ qlist_MoveAbelCards[i] ]->raise();
            qlist_cards[ qlist_MoveAbelCards[i] ]->turnfront();
        }

        //decide whether card is moveabel
        if(qlist_cards[int_numCardList]->pos() == qlist_StartCardsPos[0])
        {
            qlist_cards[int_numCardList]->bool_moveabel = false;
            qlist_cards[int_numCardList]->move(qlist_StartCardsPos[1].x(), qlist_StartCardsPos[1].y());
        }
    }
    //CardBePressed_PressedCard.int_Zorder == -1 means no cards is be pressed
    else if(CardBePressed_PressedCard.int_Zorder == -1)
    {
        //if mouse press card start area qlist_StartCardsPos[0] (65,20)
        if( check_mousePosOnArea(event->pos(), qlist_StartCardsPos[0]) == true )
        {
            //put cards that on qlist_StartCardsPos[1] (225,20) back to qlist_StartCardsPos[0] (65,20),
            //and for keeping cards zorder, do raise() and increase cards int_Zorder
            for(int i=0; i < qlist_cards.length(); i++)
            {
                if( qlist_cards[i]->pos() == qlist_StartCardsPos[1])
                {
                    int_maxZorder++;
                    qlist_cards[i]->move(qlist_StartCardsPos[0].x(), qlist_StartCardsPos[0].y());
                    qlist_cards[i]->turnback();
                    qlist_cards[i]->raise();
                    qlist_cards[i]->bool_isFront = false;
                    qlist_cards[i]->int_Zorder = int_maxZorder;
                }
            }
        }
    }
}

void Table::mouseReleaseEvent(QMouseEvent *event)
{
    //make sure has card be pressed, and it can be moved
    if( qlist_MoveAbelCards.length() > 0  &&  qlist_cards[ qlist_MoveAbelCards[0] ]->bool_moveabel == true)
    {
        //change card's pos, upper num, lower num according to PlayCards rule
        qlist_cards = releaseOn_PlayCards(qlist_cards, qlist_MoveAbelCards);
    }

    //reset cards states and qlist
    qlist_MoveAbelCards.clear();
    qlist_cardMoveFixPos.clear();
    for(int i=0; i < qlist_cards.length(); i++)
    {
        if(qlist_cards[i]->bool_isPressed == true)
        {
            qlist_cards[i]->bool_isPressed = false;
        }

        if(qlist_cards[i]->bool_PosFixable == false)
        {
            qlist_cards[i]->bool_PosFixable = true;
        }
    }
}

void Table::mouseMoveEvent(QMouseEvent *event)
{
    //if qlist_MoveAbelCards.length()=0 this for loop wont run
    for(int i=0; i< qlist_MoveAbelCards.length(); i++)
    {
        if(qlist_cards[ qlist_MoveAbelCards[i] ]->bool_moveabel == true)
        {
            qpointf_movepos = event->pos() - qlist_cardMoveFixPos[i];
            qlist_cards[ qlist_MoveAbelCards[i] ]->move(qpointf_movepos.x(), qpointf_movepos.y());
        }
    }
}

//check is any card be pressed, if there is, record its card zorder and card order number in qlist_cards with CardBePressed
CardBePressed Table:: get_thePressedCard(QList<Card *> qlist_cards, QMouseEvent *event)
{
    CardBePressed CardBePressed_temp;
    //check is any card be pressed, -1 means no card be pressed
    CardBePressed_temp.int_Zorder = -1;
    for(int i=0; i < qlist_cards.length(); i++)
    {
        //check how many cards are on the mouse pressed pos
        if( check_mousePosOnArea(event->pos(), qlist_cards[i]->pos()) == true )
        {
            //only the biggest Zorder card can be choosen
            if(CardBePressed_temp.int_Zorder <= qlist_cards[i]->int_Zorder)
            {
                //qlist_cards[i]->int_upperCardNum == -1 means no card place on qlist_cards[i]
                if(qlist_cards[i]->int_upperCardNum == -1)
                {
                    CardBePressed_temp.int_Zorder = qlist_cards[i]->int_Zorder;
                    CardBePressed_temp.int_NumInCardList = i;
                }
                else if(qlist_cards[i]->int_upperCardNum >= 0 && qlist_cards[i]->bool_isFront == true)
                {
                    CardBePressed_temp.int_Zorder = qlist_cards[i]->int_Zorder;
                    CardBePressed_temp.int_NumInCardList = i;
                }
            }
        }
    }
    return CardBePressed_temp;
}

QList<Card *> Table:: releaseOn_PlayCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards)
{
    //get all card pos in qlist_cards
    QList<QPointF> qlist_allCardPos;
    for(int i=0; i < qlist_cards.length(); i++)
    {
        qlist_allCardPos << QPointF(qlist_cards[i]->pos().x(), qlist_cards[i]->pos().y());
    }
    //get every uppermost card's Pos and order Num in qlist_cards for 7 PlayCardPos
    QList<PosNum> qlist_PlayCardPosAndNum = get_PlayCardPosAndNum(qlist_allCardPos, qlist_MoveAbelCards, get_PlayCardsPos());

    bool bool_canNotPlaced = true;
    //check if card is overlapping with 1 of any 7 PlayCardPos
    for(int i=0; i < qlist_PlayCardPosAndNum.length(); i++)
    {
        if( decide_IsOverlapping(qlist_cards[ qlist_MoveAbelCards[0] ]->pos(), qlist_PlayCardPosAndNum[i].qpointf_pos) == true )
        {
            //means no card on qlist_PlayCardPosAndNum[i].qpointf_pos
            if(qlist_PlayCardPosAndNum[i].int_cardNum == -1)
            {
                if(true)// qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber % 13 == 12
                {
                    //if qlist_cards[ qlist_MoveAbelCards[0] ] has a lower card before
                    if( qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardNum >= 0)
                    {
                        //qlist_cards[ qlist_MoveAbelCards[0] ] will move to new pos, so the the lower card has no upper card now
                        qlist_cards[ qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardNum ]->int_upperCardNum = -1;
                        //there is no card lower than qlist_cards[ qlist_MoveAbelCards[0] ]
                        qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardNum = -1;
                    }
                    //move cards to new pos qlist_PlayCardPos[i]
                    for(int j = 0; j < qlist_MoveAbelCards.length(); j++)
                    {
                        qlist_cards[ qlist_MoveAbelCards[j] ]->move( qlist_PlayCardPosAndNum[i].qpointf_pos.x(), qlist_PlayCardPosAndNum[i].qpointf_pos.y());
                        qlist_PlayCardPosAndNum[i].qpointf_pos = QPointF(qlist_PlayCardPosAndNum[i].qpointf_pos.x(), qlist_PlayCardPosAndNum[i].qpointf_pos.y() +25);
                    }
                    bool_canNotPlaced = false;
                    break;
                }
            }
            //means there is card on qlist_PlayCardPos[j], and the card has been turn front
            else if( qlist_PlayCardPosAndNum[i].int_cardNum >= 0 && qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardNum ]->bool_isFront == true)
            {
                /*check whether card that on (qlist_PlayCardPos[j].x(), qlist_PlayCardPos[j].y() + 25)
                can match card that on (qlist_PlayCardPos[j].x(), qlist_PlayCardPos[j].y() ) */
                if( (qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber % 13) - (qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardNum ]->int_cardNumber % 13) == -1 )
                {
                    //0 12    13 25    26 38    39 51
                    //0  1  0  14  0  27  0  40
                    //13 1  13 14  13 27  13 40
                    //result :
                    //if (qlist_cards[i]->int_cardNumber % 13) - (qlist_cards[k]->int_cardNumber % 13) == -1
                    //then qlist_cards[i] match qlist_cards[k]

                    //if qlist_cards[ qlist_MoveAbelCards[0] ] has a lower card before
                    if(qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardNum >= 0)
                    {
                        //qlist_cards[ qlist_MoveAbelCards[0] ] will move to new pos, so the the lower card has no upper card now
                        qlist_cards[ qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardNum ]->int_upperCardNum = -1;
                    }
                    //qlist_cards[ qlist_MoveAbelCards[0] ] has new lower card qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardNum ]
                    qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardNum = qlist_PlayCardPosAndNum[i].int_cardNum;
                    qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardNum ]->int_upperCardNum = qlist_MoveAbelCards[0];
                    //move cards to new pos qlist_PlayCardPos[i]
                    for(int j = 0; j < qlist_MoveAbelCards.length(); j++)
                    {
                        qlist_cards[ qlist_MoveAbelCards[j] ]->move( qlist_PlayCardPosAndNum[i].qpointf_pos.x(), qlist_PlayCardPosAndNum[i].qpointf_pos.y() +25);
                        qlist_PlayCardPosAndNum[i].qpointf_pos = QPointF(qlist_PlayCardPosAndNum[i].qpointf_pos.x(), qlist_PlayCardPosAndNum[i].qpointf_pos.y() +25);
                    }
                    bool_canNotPlaced = false;
                    break;
                }
            }
        }
    }
    //send card back to its originally pos
    if( bool_canNotPlaced == true)
    {
        for(int i=0; i < qlist_MoveAbelCards.length(); i++)
        {
            qlist_cards[ qlist_MoveAbelCards[i] ]->move(qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos.x(),
                                                        qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos.y());
        }
    }
    return qlist_cards;
}
