#include "table.h"

Table::Table(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Game Start");
    this->setWindowIcon( QIcon( merge_filepath("pictures/icon.png")));
    this->setMinimumSize(1200,800);
    this->setMaximumSize(1200,800);
    this->setStyleSheet("QMainWindow {background: 'green';}");

    //Botton for count score
    qpushbutton_score = new QPushButton(this);
    qpushbutton_score->setGeometry(20,720,150,60);
    qpushbutton_score->setText("Count Score");
    qpushbutton_score->setStyleSheet("QPushButton {font-size: 20pt;}");
    //Connect button signal to appropriate slot
    connect(qpushbutton_score, &QPushButton::clicked, this, &Table::clicked_startButton);

    //access three kinds of cards Area
    //fuctions are defined in frequently_used.h
    qlist_StartCardsArea  = get_StartCardsArea ();
    qlist_StackCardsArea  = get_StackCardsArea ();
    qlist_PlayCardsArea  = get_PlayCardsArea ();
    //access width and height of card
    WidHei widhei_cardSize = WidHei(110, 160);


    //access card site's pos and size, and make 6 card sites on table, and store card sites in qlist_cardSite
    //qlist_cardSite is just for showing card_empty.png and ard_site.png, it won't be used when play cards.
    //fuctions are defined in frequently_used.h
    qlist_setCardSitePosAndsize = get_cardSitePosAndSize(qlist_StartCardsArea , qlist_StackCardsArea , widhei_cardSize);
    QPixmap qpixmap_cardSite(merge_filepath("pictures/card_empty.png"));
    for(int i=0; i < qlist_setCardSitePosAndsize.length(); i++)
    {
        qlabel_cardSite = new QLabel(this);
        qlabel_cardSite->setGeometry(qlist_setCardSitePosAndsize[i]);
        qlabel_cardSite->setPixmap(qpixmap_cardSite);
        qlist_cardSite << qlabel_cardSite;
        qpixmap_cardSite = QPixmap(merge_filepath("pictures/card_site.png"));
    }


    //fuctions are defined in frequently_used.h
    //access every card's inital pos and size and upper card order num and lower card order num
    qlist_setPosSizeUpLow = get_CardsInitalPosAndSizeAndUpperCardONumAndLowerCardONum(qlist_StartCardsArea , qlist_PlayCardsArea , widhei_cardSize);
    //access card's suit filename, and card's number
    qlist_cardSuitsAndNumber = get_cardsSuitsAndNumber();   

    int int_initialZorder = 0;
    //generate 52 cards, and store cards in qlist_cards
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
    }

}

void Table::mousePressEvent(QMouseEvent *event)
{
    //check is any card be pressed, if there is, record its card zorder and card order number in qlist_cards with CardBePressed
    CardBePressed_PressedCard = get_thePressedCard(qlist_cards, event);

    //if press on StartCardsPos[0], need special treatment
    if(check_mousePosOnArea(event->pos(), qlist_StartCardsArea [0]) == true)
    {
        //-1 means no card is clicked
        if(CardBePressed_PressedCard.int_Zorder == -1)
        {
            //put cards at qlist_StartCardsArea [1] back to qlist_StartCardsArea [0]
            qlist_cards = set_PutBackToStart0(qlist_cards, CardBePressed_PressedCard, qlist_StartCardsArea , int_maxZorder);
            //update maxZorder
            for(int i=0; i < qlist_cards.length(); i++)
            {
                if(qlist_cards[i]->pos() == qlist_StartCardsArea [0])
                {
                    int_maxZorder++;
                }
            }
        }
        else if(CardBePressed_PressedCard.int_Zorder >= 0)
        {
            qlist_cards = set_PutToStart1(qlist_cards, CardBePressed_PressedCard, qlist_StartCardsArea , int_maxZorder);
            //update maxZorder
            int_maxZorder++;
        }
    }
    //all the other place has the same treatment
    else
    {
        if(CardBePressed_PressedCard.int_Zorder == -1)
        {
            //do nothing
        }
        else if(CardBePressed_PressedCard.int_Zorder >= 0)
        {
            //record moveabel cards' order number in qlist_cards
            qlist_MoveAbelCards = get_MoveAbelCard(qlist_cards, CardBePressed_PressedCard);
            //set those cards that in qlist_MoveAbelCards
            qlist_cards = set_MoveAbelCardState(qlist_cards, qlist_MoveAbelCards, event, int_maxZorder);
            //update maxZorder
            int_maxZorder += qlist_MoveAbelCards.length();
        }
    }

}

