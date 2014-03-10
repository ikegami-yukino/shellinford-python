#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>

using namespace CPPUNIT_NS;
int main(int argc, char **argv) {
  TestResult controller;
  TestResultCollector result;
  controller.addListener(&result);

  BriefTestProgressListener progress;
  controller.addListener(&progress);

  TestRunner runner;
  runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  CompilerOutputter outputter(&result, stdCOut());
  outputter.write();

  return result.wasSuccessful() ? 0 : 1;
}

