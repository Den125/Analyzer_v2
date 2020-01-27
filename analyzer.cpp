#include "analyzer.h"
#include <set>
#include <QDebug>
#include <algorithm>

bool Analyzer::equalNames(const Diagram& lhs, const Diagram& rhs) {
    return lhs.m_name == rhs.m_name;
}

void Analyzer::insert/*OrUpdate*/(const Diagram& diag, QVector<Diagram>& diagrams) {
    auto it = std::find_if(diagrams.begin(), diagrams.end(), [&diag](Diagram& elem) {
        return equalNames(diag, elem);
    });

    if (it == diagrams.end()) {
        diagrams.push_back(diag);
    }
   /* else {
        *it = diag;
    }*/
}
void Analyzer::update(const Diagram& diag, QVector<Diagram>& diagrams)
{
    auto it = std::find_if(diagrams.begin(), diagrams.end(), [&diag](Diagram& elem) {
        return equalNames(diag, elem);
    });
    if (it != diagrams.end()) {
        it->m_text=diag.m_text;
    }
}

QVector<Diagram> Analyzer::analyze(QVector<Diagram> copy_diagrams)
{
    QVector<Diagram> result(copy_diagrams);

    for (auto& diagram : copy_diagrams)
    {
        analyze_current_diagramm(diagram, result);
    }

    return result;
}

void Analyzer::analyze_current_diagramm(Diagram& item, QVector<Diagram>& all_diagrams)
{
    std::map<Diagram::Type, std::function<void(Diagram&, QVector<Diagram>&)>> functions({
        { Diagram::Type::use_case, Analyzer::analyze_usecase_diagram },
        { Diagram::Type::robustness, Analyzer::analyze_robustness_diagram },
        { Diagram::Type::sequence, Analyzer::analyze_sequence_diagram },
        { Diagram::Type::classes, Analyzer::analyze_classes_diagram }
    });

    functions[item.m_type](item, all_diagrams);
}