void Table::mouseMoveEvent(QMouseEvent *event)
{
    //if qlist_MoveAbelCards.length()=0 this for loop won't run
    for(int i=0; i< qlist_MoveAbelCards.length(); i++)
    {
        if(qlist_cards[ qlist_MoveAbelCards[i] ]->bool_moveabel == true)
        {
            qpointf_movepos = event->pos() - qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_MoveFixPos;
            qlist_cards[ qlist_MoveAbelCards[i] ]->move(qpointf_movepos.x(), qpointf_movepos.y());
        }
    }
}

void Table::mouseReleaseEvent(QMouseEvent *event)
{
    //make sure has card be pressed, and it can be moved
    if( qlist_MoveAbelCards.length() > 0  &&  qlist_cards[ qlist_MoveAbelCards[0] ]->bool_moveabel == true)
    {
        //check overlap on which StackArea, -1 means not on any StackArea
        int int_onWhichStack = get_onWhichStackPos(qlist_cards, qlist_MoveAbelCards, qlist_StackCardsArea );
        //overlapping on StackArea, move one card once
        if(int_onWhichStack >= 0 && qlist_MoveAbelCards.length() == 1)
        {
            qlist_cards = releaseOn_StackCards( qlist_cards, qlist_MoveAbelCards, qlist_StackCardsArea , int_onWhichStack);
        }
        //all the orther Area
        else
        {
            //change card's pos, upper order num, lower order num according to PlayCardsArea rule
            qlist_cards = releaseOn_PlayCards(qlist_cards, qlist_MoveAbelCards, qlist_PlayCardsArea );
        }
    }

    //reset cards states and qlist
    qlist_MoveAbelCards.clear();
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
                //qlist_cards[i]->int_upperCardONum  == -1 means no other card over the card qlist_cards[i]
                if(qlist_cards[i]->int_upperCardONum  == -1)
                {
                    CardBePressed_temp.int_Zorder = qlist_cards[i]->int_Zorder;
                    CardBePressed_temp.int_CardONum = i;
                }
                else if(qlist_cards[i]->int_upperCardONum  >= 0 && qlist_cards[i]->bool_isFront == true)
                {
                    CardBePressed_temp.int_Zorder = qlist_cards[i]->int_Zorder;
                    CardBePressed_temp.int_CardONum = i;
                }
            }
        }
    }
    return CardBePressed_temp;
}

QList<Card *> Table:: set_PutBackToStart0(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard, QList<QPointF> qlist_StartCardsArea , int int_maxZorder)
{
    //put cards that on qlist_StartCardsArea [1] (225,20) back to qlist_StartCardsArea [0] (65,20),
    //and for keeping cards zorder, do raise() and increase cards int_Zorder
    for(int i=0; i < qlist_cards.length(); i++)
    {
        if( qlist_cards[i]->pos() == qlist_StartCardsArea [1])
        {
            int_maxZorder++;
            qlist_cards[i]->move(qlist_StartCardsArea [0].x(), qlist_StartCardsArea [0].y());
            qlist_cards[i]->turnback();
            qlist_cards[i]->raise();
            qlist_cards[i]->bool_isFront = false;
            qlist_cards[i]->int_Zorder = int_maxZorder;
        }
    }
    return qlist_cards;
}

