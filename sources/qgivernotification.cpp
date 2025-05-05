#include "qgivernotification.h"
#include "ui_qGiverNotification.h"
#include "ui_qGiverRecieveColor.h"


// -----------------------------------------------------------------------------
// ~QGiverNotification()
// Destructor that free up ui's from memory
// -----------------------------------------------------------------------------
QGiverNotification::~QGiverNotification()
{
    delete ui;
    delete ui_2;
}

// -----------------------------------------------------------------------------
// QGiverNotification()
// Constructor to set up initial ui and connect button functionalities
// -----------------------------------------------------------------------------
QGiverNotification::QGiverNotification(QWidget *parent, QGiver* giver)
    : QDialog(parent), ui(new Ui::QGiverNotification), ui_2(new Ui::QGiverRecieveColor), giver(giver)
{
    ui->setupUi(this);
    style = Style::getInstance();
    styleQGiverNotificationUI();
    setWindowModality(Qt::WindowModal);

    connect(ui->continue_, &QPushButton::clicked, this, &QGiverNotification::showGiverColorScreen);
}

// -----------------------------------------------------------------------------
// styleQGiverNotificationUI()
// Method to style first ui
// -----------------------------------------------------------------------------
void QGiverNotification::styleQGiverNotificationUI() {
    style->stylePushButtons(ui->cancel);
    style->stylePushButtons(ui->continue_);
    style->styleQGiverNotificationLabel(ui->label, giver->getName());
    style->styleNotificationTextEdit(ui->text_box);
}

// -----------------------------------------------------------------------------
// styleQGiverNotificationUI()
// Method to style second ui
// -----------------------------------------------------------------------------
void QGiverNotification::styleQGiverRecieveColorUI(Ui::QGiverRecieveColor* ui_2) {
    style->stylePushButtons(ui_2->ready);
    style->styleQGiverNotificationRecieveLabel(ui_2->title);
    style->styleQGiverNotificationRecieveLabel(ui_2->location);
    style->styleQGiverNotificationRecieveTextBox(ui_2->desc);

    // Set background of the color QTextEdit
    QColor trueColor = giver->getTrueColor();
    QString colorStyle = QString("background-color: %1;").arg(trueColor.name());
    ui_2->colorDisplay->setStyleSheet(colorStyle);

    // Set the Location text
    int x = giver->getLocationofTrueColorX(); // row (starts at 0)
    int y = giver->getLocationofTrueColorY(); // col (starts at 0)

    // Adjust for display
    QChar xLetter('A' + x);   // 0 -> A, 1 -> B, 2 -> C, etc.
    int yNumber = y + 1;       // 0 -> 1, 1 -> 2, etc.

    ui_2->location->setText(QString("Location : %1 , %2").arg(xLetter).arg(yNumber));
}

// -----------------------------------------------------------------------------
// showGiverColorScreen()
// Method that handles transition between both ui's
// -----------------------------------------------------------------------------
void QGiverNotification::showGiverColorScreen() {
    // Create a new dialog
    colorDialog = new QDialog();
    ui_2->setupUi(colorDialog);

    // Style it AFTER setupUi
    styleQGiverRecieveColorUI(ui_2);
    colorDialog->setStyleSheet("background-color: black;");

    // Connect the ready button to close the colorDialog
    connect(ui_2->ready, &QPushButton::clicked, colorDialog, &QDialog::accept);

    this->accept(); // close the first notification

    colorDialog->setWindowModality(Qt::WindowModal);
    colorDialog->exec();
}
