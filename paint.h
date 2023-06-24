#ifndef PAINT_H
#define PAINT_H

#include "qgroupbox.h"
#include "qradiobutton.h"
#include <QWidget>

class QPushButton;
class QComboBox;
class QLabel;
class QCheckBox;
class Canvas;

class Paint : public QWidget
{
	Q_OBJECT

public:
	Paint(QWidget *parent = 0);
	~Paint();

private slots:
	void clearBtnPressed();
    void deleteBtnPressed();
    void colorBtnPressed();
    void changeBGColorBtnPressed();
	void primModeChanged();
    void interactionModeChanged();
    void lineWidthChanged();
    void lineShapeChanged();
    void showOutlineOnly(bool);

private:
	Canvas *viewport;

	QPushButton *btnClearCanvas;
    QPushButton *btnChangeBGColor;
	QComboBox *cobPrimModes;
    QComboBox *cobLineWidths;
    QComboBox *cobLineShapes;
	QLabel *lblPrimModes;
    QLabel *lblLineWidths;
    QLabel *lblLineShapes;
    QPushButton *btnDeleteObj;
    QPushButton *btnChangeCol;
    QCheckBox *cbOutline;
    QGroupBox* interactionModeGroup;
    QRadioButton *btnCreate;
    QRadioButton *btnDelete;
    QRadioButton *btnSetColor;
    QRadioButton *btnTransform;
};

#endif // PAINT_H
