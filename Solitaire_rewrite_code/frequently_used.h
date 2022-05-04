#ifndef FREQUENTLY_USED_H
#define FREQUENTLY_USED_H

#include <QString>
#include <QList>
#include <iostream>
#include<fstream>
#include <string>

class CardPos
{
    public:
        int x;
        int y;
};

QString merge_filepath(QString x);

QList<QString> get_cardsSuits();

#endif // FREQUENTLY_USED_H

