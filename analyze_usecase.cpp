#include "analyzer.h"
#include <QDebug>

QVector<Diagram> analyze_usecase_diagram(Diagram use_case)
{
    QVector<Diagram> list_precedents;
    QString find_str;
    QRegExp ucase ("(((?:usecase )((\\w+( as \".+\")?)|(\".+\" as \\w+)))|(\\(\\w+\\)))(?=\\n)");
    ucase.setMinimal(true);
    ucase.setCaseSensitivity(Qt::CaseInsensitive);
    int index=0;
    while ((index= ucase.indexIn(use_case.m_text, index))!=-1)
    {
        QString capture_str=ucase.cap();
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
        list_precedents.push_back(Diagram(Diagram::Type::robustness, find_str, ""));
        find_str.clear();
        index+=ucase.matchedLength();

    }
    //Analyze::get_actors_list(list_precedents,Project.path);
    return list_precedents;
}

QMap<QString,QStringList> Analyzer::get_actors_list(QVector<Diagram> diagrams)
{
    QMap<QString,QStringList> list_actors;
}
/*
QMap<QString,QStringList> Analyze::get_actors_list(QMap<QString,Structures::complex> list_elements,QString project_path)
{
    QMap<QString,QStringList> list_actors;
    QFile file(project_path+"/"+Structures::type(Structures::DiagramType::use_case)+"/use_case.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        return list_actors;
    }
    QString text_use_case=file.readAll();
    QMap<QString,QString> text_precedents;
    foreach (QString key,list_elements.keys())
    {
        if (list_elements.value(key).type==Structures::robustness)
        {

            QRegExp actor;
            actor.setPattern("\\w*\\s(\\W*|\\W*(left|right|up|down)\\W*)\\s"+key);
            actor.setMinimal(true);
            int index=0;
            while ((index= actor.indexIn(text_use_case,index))!=-1)
            {
                QString captured_element=actor.cap().split(" ")[0];
                if (text_precedents.find(captured_element)!=text_precedents.end())
                {
                    text_precedents.insert(key,text_precedents.value(key)+"("+captured_element+")\n");
                }
                else
                {
                    text_precedents.insert(key,text_precedents.value(key)+"actor "+captured_element+"\n");
                    list_actors.insert(key,QStringList()<<list_actors.value(key)<<captured_element);//captured_element,QStringList()<<list_actors.value(captured_element)<<key);
                }
                index+=actor.matchedLength();
            }
            QFile newf;
            newf.setFileName(project_path+"/"+Structures::type(Structures::robustness)+"/"+key+".txt");
            if (newf.exists() && newf.size()!=0)
            {
                 if (newf.open(QIODevice::ReadWrite))
                    {
                        QTextStream text(&newf);
                        QString str_newf=text.readAll();
                        str_newf.remove(0,9);
                        QStringList file_list;
                        file_list<<text_precedents.value(key).split('\n')<<str_newf.split('\n');
                        file_list.removeDuplicates();
                        file_list.removeAll(QString(""));
                        newf.resize(0);
                        text<<"@startuml\n"<<file_list.join('\n');
                        newf.close();
                    }
            }
            else
            {
                if (newf.open(QIODevice::WriteOnly))
                {
                    QTextStream text(&newf);
                    text<<"@startuml\n"<<text_precedents.value(key)<<"@enduml";
                    newf.close();
                }
            }

        }
    }
    return list_actors;
}

QMap<QString,Structures::complex> analyze_usecase_diagram(QString filename, ProjectData Project)
{
    QMap<QString,Structures::complex> list_precedents;
    QFile usecaseFile(Project.path+"//"+Structures::type(Structures::use_case)+"//"+filename+".txt");
    if (!usecaseFile.open(QIODevice::ReadOnly))
        return list_precedents;
    QString str=usecaseFile.readAll();
    QString find_str;
    QRegExp ucase("(usecase (.*|\\(.*\\)\\sas\\s.*)|\\(.*\\)(\\sas\\s.*)?)(?=\\n)");
    ucase.setMinimal(true);
    ucase.setCaseSensitivity(Qt::CaseInsensitive);
    int index=0;
    while ((index= ucase.indexIn(str,index))!=-1)
    {
        QString capture_str=ucase.cap();
        for (int i=capture_str.lastIndexOf(' ')+1;i<capture_str.length()&&capture_str[i]!=')';i++)
        {
            if (capture_str[i]=='(') continue;
            find_str=find_str+capture_str[i];
        }
        index+=ucase.matchedLength();
        list_precedents.insert(find_str,{Structures::DiagramType::robustness,true});
        find_str.clear();
    }
    usecaseFile.close();
    Analyze::get_actors_list(list_precedents,Project.path);
    return list_precedents;
}*/
