#include "CMergeThread.h"
#include "../CMainTabDialog.h"

CMergeThread::CMergeThread(QObject *parent) : QThread(parent)
{
    m_listFiles = g_pMainDlg->getFileWidget()->getImagePaths();
    m_textInfo = g_pMainDlg->getTextWidget()->getTextInfo();
    m_customInfo = g_pMainDlg->getCustomWidget()->getCustomInfo();
    m_outputInfo = g_pMainDlg->getOutputWidget()->getOuputInfo();
}

void CMergeThread::run()
{
    QList<QString> listFiles;
    for(int i=0; i < m_outputInfo.m_nCount; i++){
        emit(processing(i+1));
        qsrand(QDateTime::currentMSecsSinceEpoch());
        listFiles = getFiles();
        if(listFiles.empty())
            continue;

        getMergeImage(listFiles);
    }
}

//private:
int CMergeThread::getRandNum(){
    int nRand;
    nRand = rand() * QTime::currentTime().msec();
    qDebug() << nRand;
    return nRand;
}

QList<QString> CMergeThread::getFiles(){
    QList<QString> list;
    for(int i=0; i < g_ImageCount[m_outputInfo.m_nTemplate]; i++){
        QString strPath;
        strPath = m_listFiles.at(getRandNum() % m_listFiles.count());
        list.append(strPath);
    }

    return list;
}

void CMergeThread::getMergeImage(QList<QString> listFiles){
    int nTemplate = m_outputInfo.m_nTemplate;

    switch (nTemplate) {
    case 0:
        template1(listFiles);
        break;
    case 1:
        template2(listFiles);
        break;

    case 2:
        template3(listFiles);
        break;
    case 3:
        template4(listFiles);
        break;
    case 4:
        template5(listFiles);
        break;
    case 5:
        template6(listFiles);
        break;
    default:
        break;
    }
}

QString CMergeThread::getOutputFilePath(){
    QString strRet, strRandName;
    strRet = m_outputInfo.m_strOutputPath + "\\" + m_outputInfo.m_strKeyword;
    strRandName = QString::number(getRandNum()%100) + "-" + QString::number(getRandNum()%1000) + "-"  + QString::number(getRandNum()%10000) + ".jpg";
    strRet += strRandName;

    return strRet;
}

void CMergeThread::template1(QList<QString> listFiles){

}

void CMergeThread::template2(QList<QString> listFiles){

}

void CMergeThread::template3(QList<QString> listFiles){

}

void CMergeThread::template4(QList<QString> listFiles){

}

void CMergeThread::template5(QList<QString> listFiles){

}

void CMergeThread::template6(QList<QString> listFiles){

}

QImage CMergeThread::getAreaImage(int nW){

}

QImage CMergeThread::getOverlayImage(int nW){

}

void CMergeThread::addTextOverlayImage(QPainter &painter, QImage &targetImg, QImage &txtImg){

}
