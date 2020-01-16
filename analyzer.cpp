#include "analyzer.h"
#include <QDebug>
QVector<Diagram> analyze_current_diagramm(Diagram current);

QVector<Diagram> analyze_usecase_diagram(Diagram use_case);

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
QVector<Diagram> Analyzer::analyze(QVector<Diagram> diagrams)
{
    QVector<Diagram> newElements;
    foreach(Diagram element, diagrams)
    {
        newElements = analyze_current_diagramm(element);

        diagrams.append(newElements);
        newElements.clear();
     }
    return diagrams;
}

QVector<Diagram> analyze_current_diagramm(Diagram item)
{
    switch (item.m_type)
    {
        case Diagram::Type::use_case:
        {
            return analyze_usecase_diagram(item);
        }
        case Diagram::Type::robustness:
        {
            //return analyze_robustness_diagram(item);
        }
        case Diagram::Type::sequence:
        {
            // TODO проверка модели
            // TODO нужен тест!
           // analyze_sequence_diagram(name,Project);
            //анализ диаграммы последовательности не вносит изменения в список элементов
            //изменения вносятся только в предментную область
           // QMap<QString,complex> new_structure;
            //это  чтобы программа не падала
           // return new_structure;
        }
        case Diagram::Type::classes:
        {
            //QMap<QString,complex> new_structure;
           // return new_structure;
        }
    }
}

