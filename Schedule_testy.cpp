#include "Schedule.h"
#include <gtest/gtest.h>

TEST(ScheduleTest, AddNewSubjectToSchedule) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    EXPECT_TRUE(schedule.addSubjectToSchedule(math));
}

TEST(ScheduleTest, DoNotAddDuplicateSubject) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    schedule.addSubjectToSchedule(math);
    EXPECT_FALSE(schedule.addSubjectToSchedule(math));
}

TEST(ScheduleTest, FindSubjectInSchedule) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 5);
    schedule.addSubjectToSchedule(math);
    EXPECT_TRUE(schedule.findSubjectInSchedule(math));
    EXPECT_FALSE(schedule.findSubjectInSchedule(physics));
}

TEST(ScheduleTest, RemoveSubjectSuccessfully) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    EXPECT_TRUE(schedule.addSubjectToSchedule(math));
    EXPECT_TRUE(schedule.removeSubjectFromSchedule(math));
}


TEST(ScheduleTest, RemoveNonExistentSubject) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    EXPECT_FALSE(schedule.removeSubjectFromSchedule(math));
}

TEST(ScheduleTest, ScheduleStateAfterSubjectRemoval) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 5);
    schedule.addSubjectToSchedule(math);
    schedule.addSubjectToSchedule(physics);
    schedule.removeSubjectFromSchedule(math);

    EXPECT_FALSE(schedule.findSubjectInSchedule(math));
    EXPECT_TRUE(schedule.findSubjectInSchedule(physics));
}

TEST(ScheduleTest, AddMultipleDistinctSubjects) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 5);
    Subject chemistry("Chemistry", "CHEM101", 5);

    EXPECT_TRUE(schedule.addSubjectToSchedule(math));
    EXPECT_TRUE(schedule.addSubjectToSchedule(physics));
    EXPECT_TRUE(schedule.addSubjectToSchedule(chemistry));
}

TEST(ScheduleTest, AddAndRemoveSubject) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    schedule.addSubjectToSchedule(math);

    EXPECT_TRUE(schedule.findSubjectInSchedule(math));
    EXPECT_TRUE(schedule.removeSubjectFromSchedule(math));
    EXPECT_FALSE(schedule.findSubjectInSchedule(math));
}

TEST(ScheduleTest, RemoveNonExistentSubjectAfterAddingAnother) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 5);
    schedule.addSubjectToSchedule(math);

    EXPECT_FALSE(schedule.removeSubjectFromSchedule(physics));
}

TEST(ScheduleTest, RemoveSubjectByCodeSuccessfully) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    schedule.addSubjectToSchedule(math);
    EXPECT_TRUE(schedule.removeSubjectFromScheduleByCode("MATH101"));
}

TEST(ScheduleTest, RemoveSubjectByNonExistentCode) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    schedule.addSubjectToSchedule(math);
    EXPECT_FALSE(schedule.removeSubjectFromScheduleByCode("MATH102"));
}

TEST(ScheduleTest, ScheduleStateAfterSubjectRemovalByCode) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHYS101", 5);
    EXPECT_TRUE(math.addSubjectSchedule("11:00", WeekDay::Wednesday));
    EXPECT_TRUE(physics.addSubjectSchedule("14:00", WeekDay::Friday));
    schedule.addSubjectToSchedule(math);
    schedule.addSubjectToSchedule(physics);

    EXPECT_EQ(schedule.printSchedule(), "Mathematics - Wednesday_11:00 || Physics - Friday_14:00");
    schedule.removeSubjectFromScheduleByCode("MATH101");


    EXPECT_FALSE(schedule.findSubjectInSchedule(math));
    EXPECT_TRUE(schedule.findSubjectInSchedule(physics));
}

TEST(ScheduleTest, PrintEmptySchedule) {
    Schedule schedule;
    EXPECT_EQ(schedule.printSchedule(), "");
}

TEST(ScheduleTest, PrintTwoSubjectWithoutTimesInSchedule) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHY101", 5);
    schedule.addSubjectToSchedule(math);
    schedule.addSubjectToSchedule(physics);
    EXPECT_EQ(schedule.printSchedule(), "Mathematics - No time schedule || Physics - No time schedule");
}

TEST(ScheduleTest, PrintTwoSubjectWithTimesInSchedule) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHY101", 5);
    math.addSubjectSchedule("14:00", WeekDay::Monday);
    physics.addSubjectSchedule("12:00", WeekDay::Tuesday);
    schedule.addSubjectToSchedule(math);
    schedule.addSubjectToSchedule(physics);
    EXPECT_EQ(schedule.printSchedule(), "Mathematics - Monday_14:00 || Physics - Tuesday_12:00");
}

