#include <gtest/gtest.h>
#include "Professor.h"

TEST(ProfessorTest, DefaultConstructor) {
    Professor prof;
    EXPECT_EQ(prof.getName(), "");
    EXPECT_EQ(prof.getDepartment(), "");
    EXPECT_EQ(prof.getEmail(), "");
    EXPECT_EQ(prof.getOfficeHours(), "");
}

TEST(ProfessorTest, ParameterizedConstructor) {
    Professor prof("Dr. Smith", "Mathematics", "smith@example.com");
    EXPECT_EQ(prof.getName(), "Dr. Smith");
    EXPECT_EQ(prof.getDepartment(), "Mathematics");
    EXPECT_EQ(prof.getEmail(), "smith@example.com");
}

TEST(ProfessorTest, ValidateAndSetProfessorName) {
    Professor prof;
    EXPECT_TRUE(prof.setName("Dr. Smith"));
    EXPECT_EQ(prof.getName(), "Dr. Smith");
    EXPECT_FALSE(prof.setName("123Dr. Smith!"));
}

TEST(ProfessorTest, ValidateAndSetDepartment) {
    Professor prof;
    EXPECT_TRUE(prof.setDepartment("Mathematics"));
    EXPECT_EQ(prof.getDepartment(), "Mathematics");
    EXPECT_FALSE(prof.setDepartment("Math123!"));
}

TEST(ProfessorTest, ValidateAndSetEmail) {
    Professor prof;
    EXPECT_TRUE(prof.setEmail("smith@example.com"));
    EXPECT_EQ(prof.getEmail(), "smith@example.com");
    EXPECT_FALSE(prof.setEmail("smith@exam!ple.com"));
}

TEST(ProfessorTest, ValidateAndSetOfficeHours) {
    Professor prof;
    EXPECT_TRUE(prof.setOfficeHours("08:00-17:00"));
    EXPECT_EQ(prof.getOfficeHours(), "08:00-17:00");
    EXPECT_FALSE(prof.setOfficeHours("17:00-08:00"));
    EXPECT_FALSE(prof.setOfficeHours("25:00-26:00"));
    EXPECT_FALSE(prof.setOfficeHours("badformat"));
}

TEST(ProfessorTest, EmailValidationWithSpecialCharacters) {
    Professor prof;
    EXPECT_FALSE(prof.setEmail("smith@ex!ample.com"));
    EXPECT_FALSE(prof.setEmail("smi(th@example.com"));
    EXPECT_FALSE(prof.setEmail("smith@example.co)m"));
    EXPECT_FALSE(prof.setEmail("smith@exa&mple.com"));
}

TEST(ProfessorTest, EmailValidationWithMultipleAtSymbols) {
    Professor prof;
    EXPECT_FALSE(prof.setEmail("smith@@example.com"));
    EXPECT_FALSE(prof.setEmail("smi@th@example.com"));
}

TEST(ProfessorTest, OfficeHoursFormatValidation) {
    Professor prof;
    EXPECT_FALSE(prof.setOfficeHours("8-17"));
    EXPECT_TRUE(prof.setOfficeHours("08:00-17:00"));
    EXPECT_FALSE(prof.setOfficeHours("08:00:17:00"));
    EXPECT_FALSE(prof.setOfficeHours("08_00:17:00"));
    EXPECT_FALSE(prof.setOfficeHours("08_00_17_00"));
    EXPECT_FALSE(prof.setOfficeHours("08:6017:00"));
}