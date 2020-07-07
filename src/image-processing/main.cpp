#include <QApplication>

#include "widgetgallery.h"
#include "CMainTabDialog.h"

CMainTabDialog *g_pMainDlg;

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(styles);

    QApplication app(argc, argv);

    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    CMainTabDialog tabDialog;
    g_pMainDlg = &tabDialog;
    tabDialog.show();

    return app.exec();
}
