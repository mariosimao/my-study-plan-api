#include <iostream>
#include <vector>
#include <string>
#include <pqxx/pqxx>
#include "./src/Infrastructure/Persistence/SqlSubjectRepository.h"
#include "./src/Infrastructure/CLI/SubjectCliController.h"

using namespace std;

int main(int argc, char const *argv[])
{
    try {
        string connectionString = "host=localhost port=5432 dbname=my_curriculum user=my_curriculum password=password";
        pqxx::connection connection(connectionString.c_str());

        vector<string> arguments(argv, argv + argc);

        string command = arguments[1];
        arguments.erase(arguments.begin());
        arguments.erase(arguments.begin());

        if (command == "register-subject") {
            SqlSubjectRepository subjectRepository(&connection);
            SubjectCliController subjectController(&subjectRepository);

            subjectController.registerSubject(arguments);
        }
    } catch(const char* e) {
        cerr << e << endl;
        return 1;
    }

    return 0;
}