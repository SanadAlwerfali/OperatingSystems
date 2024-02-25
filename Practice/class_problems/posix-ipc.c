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
#include <sys/mman.h>

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int shm = shm_open("/foo/bar/shm.example", O_RDWR | O_CREAT, 0666);
	if (shm < 0)
	{
		err(-1, "Error in shm_open()");
	}

	if (ftruncate(shm, 4096) != 0)
	{
		err(-1, "Error in ftruncate(shm)");
	}

	void *mem = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
	if (mem == MAP_FAILED)
	{
		err(-1, "Failed to attach SHM: FD %d\n", shm);
	}
	printf("Attached shared memory at: %p\n", mem);

	return 0;
}
