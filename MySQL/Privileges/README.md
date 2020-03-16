### Author: Justin Marcy
### Date: 3/11/2020

1) Create two new users, secretary and chair.
* Solution:
~~~~sql
CREATE USER secretary IDENTIFIED BY 'password';
#Query OK, 0 rows affected (0.01 sec)
CREATE USER chair IDENTIFIED BY 'password';
#Query OK, 0 rows affected (0.01 sec)
~~~~

* No databases should be visible yet. 
~~~~sql
#Verify these two users by login to mysql:
SYSTEM mysql -u secretary -p
Enter password: *******
SHOW databases;
~~~~

| Database           |
|:--------------------|
| information_schema |

1 row in set (0.02 sec)


2) Allow user secretary select and insert permissions on the course table:
* Solution:
~~~~sql
SYSTEM mysql -u root -p
USE university;
#Database changed
GRANT select ON course TO secretary;
#Query OK, 0 rows affected (0.01 sec)
SELECT * from course;
~~~~

| course_id | title     | dept_name                 | credits |
|:-----------|:-----------|:---------------------------|:---------|
| CS460     | Databases | Comp. Sci.                |       3 |
| EE468     | Databases | Electrical and Comp. Eng. |       3 |

2 rows in set (0.01 sec)

~~~~sql
GRANT insert on course to secretary;
#Query OK, 0 rows affected (0.01 sec)
~~~~

3) Create a view, called instructor_name_dept, on instructor. instructor_name_dept should include only name and dept of an instructor, but without salary info. Grant select on view instructor_name_dept  to secretary. 
* Solution:
~~~~sql
CREATE VIEW instructor_name_dept AS SELECT name, dept_name FROM instructor;
#Query OK, 0 rows affected (0.01 sec)
GRANT SELECT on instructor_name_dept to john;
#Query OK, 0 rows affected (0.01 sec)
~~~~


4) Grant chair all permissions on all tables in University.
* Solution:
~~~~sql
GRANT ALL PRIVILEGES ON university.* TO chair;
#Query OK, 0 rows affected (0.01 sec)
~~~~
