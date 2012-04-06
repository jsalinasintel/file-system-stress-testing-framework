/*
 * Copyright 2011 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define NDEBUG
#include "fembot.h"
#include "tap.h"

#include <stdlib.h>
#include <sys/cdefs.h>

__RCSID("$Id$");


int
main()
{
    pid_t childpid;
    int status;

    plan_tests(2);

    if ((childpid = fork()) == 0) {
	close(2);
        bstg_null_check(NULL, "fred", 1234);
        abort();
    } else if (childpid > 0) {
        ok(bstg_waitpid(childpid, &status, 4) == childpid, "waited");
    }

    ok(bstg_null_check(&status, "fred", 1234) == &status, "not null");

    return 0;
}
