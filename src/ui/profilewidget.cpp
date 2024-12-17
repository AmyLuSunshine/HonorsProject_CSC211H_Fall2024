#include "ui/profilewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

ProfileWidget::ProfileWidget(Database* db, QWidget *parent)
    : QWidget(parent), database(db) {
    setupUI();
    setupStyles();
}

void ProfileWidget::setupUI() {
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 40, 40, 40);

    // Personal Information Section
    auto personalInfoGroup = new QGroupBox("Personal Information", this);
    auto personalLayout = new QVBoxLayout(personalInfoGroup);

    nameLabel = new QLabel(this);
    nameLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    emplidEdit = new QLineEdit(this);
    emplidEdit->setPlaceholderText("EMPLID");
    emplidEdit->setReadOnly(true);  // EMPLID shouldn't be editable

    majorEdit = new QLineEdit(this);
    majorEdit->setPlaceholderText("Major");

    gpaEdit = new QLineEdit(this);
    gpaEdit->setPlaceholderText("GPA");

    gradDateEdit = new QDateEdit(this);
    gradDateEdit->setDisplayFormat("MM/yyyy");
    gradDateEdit->setCalendarPopup(true);

    personalLayout->addWidget(nameLabel);
    personalLayout->addWidget(new QLabel("EMPLID:"));
    personalLayout->addWidget(emplidEdit);
    personalLayout->addWidget(new QLabel("Major:"));
    personalLayout->addWidget(majorEdit);
    personalLayout->addWidget(new QLabel("GPA:"));
    personalLayout->addWidget(gpaEdit);
    personalLayout->addWidget(new QLabel("Expected Graduation:"));
    personalLayout->addWidget(gradDateEdit);

    mainLayout->addWidget(personalInfoGroup);

    // Document Upload Section
    auto documentsGroup = new QGroupBox("Documents", this);
    auto documentsLayout = new QVBoxLayout(documentsGroup);

    uploadTranscriptBtn = new QPushButton("Upload Transcript", this);
    uploadCVBtn = new QPushButton("Upload CV", this);
    transcriptLabel = new QLabel("No transcript uploaded", this);
    cvLabel = new QLabel("No CV uploaded", this);

    documentsLayout->addWidget(uploadTranscriptBtn);
    documentsLayout->addWidget(transcriptLabel);
    documentsLayout->addWidget(uploadCVBtn);
    documentsLayout->addWidget(cvLabel);

    mainLayout->addWidget(documentsGroup);

    // Document Status Overview
    auto statusGroup = new QGroupBox("Document Status Overview", this);
    auto statusLayout = new QHBoxLayout(statusGroup);

    pendingDocsLabel = new QLabel("Documents Pending: 3", this);
    completedDocsLabel = new QLabel("Documents Completed: 5", this);
    processingDocsLabel = new QLabel("In Processing: 2", this);

    pendingDocsLabel->setStyleSheet("background: #FFECB3; padding: 10px; border-radius: 5px;");
    completedDocsLabel->setStyleSheet("background: #C8E6C9; padding: 10px; border-radius: 5px;");
    processingDocsLabel->setStyleSheet("background: #BBDEFB; padding: 10px; border-radius: 5px;");

    statusLayout->addWidget(pendingDocsLabel);
    statusLayout->addWidget(completedDocsLabel);
    statusLayout->addWidget(processingDocsLabel);

    mainLayout->addWidget(statusGroup);

    // Buttons
    auto buttonLayout = new QHBoxLayout;
    saveButton = new QPushButton("Save Changes", this);
    onboardingButton = new QPushButton("View Onboarding Status", this);

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(onboardingButton);

    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(saveButton, &QPushButton::clicked, this, &ProfileWidget::handleSaveChanges);
    connect(onboardingButton, &QPushButton::clicked, this, &ProfileWidget::handleOnboarding);
    connect(uploadTranscriptBtn, &QPushButton::clicked, this, &ProfileWidget::uploadTranscript);
    connect(uploadCVBtn, &QPushButton::clicked, this, &ProfileWidget::uploadCV);
}

void ProfileWidget::setupStyles() {
    setStyleSheet(
        "QGroupBox { font-weight: bold; border: 1px solid #DDD; border-radius: 5px; margin-top: 1ex; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px; }"
        "QLineEdit { padding: 8px; border: 1px solid #DDD; border-radius: 4px; }"
        "QPushButton { background-color: #2196F3; color: white; padding: 8px 16px; "
        "             border-radius: 4px; }"
        "QPushButton:hover { background-color: #1976D2; }"
        "QLabel { color: #333333; }"
        );

    onboardingButton->setStyleSheet(
        "QPushButton { background-color: #4CAF50; }"
        "QPushButton:hover { background-color: #388E3C; }"
        );
}

void ProfileWidget::loadUserProfile(const QString& username) {
    // TODO: Load actual data from database
    nameLabel->setText("Student Name: " + username);
    emplidEdit->setText("24580830");
    majorEdit->setText("Computer Science");
    gpaEdit->setText("3.50");
    gradDateEdit->setDate(QDate::currentDate().addYears(2));
}

void ProfileWidget::handleSaveChanges() {
    // TODO: Save to database
    QMessageBox::information(this, "Success", "Profile updated successfully!");
}

void ProfileWidget::handleOnboarding() {
    showDocumentStatus();
}

void ProfileWidget::uploadTranscript() {
    QString fileName = QFileDialog::getOpenFileName(this, "Upload Transcript",
                                                    "", "PDF Files (*.pdf);;All Files (*)");
    if (!fileName.isEmpty()) {
        transcriptLabel->setText("Transcript uploaded: " + QFileInfo(fileName).fileName());
        transcriptLabel->setStyleSheet("color: green;");
    }
}

void ProfileWidget::uploadCV() {
    QString fileName = QFileDialog::getOpenFileName(this, "Upload CV",
                                                    "", "PDF Files (*.pdf);;Word Documents (*.doc *.docx);;All Files (*)");
    if (!fileName.isEmpty()) {
        cvLabel->setText("CV uploaded: " + QFileInfo(fileName).fileName());
        cvLabel->setStyleSheet("color: green;");
    }
}

void ProfileWidget::showDocumentStatus() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Document Status");
    msgBox.setText(
        "In-Person Document Holds:\n"
        "- Original I-9 Documentation (Submit to: HR Office Room S-701)\n"
        "  Deadline: Within 3 days of start date\n\n"
        "- Social Security Card (Submit to: Payroll Office Room S-702)\n"
        "  Deadline: Before first paycheck\n\n"
        "Online Submit Holds:\n"
        "- W-4 Form (Status: Pending Submission)\n"
        "- Direct Deposit Form (Status: Pending Submission)"
        );
    msgBox.exec();
}