TEST(ScheduleTest, PrintTwoSubjectWithMultipleTimesInSchedule) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject physics("Physics", "PHY101", 5);
    math.addSubjectSchedule("14:00", WeekDay::Monday);
    math.addSubjectSchedule("09:00", WeekDay::Wednesday);
    physics.addSubjectSchedule("12:00", WeekDay::Tuesday);
    physics.addSubjectSchedule("10:30", WeekDay::Friday);
    schedule.addSubjectToSchedule(math);
    schedule.addSubjectToSchedule(physics);
    EXPECT_EQ(schedule.printSchedule(), "Mathematics - Monday_14:00; Wednesday_09:00 || Physics - Tuesday_12:00; Friday_10:30");
}

TEST(ScheduleTest, PrintSingleSubjectWithoutTime) {
    Schedule schedule;
    Subject history("History", "HIST101", 3);
    schedule.addSubjectToSchedule(history);
    EXPECT_EQ(schedule.printSchedule(), "History - No time schedule");
}

TEST(ScheduleTest, PrintSubjectWithSingleTimeSlot) {
    Schedule schedule;
    Subject art("Art", "ART101", 2);
    art.addSubjectSchedule("10:00", WeekDay::Thursday);
    schedule.addSubjectToSchedule(art);
    EXPECT_EQ(schedule.printSchedule(), "Art - Thursday_10:00");
}

TEST(ScheduleTest, PrintTwoSubjectsOneWithoutTime) {
    Schedule schedule;
    Subject math("Mathematics", "MATH101", 5);
    Subject literature("Literature", "LIT101", 4);
    math.addSubjectSchedule("16:00", WeekDay::Monday);
    schedule.addSubjectToSchedule(math);
    schedule.addSubjectToSchedule(literature);
    EXPECT_EQ(schedule.printSchedule(), "Mathematics - Monday_16:00 || Literature - No time schedule");
}

TEST(ScheduleTest, PrintSubjectWithMultipleTimeSlots) {
    Schedule schedule;
    Subject chemistry("Chemistry", "CHEM101", 4);
    chemistry.addSubjectSchedule("09:00", WeekDay::Monday);
    chemistry.addSubjectSchedule("15:00", WeekDay::Wednesday);
    schedule.addSubjectToSchedule(chemistry);
    EXPECT_EQ(schedule.printSchedule(), "Chemistry - Monday_09:00; Wednesday_15:00");
}

TEST(ScheduleTest, PrintMultipleSubjectsMultipleTimeSlots) {
    Schedule schedule;
    Subject biology("Biology", "BIO101", 4);
    Subject physics("Physics", "PHY101", 5);
    biology.addSubjectSchedule("08:00", WeekDay::Tuesday);
    biology.addSubjectSchedule("14:00", WeekDay::Thursday);
    physics.addSubjectSchedule("11:00", WeekDay::Monday);
    physics.addSubjectSchedule("13:00", WeekDay::Friday);
    schedule.addSubjectToSchedule(biology);
    schedule.addSubjectToSchedule(physics);
    EXPECT_EQ(schedule.printSchedule(), "Biology - Tuesday_08:00; Thursday_14:00 || Physics - Monday_11:00; Friday_13:00");
}

TEST(ScheduleConstructorTest, CreateEmptySchedule) {
    std::vector<Subject> subjects;
    Schedule schedule(subjects);
    EXPECT_EQ(schedule.printSchedule(), "");
}

TEST(ScheduleConstructorTest, CreateScheduleWithOneSubject) {
    std::vector<Subject> subjects;
    subjects.emplace_back("Mathematics", "MATH101", 5);
    Schedule schedule(subjects);
    EXPECT_TRUE(schedule.findSubjectInSchedule(subjects[0]));
}

TEST(ScheduleConstructorTest, CreateScheduleWithMultipleSubjects) {
    std::vector<Subject> subjects;
    subjects.emplace_back("Mathematics", "MATH101", 5);
    subjects.emplace_back("Physics", "PHYS101", 4);
    subjects.emplace_back("Chemistry", "CHEM101", 4);
    Schedule schedule(subjects);

    for (const auto& subject : subjects) {
        EXPECT_TRUE(schedule.findSubjectInSchedule(subject));
    }
}

TEST(ScheduleConstructorTest, CreateScheduleWithDuplicateSubjects) {
    std::vector<Subject> subjects;
    subjects.emplace_back("Mathematics", "MATH101", 5);
    subjects.emplace_back("Mathematics", "MATH101", 5);
    Schedule schedule(subjects);

    EXPECT_EQ(schedule.printSchedule(), "Mathematics - No time schedule");
}

