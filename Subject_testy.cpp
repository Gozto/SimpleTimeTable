#include <gtest/gtest.h>
#include "Subject.h"
#include "Professor.h"

TEST(SubjectTest, AddSubjectSchedule) {
    Subject subj;
    EXPECT_TRUE(subj.addSubjectSchedule("16:30", WeekDay::Monday));
    EXPECT_EQ(subj.getSubjectSchedule(), "Monday_16:30");
    EXPECT_FALSE(subj.addSubjectSchedule("25:30", WeekDay::Monday));
    EXPECT_TRUE(subj.addSubjectSchedule("14:00", WeekDay::Monday));
}

TEST(SubjectTest, GetSubjectInfo) {
    Professor prof("Dr. Euler", "Mathematics", "euler@example.com");
    Subject subj("Mathematics", "MATH101", 5, "Calculus course", prof, std::make_pair(WeekDay::Monday, "10:00"));
    subj.addSubjectSchedule("12:00", WeekDay::Tuesday);
    std::string expectedInfo = "Name: Mathematics\nProfessor(s): Dr. Euler\nSubject code: MATH101\nDecription: Calculus course\nNumber of credits: 5\nSchedule: Monday_10:00; Tuesday_12:00";
    EXPECT_EQ(subj.getSubjectInfo(), expectedInfo);
}

TEST(SubjectTest, AddMultipleSchedulesAndRetrieve) {
    Subject subj;
    subj.addSubjectSchedule("14:00", WeekDay::Monday);
    subj.addSubjectSchedule("16:00", WeekDay::Tuesday);
    subj.addSubjectSchedule("10:00", WeekDay::Wednesday);
    std::string expectedSchedule = "Monday_14:00; Tuesday_16:00; Wednesday_10:00";
    EXPECT_EQ(subj.getSubjectSchedule(), expectedSchedule);
}

TEST(SubjectTest, SubjectInfoFormattedCorrectly) {
    Professor prof("Prof. Knuth", "Computer Science", "knuth@example.com");
    Subject subj("Data Structures", "CS102", 4, "Study of data organization", prof, std::make_pair(WeekDay::Wednesday, "15:00"));
    std::string info = subj.getSubjectInfo();
    std::string expectedStart = "Name: Data Structures\nProfessor(s): Prof. Knuth";
    std::string expectedEnd = "Schedule: Wednesday_15:00";
    EXPECT_TRUE(info.find(expectedStart) != std::string::npos);
    EXPECT_TRUE(info.find(expectedEnd) != std::string::npos);
}


TEST(SubjectTest, SetAndGetCredits) {
    Subject subj;
    EXPECT_TRUE(subj.setSubjectCredits(3));
    EXPECT_EQ(subj.getSubjectNumOfCredits(), 3);
    EXPECT_FALSE(subj.setSubjectCredits(-1));
}

TEST(SubjectTest, SetAndGetSubjectNameValidAndInvalid) {
    Subject subj;
    EXPECT_TRUE(subj.setSubjectName("Algebra"));
    EXPECT_EQ(subj.getSubjectName(), "Algebra");
    EXPECT_FALSE(subj.setSubjectName("1234"));
}


TEST(SubjectTest, CheckScheduleFormat) {
    Subject subj;
    subj.addSubjectSchedule("08:30", WeekDay::Monday);
    std::string schedule = subj.getSubjectSchedule();
    EXPECT_EQ(schedule, "Monday_08:30");
}


TEST(SubjectTest, AddDuplicateSchedule) {
    Subject subj;
    EXPECT_TRUE(subj.addSubjectSchedule("09:00", WeekDay::Tuesday));
    EXPECT_FALSE(subj.addSubjectSchedule("09:00", WeekDay::Tuesday));
}

TEST(SubjectTest, CompleteSubjectInfo) {
    Subject subj("Programming", "CS101", 4, "Intro to Programming", Professor("Prof. Turing", "CS", "turing@example.com"));
    subj.addSubjectSchedule("10:00", WeekDay::Friday);
    std::string expectedInfo = "Name: Programming\nProfessor(s): Prof. Turing\nSubject code: CS101\nDecription: Intro to Programming\nNumber of credits: 4\nSchedule: Friday_10:00";
    EXPECT_EQ(subj.getSubjectInfo(), expectedInfo);
}

TEST(SubjectTest, AddProfessor) {
    Subject subj;
    Professor prof("Dr. Gauss", "Mathematics", "gauss@example.com");
    EXPECT_TRUE(subj.addProfessor(prof));
}

TEST(SubjectTest, SetAndGetSubjectDescription) {
    Subject subj;
    std::string description = "Advanced Mathematics";
    EXPECT_TRUE(subj.setSubjectDescription(description));
    EXPECT_EQ(subj.getSubjectDescription(), description);
    std::string invalidDescription = "";
    EXPECT_FALSE(subj.setSubjectDescription(invalidDescription));
}

TEST(SubjectTest, AddMultipleDistinctSchedules) {
    Subject subj;
    EXPECT_TRUE(subj.addSubjectSchedule("09:00", WeekDay::Monday));
    EXPECT_TRUE(subj.addSubjectSchedule("11:00", WeekDay::Wednesday));
    EXPECT_TRUE(subj.addSubjectSchedule("14:00", WeekDay::Friday));
    std::string expectedSchedule = "Monday_09:00; Wednesday_11:00; Friday_14:00";
    EXPECT_EQ(subj.getSubjectSchedule(), expectedSchedule);

}

TEST(SubjectTest, SetAndGetSubjectCode) {
    Subject subj;
    std::string newCode = "MATH102";
    EXPECT_TRUE(subj.setSubjectCode(newCode));
    EXPECT_EQ(subj.getSubjectCode(), newCode);
    std::string invalidCode = "123@@@";
    EXPECT_FALSE(subj.setSubjectCode(invalidCode));
}


