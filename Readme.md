** MINI SQL ENGINE **

Input Specifications:
1. csv files for tables, without any extra space or tab.
2. Values can be in double quotes or without quotes.
3. All the elements in files would be only INTEGERS.
4. A file named: metadata.txt(note the extension) with the following structure for each table:
	<begin_table>
	<table_name>
	<attribute1>
	....
	<attributeN>
	<end_table>

Type of Queries (with Error handing): 
1. Select all records.
	-> Select * from table_name;
2. Aggregate functions: Simple aggregate functions on a single column. Sum, average, max and min. 
	-> select max(col1) from table1;
3. Project Columns(could be any number of columns) from one or more tables.
	-> Select col1, col2 from table_name;
	-> Select with distinct from one table 
	-> select distinct(col1),col2 from table_name;
4. Select with where from one or more tables with a maximum of one AND/OR operator and no NOT operators..
	-> select col1,col2 from table1,table2 where col1 = 10 AND col2= 20;
5. Projection of one or more(including all the columns) from two tables with one join condition.
   *NO REPITION OF COLUMNS – THE JOINING COLUMN SHOULD BE PRINTED ONLY ONCE.*
	-> select * from table1, table2 where table1.col1=table2.col2;
	-> select col1,col2 from table1,table2 where table1.col1=table2.col2;

