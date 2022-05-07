#include "table.h"

Table::Table(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Game Start");
    this->setWindowIcon( QIcon( merge_filepath("pictures/icon.png")));
    this->setMinimumSize(900,700);
    this->setMaximumSize(900,700);
    this->setStyleSheet("QMainWindow {background: 'green';}");


    //access card site's pos and size, and make 5 card sites on table, and save card sites in qlabel_cardSite
    qlist_setCardSitePosAndsize = get_cardSitePosAndSize();
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
    qlist_setPosAndsize = get_initalPosAndSize();

    //generate 52 cards, and save cards in qlist_cards
    for(int i=0; i< qlist_cardSuitsAndNumber.length(); i++)
    {
        card_cardMake =
            new Card(this, qlist_cardSuitsAndNumber[i].qstring_suit, qlist_cardSuitsAndNumber[i].int_num,
                     qlist_setPosAndsize[i].x(), qlist_setPosAndsize[i].y(), i);
        card_cardMake->setGeometry(qlist_setPosAndsize[i]);
        card_cardMake->show();
        qlist_cards << (card_cardMake);
    }

    int_maxZorder = 51;

    //access 4 cards site's pos
    qlist_cardSitePos = get_cardSitePos();
    qlist_cardPlacedPos = get_cardSitePos();
}

void Table::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "table Press";

    //check whether card is press
    CardBePressed_PCard.int_Zorder = -1;
    for(int i=0; i < qlist_cards.length(); i++)
    {
        if( check_mousePosOnArea(event->pos(), qlist_cards[i]->pos()) == true )
        {
            if(CardBePressed_PCard.int_Zorder <= qlist_cards[i]->int_Zorder)
            {
                CardBePressed_PCard.int_Zorder = qlist_cards[i]->int_Zorder;
                CardBePressed_PCard.int_NumInCardList = i;
            }
        }
    }
    if(CardBePressed_PCard.int_Zorder >= 0 )
    {
        int i = CardBePressed_PCard.int_NumInCardList;
        int_maxZorder++;
        qlist_cards[i]->qpointf_bePressedPos = qlist_cards[i]->pos();
        qlist_cards[i]->bool_isPressed = true;
        qlist_cards[i]->bool_moveabel = true;
        qlist_cards[i]->int_Zorder = int_maxZorder;
        qlist_cards[i]->raise();
        qlist_cards[i]->turnfront();
//        qDebug() << qlist_cards[i]->pos() << qlist_cards[i]->int_cardNumber << qlist_cards[i]->int_Zorder;

        //decide whether card is moveabel
        if(qlist_cards[i]->pos() == QPointF(10,20))
        {
            qlist_cards[i]->bool_moveabel = false;
            qlist_cards[i]->move(130,20);
        }
    }
}

void Table::mouseReleaseEvent(QMouseEvent *event)
{
//    qDebug() << "table Release";

    //decide where cards can be placed
    //add check number
    for(int i=0; i < qlist_cards.length(); i++)
    {
        bool bool_canNotPlaced = true;
        bool bool_emptyPlace = true;
        if(qlist_cards[i]->bool_isPressed == true && qlist_cards[i]->bool_moveabel == true)
        {
            //chick if card is overlapping with 1 of any 4 cards site
            for(int j=0; j < qlist_cardPlacedPos.length(); j++)
            {
                if( decide_IsOverlapping(qlist_cards[i]->pos(), qlist_cardPlacedPos[j]) == true )
                {
                    //place the overlapping card (qlist_cardPlacedPos[j].y() + 25)
                    qlist_cards[i]->move(qlist_cardPlacedPos[j].x(), qlist_cardPlacedPos[j].y() + 25);
                    for(int k=0; k < qlist_cards.length(); k++)
                    {
                        //check whether there is another card overlapping on qlist_cardPlacedPos[j]
                        if(qlist_cards[k]->bool_isPressed == false && qlist_cards[k]->pos() == qlist_cardPlacedPos[j] )
                        {
                            bool_emptyPlace = false;
//                            qDebug() << qlist_cardPlacedPos;
                            bool_canNotPlaced = false;
                        }
                    }
                    //if there is no another card on qlist_cardPlacedPos[j], place the overlapping card on qlist_cardPlacedPos[j]
                    if(qlist_cards[i]->bool_isPressed == true && qlist_cardPlacedPos[j].y() == 20 && bool_emptyPlace == true)
                    {
                        qlist_cards[i]->move(qlist_cardPlacedPos[j].x(), qlist_cardPlacedPos[j].y() );
//                            qDebug() << qlist_cardPlacedPos
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

    //update qlist_cardPlacedPos
    qlist_cardPlacedPos = get_cardSitePos();
    for(int i=0; i < qlist_cards.length(); i++)
    {
        if(qlist_cards[i]->pos().x() == 10)
        {
            continue;
        }
        else if(qlist_cards[i]->pos().x() == 130)
        {
            continue;
        }
        else if(qlist_cards[i]->pos().x() == qlist_cardPlacedPos[0].x())
        {
            if(qlist_cards[i]->pos().y() > qlist_cardPlacedPos[0].y())
            {
                qlist_cardPlacedPos[0] = qlist_cards[i]->pos();
            }
        }
        else if(qlist_cards[i]->pos().x() == qlist_cardPlacedPos[1].x())
        {
            if(qlist_cards[i]->pos().y() > qlist_cardPlacedPos[1].y())
            {
                qlist_cardPlacedPos[1] = qlist_cards[i]->pos();
            }
        }
        else if(qlist_cards[i]->pos().x() == qlist_cardPlacedPos[2].x())
        {
            if(qlist_cards[i]->pos().y() > qlist_cardPlacedPos[2].y())
            {
                qlist_cardPlacedPos[2] = qlist_cards[i]->pos();
            }
        }
        else if(qlist_cards[i]->pos().x() == qlist_cardPlacedPos[3].x())
        {
            if(qlist_cards[i]->pos().y() > qlist_cardPlacedPos[3].y())
            {
                qlist_cardPlacedPos[3] = qlist_cards[i]->pos();
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
