#include "searchtasksallprojectsdialog.h"
#include "ui_searchtasksallprojectsdialog.h"

SearchTasksAllProjectsDialog::SearchTasksAllProjectsDialog(QWidget *parent, QString src) :
    QDialog(parent),
    ui(new Ui::SearchTasksAllProjectsDialog)
{
    ui->setupUi(this);
    this->search = src;
    getSearchResults(search);
}

SearchTasksAllProjectsDialog::~SearchTasksAllProjectsDialog()
{
    delete ui;
}

const QString &SearchTasksAllProjectsDialog::getSearch() const
{
    return search;
}

void SearchTasksAllProjectsDialog::getSearchResults(QString term){
    QList<Task> tasks = _taskDataService.fetchAllTasks(term);
    QList<Task>::iterator i;
    QListWidget *results = ui->SearchResults;
    results->setItemDelegate(new TaskSearchResultDelegate(results));
    for(i = tasks.begin(); i != tasks.end(); ++i){
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DisplayRole, i->returnTitle());
        item->setData(Qt::UserRole + 1, i->returnDescription());
        item->setData(Qt::ToolTipRole, i->returnState());
        item->setData(Qt::DecorationRole, i->returnProject());
        item->setData(Qt::SizeHintRole, i->returnUser());
        results->addItem(item);
    }


}
