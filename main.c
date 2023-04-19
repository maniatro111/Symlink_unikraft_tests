#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/param.h>
#include <fcntl.h>

static int default_init(char *name) {
	printf("\nPreparing %s test.\n", name);
	errno = 0;
}

static int run_eloop_test(char *name) {

	char *link_to_create;
#ifdef PLAIN
	link_to_create = "fs0/eloop_test/symlink40/link_to_file.txt";
#else
	link_to_create = "eloop_test/symlink40/link_to_file.txt";
#endif

	int ret = symlink("test.txt", link_to_create);
	printf("Symlink call returned %d.\n", ret);
	if (ret)
		printf("ERRNO: %d. %s. \n", errno, strerror(errno));

	return ret;
}

static int run_eexist_test(char *name) {

	char *link_to_create;
#ifdef PLAIN
	link_to_create = "fs0/eacces_test/write_test";
#else
	link_to_create = "eacces_test/write_test";
#endif

	int ret = symlink("test.txt", link_to_create);
	printf("Symlink call returned %d.\n", ret);
	if (ret)
		printf("ERRNO: %d. %s.\n", errno, strerror(errno));
	
	return ret;
}

static int run_enoent_test(char *name) {

	char *link_to_create;
#ifdef PLAIN
	link_to_create = "fs0/test.txt";
#else
	link_to_create = "test.txt";
#endif

	int	ret = symlink("", "test.txt");
	printf("Symlink call returned %d.\n", ret);
	if (ret)
		printf("ERRNO: %d. %s.\n", errno, strerror(errno));
}

static int run_write_content_test(char *name) {

#ifdef PLAIN
	#define FILENAME "fs0/symlink_inside_2"
#else
	#define FILENAME "symlink_inside_2"
#endif

	#define ORIG_FILENAME "abc.txt"
	int ret = symlink(ORIG_FILENAME, FILENAME);

	printf("Symlink call returned %d\n", ret);
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
	
	ret = write(fd, "abcd\n", 5);
	
	if (ret < 0) {
		printf("write failed errno=%d\n", errno);
		return 1;
	}
	ret = close(fd);
	if (ret < 0) {
		printf("close failed errno=%d\n", errno);
		return 1;
	}
	ret = unlink(FILENAME);
	if (ret < 0) {
		printf("unlink failed errno=%d\n", errno);
		return 1;
    }
}

static void default_clean(char *name) {
	fprintf(stderr, "FINISHING %s test.\n", name);
	fprintf(stderr, "--------------------\n");
}

struct test_ops {
	char *name;
	int (*prepare) (char *name);
	int (*run) (char *name);
	void (*clean) (char *name);
};

struct test_ops tests[] = {
	{
		.name = "ELOOP",
		.prepare = default_init,
		.run = run_eloop_test,
		.clean = default_clean
	},
	{
		.name = "EEXIST",
		.prepare = default_init,
		.run = run_eexist_test,
		.clean = default_clean
	},
	{
		.name = "ENOENT",
		.prepare = default_init,
		.run = run_enoent_test,
		.clean = default_clean
	},
	{
		.name = "WRITE_CONTENT",
		.prepare = default_init,
		.run = run_write_content_test,
		.clean = default_clean
	}
};

int main()
{

	int i = 0;
	for ( i = 0; i < sizeof(tests)/sizeof(*tests); i++) 
	{
		tests[i].prepare(tests[i].name);
		tests[i].run(tests[i].name);
		tests[i].clean(tests[i].name);
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
	}*/
	return 0;
}
