#ifndef STUDENT_SEMESTER_H
#define STUDENT_SEMESTER_H
#include <boost/date_time/gregorian/gregorian.hpp>
#include <ctime>
#include <string>
#include <vector>
#include "SubjectAttempt.h"

using namespace std;
using namespace boost::gregorian;
class StudentSemester
{
    private:
        string _id;
        string _name;
        date _startDate;
        date _endDate;
        vector<SubjectAttempt> _subjects;
        void checkPeriod(date newStartDate, date newEndDate);
    public:
        StudentSemester(
            string id,
            string name,
            date startDate,
            date endDate
        );
        StudentSemester(
            string id,
            string name,
            date startDate,
            date endDate,
            vector<SubjectAttempt> subjectAttempts
        );
        string getId();
        string getName();
        date getStartDate();
        date getEndDate();
        vector<SubjectAttempt> getSubjectsAttempts();
        SubjectAttempt& findSubjectAttempt(string subjectId);
        SubjectAttempt& findSubjectAttemptById(string attemptId);
        bool attemptWithSubjectExists(string subjectId);
        void rename(string newName);
        void changeDates(date newStartDate, date newEndDate);
        void addSubjectAttempt(SubjectAttempt& attempt);
        void removeSubjectAttempt(string attemptId);
        void changeSubjectGrade(string attemptId, float grade);
        void changeSubjectProfessor(string attemptId, string professorName);
};
#endif
