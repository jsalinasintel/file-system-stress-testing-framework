# Summary #
A [monkey test](MonkeyTesting.md) tool framework that can be used to stress test POSIX filesystems. There is a library of common filesystem operations (open,mmap, etc).  And a small framework library that does some house keeping (like tracking open FDs).  Some [example tools](ExampleTests.md) are provided.

Reading the [monkey test](MonkeyTesting.md) overview, would help you understand the goals of this project.

# Objectives #

Develop a new [monkey test](MonkeyTesting.md) tool that will meet these objectives:

  * Simplify adding new tests to the operational pool.
  * Increase code sharing of operation pools between different test tools.
  * Every test tool should use the same execution framework.
  * Every test tool should have the same command line API.
  * Every test tool should have a clearly defined test strategy.
  * Develop methods to reduce the effects of the [Pesticide Paradox](Dictionary#Pesticide_Paradox.md)
  * Develop methods to reduce the [amount of code](http://www.linux-mips.org/pub/linux/mips/people/macro/DEC/DTJ/DTJT08/DTJT08PF.PDF) and the execution time of the monkey test to reproduce the kernel bug.
  * Develop methods that take advantage of [clusters](http://googleonlinesecurity.blogspot.com/2011/08/fuzzing-at-scale.html).


# Our Approach #

## Operational Pool ##

  * The operation pool is maintained as a library and can be shared between multiple test tools with different test strategies.
  * Instead of altering an existing operation -- fork the operation and create a new one.

## Execution Framework ##

  * Use the [krt](MonkeyTesting#krt.md) framework for all test tools.
  * All tools need to have the same command line API to allow script reuse.

## Strategy ##

  * All test tools use the [krt](MonkeyTesting#krt.md) framework and common operation libraries.
  * Each test tool needs to have a well defined test strategy.
  * Instead of changing a tool's strategy, fork the tool and create a new one.
  * Make it easy to add new operations to the pool.
  * Make it easy to prototype a new test strategy.


## Scale ##

Split the monkey tool into two parts: one tool uses entropy to generate a file system operation list and another tool that replays this pre-generated operation list.

Using pre-generated operation lists is a win due to the future improvements this technique enables:
  * competitive algorithms can be used to create operation lists that maximize bug count
  * [corpus distillation](http://googleonlinesecurity.blogspot.com/2011/08/fuzzing-at-scale.html) techniques can be used to create operation lists that maximize code coverage
  * regression test suites can be created using a set of minimized operation lists that have caused past regressions
  * improvements can be made to the front end without effecting existing regression tests
  * [automated techniques](FreeBSDKern159971.md) can be developed to reduce a operation list to the minimum required to reproduce the failure in the software under test

# Wiki Page Index #

  * [Common terms](Dictionary.md)
  * [Monkey testing overview](MonkeyTesting.md)
  * [Using Clodagh to find a bug in FreeBSD](FreeBSDKern159971.md)
  * [Example monkey tools developed by this project](ExampleTests.md)
  * [How to install and use the software](InstallationGuide.md)