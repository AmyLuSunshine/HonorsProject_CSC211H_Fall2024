#include "ui/searchfilterwidget.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

SearchFilterWidget::SearchFilterWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void SearchFilterWidget::setupUI() {
    auto layout = new QVBoxLayout(this);
    searchEdit = new QLineEdit(this);
    filterCombo = new QComboBox(this);

    layout->addWidget(searchEdit);
    layout->addWidget(filterCombo);

    connect(searchEdit, &QLineEdit::textChanged,
            this, &SearchFilterWidget::searchTextChanged);
    connect(filterCombo, &QComboBox::currentTextChanged,
            this, &SearchFilterWidget::filterChanged);
}
