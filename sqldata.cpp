#include "sqldata.h"

Sqldata::Sqldata()
{
 connOpen();
 qry->prepare("select * from DataInfo");
 if(qry->exec())
     {
       while(qry->next()){
        data->weekday=qry->value(0).toString();
        data->BeginTime=qry->value(1).toString();
        data->EndTime=qry->value(2).toString();

       }
}

