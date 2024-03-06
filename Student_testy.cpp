#include <gtest/gtest.h>
#include "Student.h"

TEST(StudentConstructorTest, CreateStudentWithValidNameAndID) {
    Student student("John Doe", "JD123");
    EXPECT_EQ(student.getName(), "John Doe");
    EXPECT_EQ(student.getStudentID(), "JD123");
}

TEST(StudentConstructorTest, CreateStudentWithInvalidName) {
    Student student("J0hn*^", "JD123");
    EXPECT_NE(student.getName(), "J0hn*^");
    EXPECT_EQ(student.getStudentID(), "JD123");
}

TEST(StudentConstructorTest, CreateStudentWithInvalidID) {
    Student student("John Doe", "123!!!");
    EXPECT_EQ(student.getName(), "John Doe");
    EXPECT_NE(student.getStudentID(), "123!!!");
}

TEST(StudentConstructorTest, CreateStudentWithInvalidNameAndID) {
    Student student("J0hn*^", "123!!!");
    EXPECT_NE(student.getName(), "J0hn*^");
    EXPECT_NE(student.getStudentID(), "123!!!");
}

TEST(StudentConstructorTest, CreateStudentWithValidNameIDAndEmptySchedule) {
    Schedule emptySchedule;
    Student student("Alice Smith", "AS123", emptySchedule);
    EXPECT_EQ(student.getName(), "Alice Smith");
    EXPECT_EQ(student.getStudentID(), "AS123");
    EXPECT_TRUE(student.getPrintedSchedule().empty());
}

TEST(StudentConstructorTest, CreateStudentWithValidNameIDAndPopulatedSchedule) {
    Schedule schedule;
    Subject math("Math", "MATH101", 5);
    schedule.addSubjectToSchedule(math);
    Student student("Bob Johnson", "BJ456", schedule);
    EXPECT_EQ(student.getName(), "Bob Johnson");
    EXPECT_EQ(student.getStudentID(), "BJ456");
    EXPECT_FALSE(student.getPrintedSchedule().empty());
    EXPECT_EQ(student.getSchedule().findSubjectIndexInScheduleByCode("MATH101"), 0);
}

TEST(StudentConstructorTest, CreateStudentWithInvalidNameIDButValidSchedule) {
    Schedule schedule;
    Subject physics("Physics", "PHYS101", 4);
    schedule.addSubjectToSchedule(physics);
    Student student("J@ne D0e", "123!!", schedule);
    EXPECT_NE(student.getName(), "J@ne D0e");
    EXPECT_NE(student.getStudentID(), "123!!");
    EXPECT_FALSE(student.getPrintedSchedule().empty());
}

TEST(StudentTest, EnrollNewSubjectSuccessfully) {
    Student student("John Doe", "JD123");
    Subject math("Math", "MATH101", 5);
    EXPECT_TRUE(student.enrollSubject(math));
}

TEST(StudentTest, EnrollSameSubjectTwice) {
    Student student("Alice Smith", "AS456");
    Subject physics("Physics", "PHYS101", 4);
    student.enrollSubject(physics);
    EXPECT_FALSE(student.enrollSubject(physics));
}

TEST(StudentTest, CheckEnrolledSubjectsCountAfterEnrollment) {
    Student student("Bob Johnson", "BJ789");
    Subject chemistry("Chemistry", "CHEM101", 4);
    student.enrollSubject(chemistry);
    auto enrolledSubjects = student.getEnrolledSubjects();
    EXPECT_EQ(enrolledSubjects.size(), 1);
}

TEST(StudentTest, CheckScheduleAfterEnrollment) {
    Student student("Eve Adams", "EA234");
    Subject biology("Biology", "BIO101", 3);
    student.enrollSubject(biology);
    EXPECT_FALSE(student.getPrintedSchedule().empty());
    EXPECT_NE(student.getPrintedSchedule().find("Biology"), std::string::npos);
}

TEST(StudentTest, DropSubjectSuccessfully) {
    Student student("John Doe", "JD123");
    Subject math("Math", "MATH101", 5);
    student.enrollSubject(math);
    EXPECT_TRUE(student.dropSubject(math));
}

