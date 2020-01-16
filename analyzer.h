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
    static QVector<Diagram> analyze(QVector<Diagram> copy_diagrams);
    static QMap<QString,QStringList> get_actors_list(QVector<Diagram> diagrams);
  //  static QMap<QString, complex> analyze(QMap<QString,Structures::complex> list_elements, QString project_path);
    //static QMap<QString, QStringList> get_actors_list(QMap<QString,Structures::complex> list_elements, QString project_path);
private:
    static bool equalNames(const Diagram& lhs, const Diagram& rhs);
    static void insertOrUpdate(const Diagram& diag, QVector<Diagram>& diagrams);

    static void analyze_current_diagramm(Diagram &current, QVector<Diagram>& all_diagrams);

    static void analyze_usecase_diagram(Diagram& use_case, QVector<Diagram>& all_diagrams);
    static void analyze_robustness_diagram(Diagram& use_case, QVector<Diagram>& all_diagrams) {

    }
    static void analyze_sequence_diagram(Diagram& use_case, QVector<Diagram>& all_diagrams) {

    }
    static void analyze_classes_diagram(Diagram& use_case, QVector<Diagram>& all_diagrams) {

    }
};

#endif // ANALYZER_H