QList<Card *> Table:: set_PutToStart1(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard, QList<QPointF> qlist_StartCardsArea , int int_maxZorder)
{
    //if card is at qlist_StartCardsArea [0]
    if(qlist_cards[ CardBePressed_PressedCard.int_CardONum ]->pos() == qlist_StartCardsArea [0])
    {
        int_maxZorder++;
        qlist_cards[ CardBePressed_PressedCard.int_CardONum ]->bool_moveabel = false;
        qlist_cards[ CardBePressed_PressedCard.int_CardONum ]->turnfront();
        qlist_cards[CardBePressed_PressedCard.int_CardONum]->int_Zorder = int_maxZorder;
        qlist_cards[ CardBePressed_PressedCard.int_CardONum ]->raise();
        qlist_cards[ CardBePressed_PressedCard.int_CardONum ]->move(qlist_StartCardsArea [1].x(), qlist_StartCardsArea [1].y());
    }
    return qlist_cards;
}

QList<int> Table:: get_MoveAbelCard(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard)
{
    QList<int> qlist_MoveAbelCardsTemp;
    int int_tempUpCardNum = CardBePressed_PressedCard.int_CardONum;
    //the pressed card and its upper cards will be record in qlist_MoveAbelCards, int_tempUpCardNum == -1 means no upper card
    while(int_tempUpCardNum > -1)
    {
        qlist_MoveAbelCardsTemp << int_tempUpCardNum;
        int_tempUpCardNum = qlist_cards[ int_tempUpCardNum ]->int_upperCardONum ;
    }
    return qlist_MoveAbelCardsTemp;
}

QList<Card *> Table:: set_MoveAbelCardState(QList<Card *> qlist_cards,  QList<int> qlist_MoveAbelCards, QMouseEvent *event, int int_maxZorder)
{
    //if qlist_MoveAbelCards.length()=0 this for loop wont run
    for(int i=0; i < qlist_MoveAbelCards.length(); i++)
    {
        //set card state
        int_maxZorder++;
        qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos = qlist_cards[ qlist_MoveAbelCards[i] ]->pos();
        //qpointf_MoveFixPos is used on void Table::mouseMoveEvent(QMouseEvent *event)
        qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_MoveFixPos = ( event->pos() - qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos );
        qlist_cards[ qlist_MoveAbelCards[i] ]->bool_isPressed = true;
        qlist_cards[ qlist_MoveAbelCards[i] ]->bool_moveabel = true;
        qlist_cards[ qlist_MoveAbelCards[i] ]->bool_isFront = true;
        qlist_cards[ qlist_MoveAbelCards[i] ]->int_Zorder = int_maxZorder;
        qlist_cards[ qlist_MoveAbelCards[i] ]->raise();
        qlist_cards[ qlist_MoveAbelCards[i] ]->turnfront();
    }
    return qlist_cards;
}

int Table:: get_onWhichStackPos(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_StackCardsArea )
{
    //check wether overlap on StackPos, -1 means no result
    int int_onWhichStack = -1;
    for(int i=0; i < qlist_StackCardsArea .length(); i++)
    {
        if( decide_IsOverlapping( qlist_cards[ qlist_MoveAbelCards[0] ]->pos(), qlist_StackCardsArea [i]) == true)
        {
            int_onWhichStack = i;
        }
    }
    return int_onWhichStack;
}

