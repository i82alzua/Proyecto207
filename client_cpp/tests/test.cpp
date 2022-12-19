#include "tests1.hpp"
#include "tests2.hpp"
#include "tests3.hpp"

#include "../vendor/cute/cute.h"
#include "../vendor/cute/cute_runner.h"
#include "../vendor/cute/ide_listener.h"
#include "../vendor/cute/cute_suite.h"


cute::test testsStudent[] = {
    CUTE(test_enroll),
    CUTE(test_unenroll)
};

cute::test testsResource[] = {
    CUTE(test_create_resource)
};

cute::test testsCourse[] = {
    CUTE(test_create_course)
};

cute::test testsAdmin[] = {
    CUTE(test_edit_user),
    CUTE(test_delete_resource),
    CUTE(test_delete_course)
};

int main () {
    cute::ide_listener<> listener{};
    auto run = cute::makeRunner(listener);
    
    cute::suite sStudent(testsStudent, testsStudent + (sizeof(testsStudent) / sizeof(testsStudent[0])));
    cute::suite sResource(testsResource, testsResource + (sizeof(testsResource) / sizeof(testsResource[0])));
    cute::suite sCourse(testsCourse, testsCourse + (sizeof(testsCourse) / sizeof(testsCourse[0])));
    cute::suite sAdmin(testsAdmin, testsAdmin + (sizeof(testsAdmin) / sizeof(testsAdmin[0])));

    int r1 = run(sStudent, "Suite Estudiante");
    int r2 = run(sResource, "Suite Coordinador Recursos");
    int r3 = run(sCourse, "Suite Coordinador Cursos");
    int r4 = run(sAdmin, "Suite Administrador");
}