#include "frequently_used.h"
using namespace std;

QString merge_filepath(QString x)
{
    QString y = "C:/Users/88696/Desktop/Solitaire_rewrite_code/";
    QString z;
    z = y + x;
    return z;
}


QList<QString> get_cardsSuits()
{
    QList<QString> qlist_cardsSuits;
    ifstream fileread("C:/Users/88696/Desktop/Solitaire_rewrite_code/pictures/card_suits.txt");

    if(fileread)
    {
        for(string string_readline;getline(fileread,string_readline);)
        {
            //QString::fromStdString(string_readline) convert string to QString
            qlist_cardsSuits << (QString::fromStdString(string_readline));
        }
    }
    else
    {
//        qDebug() << "no such file" ;
    }

    return qlist_cardsSuits;
}