QList<Card *> Table:: releaseOn_StackCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_StackCardsArea , int int_onWhichStack)
{
    bool bool_canNotPlaced = true;
    int int_AlreadyOnStack = -1;
    int int_tempZorder= -1;
    //check is there any card on StackCardsArea already
    for(int i=0; i < qlist_cards.length(); i++)
    {
        if( qlist_cards[i]->pos() == qlist_StackCardsArea [ int_onWhichStack ])
        {
            //find the uppermost card
            if( qlist_cards[i]->int_Zorder >= int_tempZorder)
            {
                int_AlreadyOnStack = i;
                int_tempZorder = qlist_cards[i]->int_Zorder;
            }
        }
    }

    if( int_AlreadyOnStack >= 0)
    {
        if( qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber -  qlist_cards[int_AlreadyOnStack]->int_cardNumber == 1 )
        {
            //make sure two cards has the same suit
            if( qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber / 13 == qlist_cards[int_AlreadyOnStack]->int_cardNumber / 13 )
            {
                //set card that under qlist_cards[ qlist_MoveAbelCards[0] ] previously, int_upperCardONum  = -1
                if( qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  >= 0)
                {
                    qlist_cards[ qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  ]->int_upperCardONum  = -1;
                }
                //move and raise card in qlist_MoveAbelCards
                qlist_cards[ qlist_MoveAbelCards[0] ]->move(qlist_StackCardsArea [ int_onWhichStack ].x(), qlist_StackCardsArea [ int_onWhichStack ].y());
                //once card level PlayCardArea, upper lower all set to -1
                qlist_cards[ qlist_MoveAbelCards[0] ]->int_upperCardONum  = -1;
                qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  = -1;

                bool_canNotPlaced = false;
            }
        }
    }
    else if( int_AlreadyOnStack == -1)
    {
        //qlist_MoveAbelCards[ qlist_MoveAbelCards.length()-1 ] % 13 ==0 means ace is the uppermost card in qlist_MoveAbelCards
        if( qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber % 13 ==0 )
        {
            //set card that under qlist_cards[ qlist_MoveAbelCards[0] ] previously, int_upperCardONum  = -1
            if( qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  >= 0)
            {
                qlist_cards[ qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  ]->int_upperCardONum  = -1;
            }
            //move and raise card in qlist_MoveAbelCards
            qlist_cards[ qlist_MoveAbelCards[0] ]->move(qlist_StackCardsArea [ int_onWhichStack ].x(), qlist_StackCardsArea [ int_onWhichStack ].y());
            //once card level PlayCardPos, upper lower all set to -1
            qlist_cards[ qlist_MoveAbelCards[0] ]->int_upperCardONum  = -1;
            qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  = -1;

            bool_canNotPlaced = false;
        }
    }
    //send card back to its original pos
    if(bool_canNotPlaced == true)
    {
        for(int i=0; i < qlist_MoveAbelCards.length(); i++)
        {
            int int_backX = qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos.x();
            int int_backY = qlist_cards[ qlist_MoveAbelCards[i] ]->qpointf_bePressedPos.y();
            qlist_cards[ qlist_MoveAbelCards[i] ]->move( int_backX, int_backY );
        }
    }
    return qlist_cards;
}

