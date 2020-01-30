#include "analyzer.h"
#include <QDebug>

void Analyzer::analyze_usecase_diagram(Diagram& use_case, QVector<Diagram>& all_diagrams)
{
    QString find_str;

    QRegExp ucase ("(((?:usecase )((\\w+( as \".+\")?)|(\".+\" as \\w+)))|(\\(\\w+\\)))(?=\\n)");
    ucase.setMinimal(true);
    ucase.setCaseSensitivity(Qt::CaseInsensitive);
    QVector<QString> robustnessDg;

    int index=0;
    while ((index = ucase.indexIn(use_case.m_text, index))!=-1)
    {
        QString capture_str = ucase.cap();
        if (capture_str.startsWith('('))
        {
            find_str = capture_str.mid(1, capture_str.length()-2);
        }
        else if (capture_str.startsWith("usecase"))
        {
            QStringList captured=capture_str.split(" ");
            if (captured[1].startsWith("\""))
            {
                find_str = captured[captured.indexOf(QRegExp("\\bas\\b"), 2) + 1];
            }
            else find_str = captured[1];
        }

        insert(Diagram(Diagram::Type::robustness, find_str, ""), all_diagrams);
        robustnessDg.push_back(find_str);
        find_str.clear();
        index+=ucase.matchedLength();
    }
    for (int i=0;i<all_diagrams.count();i++)
    {
        if (std::find_if(robustnessDg.begin(), robustnessDg.end(), [=](QString name) {
                    return name == all_diagrams[i].m_name;
                })==robustnessDg.end()
                && all_diagrams[i].m_type == Diagram::Type::robustness)
        {
            remove(all_diagrams[i],all_diagrams);
        }
    }
    Analyzer::get_actors_list(all_diagrams);
}

QMap<QString,QStringList> Analyzer::get_actors_list(QVector<Diagram> &diagrams)
{
    QMap<QString,QStringList> list_actors;
    auto usecaseIt = std::find_if(diagrams.begin(), diagrams.end(), [](const Diagram& diag) {
        return diag.m_type==Diagram::Type::use_case;
    });

    if (usecaseIt == diagrams.end()) {
        return list_actors;
    }

    QMap<QString,QString> text_precedents;
    foreach (Diagram diag,diagrams)
    {
        if (diag.m_type==Diagram::Type::robustness)
        {
            QRegExp actor;
            actor.setPattern("\\w*\\s(\\W*|\\W*(left|right|up|down)\\W*)\\s"+diag.m_name);
            actor.setMinimal(true);
            int index=0;
            while ((index= actor.indexIn(usecaseIt->m_text,index))!=-1)
            {
                QString captured_element=actor.cap().split(" ")[0];
                if (text_precedents.find(captured_element)!=text_precedents.end())
                {
                    text_precedents.insert(diag.m_name,text_precedents.value(diag.m_name)+"("+captured_element+")");
                }
                else
                {
                    text_precedents.insert(diag.m_name,text_precedents.value(diag.m_name)+"actor "+captured_element);
                    list_actors.insert(diag.m_name,QStringList()<<list_actors.value(diag.m_name)<<captured_element);
                }
                index+=actor.matchedLength();
            }
            if (diag.m_text.isEmpty())
            {
                diag.m_text="@startuml\n"+text_precedents.value(diag.m_name)+"\n@enduml";
            }
            else
            {
                diag.m_text.remove(0,9);
                QStringList diag_text;
                diag_text<<text_precedents.value(diag.m_name)<<diag.m_text.split('\n');
                diag_text.removeDuplicates();
                diag_text.removeAll(QString(""));
                diag.m_text="@startuml\n"+diag_text.join('\n');
            }

        }
        update(diag,diagrams);
    }
    return list_actors;
 }
