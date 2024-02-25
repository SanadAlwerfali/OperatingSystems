/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <err.h>
#include <stdio.h>


int main()
{
	int hopefully_unique = 42;

	key_t key = ftok("/usr/local/share/examples", hopefully_unique);
	if (key == -1)
	{
		err(-1, "Error in ftok()");
	}

	int shmid = shmget(key, 4096, IPC_CREAT | S_IRUSR | S_IWUSR);
	if (shmid == -1)
	{
		err(-1, "Error in shmget()");
	}

	void *mem = shmat(shmid, NULL, 0);
	if (mem == -1)
	{
		err(-1, "Failed to attach SHM with ID %d\n", shmid);
	}
	printf("Attached shared memory at: %p\n", mem);

	return 0;
}