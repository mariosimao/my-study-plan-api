#include "DomainException.h"
#include "Student.h"

Student::Student(string id)
{
    this->_id = id;
    this->_semesters = vector<StudentSemester>();
}

Student::Student(string id, vector<StudentSemester> semesters)
{
    this->_id = id;

    for (auto semester: semesters) {
        this->_semesters.emplace_back(semester);
    }
}

string Student::getId()
{
    return this->_id;
}

vector<StudentSemester> Student::getStudentSemesters()
{
    return this->_semesters;
}

StudentSemester& Student::findStudentSemester(string semesterId)
{
    for (StudentSemester& semester: this->_semesters) {
        if (semester.getId() == semesterId) {
            return semester;
        }
    }

    throw DomainException("Semester not found.");
}

void Student::planSemester(
    string semesterId,
    boost::gregorian::date startDate,
    boost::gregorian::date endDate
) {
    this->checkSemesterPeriod(startDate, endDate);

    int year = startDate.year();
    int semester = (startDate.month() <= 6) ? 1 : 2;
    string name = to_string(year) + "." + to_string(semester);

    StudentSemester studentSemester(semesterId, name, startDate, endDate);

    this->_semesters.push_back(studentSemester);
}

void Student::editSemester(
    string semesterId,
    string newName,
    boost::gregorian::date newStartDate,
    boost::gregorian::date newEndDate
) {
    StudentSemester& semester = this->findStudentSemester(semesterId);

    this->checkSemesterPeriod(newStartDate, newEndDate, semesterId);

    semester.rename(newName);
    semester.changeDates(newStartDate, newEndDate);
}

void Student::removeSemester(string semesterId)
{
    this->_semesters.erase(
        remove_if(
            this->_semesters.begin(),
            this->_semesters.end(),
            [semesterId](StudentSemester semester) {
                return semester.getId() == semesterId;
            }
        ),
        this->_semesters.end()
    );

    return;
}

void Student::planSubjectAttempt(
    string attemptId,
    string semesterId,
    string subjectId
) {
    StudentSemester& semester = this->findStudentSemester(semesterId);

    SubjectAttempt attempt(attemptId, subjectId);

    semester.addSubjectAttempt(attempt);
}

void Student::removeSubjectAttempt(string semesterId, string attemptId)
{
    StudentSemester& semester = this->findStudentSemester(semesterId);

    semester.removeSubjectAttempt(attemptId);
}

void Student::changeSubjectGrade(string semesterId, string attemptId, float grade)
{
    StudentSemester& semester = this->findStudentSemester(semesterId);

    semester.changeSubjectGrade(attemptId, grade);
}

void Student::changeSubjectProfessor(string semesterId, string attemptId, string professor)
{
    StudentSemester& semester = this->findStudentSemester(semesterId);

    semester.changeSubjectProfessor(attemptId, professor);
}

void Student::moveSubjectAttempt(string oldSemesterId, string attemptId, string newSemesterId)
{
    if (oldSemesterId == newSemesterId) {
        return;
    }

    StudentSemester& oldSemester = this->findStudentSemester(oldSemesterId);
    StudentSemester& newSemester = this->findStudentSemester(newSemesterId);

    SubjectAttempt& attempt = oldSemester.findSubjectAttemptById(attemptId);

    newSemester.addSubjectAttempt(attempt);
    oldSemester.removeSubjectAttempt(attemptId);
}

void Student::checkSemesterPeriod(
    date newStartDate,
    date newEndDate,
    string semesterId
) {
    boost::gregorian::date_period period(newStartDate, newEndDate);
    for (StudentSemester semester: this->_semesters) {
        if (semester.getId() == semesterId) {
            continue;
        }

        boost::gregorian::date_period auxPeriod(
            semester.getStartDate(),
            semester.getEndDate()
        );

        if (period.intersects(auxPeriod)) {
            throw DomainException("Semester overlaps with previously registered semester.");
        }
    }
}
