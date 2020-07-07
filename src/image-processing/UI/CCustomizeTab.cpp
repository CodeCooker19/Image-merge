#include "CCustomizeTab.h"
#include "../global.h"

//class CColorImage
//public:
CColorImage::CColorImage(QColor color, QWidget *parent) : QWidget(parent)
{

}

//protected:
void CColorImage::paintEvent(QPaintEvent *event){

}

//class CCustomizeTab
//public
CCustomizeTab::CCustomizeTab(QWidget *parent) : QWidget(parent)
{

}

CUSTOM_INFO CCustomizeTab::getCustomInfo(){

}

//private:
void CCustomizeTab::initUI(){

}

void CCustomizeTab::setupFontTree()
{

}

//private slots:
void CCustomizeTab::showFont(QTreeWidgetItem *item)
{

}

void CCustomizeTab::updateStyles(QTreeWidgetItem *item, int column)
{

}

void CCustomizeTab::onFontSizeChange(int nFontSize){

}

void CCustomizeTab::onFontColorClicked(){

}

void CCustomizeTab::onBackColorClicked(){

}

void CCustomizeTab::onOpacitySpinChange(int nOpacity){

}

void CCustomizeTab::onOpacitySliderChange(int nOpacity){

}

//protected:
void CCustomizeTab::showEvent(QShowEvent *event){

}
