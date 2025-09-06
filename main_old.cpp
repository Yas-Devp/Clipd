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


int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QWidget window ;
    window.setWindowTitle("ClipD Manager");
    window.setWindowIcon(QIcon("icon.png"));

    auto *layout = new QVBoxLayout();
    auto *list = new QListWidget();
    layout->addWidget(list);

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
        if (!text.isEmpty()){
            list->insertItem(0, text);
        }
        if (list->count() > 5){
            QListWidgetItem* item = list->takeItem(5);
            delete item;
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

    window.hide();

    return app.exec();
}
