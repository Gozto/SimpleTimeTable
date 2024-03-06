#include "StudyProgram.h"
#include <gtest/gtest.h>

TEST(StudyProgramTest, ConstructorWithProgramNameAndCredits) {
    Schedule sampleSchedule;
    StudyProgram program("Engineering", 120, sampleSchedule);
    EXPECT_EQ(program.getProgramName(), "Engineering");
    EXPECT_EQ(program.getTotalCredits(), 120);
}

TEST(StudyProgramTest, ConstructorWithNameSubjectsAndProfessors) {
    Schedule sampleSchedule;
    auto math = std::make_shared<Subject>("Mathematics", "MATH101", 5);
    auto physics = std::make_shared<Subject>("Physics", "PHYS101", 4);
    std::vector<std::shared_ptr<Subject>> subjects = {math, physics};

    auto prof1 = std::make_shared<Professor>("Dr. Smith", "Mathematics", "smith@example.com");
    auto prof2 = std::make_shared<Professor>("Dr. Johnson", "Physics", "johnson@example.com");
    std::vector<std::shared_ptr<Professor>> professors = {prof1, prof2};

    StudyProgram program("Science", subjects, professors, sampleSchedule);
    EXPECT_EQ(program.getProgramName(), "Science");
    EXPECT_EQ(program.getTotalCredits(), 9);
    EXPECT_EQ(program.getAllSubjects().size(), 2);
    EXPECT_EQ(program.getAllProfessors().size(), 2);
}

TEST(StudyProgramTest, ConstructorWithNameSubjectsProfessorsAndStudents) {
    Schedule sampleSchedule;

    auto math = std::make_shared<Subject>("Mathematics", "MATH101", 5);
    auto chemistry = std::make_shared<Subject>("Chemistry", "CHEM101", 4);
    std::vector<std::shared_ptr<Subject>> subjects = {math, chemistry};

    auto prof1 = std::make_shared<Professor>("Dr. Brown", "Chemistry", "brown@example.com");
    auto prof2 = std::make_shared<Professor>("Dr. Green", "Biology", "green@example.com");
    std::vector<std::shared_ptr<Professor>> professors = {prof1, prof2};

    auto student1 = std::make_shared<Student>("John Doe", "JD123");
    auto student2 = std::make_shared<Student>("Jane Smith", "JS456");
    std::vector<std::shared_ptr<Student>> students = {student1, student2};

    StudyProgram program("Biology", subjects, professors, students, sampleSchedule);
    EXPECT_EQ(program.getProgramName(), "Biology");
    EXPECT_EQ(program.getTotalCredits(), 9);
    EXPECT_EQ(program.getAllSubjects().size(), 2);
    EXPECT_EQ(program.getAllProfessors().size(), 2);
    EXPECT_EQ(program.getAllStudents().size(), 2);
}

TEST(StudyProgramTest, GetProgramSchedule) {
    Schedule sampleSchedule;
    auto math = std::make_shared<Subject>("Mathematics", "MATH101", 5);
    auto physics = std::make_shared<Subject>("Physics", "PHYS101", 4);

    sampleSchedule.addSubjectToSchedule(*math);
    sampleSchedule.addSubjectToSchedule(*physics);

    std::vector<std::shared_ptr<Subject>> subjects = {math, physics};
    std::vector<std::shared_ptr<Professor>> professors;
    StudyProgram program("Science", subjects, professors, sampleSchedule);
    Schedule programSchedule = program.getProgramSchedule();
    EXPECT_EQ(programSchedule.getNumberOfSubjects(), 2);
}

TEST(StudyProgramTest, ConstructorWithProgramNameCreditsAndSchedule) {
    Schedule schedule;
    StudyProgram program("Computer Science", 120, schedule);
    EXPECT_EQ(program.getProgramName(), "Computer Science");
    EXPECT_EQ(program.getTotalCredits(), 120);
}

TEST(StudyProgramTest, AddAndRemoveSubject) {
    Schedule schedule;
    StudyProgram program("Biology", 100, schedule);
    Subject biology("Biology", "BIO101", 5);
    program.addSubject(biology);
    EXPECT_EQ(program.getAllSubjects().size(), 1);
    program.removeSubject(biology);
    EXPECT_TRUE(program.getAllSubjects().empty());
}

