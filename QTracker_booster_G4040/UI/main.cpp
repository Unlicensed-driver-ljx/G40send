//#include "qtracker.h"
#include "slidingwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QtNetwork/QNetworkInterface>
#include "Tool/GlobalParameter.h"

QStringList getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    int nCnt = nets.count();
    QStringList strMacAddrList;
    strMacAddrList.clear();
    for(int i = 0; i < nCnt; i ++)
    {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp)  && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddrList.append(nets[i].hardwareAddress());
        }
    }
    return strMacAddrList;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GlobalParameter* g_param = GlobalParameter::getInstance();
    QString addr = g_param->trackParam.sn;
    if(addr.size() != 19)
    {
        QMessageBox::information(NULL, "Abort", "The lincense is not correct");
        return 0;
    }
    else
    {
        addr.remove(0, 5);
        addr.remove("-");
        addr.insert(10, ":");
        addr.insert(8, ":");
        addr.insert(6, ":");
        addr.insert(4, ":");
        addr.insert(2, ":");
    }
    QStringList sn = getHostMacAddress();
    if(sn.contains(addr, Qt::CaseInsensitive) || QString::compare(addr, g_param->key, Qt::CaseInsensitive) == 0)
    {
        //QTracker w;
        SlidingWindow w;
        //w.showMaximized();
        w.show();
        return a.exec();
    }
    else
    {
        QMessageBox::information(NULL, "Abort", "The lincense is not correct");
        return 0;
    }
}
