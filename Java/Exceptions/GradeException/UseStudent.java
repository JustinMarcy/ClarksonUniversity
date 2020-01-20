import Student.Student;

public class UseStudent {
  Student ms1 = Student("ms1",{});
  Student ms2 = Student("ms2",{10.0,5,3.5,6,4});
  ms1.updateCourseGrades(10.5,40);
  ms2.updateCourseGrades(8,-6.5,20.0);

  system.out.println(ms1.numStudents());
  system.out.println(msi.numStudents());

  system.out.println(ms1.listGrades());
  system.out.println(msi.listgrades());

}
