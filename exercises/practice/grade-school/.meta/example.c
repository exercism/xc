#include "grade_school.h"
#include <stdlib.h>
#include <string.h>

static roster_t roster = { 0 };

static int compare_student_names(const void *s1, const void *s2)
{
   const student_t *student1 = (const student_t *)s1;
   const student_t *student2 = (const student_t *)s2;
   return strncmp(student1->name, student2->name, MAX_NAME_LENGTH);
}

static int compare_student_grades_and_names(const void *s1, const void *s2)
{
   const student_t *student1 = (const student_t *)s1;
   const student_t *student2 = (const student_t *)s2;

   if (student1->grade > student2->grade)
      return 1;
   else if (student1->grade < student2->grade)
      return -1;
   else
      return compare_student_names(student1, student2);
}

static bool are_students_in_multiple_grades(roster_t students)
{
   for (size_t i = 0; i < students.count; ++i)
      for (size_t j = 0; j < students.count; ++j)
         if (i != j
             && !strncmp(students.students[i].name, students.students[j].name,
                         MAX_NAME_LENGTH)
             && students.students[i].grade != students.students[j].grade)
            return true;

   return false;
}

bool add_student(char *name, uint8_t grade)
{
   bool added = false;

   if (roster.count < MAX_STUDENTS) {
      roster.students[roster.count].name = name;
      roster.students[roster.count].grade = grade;
      ++roster.count;
      qsort(roster.students, roster.count, sizeof(roster.students[0]),
            compare_student_grades_and_names);
      added = true;
   }

   return added;
}

roster_t get_roster(void)
{
   return roster;
}

roster_t get_grade(uint8_t grade)
{
   roster_t grade_roster = { 0 };

   if (are_students_in_multiple_grades(roster))
      return grade_roster;

   for (size_t i = 0; i < roster.count && grade_roster.count < MAX_STUDENTS;
        ++i) {
      if (roster.students[i].grade == grade) {
         grade_roster.students[grade_roster.count].name =
             roster.students[i].name;
         grade_roster.students[grade_roster.count].grade = grade;
         ++grade_roster.count;
      }
   }
   return grade_roster;
}

void clear_roster(void)
{
   for (size_t i = 0; i < roster.count; ++i) {
      roster.students[i].name = NULL;
      roster.students[i].grade = 0;
   }
   roster.count = 0;
}
