#include "pch.h"

#include "process.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QMainWindow *mw = new QMainWindow(nullptr);
    {
        mw->setWindowTitle("process_key_events");
        mw->setMinimumSize(350, 300);
        mw->setMaximumSize(350, 300);
    }
    mw->show();


    QListWidget *lw = new QListWidget(mw);
    {
        lw->resize(150, 200);
    }
    lw->show();


    QListWidget *lw_info = new QListWidget(mw);
    {
        lw_info->setGeometry(200, 0, 150, 200);
    }
    lw_info->show();



    QPushButton *pb_select = new QPushButton(mw);
    {
        pb_select->setText("select");
        pb_select->setGeometry(0, 200, 75, 25);
        
        QObject::connect(pb_select, QPushButton::clicked, [lw, lw_info]()
        {
            process::RemoveKeyboardHook();

            if (lw->currentItem()) 
            {
                auto res = lw->currentItem()->text().toStdWString();
                int begin = res.find_last_of(L'(')+1;

                int pid = std::stoi(res.c_str()+begin);

                process::SetHook(pid, lw_info);
            }
            // qDebug() << "pb_select";
        });
    }
    pb_select->show();


    QPushButton *pb_update = new QPushButton(mw);
    {
        pb_update->setText("update");
        pb_update->setGeometry(75, 200, 75, 25);
        
        QObject::connect(pb_update, QPushButton::clicked, [lw]()
        {
            lw->clear();
            lw->addItems(process::GetAllProcess());
            // qDebug() << "pb_update"; 
        });
    }
    pb_update->show();
    

    return app.exec();
}