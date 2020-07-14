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
    QImage sourceImg(listFiles.at(0));
    QImage txtImg;
    int nW, nH;
    nW = PANEL_SIZE + 2 * INTERVAL_SIZE;
    nH = PANEL_SIZE + 2 * INTERVAL_SIZE;

    if(m_textInfo.m_bIsArea){//insert area
        if(m_textInfo.m_nAreaPos == TOP || m_textInfo.m_nAreaPos == BOTTOM){
            txtImg = getAreaImage(PANEL_SIZE);
            nH += txtImg.height();
        }

        QImage targetImg(nW, nH, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&targetImg);
        painter.fillRect(targetImg.rect(), Qt::white);

        switch (m_textInfo.m_nAreaPos) {
        case TOP:
            painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE, txtImg);
            painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE + txtImg.height(), sourceImg);
            break;
        case BOTTOM:
            painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE, sourceImg);
            painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE + sourceImg.height(), txtImg);
            break;
        default:
            painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE, sourceImg);
            break;
        }

        painter.end();
        targetImg.save(getOutputFilePath());
    }
    else{//overlay
        if(m_textInfo.m_nOverlayPos != NONE_OVERLAY){
            txtImg = getOverlayImage(PANEL_SIZE * 0.7);
        }

        QImage targetImg(nW, nH, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&targetImg);
        painter.fillRect(targetImg.rect(), Qt::white);
        painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE, sourceImg);

        addTextOverlayImage(painter, targetImg, txtImg);

        painter.end();
        targetImg.save(getOutputFilePath());
    }
}

void CMergeThread::template2(QList<QString> listFiles){
    QImage sourceImg[2];
    QImage txtImg;
    int nW, nH;
    int nImageCount;

    nImageCount = g_ImageCount[m_outputInfo.m_nTemplate];
    nW = PANEL_SIZE*2 + 3 * INTERVAL_SIZE;
    nH = PANEL_SIZE + 2 * INTERVAL_SIZE;

    for(int i=0; i < nImageCount; i++){
        sourceImg[i] = QImage(listFiles.at(i));
    }

    if(m_textInfo.m_bIsArea){//insert area
        if(m_textInfo.m_nAreaPos == TOP || m_textInfo.m_nAreaPos == BOTTOM){
            txtImg = getAreaImage(PANEL_SIZE*2 + INTERVAL_SIZE);
            nH += txtImg.height();
        }

        QImage targetImg(nW, nH, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&targetImg);
        painter.fillRect(targetImg.rect(), Qt::white);

        switch (m_textInfo.m_nAreaPos) {
        case TOP:
            painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE, txtImg);
            for(int i=0; i < nImageCount; i++){
                painter.drawImage(INTERVAL_SIZE*(i+1) + PANEL_SIZE*i, INTERVAL_SIZE + txtImg.height(), sourceImg[i]);
            }
            break;
        case BOTTOM:
            for(int i=0; i < nImageCount; i++){
                painter.drawImage(INTERVAL_SIZE*(i+1) + PANEL_SIZE*i, INTERVAL_SIZE, sourceImg[i]);
            }
            painter.drawImage(INTERVAL_SIZE, INTERVAL_SIZE + PANEL_SIZE, txtImg);
            break;
        default:
            for(int i=0; i < nImageCount; i++){
                painter.drawImage(INTERVAL_SIZE*(i+1) + PANEL_SIZE*i, INTERVAL_SIZE, sourceImg[i]);
            }
            break;
        }

        painter.end();
        targetImg.save(getOutputFilePath());
    }
    else{//overlay
        if(m_textInfo.m_nOverlayPos != NONE_OVERLAY){
            txtImg = getOverlayImage(PANEL_SIZE * 0.7);
        }

        QImage targetImg(nW, nH, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&targetImg);
        painter.fillRect(targetImg.rect(), Qt::white);

        for(int i=0; i < nImageCount; i++){
            painter.drawImage(INTERVAL_SIZE*(i+1) + PANEL_SIZE*i, INTERVAL_SIZE, sourceImg[i]);
        }

        addTextOverlayImage(painter, targetImg, txtImg);

        painter.end();
        targetImg.save(getOutputFilePath());
    }
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
    if(m_textInfo.m_listText.isEmpty() || (m_textInfo.m_bIsArea && m_textInfo.m_nAreaPos == NONE_AREA)){
        //not input text in text tab.
        return QImage();
    }

    int nTxtW, nTxtH, nLine;
    QFont font = m_customInfo.m_font;
    QFontMetrics mt(font);
    QString strText;
    int nRand;
    nRand = getRandNum() % m_textInfo.m_listText.count();

    strText = m_textInfo.m_listText.at(nRand);
    nTxtW = mt.width(strText);
    nLine = nTxtW/nW;

    if(nTxtW % nW != 0)
        nLine++;
    nTxtH = nLine * mt.height();

    QImage txtImg(nW, nTxtH, QImage::Format_ARGB32_Premultiplied);
    QPainter painterTxt(&txtImg);
    painterTxt.setFont(font);
    painterTxt.setPen(m_customInfo.m_colorFont);
    painterTxt.fillRect(txtImg.rect(), m_customInfo.m_colorBack);
    QTextOption options;
    options.setTextDirection(Qt::LayoutDirectionAuto);
    options.setWrapMode(QTextOption::WordWrap);
    options.setAlignment(Qt::AlignCenter);
    painterTxt.drawText(txtImg.rect(), strText, options);
    painterTxt.end();

    return txtImg;
}

