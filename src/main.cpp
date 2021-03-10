#include "MainWindow.h"
#include "QtWidgets/QApplication"

int main(int argc,char** argv)
{
    QApplication* app=new QApplication(argc,argv);
    MainWindow* wnd=new MainWindow(NULL);
    wnd->show();
    app->exec();
    return 0;
}
