#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>

class SearchFilterWidget : public QWidget {
    Q_OBJECT
public:
    explicit SearchFilterWidget(QWidget *parent = nullptr);

signals:
    void searchTextChanged(const QString& text);
    void filterChanged(const QString& filter);

private:
    void setupUI();
    QLineEdit* searchEdit;
    QComboBox* filterCombo;
};
