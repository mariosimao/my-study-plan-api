#ifndef PLAN_SEMESTER_H
#define PLAN_SEMESTER_H
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "Views/StudentSemesterView.h"
#include "../Domain/IStudentRepository.h"

using namespace std;

class PlanSemester
{
    private:
        IStudentRepository& _studentRepository;
    public:
        PlanSemester(IStudentRepository& studentRepository);
        StudentSemesterView execute(
            string studentId,
            boost::gregorian::date startDate,
            boost::gregorian::date endDate
        );
};
#endif
