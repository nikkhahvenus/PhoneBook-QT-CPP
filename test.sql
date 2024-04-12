//bool DbClass::createTables()
//{
//    if(!(dbClassPtr->phoneDB.isValid() && dbClassPtr->phoneDB.isOpen())){
//        Logger::dLog("Run readyConnection to make DB connection ready to use");
//        return false;
//    }
////    bool AllTablesCreated = true;
//    QSqlDatabase &db= dbClassPtr->phoneDB;

//    QSqlQuery query(db);

//    const QString createSQL = "CREATE TABLE IF NOT EXISTS customers ( "
//                                      "                customerID INTEGER PRIMARY KEY AUTOINCREMENT, "
//                                      "                firstName VARCHAR, "
//                                      "                lastName VARCHAR"
//                                      ");";



//    if (!query.exec(createSQL)) {
//        Logger::dLog("Create table error: %1" + query.lastError().text());
//    }
//    return true;
//}


//void MainWindow::on_pushButton_clicked()
//{
//    QString id,family,name;
//    id = "120";
//    name = "hamid";
//    family = "zzz";

//    QSqlQuery qry;
//    qry.prepare("insert into tbl (id,name,family)  values(149, 'Dennis', 'Young')");

////        qry.prepare("INSERT INTO tbl (id,name,family) VALUES (:id,:name,:family)");
////        qry.bindValue(":id", id);
////        qry.bindValue(":name", name);
////        qry.bindValue(":family", family);

////        qry.prepare("INSERT INTO tbl (name,family) VALUES (:name,:family)");
////        qry.bindValue(":name", name);
////        qry.bindValue(":family", family);

////        qry.prepare("insert into tbl (id,name,family) values ('"+id+"','"+name+"','"+family+"')" );

////        qry.prepare("insert into tbl (name,family) values ('"+name+"','"+family+"')" );
//    if(qry.exec()){
//        QMessageBox::critical(this,"save","saved");

//    }
//    else{
//        QMessageBox::critical(this,"error:",qry.lastError().text());
//    }
//}


--dbClassPtr->phoneDB.removeDatabase(QSqlDatabase::defaultConnection);


--while (query.next()) {
--        int id = query.value(0).toInt();
--        QString filename = query.value(1).toString();
--        int filesize = query.value(2).toInt();
--        QDateTime lastupdate = query.value(3).toDateTime();
--        qDebug() << id << " " << filename << " " << filesize << " " << lastupdate;
--    }
--CREATE TABLE IF NOT EXISTS `table1` (

--    `id` INTEGER,
--    `bla1` TEXT,
--    PRIMARY KEY(`id`)
--);
--CREATE TABLE IF NOT EXISTS `table2` (
--    `id` INTEGER,
--    `bla2` TEXT,
--    PRIMARY KEY(`id`)
--);

--INSERT INTO `table2` (`bla2`) VALUES ('Hello World!');

--INSERT INTO owner (phone) VALUES ('09177001982');


--CREATE TABLE IF NOT EXISTS owner (
--    id INTEGER PRIMARY KEY AUTOINCREMENT,
--    phone VARCHAR(12) UNIQUE NOT NULL
--);




--CREATE TABLE IF NOT EXISTS `CloudFile` (
--  `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
--  `FileName` varchar(255) NOT NULL,
--  `FileSize` INTEGER NOT NULL DEFAULT 0,
--  `LastUpdate` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
--) ;
--INSERT INTO CloudFile (FileName,FileSize) VALUES ('f.txt',2000);
--SELECT * FROM `CloudFile` ;
