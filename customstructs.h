#ifndef CUSTOMSTRUCTS_H
#define CUSTOMSTRUCTS_H

#include <QSet>
#include <QString>


struct ProjectStruct{
    int db_id;
    QString name;
    int color;
    QSet<QString> subprojects;
};

#endif // CUSTOMSTRUCTS_H
