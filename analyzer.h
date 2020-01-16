#ifndef ANALYZER_H
#define ANALYZER_H

#include "analyzer_global.h"

#include <QMap>
#include <QVector>
#include <QJsonObject>
#include "diagram.h"

class ANALYZER_EXPORT Analyzer
{
public:
    static QVector<Diagram> analyze(QVector<Diagram> diagrams);
    static QMap<QString,QStringList> get_actors_list(QVector<Diagram> diagrams);
  //  static QMap<QString, complex> analyze(QMap<QString,Structures::complex> list_elements, QString project_path);
    //static QMap<QString, QStringList> get_actors_list(QMap<QString,Structures::complex> list_elements, QString project_path);
};

#endif // ANALYZER_H
