### Author: Justin Marcy
### Date: 2/14/2020

1) Display name and department of all instructors whose name beginning with letter J.
* Solution:
~~~~sql
SELECT name, dept_name FROM instructor WHERE name LIKE 'J%';
~~~~
* Result:

| name  | dept_name                 |
|:-------|:---------------------------|
| Joe   | History                   |
| James | Politics                  |
| Joe   | Electrical and Comp. Eng. |
| Jhon  | Math                      |
| Joe   | Comp. Eng.                |
| Jamie | Comp. Eng.                |
| Jerry | Comp. Eng.                |
| Jimbo | Graphics                  |
| Jeff  | Math                      |
| Josh  | Comp. Sci.                |

10 rows in set (0.00 sec)


2) Display name and department of all instructors whose name containing two or three letters.
* Solution:
~~~~sql
SELECT name, dept_name FROM instructor WHERE char_length(name)=3 OR char_length(name)=2;
~~~~
* Result:

| name | dept_name                 |
|:------|:---------------------------|
| Joe  | History                   |
| Sam  | Comp. Sci.                |
| Ben  | Chemistry                 |
| Tzu  | Military Science          |
| Hou  | Electrical and Comp. Eng. |
| Joe  | Electrical and Comp. Eng. |
| Tom  | Robotics                  |
| Joe  | Comp. Eng.                |

8 rows in set (0.00 sec)


3) Display the department and name of all instructors first by department, then by name, both in alphabetical order.
* Solution:
~~~~sql
SELECT dept_name, name FROM instructor ORDER BY dept_name;
~~~~
* Result:

| name       | dept_name                 |
|:------------|:---------------------------|
| Adams      | History                   |
| Allison    | Psychology                |
| Anise      | Physics                   |
| Ben        | Chemistry                 |
| Carl       | Comp. Sci.                |
| Charles    | History                   |
| Devito     | Physics                   |
| Echo       | Communications            |
| Einstein   | Physics                   |
| Fives      | Military Science          |
| Gabriel    | Comp. Sci.                |
| Hermes     | Political Science         |
| Hou        | Electrical and Comp. Eng. |
| James      | Politics                  |
| Jamie      | Comp. Eng.                |
| Jeff       | Math                      |
| Jerry      | Comp. Eng.                |
| Jhon       | Math                      |
| Jimbo      | Graphics                  |
| Joe        | History                   |
| Joe        | Electrical and Comp. Eng. |
| Joe        | Comp. Eng.                |
| Josh       | Comp. Sci.                |
| Kristen    | Statistics                |
| Lovelace   | Comp. Sci.                |
| Marbles    | Math                      |
| Marty      | Comp. Sci.                |
| Michael    | Chemistry                 |
| Newell     | Comp. Sci.                |
| O'Riley    | Music                     |
| Pearson    | Economics                 |
| Pepe       | U.S. History              |
| Ryan       | Comp. Sci.                |
| Sally      | Chemistry                 |
| Sam        | Comp. Sci.                |
| Smith      | Chemistry                 |
| Tom        | Robotics                  |
| Torvald    | Comp. Sci.                |
| Tyler      | U.S. History              |
| Tzu        | Military Science          |
| Viellas    | Digital Arts              |
| Washington | History                   |
| Young      | Military Science          |

43 rows in set (0.00 sec)

4) Use the set union operator to find out all the instructors from both `Comp. Sci.' and `Comp. Eng.' departments.
* Solution:
~~~~sql
SELECT name, dept_name FROM instructor 
WHERE dept_name LIKE '%Comp. Sci.' 
UNION 
SELECT name, dept_name FROM instructor 
WHERE dept_name LIKE '%Comp. Eng.';
~~~~
* Result:

| name     | dept_name                 |
|:----------|:---------------------------|
| Sam      | Comp. Sci.                |
| Gabriel  | Comp. Sci.                |
| Lovelace | Comp. Sci.                |
| Torvald  | Comp. Sci.                |
| Marty    | Comp. Sci.                |
| Ryan     | Comp. Sci.                |
| Newell   | Comp. Sci.                |
| Carl     | Comp. Sci.                |
| Josh     | Comp. Sci.                |
| Hou      | Electrical and Comp. Eng. |
| Joe      | Electrical and Comp. Eng. |
| Joe      | Comp. Eng.                |
| Jamie    | Comp. Eng.                |
| Jerry    | Comp. Eng.                |

14 rows in set (0.00 sec)
