#include <QRegExp>
#include "analyzer.h"
#include <QDebug>

void Analyzer::analyze_robustness_diagram(Diagram& robustness, QVector<Diagram>& all_diagrams)
{
    QStringList objects;
    QRegExp objects_all("\\b(actor |boundary |entity |control ).*(?=\\n)");
    objects_all.setMinimal(true);
    objects_all.setCaseSensitivity(Qt::CaseInsensitive);
    int index=0;
    while ((index= objects_all.indexIn(robustness.m_text,index))!=-1)
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
            captured_object[1] = "\":" + captured_object[1] + "\"";
            captured_object[1].remove("  ");
        }
        index += objects_all.cap().length();
        objects<<captured_object.join(" ");
    }
    foreach (Diagram diag,all_diagrams)
    {
        if (diag.m_name.contains(robustness.m_name) &&
                diag.m_type == Diagram::Type::sequence)
        {
            int ind;
            if ((ind = diag.m_text.indexOf("end note\n")) != -1)
            {
                diag.m_text.insert(ind+9, '\n' + objects.join('\n') + '\n');
            }
            else
            {
                diag.m_text.insert(9, '\n' + objects.join('\n')+'\n');
            }
            diag.m_text.replace(diag.m_text.length()-7, 7, "\n@enduml");
            QStringList diag_text = diag.m_text.split('\n');
            diag_text.removeDuplicates();
            diag_text.removeAll("");
            diag.m_text = diag_text.join('\n');
            update(diag, all_diagrams);
        }
    }


}
