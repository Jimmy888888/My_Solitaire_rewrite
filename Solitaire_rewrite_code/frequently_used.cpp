#include "frequently_used.h"
using namespace std;

QString merge_filepath(QString x)
{
    QString y = "C:/Users/88696/Desktop/Git_for_interview/Solitaire_rewrite/Solitaire_rewrite_code/";
    QString z;
    z = y + x;
    return z;
}

QList<QRect> get_cardSitePosAndSize()
{
    QList<QRect> qlist_posAndsize;
    QRect qrect_startArea(10,20,110,160);
    qlist_posAndsize << (qrect_startArea);

    QRect qrect_areaOne(340,20,110,160);
    qlist_posAndsize << (qrect_areaOne);

    QRect qrect_areaTwo(470,20,110,160);
    qlist_posAndsize << (qrect_areaTwo);

    QRect qrect_areaThree(600,20,110,160);
    qlist_posAndsize << (qrect_areaThree);

    QRect qrect_areaFour(730,20,110,160);
    qlist_posAndsize << (qrect_areaFour);

    return qlist_posAndsize;
}


QList<SuitAndNumber> get_cardsSuitsAndNumber()
{
    QList<SuitAndNumber> qlist_cardsSuitsAndNumber;
    SuitAndNumber SuitAndNumber_temp;
    int int_num = 1, int_random = 0;
    ifstream fileread("C:/Users/88696/Desktop/Git_for_interview/Solitaire_rewrite/Solitaire_rewrite_code/pictures/card_suits.txt");

    if(fileread)
    {
        for(string string_readline;getline(fileread,string_readline);)
        {
            //QString::fromStdString(string_readline) convert string to QString
            SuitAndNumber_temp.qstring_suit = QString::fromStdString(string_readline);
            SuitAndNumber_temp.int_num = int_num;
            qlist_cardsSuitsAndNumber << (SuitAndNumber_temp);
            int_num++;
        }

        //randomly reorder 52 cards
        for(int i=0; i < qlist_cardsSuitsAndNumber.length(); i++)
        {
            int_random= rand()%52;
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


QList<QRect> get_initalPosAndSize()
{
    QList<QRect> qlist_posAndsize;
    QRect qrect_startArea(10,20,110,160);

    //48 cards have the same inital pos
    for(int i=0; i<48; i++)
    {
        qlist_posAndsize << (qrect_startArea);
    }

    QRect qrect_areaOne(340,20,110,160);
    qlist_posAndsize << (qrect_areaOne);

    QRect qrect_areaTwo(470,20,110,160);
    qlist_posAndsize << (qrect_areaTwo);

    QRect qrect_areaThree(600,20,110,160);
    qlist_posAndsize << (qrect_areaThree);

    QRect qrect_areaFour(730,20,110,160);
    qlist_posAndsize << (qrect_areaFour);

    return qlist_posAndsize;
}


QList<QPointF> get_cardSitePos()
{
    QList<QPointF> qlist_cardSitePos;

    QPointF qpointf_sitePosStart(10,20);
    qlist_cardSitePos << (qpointf_sitePosStart);

    QPointF qpointf_sitePosOne(340,20);
    qlist_cardSitePos << (qpointf_sitePosOne);

    QPointF qpointf_sitePosTwo(470,20);
    qlist_cardSitePos << (qpointf_sitePosTwo);

    QPointF qpointf_sitePosThree(600,20);
    qlist_cardSitePos << (qpointf_sitePosThree);

    QPointF qpointf_sitePosFour(730,20);
    qlist_cardSitePos << (qpointf_sitePosFour);

    return qlist_cardSitePos;
}
