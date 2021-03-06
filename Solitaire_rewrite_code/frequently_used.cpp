#include "frequently_used.h"
using namespace std;

WidHei::WidHei(int w, int h)
{
    int_width = w;
    int_height = h;
}

PosSizeUpLow::PosSizeUpLow(int x, int y, int w, int h, int up, int low)
{
    qrect_posSize.setRect(x, y, w, h);
    uplow_ul.int_upper = up;
    uplow_ul.int_lower = low;
}

QString merge_filepath(QString x)
{
    QString y = "/Users/kangrenjun/My_Solitaire_rewrite/Solitaire_rewrite_code/";
    QString z;
    z = y + x;
    return z;
}

bool decide_IsOverlapping(QPointF qpointf_posOne, QPointF qpointf_posTwo)
{
    bool bool_IsOverlapping = false;
    //every card's width=110 height=160, use qAbs() to judgu if two cards is overlapping
    if( (qAbs(qpointf_posOne.x() - qpointf_posTwo.x()) <= 110) && (qAbs(qpointf_posOne.y() - qpointf_posTwo.y()) <= 160) )
    {
        bool_IsOverlapping = true;
    }

    return bool_IsOverlapping;
}

bool check_mousePosOnArea(QPointF qpointf_mousePos, QPointF qpointf_areaPos)
{
    bool bool_on = false;
    if(qpointf_mousePos.x() >= qpointf_areaPos.x() && qpointf_mousePos.x() <= (qpointf_areaPos.x()+110)
            && qpointf_mousePos.y() >= qpointf_areaPos.y() && qpointf_mousePos.y() <= (qpointf_areaPos.y()+160) )
    {
        bool_on = true;
    }

    return bool_on;
}

QList<QPointF> get_StartCardsArea ()
{
    QList<QPointF> qlist_StartCardsArea;

    QPointF qpointf_posOne(65,20);
    qlist_StartCardsArea << qpointf_posOne;

    QPointF qpointf_posTwo(225,20);
    qlist_StartCardsArea << qpointf_posTwo;

    return qlist_StartCardsArea;
}

QList<QPointF> get_StackCardsArea ()
{
    QList<QPointF> qlist_StackCardsArea;

    QPointF qpointf_posOne(545,20);
    qlist_StackCardsArea << qpointf_posOne;

    QPointF qpointf_posTwo(705,20);
    qlist_StackCardsArea << qpointf_posTwo;

    QPointF qpointf_posThree(865,20);
    qlist_StackCardsArea << qpointf_posThree;

    QPointF qpointf_posFour(1025,20);
    qlist_StackCardsArea << qpointf_posFour;

    return qlist_StackCardsArea;
}

QList<QPointF> get_PlayCardsArea ()
{
    QList<QPointF> qlist_PlayCardsArea;

    QPointF qpointf_posOne(65,200);
    qlist_PlayCardsArea << qpointf_posOne;

    QPointF qpointf_posTwo(225,200);
    qlist_PlayCardsArea << qpointf_posTwo;

    QPointF qpointf_posThree(385,200);
    qlist_PlayCardsArea << qpointf_posThree;

    QPointF qpointf_posFour(545,200);
    qlist_PlayCardsArea << qpointf_posFour;

    QPointF qpointf_posFive(705,200);
    qlist_PlayCardsArea << qpointf_posFive;

    QPointF qpointf_posSix(865,200);
    qlist_PlayCardsArea << qpointf_posSix;

    QPointF qpointf_posSeven(1025,200);
    qlist_PlayCardsArea << qpointf_posSeven;

    return qlist_PlayCardsArea;
}

QList<PosSizeUpLow> get_CardsInitalPosAndSizeAndUpperCardONumAndLowerCardONum( QList<QPointF> qlist_StartCardsArea, QList<QPointF> qlist_PlayCardsArea, WidHei widhei_cardSize)
{
    QList<PosSizeUpLow> qlist_PosSizeUpLow;
    int int_cardOrderInQlist=0;

    //24 cards that on qlist_StartCardsArea[0]
    //have the same inital pos, and the same (upper, lower) = (-1, -1)
    PosSizeUpLow posSizeUpLow_startArea(qlist_StartCardsArea[0].x(), qlist_StartCardsArea[0].y(), widhei_cardSize.int_width , widhei_cardSize.int_height, -1, -1);
    for(int i=0; i<24; i++)
    {
        qlist_PosSizeUpLow << (posSizeUpLow_startArea);
        int_cardOrderInQlist++;
    }

    //qlist_PlayCardsArea[0] has 1 card, qlist_PlayCardsArea[1] has two cards, qlist_PlayCardsArea[2] has three cars,and so on
    int int_up = 0;
    int int_low = 0;
    for(int i=0; i < qlist_PlayCardsArea.length(); i++)
    {
        PosSizeUpLow posSizeUpLow_playArea(qlist_PlayCardsArea[i].x(), qlist_PlayCardsArea[i].y(), widhei_cardSize.int_width , widhei_cardSize.int_height, int_up, int_low);
        for(int j=0; j <= i; j++)
        {
            //int_up record previous card order in qlist
            int_up = int_cardOrderInQlist + 1;
            //int_low record next card order in qlist
            int_low = int_cardOrderInQlist - 1;
            int_cardOrderInQlist++;
            //first pos of qlist_PlayCardsArea[i]
            if(j == 0)
            {
                int_low = -1;
            }
            //last pos of qlist_PlayCardsArea[i]
            if(j == i)
            {
                int_up = -1;
            }
            posSizeUpLow_playArea.uplow_ul.int_upper = int_up;
            posSizeUpLow_playArea.uplow_ul.int_lower = int_low;
            qlist_PosSizeUpLow << (posSizeUpLow_playArea);
            //next card is lower 25 than previous
            PosSizeUpLow posSizeUpLow_playAreaTemp(posSizeUpLow_playArea.qrect_posSize.x(), posSizeUpLow_playArea.qrect_posSize.y() + 25 ,
                                                   posSizeUpLow_playArea.qrect_posSize.width(), posSizeUpLow_playArea.qrect_posSize.height(), int_up, int_low);
            posSizeUpLow_playArea = posSizeUpLow_playAreaTemp;
        }
    }
    return qlist_PosSizeUpLow;
}