QImage CMergeThread::getOverlayImage(int nW){
    if(m_textInfo.m_listText.isEmpty() || (!m_textInfo.m_bIsArea && m_textInfo.m_nOverlayPos == NONE_OVERLAY)){
        //not input text in text tab.
        return QImage();
    }

    int nTxtW, nTxtH, nLine;
    QFont font = m_customInfo.m_font;
    QFontMetrics mt(font);
    QString strText;
    int nRand;
    nRand = getRandNum() % m_textInfo.m_listText.count();

    strText = m_textInfo.m_listText.at(nRand);
    nTxtW = mt.width(strText);
    nLine = nTxtW/nW;

    if(nTxtW % nW != 0)
        nLine++;
    nTxtH = nLine * mt.height();

    QImage txtImg(nW, nTxtH, QImage::Format_ARGB32_Premultiplied);
    QPainter painterTxt(&txtImg);
    painterTxt.setFont(font);
    painterTxt.setPen(m_customInfo.m_colorFont);
    painterTxt.setOpacity(((qreal)m_customInfo.m_nOpacity)/(qreal)100.0);
    painterTxt.fillRect(txtImg.rect(), m_customInfo.m_colorBack);
    QTextOption options;
    options.setTextDirection(Qt::LayoutDirectionAuto);
    options.setWrapMode(QTextOption::WordWrap);
    options.setAlignment(Qt::AlignCenter);
    painterTxt.setOpacity(1);
    painterTxt.drawText(txtImg.rect(), strText, options);
    painterTxt.end();

    return txtImg;
}

void CMergeThread::addTextOverlayImage(QPainter &painter, QImage &targetImg, QImage &txtImg){
    switch (m_textInfo.m_nOverlayPos) {
    case TOP_LEFT:
        painter.drawImage(INTERVAL_SIZE*3, INTERVAL_SIZE*3, txtImg);
        break;
    case TOP_CENTER:
        painter.drawImage((targetImg.width() - txtImg.width())/2, INTERVAL_SIZE*3, txtImg);
        break;
    case TOP_RIGHT:
        painter.drawImage(targetImg.width() - txtImg.width() - INTERVAL_SIZE*3, INTERVAL_SIZE*3, txtImg);
        break;
    case MIDDLE_LEFT:
        painter.drawImage(INTERVAL_SIZE*3, (targetImg.height() - txtImg.height())/2, txtImg);
        break;
    case MIDDLE_CENTER:
        painter.drawImage((targetImg.width() - txtImg.width())/2, (targetImg.height() - txtImg.height())/2, txtImg);
        break;
    case MIDDLE_RIGHT:
        painter.drawImage(targetImg.width() - txtImg.width() - INTERVAL_SIZE*3, (targetImg.height() - txtImg.height())/2, txtImg);
        break;
    case BOTTOM_LEFT:
        painter.drawImage(INTERVAL_SIZE*3, targetImg.height() - txtImg.height() - INTERVAL_SIZE*3, txtImg);
        break;
    case BOTTOM_CENTER:
        painter.drawImage((targetImg.width() - txtImg.width())/2, targetImg.height() - txtImg.height() - INTERVAL_SIZE*3, txtImg);
        break;
    case BOTTOM_RIGHT:
        painter.drawImage(targetImg.width() - txtImg.width() - INTERVAL_SIZE*3, targetImg.height() - txtImg.height() - INTERVAL_SIZE*3, txtImg);
        break;
    default:
        break;
    }
}
