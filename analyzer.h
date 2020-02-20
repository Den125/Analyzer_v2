#ifndef ANALYZER_H
#define ANALYZER_H

#include "analyzer_global.h"

#include <QMap>
#include <QVector>
#include <QJsonObject>
#include "diagram.h"
extern "C"
{
    Q_DECL_EXPORT QVector<Diagram> analyze(QVector<Diagram> copy_diagrams);
    Q_DECL_EXPORT QMap<QString,QStringList> get_actors_list(QVector<Diagram> &diagrams);

    bool equalNames(const Diagram& lhs, const Diagram& rhs);
    void insert(const Diagram& diag, QVector<Diagram>& diagrams);
    void update(const Diagram& diag, QVector<Diagram>& diagrams);
    void remove_diag(const Diagram& diag, QVector<Diagram>& diagrams);
    void analyze_current_diagramm(Diagram &current, QVector<Diagram>& all_diagrams);

    void analyze_usecase_diagram(Diagram& use_case, QVector<Diagram>& all_diagrams);
    void analyze_robustness_diagram(Diagram& robustness, QVector<Diagram>& all_diagrams);
    void analyze_sequence_diagram(Diagram& sequence, QVector<Diagram>& all_diagrams);
    void analyze_classes_diagram(Diagram& classes, QVector<Diagram>& all_diagrams);
};

#endif // ANALYZER_H
