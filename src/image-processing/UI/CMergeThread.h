#ifndef CMERGETHREAD_H
#define CMERGETHREAD_H

#include <QThread>
#include "../global.h"

class CMergeThread : public QThread
{
    Q_OBJECT
public:
    explicit CMergeThread(QObject *parent = nullptr);
    void run() override;

private:
    int             getRandNum();
    QList<QString>  getFiles();
    void            getMergeImage(QList<QString> listFiles);
    QString         getOutputFilePath();
    void            template1(QList<QString> listFiles);
    void            template2(QList<QString> listFiles);
    void            template3(QList<QString> listFiles);
    void            template4(QList<QString> listFiles);
    void            template5(QList<QString> listFiles);
    void            template6(QList<QString> listFiles);
    QImage          getAreaImage(int nW);
    QImage          getOverlayImage(int nW);
    void            addTextOverlayImage(QPainter &painter, QImage &targetImg, QImage &txtImg);

private:
    int     m_nCount;
    QList<QString>  m_listFiles;
    TEXT_INFO       m_textInfo;
    CUSTOM_INFO     m_customInfo;
    OUTPUT_INFO     m_outputInfo;

signals:
    void    processing(int index);

public slots:
};

#endif // CMERGETHREAD_H
