#include <QRegExp>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include "analyzer.h"
#include <QDebug>
QStringList analyze_robustness_file(QString str);
//QStringList analyze_description(QMap<QString,Structures::complex>* list_elements, QString key, QJsonObject json_object, QStringList objects, ProjectData Project);

QStringList analyze_robustness_file(QString str)
{
    QStringList objects;
    QRegExp objects_all("\\b(actor |boundary |entity |control ).*(?=\\n)");
    objects_all.setMinimal(true);
    objects_all.setCaseSensitivity(Qt::CaseInsensitive);
    int index=0;
    while ((index= objects_all.indexIn(str,index))!=-1)
    {
        QStringList captured_object=objects_all.cap().split(" ");
        if (captured_object[0]!="actor")
        {
            if (captured_object.length()==2)
            {
                captured_object<<"as";
                captured_object<<captured_object[1];
            }
            else if (captured_object.length()>=4)
            {
                QStringList cap_obj;
                cap_obj<<captured_object[0]<<" ";
                int i=1;
                for (;captured_object[i]!="as"&&i<captured_object.length();i++)
                {
                    captured_object[i].remove("\"");
                    cap_obj[1]=cap_obj[1]+" "+captured_object[i];
                }
                cap_obj<<captured_object[i]<<captured_object[i+1];
                captured_object.clear();
                captured_object=cap_obj;
            }
            captured_object[1]="\":"+captured_object[1]+"\"";
            captured_object[1].remove("  ");
        }
        index+=objects_all.cap().length();
        objects<<captured_object.join(" ");
    }
    return objects;
}/*
QStringList analyze_description(QMap<QString,Structures::complex>* list_elements, QString key, QJsonObject json_object, QStringList objects, ProjectData Project)
{
    QStringList sequences;
    const QString format_text=".txt",format_picture=".png";
    int index_seq=0;
    for (;index_seq<json_object.count()-3;index_seq++)
    {
        QString str,name;
        QJsonValue seq_list=json_object.value("list_seq"+QString::number(index_seq));
        if (seq_list.toObject().value("type_seq").toString()=="main")
        {
            str.append("Главная последовательность:\n");
            name=key+"_main";
            list_elements->insert(name,{Structures::DiagramType::sequence,true});
        }
        else
        {
            str.append("Альтернативная последовательность "+QString::number(index_seq)+":\n");
            name=key+"_alt"+QString::number(index_seq);
            list_elements->insert(name,{Structures::sequence,true});
        }
        int index_elem=0;
        QJsonValue list_seq=seq_list.toObject().value("seq");
        if (!(list_seq.toObject().keys().empty()))
        {
            for (;index_elem<list_seq.toObject().keys().count();index_elem++)
            {
                QJsonValue elem_seq=list_seq.toObject().value(QString::number(index_elem));
                str.append(QString::number(index_elem)+") "+elem_seq.toString()+"\n");
            }
        }
        sequences<<str;
        QFile newfile(Project.path+"/"+Structures::type(Structures::sequence)+"/"+name+format_text);
        if (newfile.open(QIODevice::ReadWrite))
        {
            QTextStream text(&newfile);
            QString file_text;
            if (newfile.size()!=0)
            {
                file_text=text.readAll();
                QRegExp note("note left.*end note");
                int index=0;
                if ((index= note.indexIn(file_text,index))!=-1)
                {
                    file_text.replace(index,note.matchedLength(),"note left\n "+str+"end note");
                    newfile.resize(0);
                    text<<file_text;
                }
                else
                {
                    file_text.chop(7);
                    file_text.append("note left\n "+str+"\n end note");
                    newfile.resize(0);
                    text<<file_text<<objects.join(' ')<<"\n@enduml";
                }
            }
            else
            {
                text<<"@startuml\nnote left\n"<<str<<"end note\n"<<objects.join('\n')<<"\n@enduml";
            }
            newfile.close();
        }
    }
    return sequences;
 }
*/
/*
QMap<QString,Structures::complex> analyze_robustness_diagram(QString filename, ProjectData Project)
{
    QStringList objects,sequences;
    const QString format_text=".txt",format_picture=".png";
    QString str,file_str;
    QMap<QString,Structures::complex> list_elements;
    QFile file(Project.path+"/"+Structures::type(Structures::robustness)+"/"+filename+format_text);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in_file(&file);
        file_str=in_file.readAll();
        objects=analyze_robustness_file(file_str);
    }
    QFile desc(Project.path+"/"+"description.json");
    if (desc.exists())
    {
        if (desc.open(QIODevice::ReadOnly))
        {
            QJsonDocument doc = QJsonDocument::fromJson(desc.readAll());
            if (doc.isNull())
            {
            // qDebug()<<"Ошибка чтения JSON";
                return list_elements;
            }
            QJsonObject root = doc.object().value(filename).toObject();
            sequences<<analyze_description(&list_elements,filename,root,objects,Project);
            desc.close();
        }
    }
    return list_elements;
}
*/
