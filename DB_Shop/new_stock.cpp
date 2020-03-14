#include "new_stock.h"
#include "ui_new_stock.h"

new_stock::new_stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_stock)
{
    ui->setupUi(this);

    DB.Connect();

    if(DB.IsConnected() == false){
        qDebug() << "Database connection error";
        exit(0);
    }

    supplier_called = false;

    set_input_method();

    load_suppliers();

}

new_stock::~new_stock()
{
    DB.Disconnect();
    delete ui;
}

void new_stock::on_btn_addsupplier_clicked()
{
    supplier_called = true;

    this->close();

    /*
    New_supplier* supplier = new New_supplier(this,0,0);
    supplier->setFixedSize(supplier->width(),supplier->height());
    DB.Disconnect();
    supplier->exec();
    DB.Connect();
    */
}

void new_stock::load_suppliers(){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Company name\" from suppliers";

    if(DB.Execute(query_str,query)==false){
        qDebug() << query.lastQuery();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal,"Company name");

    ui->tbl_supplier->setModel(model);

    ui->tbl_supplier->setColumnWidth(0,180);

    ui->tbl_supplier->setSelectionMode(QAbstractItemView::SingleSelection);
}


bool new_stock::new_supplier_called(){
    return supplier_called;
}

void new_stock::set_input_method(){

    ui->txt_cost->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));
    ui->txt_stock->setValidator(new QRegExpValidator(QRegExp("[0-9]*"),this));

}

bool new_stock::check_inputs(){

    QItemSelectionModel *select = ui->tbl_supplier->selectionModel();

    if(select->hasSelection() == false){
        QMessageBox::warning(this,"Input Error","First select a supplier or add new one");
        return false;
    }

    if(ui->txt_name->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Stock name");
        return false;
    }

    if(ui->txt_category->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Category");
        return false;
    }

    if(ui->txt_cost->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Cost value");
        return false;
    }

    if(ui->txt_stock->text().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Stock number");
        return false;
    }

    if(ui->textEdit->toPlainText().remove(" ").isEmpty() == true){
        QMessageBox::warning(this,"Input Error","Enter Description");
        return false;
    }

    return true;
}


void new_stock::on_tbl_supplier_clicked(const QModelIndex &index)
{
    QString Category = get_category(index.data().toString());

    ui->txt_category->setText(Category);

}


QString new_stock::get_category(QString Company){

    QString query_str;
    QSqlQuery query;

    query_str = "select \"Company Type\" from suppliers where \"Company name\" = \'" + Company + "\';";

    if(DB.Execute(query_str,query) == false){
        qDebug() << query.lastQuery() << query.lastError();
        return "";
    }

    query.first();

    return query.value(0).toString();
}
