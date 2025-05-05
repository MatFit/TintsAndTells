#ifndef QGIVERNOTIFICATION_H
#define QGIVERNOTIFICATION_H
#include <QDialog>
#include <QString>
#include "style.h"
#include "player.h"

// ============================================================================
// Class: QGiverNotification
// Overview:
//   Handles new UI notifications to make the Q-Giver recieve their color
//   more seamlessly
// ============================================================================


namespace Ui {
// This must match the class name inside ui_qGiverNotification.h
class QGiverNotification;
class QGiverRecieveColor;
}

class QGiverNotification : public QDialog
{
    Q_OBJECT

public:
    explicit QGiverNotification(QWidget *parent = nullptr, QGiver *giver = nullptr); // Constructor
    ~QGiverNotification(); // Deconstructor
    void styleQGiverNotificationUI(); // First UI for QGiver
    void styleQGiverRecieveColorUI(Ui::QGiverRecieveColor* ui_2); // Second UI for QGiver
    void showGiverColorScreen(); // Helps transition first UI to second

private:
    // Dialog pointer to be used for UI
    QDialog* colorDialog = nullptr;
    // UI's for Q-Giver
    Ui::QGiverNotification *ui;
    Ui::QGiverRecieveColor *ui_2;

    // Use QGiver for it's name and style class to style
    QGiver *giver;
    Style *style;
};

#endif // QGIVERNOTIFICATION_H