TEST(StudentTest, DropNonExistentSubject) {
    Student student("Alice Smith", "AS456");
    Subject physics("Physics", "PHYS101", 4);
    EXPECT_FALSE(student.dropSubject(physics));
}

TEST(StudentTest, DropSubjectByCodeSuccessfully) {
    Student student("Bob Johnson", "BJ789");
    Subject chemistry("Chemistry", "CHEM101", 4);
    student.enrollSubject(chemistry);
    EXPECT_TRUE(student.dropSubjectByCode("CHEM101"));
}

TEST(StudentTest, DropSubjectByNonExistentCode) {
    Student student("Eve Adams", "EA234");
    EXPECT_FALSE(student.dropSubjectByCode("BIO101"));
}

TEST(StudentComplexTest, EnrollAndDropMultipleSubjects) {
    Student student("Alex Brown", "AB123");
    Subject math("Math", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 4);
    Subject chemistry("Chemistry", "CHEM101", 4);

    student.enrollSubject(math);
    student.enrollSubject(physics);
    student.enrollSubject(chemistry);

    auto enrolledSubjects = student.getEnrolledSubjects();
    EXPECT_EQ(enrolledSubjects.size(), 3);

    student.dropSubjectByCode("PHYS101");

    enrolledSubjects = student.getEnrolledSubjects();
    EXPECT_EQ(enrolledSubjects.size(), 2);
    EXPECT_FALSE(student.getPrintedSchedule().find("Physics") != std::string::npos);
}

TEST(StudentComplexTest, EnrollDuplicateSubjectsAndCheckSchedule) {
    Student student("Cathy Green", "CG456");
    Subject biology("Biology", "BIO101", 3);
    student.enrollSubject(biology);
    student.enrollSubject(biology);

    auto enrolledSubjects = student.getEnrolledSubjects();
    EXPECT_EQ(enrolledSubjects.size(), 1);

    EXPECT_NE(student.getPrintedSchedule().find("Biology"), std::string::npos);
}


TEST(StudentComplexTest, SequentialEnrollmentAndDropping) {
    Student student("David Lee", "DL789");
    Subject art("Art", "ART101", 2);
    Subject music("Music", "MUSIC101", 3);

    student.enrollSubject(art);
    student.enrollSubject(music);

    EXPECT_EQ(student.getEnrolledSubjects().size(), 2);
    EXPECT_FALSE(student.getPrintedSchedule().empty());

    student.dropSubject(art);

    EXPECT_EQ(student.getEnrolledSubjects().size(), 1);
    EXPECT_TRUE(student.getPrintedSchedule().find("Art") == std::string::npos);
}

TEST(StudentTest, GetEnrolledSubjectsStringWithMultipleSubjects) {
    Student student("John Doe", "JD123");
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 4);

    student.enrollSubject(math);
    student.enrollSubject(physics);

    std::string expectedString = "Mathematics, Physics";
    EXPECT_EQ(student.getEnrolledSubjectsString(), expectedString);
}

TEST(StudentTest, GetEnrolledSubjectsStringWithNoSubjects) {
    Student student("Alice Smith", "AS456");

    EXPECT_TRUE(student.getEnrolledSubjectsString().empty());
}

TEST(StudentTest, GetStudentInfoWithCompleteData) {
    Student student("John Doe", "JD123");
    Subject math("Mathematics", "MATH101", 5);
    student.enrollSubject(math);

    std::string expectedInfo = "Name: John Doe\nstudentID: JD123\nEnrolled subjects: Mathematics\nStudent schedule: Mathematics - No time schedule";
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}

TEST(StudentTest, GetStudentInfoWithNoName) {
    Student student("", "JD123");
    Subject physics("Physics", "PHYS101", 4);
    student.enrollSubject(physics);

    std::string expectedInfo = "Name: no info\nstudentID: JD123\nEnrolled subjects: Physics\nStudent schedule: Physics - No time schedule";
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}

TEST(StudentTest, GetStudentInfoWithNoStudentID) {
    Student student("Alice Smith", "");
    Subject chemistry("Chemistry", "CHEM101", 4);
    student.enrollSubject(chemistry);

    std::string expectedInfo = "Name: Alice Smith\nstudentID: no info\nEnrolled subjects: Chemistry\nStudent schedule: Chemistry - No time schedule";
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}

