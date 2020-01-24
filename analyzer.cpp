#include "analyzer.h"
#include <set>
#include <QDebug>
#include <algorithm>

/*
QMap<QString,complex> analyze_current_file(DiagramType type, QString name, ProjectData Project);

QMap<QString,Structures::complex> analyze_robustness_diagram(QString filename, ProjectData Project);

QMap<QString, Structures::complex> analyze_usecase_diagram(QString filename, ProjectData Project);

QMap<QString,QStringList> analyze_sequence_diagram(QString filename, ProjectData Project);

QMap<QString,Structures::complex> Analyzer::analyze(QMap<QString,Structures::complex> list_elements,
                    QString project_path)
{
    ProjectData Project;
    Project.mapElements=list_elements;
    Project.path=project_path;
    setFalseAllStatus(Project);
    foreach(QString name,Project.mapElements.keys())
    {
        QMap<QString,complex> newElements=analyze_current_file(Project.mapElements[name].type,name,Project);
        foreach (QString key,Project.mapElements.keys())
        {
            if (newElements.find(key)!=newElements.end())
            {
                Project.mapElements[key].status=true;
                newElements.remove(key);
            }
        }
        Project.mapElements.unite(newElements);
    }
    return Project.mapElements;
}

QMap<QString,complex> analyze_current_file(DiagramType type, QString name,ProjectData Project)
{
    switch (type)
    {
        case Structures::use_case:
        {
            return analyze_usecase_diagram(name, Project);
        }
        case Structures::robustness:
        {
            return analyze_robustness_diagram(name,Project);
        }
        case Structures::sequence:
        {
            // TODO проверка модели
            // TODO нужен тест!
            analyze_sequence_diagram(name,Project);
            //анализ диаграммы последовательности не вносит изменения в список элементов
            //изменения вносятся только в предментную область
            QMap<QString,complex> new_structure;
            //это  чтобы программа не падала
            return new_structure;
        }
        case Structures::classes:
        {
            QMap<QString,complex> new_structure;
            return new_structure;
        }
    }
}
*/

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

