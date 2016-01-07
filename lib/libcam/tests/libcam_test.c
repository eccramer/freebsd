#include <sys/cdefs.h>
//RCSID goes here

#include <atf-c.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <camlib.h>

ATF_TC(libcam_get_device_not_exists);

ATF_TC_HEAD(libcam_get_device_not_exists, tc)
{

	atf_tc_set_md_var(tc, "descr", "test cam_get_device with a valid device path that does not exist.");
}

ATF_TC_BODY(libcam_get_device_not_exists, tc)
{
	char* path = "/dev/foo1";
	char  dev_name[10];
	int   devnamelen = 10;
	int   unit = 0;
	int   result = 0;
	struct cam_device * dev;

	atf_tc_expect_fail("Passing in /dev/foo1, a bad device path.");

	ATF_CHECK(cam_get_device(path, dev_name, devnamelen, &unit) == -1);

}

ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, libcam_get_device_not_exists);

	return atf_no_error();
}
