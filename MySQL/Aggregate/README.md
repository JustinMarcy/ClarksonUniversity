### Author: Justin Marcy
### Date: 2/28/2020

1) Find the total number of instructors per department.
* Solution: 
~~~~sql
SELECT dept_name, count(*) FROM instructor 
GROUP BY dept_name;
~~~~
* Result:

| dept_name                 | count(*) |
|:---------------------------|:----------|
| Chemistry                 |        4 |
| Communications            |        1 |
| Comp. Eng.                |        3 |
| Comp. Sci.                |        9 |
| Digital Arts              |        1 |
| Economics                 |        1 |
| Electrical and Comp. Eng. |        2 |
| Graphics                  |        1 |
| History                   |        4 |
| Math                      |        3 |
| Military Science          |        3 |
| Music                     |        1 |
| Physics                   |        3 |
| Political Science         |        1 |
| Politics                  |        1 |
| Psychology                |        1 |
| Robotics                  |        1 |
| Statistics                |        1 |
| U.S. History              |        2 |

19 rows in set (0.00 sec)

2) Find the names and average salaries of all departments whose average salary is between 70000 and 80000 dollars.
* Solution:
~~~~sql
USE university;
SELECT dept_name, AVG(salary) 'Average Salary' 
FROM instructor
GROUP BY dept_name
HAVING AVG(salary) > 70000 AND AVG(salary) < 80000
~~~~
* Result:

| dept_name                 | AVG(salary) |
|:---------------------------|:-------------|
| Comp. Sci.                |  71666.6667 |
| Economics                 |  75000.0000 |
| Electrical and Comp. Eng. |  77500.0000 |
| Military Science          |  76666.6667 |

4 rows in set (0.00 sec)

3) Find the total number of instructors who teach a course in the Spring 2019 semester.
* Solution:
~~~~sql
SELECT instr_id, COUNT(distinct instr_id) FROM teaches 
WHERE teaches.semester=2 AND teaches.year=2019;
~~~~
* Result:


| instr_id | COUNT(distinct instr_id) |
|:----------|:--------------------------|
|     7101 |                        3 |

1 row in set (0.00 sec)

4) Find instructors who earn more than everyone in the Comp. Sci. Department.
~~~~sql
USE university;
SELECT name
FROM instructor
WHERE salary > (
SELECT MAX(salary) 'Max Salary'
FROM instructor 
where instructor.dept_name='Comp. Sci.'
)
~~~~
* Result:


| name    |
|:---------:|
| Viellas |

1 row in set (0.00 sec)


5)  Find the distinct names of students who take a course in the Spring 2019 semester.
* Solution:
~~~~sql
USE university;
SELECT distinct name
FROM student
WHERE id IN (
SELECT id 
FROM takes
WHERE takes.semester=2 AND takes.year=2019
)
~~~~
* Result:

| name     |
|:---------|
| Zhang    |
| Shankar  |
| Peltier  |
| Levy     |
| Williams |
| Megan    |
| Bourikas |

7 rows in set (0.00 sec)


