#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QClipboard>
#include <QListWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <string>
#include <QSystemTrayIcon>
#include <iostream>
#include <cstdlib>
#include <vector>


void copyToClipboard(std::string text) {
    text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());
    std::string command = "echo \"" + text + "\" | xclip -selection clipboard";
    system(command.c_str());
}


int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QWidget window ;
    window.setWindowTitle("ClipD Manager");
    window.setWindowIcon(QIcon("icon.png"));

    auto *layout = new QVBoxLayout();
    auto *list = new QListWidget();
    layout->addWidget(list);

    std::vector<std::string> copiedTexts;

    QObject::connect(QApplication::clipboard(), &QClipboard::dataChanged, [&](){
        //QString text = QApplication::clipboard()->text();
        std::string tt = QApplication::clipboard()->text().toStdString();
        std::string text_ = "";

        //avoiding long texts show
        if (tt.find("\n") != std::string::npos){
            text_ = tt.substr(0, tt.find("\n")) + "...";
        }else  if (tt.length() > 35){
            text_ = tt.substr(0, 35) + "...";
        }else{
            text_ = tt;
        }

        //item adding
        QString text = QString::fromStdString(text_);


        for(int i = 0 ; i < list->count() ; i++){
            if (list->item(i)->text().toStdString() == text_){
                return;
            }
        }
        if (!text.isEmpty()){
            list->insertItem(0, text);
        }
        if (list->count() > 5){
            QListWidgetItem* item = list->takeItem(5);
            delete item;
            copiedTexts[0] = copiedTexts[1];
            copiedTexts[1] = copiedTexts[2];
            copiedTexts[2] = copiedTexts[3];
            copiedTexts[3] = copiedTexts[4];
            copiedTexts[4] = text_;

        }else{
            copiedTexts.push_back(text_);
        }
    });

    window.setLayout(layout);
    window.resize(400, 300);

    if (QSystemTrayIcon::isSystemTrayAvailable()){
        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon("icon.png"), &app);
        QMenu *trayMenu = new QMenu();
        QAction *showAction = trayMenu->addAction("Show");
        QAction *hideAction = trayMenu->addAction("hide");
        QAction *quitAction = trayMenu->addAction("Quit");

        QObject::connect(showAction, &QAction::triggered, [&](){
            window.showNormal();
            window.activateWindow();
        });

        QObject::connect(hideAction, &QAction::triggered, [&](){
            window.hide();
        });
        QObject::connect(quitAction, &QAction::triggered, &app, &QApplication::quit);

        trayIcon->setContextMenu(trayMenu);
        trayIcon->show();

        QObject::connect(trayIcon, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason){
            if(reason == QSystemTrayIcon::Trigger){
                window.showNormal();
                window.activateWindow();
            }
        });
    }else{
        std::cout << "trayIcon not possible to start !" << std::endl;
    }

    QObject::connect(list, &QListWidget::itemClicked, [&](QListWidgetItem* item){
        copyToClipboard(list->item(list->row(item))->text().toStdString());
        QListWidgetItem* item_select = list->takeItem(0);
        delete item_select;
    });

    window.hide();

    return app.exec();
}