QList<Card *> Table:: releaseOn_PlayCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_PlayCardsArea )
{
    //get all card pos in qlist_cards
    QList<QPointF> qlist_allCardPos;
    for(int i=0; i < qlist_cards.length(); i++)
    {
        qlist_allCardPos << QPointF(qlist_cards[i]->pos().x(), qlist_cards[i]->pos().y());
    }
    //get every uppermost card's Pos and order Num in qlist_cards for 7 PlayCardPos
    QList<PosNum> qlist_PlayCardPosAndNum = get_PlayCardPosAndNum(qlist_allCardPos, qlist_MoveAbelCards, qlist_PlayCardsArea );

    bool bool_canNotPlaced = true;
    //check if card is overlapping with 1 of any 7 PlayCardPos
    for(int i=0; i < qlist_PlayCardPosAndNum.length(); i++)
    {
        if( decide_IsOverlapping(qlist_cards[ qlist_MoveAbelCards[0] ]->pos(), qlist_PlayCardPosAndNum[i].qpointf_pos) == true )
        {
            //means no card on qlist_PlayCardPosAndNum[i].qpointf_pos
            if(qlist_PlayCardPosAndNum[i].int_cardONum == -1)
            {
                if(qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber % 13 == 12)// only k can be placed
                {
                    //if qlist_cards[ qlist_MoveAbelCards[0] ] has a lower card before
                    if( qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  >= 0)
                    {
                        //qlist_cards[ qlist_MoveAbelCards[0] ] will move to new pos, so the the lower card has no upper card now
                        qlist_cards[ qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  ]->int_upperCardONum  = -1;
                        //there is no card lower than qlist_cards[ qlist_MoveAbelCards[0] ]
                        qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  = -1;
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
            else if( qlist_PlayCardPosAndNum[i].int_cardONum >= 0 && qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardONum ]->bool_isFront == true)
            {
                /*check wether card that on (qlist_PlayCardPos[j].x(), qlist_PlayCardPos[j].y() + 25)
                can match card that on (qlist_PlayCardPos[j].x(), qlist_PlayCardPos[j].y() ) */
                //0 12    13 25    26 38    39 51
                //0  1  0  14  0  27  0  40
                //13 1  13 14  13 27  13 40
                //result :
                //if (qlist_cards[i]->int_cardNumber % 13) - (qlist_cards[k]->int_cardNumber % 13) == -1
                //then qlist_cards[i] match qlist_cards[k]
                if( (qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber % 13) - (qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardONum ]->int_cardNumber % 13) == -1 )
                {
                    //0~12 are club, 26~38 are spade, these are black cards
                    //13~25 are diamond, 39~51 are heart , these are red cards
                    //only red card can be put on black card, and only black card can be put on red card
                    int int_InMove = (qlist_cards[ qlist_MoveAbelCards[0] ]->int_cardNumber / 13) % 2;
                    int int_OnPlay = (qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardONum ]->int_cardNumber / 13) % 2;
                    //qAbs(int_InMove - int_OnPlay) == 1 means one card is red and another is black
                    if( qAbs(int_InMove - int_OnPlay) == 1 )
                    {
                        //if qlist_cards[ qlist_MoveAbelCards[0] ] has a lower card before
                        if(qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  >= 0)
                        {
                            //qlist_cards[ qlist_MoveAbelCards[0] ] will move to new pos, so the the lower card has no upper card now
                            qlist_cards[ qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  ]->int_upperCardONum  = -1;
                        }
                        //qlist_cards[ qlist_MoveAbelCards[0] ] has new lower card qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardNum ]
                        qlist_cards[ qlist_MoveAbelCards[0] ]->int_lowerCardONum  = qlist_PlayCardPosAndNum[i].int_cardONum;
                        qlist_cards[ qlist_PlayCardPosAndNum[i].int_cardONum ]->int_upperCardONum  = qlist_MoveAbelCards[0];
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
    }
    //send card back to its original pos
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

void Table::clicked_startButton()
{
    //count Club, Diamond, Spade, Heart, and total cards
    int int_Club = 0;
    int int_Diamond = 0;
    int int_Spade = 0;
    int int_Heart = 0;
    int int_TotalScore = 0;
    //check all cards
    for(int i=0; i < qlist_cards.length(); i++)
    {
        //cards in StackArea
        bool bool_inStack = false;
        for(int j=0; j < qlist_StackCardsArea .length(); j++)
        {
            if( qlist_cards[i]->pos() == qlist_StackCardsArea [j])
            {
                bool_inStack = true;
            }
        }
        //count four suits cards
        if(bool_inStack == true)
        {
            int int_grouping = qlist_cards[i]->int_cardNumber / 13;
            if( int_grouping == 0)
            {
                int_Club++;
            }
            else if( int_grouping == 1)
            {
                int_Diamond++;
            }
            else if( int_grouping == 2)
            {
                int_Spade++;
            }
            else if( int_grouping == 3)
            {
                int_Heart++;
            }
        }

    }
    //four suits cards add togather
    int_TotalScore = int_Club + int_Diamond + int_Spade + int_Heart;

    scoreboard_score = new Scoreboard(int_Club, int_Diamond, int_Spade, int_Heart, int_TotalScore);
    scoreboard_score->show();
    this->setEnabled(false);
    connect(scoreboard_score, &Scoreboard::close_scoreboard, this, &Table::close_scoreBoard);
}

void Table::close_scoreBoard()
{
    this->setEnabled(true);
}

void Table::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Question",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }

    emit close_table();
}
