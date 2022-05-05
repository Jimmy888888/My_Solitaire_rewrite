#include "frequently_used.h"
using namespace std;

QString merge_filepath(QString x)
{
    QString y = "C:/Users/88696/Desktop/Git_for_interview/Solitaire_rewrite/Solitaire_rewrite_code/";
    QString z;
    z = y + x;
    return z;
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
//        qDebug() << "no such file" ;
    }

    return qlist_cardsSuitsAndNumber;
}

PosAndSize::PosAndSize(int x,int y,int w,int h)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}

QList<PosAndSize> get_initalPosAndSize()
{
    QList<PosAndSize> qlist_posAndsize;
    PosAndSize posAndSize_startArea(10,20,110,160);

    //48 cards have the same inital pos
    for(int i=0; i<48; i++)
    {
        qlist_posAndsize << (posAndSize_startArea);
    }

    PosAndSize posAndSize_areaOne(340,20,110,160);
    qlist_posAndsize << (posAndSize_areaOne);

    PosAndSize posAndSize_areaTwo(470,20,110,160);
    qlist_posAndsize << (posAndSize_areaTwo);

    PosAndSize posAndSize_areaThree(600,20,110,160);
    qlist_posAndsize << (posAndSize_areaThree);

    PosAndSize posAndSize_areaFour(730,20,110,160);
    qlist_posAndsize << (posAndSize_areaFour);

    return qlist_posAndsize;
}

QList<PosAndSize> get_cardSitePosAndSize()
{
    QList<PosAndSize> qlist_posAndsize;
    PosAndSize posAndSize_startArea(10,20,110,160);
    qlist_posAndsize << (posAndSize_startArea);

    PosAndSize posAndSize_areaOne(340,20,110,160);
    qlist_posAndsize << (posAndSize_areaOne);

    PosAndSize posAndSize_areaTwo(470,20,110,160);
    qlist_posAndsize << (posAndSize_areaTwo);

    PosAndSize posAndSize_areaThree(600,20,110,160);
    qlist_posAndsize << (posAndSize_areaThree);

    PosAndSize posAndSize_areaFour(730,20,110,160);
    qlist_posAndsize << (posAndSize_areaFour);

    return qlist_posAndsize;
}
