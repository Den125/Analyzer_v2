#include "analyzer.h"
#include <QDebug>

void Analyzer::analyze_sequence_diagram(Diagram& sequence, QVector<Diagram>& all_diagrams)
{
    QMap<QString,QStringList> class_list;
    QRegExp objects("\".*:.*\"\\sas\\s.*(?=\\n)");
    objects.setMinimal(true);
    int index=0;
    while ((index= objects.indexIn(sequence.m_text,index))!=-1)
    {
        QString class_name;
        class_name=objects.cap().split("\" ")[0];
        class_name=class_name.right(class_name.length()-class_name.indexOf(":",0)-1);
        qDebug()<<class_name;
        QString class_psevdo=objects.cap().split(" ")[2];
        QRegExp class_method("("+class_psevdo+"\\s-\\W{1,}\\s\\w*|\\w*\\s<\\W{1,}\\s"+class_psevdo+")\\s:.*\\n");
        class_method.setMinimal(true);
        QStringList methods;
        int index2=index;
        while ((index2=class_method.indexIn(sequence.m_text,index2))!=-1)
        {
            QStringList method=class_method.cap().split(" : ");
            method[1].chop(1);
            methods<<method[1]+"()";
            index2+=class_method.matchedLength();
        }
        class_list.insert(class_name,methods);
        index=index+objects.matchedLength();
    }
    Diagram classes;
    foreach (Diagram diag,all_diagrams)//упростить?
    {
        if (diag.m_type==Diagram::Type::classes)
        {
            classes=diag;
            break;
        }
    }

    foreach (QString name_class,class_list.keys())
    {
        //TODO сделай реализацию
        QRegExp find_class("class "+name_class+"\\{.*\\}");
        int index=0;
        if ((index=find_class.indexIn(classes.m_text,index))!=-1)
        {

        }
        else
        {
            classes.m_text.insert(9,"\nclass "+name_class+"{\n"+class_list.value(name_class).join('\n')+"\n}");
        }
    }
    update(classes,all_diagrams);
}
