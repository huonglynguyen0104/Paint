#include <QPushButton> 
#include <QComboBox>
#include <QLabel>
#include <QColorDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QDebug>
#include <QGroupBox>
#include <QRadioButton>
#include "paint.h"
#include "canvas.h"

/** c'tor */
Paint::Paint(QWidget *parent)
	: QWidget(parent)
{
	// instantiate Canvas and button
	viewport = new Canvas();

	btnClearCanvas = new QPushButton("&Clear Canvas");
    btnChangeBGColor = new QPushButton("& Change BG Color");

    cobPrimModes = new QComboBox();
    cobPrimModes->addItem(tr("None"), Canvas::NONE);
    cobPrimModes->addItem(tr("Line"), Canvas::LINE);
    cobPrimModes->addItem(tr("Freehand"), Canvas::FREE_HAND);
    cobPrimModes->addItem(tr("Circle"), Canvas::CIRCLE);
    cobPrimModes->addItem(tr("Rectangle"), Canvas::RECTANGLE);
    //cobPrimModes->addItem(tr("Triangle"), Canvas::TRIANGLE);
    //cobPrimModes->addItem(tr("Polygon"), Canvas::POLYGON);

    lblPrimModes = new QLabel("Primitive Mode");
    lblPrimModes->setBuddy(cobPrimModes);

    cobLineWidths = new QComboBox();
    cobLineWidths->addItem(tr("1.0"), Canvas::WIDTH1);
    cobLineWidths->addItem(tr("2.0"), Canvas::WIDTH2);
    cobLineWidths->addItem(tr("3.0"), Canvas::WIDTH3);
    cobLineWidths->addItem(tr("4.0"), Canvas::WIDTH4);

    lblLineWidths = new QLabel("Line Width");
    lblLineWidths->setBuddy(cobLineWidths);

    cobLineShapes = new QComboBox();
    cobLineShapes->addItem(tr("Solid Line"), Canvas::SOLIDLINE);
    cobLineShapes->addItem(tr("Dash Line"), Canvas::DASHLINE);
    cobLineShapes->addItem(tr("Dot Line"), Canvas::DOTLINE);

    lblLineShapes = new QLabel("Line Shape");
    lblLineShapes->setBuddy(cobLineShapes);

    btnDeleteObj = new QPushButton("&Delete Selected");
    btnDeleteObj->setDisabled(true);
    btnChangeCol = new QPushButton("C&hange Object Color");

    cbOutline = new QCheckBox("Show Only &Outline", this);
    cbBBoxes = new QCheckBox("Show all BBoxes", this);

    interactionModeGroup = new QGroupBox("Selection Tools");
    btnCreate = new QRadioButton(tr("Create"));
    btnDelete = new QRadioButton(tr("Delete"));
    btnSetColor = new QRadioButton(tr("Set Color"));
    btnTransform = new QRadioButton(tr("Transform"));

    btnCreate->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(btnCreate);
    vbox->addWidget(btnDelete);
    vbox->addWidget(btnSetColor);
    vbox->addWidget(btnTransform);
    interactionModeGroup->setLayout(vbox);

	// create layout and add gui elements to it
	QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(viewport,       0, 0, 1, 4);
    mainLayout->addWidget(btnChangeCol,   2, 3);
    mainLayout->addWidget(cbOutline,      2, 2, Qt::AlignRight);
    mainLayout->addWidget(lblPrimModes,   1, 2, Qt::AlignRight);
    mainLayout->addWidget(cobPrimModes,   1, 3);
    //mainLayout->addWidget(btnDeleteObj,   2, 0);
    mainLayout->addWidget(btnClearCanvas, 4, 3);
    mainLayout->addWidget(btnChangeBGColor, 3, 3);

    mainLayout->addWidget(interactionModeGroup, 1, 0 );
    mainLayout->addWidget(lblLineWidths,  2, 1, Qt::AlignLeft);
    mainLayout->addWidget(cobLineWidths,  2, 0);
    mainLayout->addWidget(lblLineShapes,  3, 1, Qt::AlignLeft);
    mainLayout->addWidget(cobLineShapes,  3, 0);
    mainLayout->addWidget(cbBBoxes,       3, 2, Qt::AlignRight);

	// add layout to this widget instance
	setLayout(mainLayout);
	
    // connect button click event to clear canvas handler
    connect(btnClearCanvas, SIGNAL(clicked()),
            this, SLOT(clearBtnPressed()));
    // connect button click event to delete selected object handler
    connect(btnDeleteObj, SIGNAL(clicked()),
            this, SLOT(deleteBtnPressed()));
    // connect button click event to color chooser handler
    connect(btnChangeCol, SIGNAL(clicked()),
            this, SLOT(colorBtnPressed()));
    // connect list view to primitive changed event handler
    connect(cobPrimModes, SIGNAL(activated(int)),
            this, SLOT(primModeChanged()));
    // connect checkbox to toggle outline event handler
    connect(cbOutline, SIGNAL(toggled(bool)),
            this, SLOT(showOutlineOnly(bool)));
    connect(btnCreate, SIGNAL(toggled(bool)),
            this, SLOT(interactionModeChanged()));
    connect(btnDelete, SIGNAL(toggled(bool)),
            this, SLOT(interactionModeChanged()));
    connect(btnSetColor, SIGNAL(toggled(bool)),
            this, SLOT(interactionModeChanged()));
    connect(btnTransform, SIGNAL(toggled(bool)),
            this, SLOT(interactionModeChanged()));
    connect(cobLineWidths, SIGNAL(activated(int)),
            this, SLOT(lineWidthChanged()));
    connect(cobLineShapes, SIGNAL(activated(int)),
            this, SLOT(lineShapeChanged()));
    connect(btnChangeBGColor, SIGNAL(clicked()),
            this, SLOT(changeBGColorBtnPressed()));
    connect(cbBBoxes, SIGNAL(toggled(bool)),
            this, SLOT(showBBoxes(bool)));
}

