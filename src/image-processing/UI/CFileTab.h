#ifndef CFILETAB_H
#define CFILETAB_H

#include <QWidget>
#include <QtWidgets>

class CFileTab : public QWidget
{
    Q_OBJECT
public:
    explicit CFileTab(QWidget *parent = nullptr);
    QList<QString>  getImagePaths();

private:
    void    initUI();
    void    showImportFileCount();

private:
    QPushButton     *m_pAddImageBtn;
    QPushButton     *m_pAddFolderBtn;
    QPushButton     *m_pRemoveFileBtn;
    QPushButton     *m_pClearFileBtn;

    QListWidget     *m_pFileListWidget;
    QLabel          *m_pImportLabel;
    QLabel          *m_pSelectLabel;

    QPushButton     *m_pAddExtBtn;
    QPushButton     *m_pRemoveExtBtn;
    QPushButton     *m_pClearExtBtn;

    QListWidget     *m_pExtListWidget;
    QLineEdit       *m_pExtLineEdit;

signals:

private slots:
    void    onAddImageClickded();
    void    onAddFolderClickded();
    void    onRemoveFileClickded();
    void    onClearFileClickded();
    void    onAddExtClickded();
    void    onRemoveExtClickded();
    void    onClearExtClickded();
    void    onFileSelectionChangeded();
};

#endif // CFILETAB_H
