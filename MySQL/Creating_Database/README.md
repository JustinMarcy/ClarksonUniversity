### Author: Justin Marcy
### Date: 1/27/2020

## Creating a database
~~~~sql
CREATE database university;
~~~~
## Select the database
~~~~sql
USE university;
~~~~
## Creating a table (ex. department)
~~~~sql
CREATE table department (dept_name varchar(25), building varchar(10), budget integer, PRIMARY KEY(dept_name));
~~~~
## Modifying data type or size of a column
~~~~sql
ALTER table department modify building char(15); 
~~~~
## Inserting data into a table (ex. department)
~~~~sql
INSERT into department (dept_name, building, budget) values
    -> ("Electrical and Comp. Eng.", "CAMP", 20000),
    -> ("Physics", "Science Center", 10000),
    -> ("Comp. Eng.", "Science Center", 10101),
    -> ("Comp. Sci.", "Science Center", 32000),
    -> ("Military Science", "Snell", 50000),
    -> ("History", "Snell", 10050),
    -> ("Politics", "Snell", 10030),
    -> ("Digital Arts", "Snell", 10700),
    -> ("Graphics", "Snell", 10900),
    -> ("U.S. History", "Snell", 30000),
    -> ("Chemistry", "Science Center", 56700),
    -> ("Math", "Science Center", 20000),
    -> ("Political Science", "Science Center", 25000),
    -> ("Statistics", "Science Center", 20600),
    -> ("Robotics", "Science Center", 19500),
    -> ("Psychology", "Snell", 30700),
    -> ("Music", "Snell", 21500),
    -> ("Economics", "Snell", 40100),
    -> ("Software Eng", "CAMP", 56000),
    -> ("Communications", "Snell", 50000);
~~~~
## Count number of rows in a table
~~~~sql
select count(*) from instructor;
~~~~
* Result:

| count(*) |
|:---------|
|       43 |
