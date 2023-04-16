#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mount.h>
#include <limits.h>

#define SOURCE_FILE "eio_test/test.txt"
#define DESTINATION_FILE "eio_test/destination_file"

#define min(a,b) \
	({ __typeof__ (a) _a = (a); \
		__typeof__ (b) _b = (b); \
		_a < _b ? _a : _b; })


int main()
{
	// EACCES TEST
	int ret;// = symlink("read_test/test.txt", "eacces_test/eacces_read");
	/*printf("Symlink call returned %d.\n", ret);
	if (ret) {
		printf("ERRNO: %d. %s.\n", errno,  strerror(errno));
	}
	ret = symlink("../../abc.txt", "eacces_test/write_test/trial");
	printf("Symlink call returned %d.\n", ret);
	if (ret) {
		printf("ERRNO: %d. %s.\n", errno, strerror(errno));
	}

	//EEXIST
	ret = symlink("test.txt", "eacces_test/write_test");
	printf("Symlink call returned %d.\n", ret);
	if (ret) {
		printf("ERRNO: %d. %s.\n", errno, strerror(errno));
	} */

	//EIO
	//ELOOP
	ret = symlink("test.txt", "eloop_test/symlink");
	printf("Symlink call returned %d.\n", ret);
	if (ret) {
		printf("ERRNO: %d. %s. \n", errno, strerror(errno));
	}
	ret = symlink("symlink", "eloop_test/symlink");
	printf("Symlink call returned %d.\n", ret);
	if (ret) {
		printf("ERRNO: %d. %s. \n", errno, strerror(errno));
	}
/*	//ENAMETOOLONG
	char target[] = "trial";
	char linkname[PATH_MAX + 1];
	memset(linkname, 'A', sizeof(linkname)); // create a target path that is too long
	linkname[sizeof(linkname) - 1] = '\0';
	
	ret = symlink(target, linkname);
	printf("Symlink call returned %d.\n", ret);
	if (ret) {
		printf("ERRNO: %d. %s.\n", errno, strerror(errno));
	}
	//ENOENT
	ret = symlink("", "test.txt");
	printf("Symlink call returned %d.\n", ret);
	if (ret) {
		printf("ERRNO: %d. %s.\n", errno, strerror(errno));
	}
	//ENOSPC
	//ENOTDIR
	//EROFS*/
	/*char buf[10];
	strcpy(buf, "abcdefg");

	int ret = symlink(ORIG_FILENAME, FILENAME);

	printf("symlink call returned %d\n", ret);
	if (ret < 0) {
		printf("failed to create symlink errno=%d\n", errno);
	  return 1;
	}

	int fd = open(FILENAME, O_RDWR);
	printf("fd=%d\n", fd);
	if (fd < 0) {
		printf("open failed errno=%d\n", errno);
		return 1;
	}
	
	ret = write(fd, "abcd", 4);  //read(fd, buf, 9);
	buf[10]='\0';
	
	if (ret < 0) {
		printf("write failed errno=%d\n", errno);
	  return 1;
	}
	printf("read buffer: %s\n", buf);
	ret = close(fd);
  if (ret < 0) {
		printf("close failed errno=%d\n", errno);
	  return 1;
	}
	return 0;*/
	return 0;
}
