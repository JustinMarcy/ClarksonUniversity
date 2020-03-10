### Author: Justin Marcy
### Date: 3/4/2020

## Description:
Practice and understand 'join' between idependent and related tables. Use the 'university' Database.

1) Find name and salary of instructors who earn more than at least one person in Comp. Sci. Department
'''
USE university;
SELECT name, salary
FROM instructor
WHERE salary > (
SELECT MIN(salary) 'Min Salary'
FROM instructor 
WHERE instructor.dept_name='Comp. Sci.'
)
'''
* Result:
+------------+--------+
| name       | salary |
+------------+--------+
| Joe        |  58000 |
| James      |  93000 |
| Echo       |  70000 |
| Washington |  95000 |
| Sam        |  45000 |
| Ben        |  56000 |
| Tzu        |  80000 |
| Gabriel    |  88000 |
| Hou        |  90000 |
| Adams      |  65000 |
| Marbles    |  57800 |
| Pearson    |  75000 |
| Allison    |  85000 |
| Lovelace   |  78000 |
| Pepe       |  89500 |
| Torvald    |  99000 |
| Viellas    | 130000 |
| Einstein   |  95000 |
| Joe        |  65000 |
| Tom        |  70000 |
| Charles    |  55000 |
| O'Riley    |  60000 |
| Kristen    |  66000 |
| Marty      |  60000 |
| Jhon       |  70000 |
| Tyler      |  87000 |
| Michael    |  76000 |
| Smith      |  98780 |
| Fives      |  75000 |
| Devito     |  99000 |
| Joe        |  71000 |
| Anise      |  89000 |
| Newell     |  98000 |
| Jamie      |  93000 |
| Jerry      |  96000 |
| Jimbo      |  50000 |
| Hermes     |  45000 |
| Young      |  75000 |
| Jeff       |  67000 |
| Carl       |  70000 |
| Josh       |  65000 |
+------------+--------+
41 rows in set (0.00 sec)

2) Find all courses taught in both the Fall 2019 semester and in the Spring 2020 semester.
'''
USE university;
SELECT DISTINCT course_id
FROM teaches
WHERE (teaches.semester = 1 AND teaches.year = 2019) 
OR (teaches.semester = 2 AND teaches.year = 2020)
'''
* Result:
+-----------+
| course_id |
+-----------+
| CS141     |
+-----------+
1 row in set (0.00 sec)

3) Find the names of instructors who teach a course in the Spring 2019 semester
'''
USE university;
SELECT name
FROM instructor
WHERE ID IN (
SELECT instr_id
FROM teaches
WHERE teaches.semester = 1 AND teaches.year = 2019
)
'''
* Result:
+---------+
| name    |
+---------+
| Sam     |
| Gabriel |
+---------+
2 rows in set (0.00 sec)

4) Find distinct names of student taught by instructor with id 7101.
'''
USE university;
SELECT name
FROM student 
WHERE id IN (
SELECT id
FROM takes
WHERE course_id IN (
SELECT course_id
FROM teaches
WHERE instr_id=7101
)
)
'''
* Result
+----------+
| name     |
+----------+
| Zhang    |
| Shankar  |
| Levy     |
| Williams |
| Bourikas |
+----------+
5 rows in set (0.00 sec)