TEST(StudentTest, GetStudentInfoWithNoEnrolledSubjects) {
    Student student("Bob Johnson", "BJ456");

    std::string expectedInfo = "Name: Bob Johnson\nstudentID: BJ456\nEnrolled subjects: \nStudent schedule: ";
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}

TEST(StudentTest, GetStudentInfoWithEmptyScheduleAndNoSubjects) {
    Student student("David Lee", "DL789");

    std::string expectedInfo = "Name: David Lee\nstudentID: DL789\nEnrolled subjects: \nStudent schedule: ";
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}

TEST(StudentTest, GetStudentInfoWithMultipleEnrolledSubjects) {
    Student student("Eve Adams", "EA234");
    Subject bio("Biology", "BIO101", 3);
    Subject art("Art", "ART102", 2);
    student.enrollSubject(bio);
    student.enrollSubject(art);

    std::string expectedInfo = "Name: Eve Adams\nstudentID: EA234\nEnrolled subjects: Biology, Art\nStudent schedule: Biology - No time schedule || Art - No time schedule";
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}

TEST(StudentTest, GetStudentInfoWithSubjectsHavingTimes) {
    Student student("Emma Wilson", "EW001");
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 4);

    math.addSubjectSchedule("10:00", WeekDay::Monday);
    physics.addSubjectSchedule("14:00", WeekDay::Wednesday);

    student.enrollSubject(math);
    student.enrollSubject(physics);

    std::string expectedInfo = "Name: Emma Wilson\nstudentID: EW001\nEnrolled subjects: Mathematics, Physics\nStudent schedule: Mathematics - Monday_10:00 || Physics - Wednesday_14:00";
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}

TEST(StudentComplexTest, ComprehensiveStudentFunctionalityTest) {
    Student student("Emily Clark", "EC456");
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 4);
    Subject chemistry("Chemistry", "CHEM101", 4);
    Subject history("History", "HIST101", 3);

    math.addSubjectSchedule("09:00", WeekDay::Monday);
    physics.addSubjectSchedule("11:00", WeekDay::Tuesday);
    chemistry.addSubjectSchedule("13:00", WeekDay::Wednesday);

    student.enrollSubject(math);
    student.enrollSubject(physics);
    student.enrollSubject(chemistry);
    student.enrollSubject(history);

    student.dropSubjectByCode("CHEM101");

    std::string expectedEnrolledSubjects = "Mathematics, Physics, History";
    EXPECT_EQ(student.getEnrolledSubjectsString(), expectedEnrolledSubjects);

    std::string expectedSchedule = "Mathematics - Monday_09:00 || Physics - Tuesday_11:00 || History - No time schedule";
    EXPECT_EQ(student.getPrintedSchedule(), expectedSchedule);

    std::string expectedInfo = "Name: Emily Clark\nstudentID: EC456\nEnrolled subjects: Mathematics, Physics, History\nStudent schedule: " + expectedSchedule;
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
    student.writeStudentInfoToFile(R"(C:\Users\gosti\C++\TEST.txt)");
}

TEST(StudentTest, EnrollSubjectsFromFile) {

    Student student("John Doe", "JD123");
    EXPECT_TRUE(
            student.enrollSubjectsFromFile("C:\\Users\\gosti\\C++\\FMFI rozvrh - projekt\\StudentEnrollSubjects.txt"));

    auto enrolledSubjects = student.getEnrolledSubjects();
    EXPECT_EQ(enrolledSubjects.size(), 2);
    EXPECT_EQ(enrolledSubjects[0]->getSubjectName(), "Mathematics");
    EXPECT_EQ(enrolledSubjects[1]->getSubjectName(), "Physics");

    std::string expectedInfo = "Name: John Doe\nstudentID: JD123\nEnrolled subjects: Mathematics, Physics\nStudent schedule: ";
    expectedInfo += student.getPrintedSchedule();
    EXPECT_EQ(student.getStudentInfo(), expectedInfo);
}