/** d'tor */
Paint::~Paint()
{
}

/** method for handling button clicked event */
void Paint::clearBtnPressed()
{
	viewport->clearCanvas();

	// force redraw
	update();
    qDebug() << "Clear image called";
}

void Paint::deleteBtnPressed()
{
    // Implementation requires inside test for all objects for selection
    qDebug() << "Next action: delete selected item (NYI)";
}

void Paint::colorBtnPressed()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if (color.isValid()) {
        qDebug() << "Color Choosen : " << color.name();
        viewport->setColor(color);
    }
}

void Paint::changeBGColorBtnPressed(){
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    if (color.isValid()) {
        qDebug() << "Color Choosen : " << color.name();
        viewport->changeBGColor(color);
        update();
        qDebug() << "Back Ground Color changed.";
    }
}

void Paint::showOutlineOnly(bool outline)
{
    qDebug() << "Only show outline: " << outline;
    viewport->setFillMode(!outline);
}

void Paint::showBBoxes(bool bBoxes) {
    qDebug() << "Show all BBoxes: " << bBoxes;
    viewport->setShowBBoxes(bBoxes);
}

void Paint::primModeChanged()
{
	int mode = cobPrimModes->itemData(
			   cobPrimModes->currentIndex(), Qt::UserRole).toInt();
	viewport->setPrimitiveMode(mode);
    qDebug() << "Primitive Mode changed to " << mode;
}

void Paint::lineWidthChanged()
{
    int mode = cobLineWidths->itemData(
                               cobLineWidths->currentIndex(), Qt::UserRole).toInt();
    viewport->setLineWidth(mode);
    qDebug() << "Line Width Mode changed to " << mode;
}

void Paint::lineShapeChanged()
{
    int mode = cobLineShapes->itemData(
                               cobLineShapes->currentIndex(), Qt::UserRole).toInt();
    viewport->setLineShape(mode);
    qDebug() << "Line Shape Mode changed to " << mode;
}

void Paint::interactionModeChanged(){
    int mode = 0;
    if (btnCreate->isChecked())     mode = 0;
    if (btnDelete->isChecked())     mode = 1;
    if (btnSetColor->isChecked())   mode = 2;
    if (btnTransform->isChecked())  mode = 3;

    viewport->setInteractionMode(mode);
    qDebug() << "Interaction Mode changed to " << mode;
}