TEST(StudyProgramTest, AddAndRemoveStudent) {
    Schedule schedule;
    StudyProgram program("Engineering", 120, schedule);
    Student student("John Doe", "JD123");
    program.addStudent(student);
    EXPECT_EQ(program.getAllStudents().size(), 1);
    program.removeStudent(student);
    EXPECT_TRUE(program.getAllStudents().empty());
}

TEST(StudyProgramTest, TotalCreditsCalculation) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 4);
    Subject physics("Physics", "PHYS102", 3);
    std::vector<std::shared_ptr<Subject>> subjects = {std::make_shared<Subject>(math), std::make_shared<Subject>(physics)};
    std::vector<std::shared_ptr<Professor>> professors;
    StudyProgram program("Science", subjects, professors, schedule);
    EXPECT_EQ(program.getTotalCredits(), 7);
}

TEST(StudyProgramTest, GetProgramSchedule2) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    schedule.addSubjectToSchedule(math);
    StudyProgram program("Science", 120, schedule);
    Schedule retrievedSchedule = program.getProgramSchedule();
    EXPECT_EQ(retrievedSchedule.printSchedule(), "Mathematics - No time schedule");
}

TEST(StudyProgramTest, FindStudentByID) {
    Schedule schedule;
    Student student1("Alice Johnson", "AJ123");
    Student student2("Bob Smith", "BS456");
    StudyProgram program("Engineering", 120, schedule);
    program.addStudent(student1);
    program.addStudent(student2);
    int index = program.findStudentIndexInProgramByID("AJ123");
    EXPECT_NE(index, -1);
    EXPECT_EQ(program.getAllStudents()[index]->getStudentID(), "AJ123");
}

TEST(StudyProgramTest, AddMultipleSubjectsAndStudentsAndCheckSchedule) {
    Schedule schedule;
    StudyProgram program("Engineering", 120, schedule);

    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 4);
    program.addSubject(math);
    program.addSubject(physics);

    Student student1("Alice Johnson", "AJ123");
    Student student2("Bob Smith", "BS456");
    program.addStudent(student1);
    program.addStudent(student2);

    EXPECT_EQ(program.getAllSubjects().size(), 2);
    EXPECT_EQ(program.getAllStudents().size(), 2);
    EXPECT_EQ(program.getProgramSchedule().printSchedule(), "Mathematics - No time schedule || Physics - No time schedule");
}

TEST(StudyProgramTest, RemoveSubjectAndStudentAndUpdateSchedule) {
    Schedule schedule;
    StudyProgram program("Computer Science", 120, schedule);

    Subject coding("Coding 101", "CODE101", 5);
    program.addSubject(coding);
    EXPECT_EQ(program.getAllSubjects().size(), 1);
    program.removeSubject(coding);
    EXPECT_TRUE(program.getAllSubjects().empty());

    Student student("Jane Doe", "JD456");
    program.addStudent(student);
    EXPECT_EQ(program.getAllStudents().size(), 1);
    program.removeStudent(student);
    EXPECT_TRUE(program.getAllStudents().empty());

    EXPECT_EQ(program.getProgramSchedule().printSchedule(), "");
}

TEST(StudyProgramTest, FindAndUpdateSubjectsAndStudentsInProgram) {
    Schedule schedule;
    StudyProgram program("Biology", 100, schedule);

    Subject bio1("Biology I", "BIO101", 4);
    Subject bio2("Biology II", "BIO102", 4);
    program.addSubject(bio1);
    program.addSubject(bio2);

    int bioIndex = program.findSubjectIndexInProgramByCode("BIO102");
    EXPECT_NE(bioIndex, -1);
    program.removeSubjectByCode("BIO102");
    EXPECT_EQ(program.findSubjectIndexInProgramByCode("BIO102"), -1);

    Student student("Eve Adams", "EA789");
    program.addStudent(student);
    int studentIndex = program.findStudentIndexInProgramByID("EA789");
    EXPECT_NE(studentIndex, -1);

    EXPECT_EQ(program.getProgramSchedule().printSchedule(), "Biology I - No time schedule");
}










