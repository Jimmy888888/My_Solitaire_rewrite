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

    //access 7 cards site's pos
    qlist_PlaceCardPos = get_PlayCardsPos();
}

void Table::mousePressEvent(QMouseEvent *event)
{
    //check is any card be pressed
    CardBePressed_PressedCard.int_Zorder = -1;
    for(int i=0; i < qlist_cards.length(); i++)
    {
        //check how many cards are on the mouse pressed pos
        if( check_mousePosOnArea(event->pos(), qlist_cards[i]->pos()) == true )
        {
            //only the biggest Zorder card can be choosen
            if(CardBePressed_PressedCard.int_Zorder <= qlist_cards[i]->int_Zorder)
            {
                //qlist_cards[i]->int_upperCardNum == -1 means no card place on qlist_cards[i]
                if(qlist_cards[i]->int_upperCardNum == -1)
                {
                    CardBePressed_PressedCard.int_Zorder = qlist_cards[i]->int_Zorder;
                    CardBePressed_PressedCard.int_NumInCardList = i;
                }

            }
        }
    }

    //CardBePressed_PressedCard.Zorder >=0 means card is be pressed, set card state
    if(CardBePressed_PressedCard.int_Zorder >= 0 )
    {
        int i = CardBePressed_PressedCard.int_NumInCardList;
        int_maxZorder++;
        qlist_cards[i]->qpointf_bePressedPos = qlist_cards[i]->pos();
        qlist_cards[i]->bool_isPressed = true;
        qlist_cards[i]->bool_moveabel = true;
        qlist_cards[i]->bool_isFront = true;
        qlist_cards[i]->int_Zorder = int_maxZorder;
        qlist_cards[i]->raise();
        qlist_cards[i]->turnfront();

        //decide whether card is moveabel
        if(qlist_cards[i]->pos() == qlist_StartCardsPos[0])
        {
            qlist_cards[i]->bool_moveabel = false;
            qlist_cards[i]->move(qlist_StartCardsPos[1].x(), qlist_StartCardsPos[1].y());
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
    //update qlist_PlaceCardPos
    qlist_PlaceCardPos = get_PlayCardsPos();
    //intArray_PlaceCardNum recorder card order num that in qlist_cards for every qlist_PlaceCardPos
    int intArray_PlaceCardNum[7];
    //initialize intArray_PlaceCardNum, -1 means no card
    std::fill_n(intArray_PlaceCardNum, 7, -1);

    //record the uppermost card pos for every qlist_PlaceCardPos[j]
    for(int i=0; i < qlist_cards.length(); i++)
    {
        for(int j=0; j < qlist_PlaceCardPos.length(); j++)
        {
            if( qlist_cards[i]->pos().x() == qlist_PlaceCardPos[j].x())
            {
                if( qlist_cards[i]->pos().y() >= qlist_PlaceCardPos[j].y())
                {
                    //record the uppermost card pos for every qlist_PlaceCardPos[j]
                    qlist_PlaceCardPos[j] = qlist_cards[i]->pos();
                    //also record card order num that in qlist_cards
                    intArray_PlaceCardNum[j] = i;
                }
            }
        }
    }

    //
    for(int i=0; i < qlist_cards.length(); i++)
    {
        bool bool_canNotPlaced = true;

        if(qlist_cards[i]->bool_isPressed == true && qlist_cards[i]->bool_moveabel == true)
        {
            //chick if card is overlapping with 1 of any 4 cardPlacedPos
            for(int j=0; j < qlist_PlaceCardPos.length(); j++)
            {
                if( decide_IsOverlapping(qlist_cards[i]->pos(), qlist_PlaceCardPos[j]) == true )
                {
                    //means no card on qlist_PlaceCardPos[j]
                    if(intArray_PlaceCardNum[j] == -1)
                    {
                        //if there is no card on qlist_PlaceCardPos[j], place the overlapping card on qlist_PlaceCardPos[j]
                        if(qlist_cards[i]->bool_isPressed == true && qlist_PlaceCardPos[j].y() == qlist_PlayCardsPos[0].y())
                        {
                            //set qlist_cards[i]->int_lowerCardNum upper =-1
                            if(qlist_cards[i]->int_lowerCardNum >= 0)
                            {
                                qlist_cards[ qlist_cards[i]->int_lowerCardNum ]->int_upperCardNum = -1;
                            }
                            qlist_cards[i]->move(qlist_PlaceCardPos[j].x(), qlist_PlaceCardPos[j].y() );
                            qlist_cards[i]->int_upperCardNum = -1;
                            qlist_cards[i]->int_lowerCardNum = -1;
                            //qDebug() << qlist_cards[i]->int_cardNumber;
                            bool_canNotPlaced = false;
                        }
                    }
                    //means there is card on qlist_PlaceCardPos[j]
                    else if(intArray_PlaceCardNum[j] >= 0)
                    {
                        /*check whether card that on (qlist_PlaceCardPos[j].x(), qlist_PlaceCardPos[j].y() + 25)
                        can match card that on (qlist_PlaceCardPos[j].x(), qlist_PlaceCardPos[j].y() ) */
                        if( (qlist_cards[i]->int_cardNumber % 13) - (qlist_cards[intArray_PlaceCardNum[j]]->int_cardNumber % 13) == -1 )
                        {
                            //0 12    13 25    26 38    39 51
                            //0  1  0  14  0  27  0  40
                            //13 1  13 14  13 27  13 40
                            //result :
                            //if (qlist_cards[i]->int_cardNumber % 13) - (qlist_cards[k]->int_cardNumber % 13) == -1
                            //then qlist_cards[i] match qlist_cards[k]

                            //set card that lower than qlist_cards[i] previously upper =-1
                            if(qlist_cards[i]->int_lowerCardNum >= 0)
                            {
                                qlist_cards[ qlist_cards[i]->int_lowerCardNum ]->int_upperCardNum = -1;
                            }
                            qlist_cards[i]->move(qlist_PlaceCardPos[j].x(), qlist_PlaceCardPos[j].y() + 25);
                            qlist_cards[i]->int_lowerCardNum = intArray_PlaceCardNum[j];
                            qlist_cards[intArray_PlaceCardNum[j]]->int_upperCardNum = i;

                            bool_canNotPlaced = false;

                        }
                        //qDebug() << qlist_PlaceCardPos;
                    }
                    break;
                }
            }
            //send card back to its originally pos
            if( bool_canNotPlaced == true)
            {
                qlist_cards[i]->move(qlist_cards[i]->qpointf_bePressedPos.x(), qlist_cards[i]->qpointf_bePressedPos.y());
            }
        }
    }

    //reset cards states
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
    //let card move with mouse
    for(int i=0; i<qlist_cards.length(); i++)
    {
        if(qlist_cards[i]->bool_isPressed == true && qlist_cards[i]->bool_moveabel == true)
        {
            if(qlist_cards[i]->bool_PosFixable == true)
            {
                qpointf_fixpos = event->pos() - qlist_cards[i]->qpointf_bePressedPos;
                qlist_cards[i]->bool_PosFixable = false;
            }
            qpointf_movepos = event->pos() - qpointf_fixpos;
            qlist_cards[i]->move(qpointf_movepos.x(), qpointf_movepos.y());
        }
    }

}

//card moveabel ,who owns pressevent, add clickevent?