QList<SuitAndNumber> get_cardsSuitsAndNumber()
{
    QList<SuitAndNumber> qlist_cardsSuitsAndNumber;
    SuitAndNumber SuitAndNumber_temp;
    int int_cardNum = 0, int_random = 0;
    string cardsListPath = merge_filepath("pictures/card_suits.txt").toStdString();//QString to string
    ifstream fileread( cardsListPath );

    if(fileread)
    {
        for(string string_readline;getline(fileread,string_readline);)
        {
            //QString::fromStdString(string_readline) convert string to QString
            SuitAndNumber_temp.qstring_suit = QString::fromStdString(string_readline);
            SuitAndNumber_temp.int_num = int_cardNum;
            qlist_cardsSuitsAndNumber << (SuitAndNumber_temp);
            int_cardNum++;
        }

        //randomly reorder 52 cards
        for(int i=0; i < qlist_cardsSuitsAndNumber.length(); i++)
        {
            int_random= arc4random()%52;
            SuitAndNumber_temp = qlist_cardsSuitsAndNumber[i];
            qlist_cardsSuitsAndNumber[i] = qlist_cardsSuitsAndNumber[int_random];
            qlist_cardsSuitsAndNumber[int_random] = SuitAndNumber_temp;
        }
    }
    else
    {
        //if readfile fail
    }

    return qlist_cardsSuitsAndNumber;
}

QList<QRect> get_cardSitePosAndSize( QList<QPointF> qlist_StartCardsArea, QList<QPointF> qlist_StackCardsArea, WidHei widhei_cardSize)
{
    QList<QRect> qlist_posAndsize;

    for(int i=0; i < qlist_StartCardsArea.length(); i++)
    {
        QRect qrect_startArea(qlist_StartCardsArea[i].x(), qlist_StartCardsArea[i].y(), widhei_cardSize.int_width , widhei_cardSize.int_height);
        qlist_posAndsize << (qrect_startArea);
    }

    for(int i=0; i < qlist_StackCardsArea.length(); i++)
    {
        QRect qrect_stackArea(qlist_StackCardsArea[i].x(), qlist_StackCardsArea[i].y(), widhei_cardSize.int_width , widhei_cardSize.int_height);
        qlist_posAndsize << (qrect_stackArea);
    }
    return qlist_posAndsize;
}

QList<PosNum> get_PlayCardPosAndNum( QList<QPointF> qlist_allCardPos, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_PlayCardsArea)
{
    QList<PosNum> qlist_PlayCardPosAndNum;
    PosNum posnum_temp;

    //intArray_PlaceCardNum recorder card order num that in qlist_cards for 7 PlayCardPos in qlist_PlayCardsArea
    int intArray_PlaceCardNum[7];
    //initialize intArray_PlaceCardNum, -1 means no card
    std::fill_n(intArray_PlaceCardNum, 7, -1);
    //initialize qlist_PlayCardPosAndNum
    for(int i=0; i < qlist_PlayCardsArea.length(); i++)
    {
        posnum_temp.int_cardONum = intArray_PlaceCardNum[i];
        posnum_temp.qpointf_pos = qlist_PlayCardsArea[i];
        qlist_PlayCardPosAndNum << posnum_temp;
    }
    //record the uppermost card pos in 7 qlist_PlayCardsArea
    bool bool_NoChosen;
    for(int i=0; i < qlist_allCardPos.length(); i++)
    {
        bool_NoChosen = true;
        //skip chosen cards that in qlist_MoveAbelCards[j]
        //if qlist_MoveAbelCards.length()=0 this for loop wont run
        for(int j=0; j < qlist_MoveAbelCards.length(); j++)
        {
            if(i == qlist_MoveAbelCards[j])
            {
                bool_NoChosen = false;
            }
        }
        if( bool_NoChosen)
        {
            for(int k=0; k < qlist_PlayCardPosAndNum.length(); k++)
            {
                if( qlist_allCardPos[i].x() == qlist_PlayCardPosAndNum[k].qpointf_pos.x())
                {
                    if( qlist_allCardPos[i].y() >= qlist_PlayCardPosAndNum[k].qpointf_pos.y())
                    {
                        //record the uppermost card pos for every qlist_PlayCardPosAndNum[k].qpointf_pos
                        qlist_PlayCardPosAndNum[k].qpointf_pos = qlist_allCardPos[i];
                        //also record card order num that in qlist_allCardPos
                        qlist_PlayCardPosAndNum[k].int_cardONum = i;
                    }
                }
            }
        }
    }

    return qlist_PlayCardPosAndNum;
}
