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
    //access card's inital pos and size
    qlist_setPosSizeUpLow = get_CardsInitalPosSizeUpLow(qlist_StartCardsPos, qlist_PlayCardsPos, widhei_cardSize);

    int int_upperCard = -1;
    int int_lowerCard = -1;
    int int_initialZorder = 0;
    //generate 52 cards, and save cards in qlist_cards
    for(int i=0; i< qlist_cardSuitsAndNumber.length(); i++)
    {
        int_initialZorder = i;
        int_upperCard = qlist_setPosSizeUpLow[i].uplow_ul.int_upper;
        int_lowerCard = qlist_setPosSizeUpLow[i].uplow_ul.int_lower;
        if(qlist_setPosSizeUpLow[i].uplow_ul.int_upper != -1)
        {
            int_upperCard = qlist_cardSuitsAndNumber[i+1].int_num;
        }
        if(qlist_setPosSizeUpLow[i].uplow_ul.int_lower != -1)
        {
            int_lowerCard = qlist_cardSuitsAndNumber[i-1].int_num;
        }
        card_cardMake =
            new Card(this, qlist_cardSuitsAndNumber[i].qstring_suit, qlist_cardSuitsAndNumber[i].int_num,
                     qlist_setPosSizeUpLow[i].qrect_posSize.x(), qlist_setPosSizeUpLow[i].qrect_posSize.y(),
                     int_initialZorder, int_upperCard, int_lowerCard);
        card_cardMake->setGeometry(qlist_setPosSizeUpLow[i].qrect_posSize);
        card_cardMake->show();
        qlist_cards << (card_cardMake);
        qDebug() << card_cardMake->qpointf_bePressedPos << " " << i  << " " <<card_cardMake->int_cardNumber << " " <<  card_cardMake->int_upperCardNum<< " " << card_cardMake->int_lowerCardNum;
    }

    //access 7 cards site's pos
//    qlist_cardSitePos = get_PlayCardsPos();
    qlist_cardPlacedPos = get_PlayCardsPos();
}

void Table::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "table Press";

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
                CardBePressed_PressedCard.int_Zorder = qlist_cards[i]->int_Zorder;
                CardBePressed_PressedCard.int_NumInCardList = i;
            }
        }
    }

    //Zorder >=0 means card is be pressed, set card state
    if(CardBePressed_PressedCard.int_Zorder >= 0 )
    {
        int i = CardBePressed_PressedCard.int_NumInCardList;
        int_maxZorder++;
        qlist_cards[i]->qpointf_bePressedPos = qlist_cards[i]->pos();
        qlist_cards[i]->bool_isPressed = true;
        qlist_cards[i]->bool_moveabel = true;
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
        //if mouse press card start area (65,20)
        if( check_mousePosOnArea(event->pos(), qlist_StartCardsPos[0]) == true )
        {
            //put cards that on (130,20) back to (65,20),
            //and for keeping cards zorder, raise() cards int_Zorder
            for(int i=0; i < qlist_cards.length(); i++)
            {
                if( qlist_cards[i]->pos() == qlist_StartCardsPos[1])
                {
                    int_maxZorder++;
                    qlist_cards[i]->move(qlist_StartCardsPos[0].x(), qlist_StartCardsPos[0].y());
                    qlist_cards[i]->turnback();
                    qlist_cards[i]->raise();
                    qlist_cards[i]->int_Zorder = int_maxZorder;
                }
            }
        }
    }
}

void Table::mouseReleaseEvent(QMouseEvent *event)
{
//    qDebug() << "table Release";

    //decide where cards can be placed

    //update qlist_cardPlacedPos
    qlist_cardPlacedPos = get_PlayCardsPos();
    for(int i=0; i < qlist_cards.length(); i++)
    {
        for(int j=0; j < qlist_cardPlacedPos.length(); j++)
        {
            if( qlist_cards[i]->pos().x() == qlist_cardPlacedPos[j].x())
            {
                if( qlist_cards[i]->pos().y() >= qlist_cardPlacedPos[j].y())
                {
                    qlist_cardPlacedPos[j] = qlist_cards[i]->pos();
                }
            }
        }
    }

    //add check number
    for(int i=0; i < qlist_cards.length(); i++)
    {
        bool bool_canNotPlaced = true;
        bool bool_emptyPlace = true;
        if(qlist_cards[i]->bool_isPressed == true && qlist_cards[i]->bool_moveabel == true)
        {
            //chick if card is overlapping with 1 of any 4 cardPlacedPos
            for(int j=0; j < qlist_cardPlacedPos.length(); j++)
            {
                if( decide_IsOverlapping(qlist_cards[i]->pos(), qlist_cardPlacedPos[j]) == true )
                {
                    //place the overlapping card on qlist_cardPlacedPos[j] under 25
                    qlist_cards[i]->move(qlist_cardPlacedPos[j].x(), qlist_cardPlacedPos[j].y() + 25);
                    for(int k=0; k < qlist_cards.length(); k++)
                    {
                        //check whether is there any card on qlist_cardPlacedPos[j]
                        if(qlist_cards[k]->bool_isPressed == false && qlist_cards[k]->pos() == qlist_cardPlacedPos[j] )
                        {
                            /*check whether card that on (qlist_cardPlacedPos[j].x(), qlist_cardPlacedPos[j].y() + 25)
                            can match card that on (qlist_cardPlacedPos[j].x(), qlist_cardPlacedPos[j].y() ) */
                            if( (qlist_cards[i]->int_cardNumber % 13) - (qlist_cards[k]->int_cardNumber % 13) == -1 )
                            {
                                //0 12    13 25    26 38    39 51
                                //0  1  0  14  0  27  0  40
                                //13 1  13 14  13 27  13 40
                                //result :
                                //if (qlist_cards[i]->int_cardNumber % 13) - (qlist_cards[k]->int_cardNumber % 13) == -1
                                //then qlist_cards[i] match qlist_cards[k]
                                qlist_cards[i]->int_lowerCardNum = qlist_cards[k]->int_cardNumber;
                                qlist_cards[k]->int_upperCardNum = qlist_cards[i]->int_cardNumber;
                                bool_canNotPlaced = false;
                            }


                            bool_emptyPlace = false;
                            //qDebug() << qlist_cardPlacedPos;

                        }
                    }
                    //if there is no another card on qlist_cardPlacedPos[j], place the overlapping card on qlist_cardPlacedPos[j]
                    if(qlist_cards[i]->bool_isPressed == true && qlist_cardPlacedPos[j].y() == 20 && bool_emptyPlace == true)
                    {
                        qlist_cards[i]->move(qlist_cardPlacedPos[j].x(), qlist_cardPlacedPos[j].y() );
                        qlist_cards[i]->int_upperCardNum = -1;
                        qlist_cards[i]->int_lowerCardNum = -1;
                        //qDebug() << qlist_cards[i]->int_cardNumber;
                        bool_canNotPlaced = false;
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


//    qDebug() << qlist_cardPlacedPos;

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
