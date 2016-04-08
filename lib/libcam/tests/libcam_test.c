#include <sys/cdefs.h>
//RCSID goes here

#include <atf-c.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <camlib.h>

/* cam_get_device tests */

ATF_TC(libcam_get_device_null_path);

ATF_TC_HEAD(libcam_get_device_null_path, tc)
{
	atf_tc_set_md_var(tc, "descr", "test cam_get_device with a null path string.");
}

ATF_TC_BODY(libcam_get_device_null_path, tc)
{
	char* path = NULL;
	char  dev_name[10];
	int   devnamelen = 10;
	int   unit = 0;
	int   result = 0;
	struct cam_device * dev;

	atf_tc_expect_fail("Passing in a null device path.");

	ATF_CHECK(cam_get_device(path, dev_name, devnamelen, &unit) == 0);
}

ATF_TC(libcam_get_device_empty_path);

ATF_TC_HEAD(libcam_get_device_empty_path, tc)
{
	atf_tc_set_md_var(tc, "descr", 
			  "test cam_get_device with an empty path string.");
}

ATF_TC_BODY(libcam_get_device_empty_path, tc)
{
	char* path = "";
	char  dev_name[10];
	int   devnamelen = 10;
	int   unit = 0;
	int   result = 0;
	struct cam_device * dev;

	atf_tc_expect_fail("Passing in an empty device path.");

	ATF_CHECK(cam_get_device(path, dev_name, devnamelen, &unit) == 0);
}

ATF_TC(libcam_get_device_no_text_after_slash);

ATF_TC_HEAD(libcam_get_device_no_text_after_slash, tc)
{
	atf_tc_set_md_var(tc, "descr", 
			  "test cam_get_device with an invalid device path that is only /.");
}

ATF_TC_BODY(libcam_get_device_no_text_after_slash, tc)
{
	char* path = "/";
	char  dev_name[10];
	int   devnamelen = 10;
	int   unit = 0;
	int   result = 0;
	struct cam_device * dev;

	atf_tc_expect_fail("Passing in /, a bad device path.");

	ATF_CHECK(cam_get_device(path, dev_name, devnamelen, &unit) == 0);
}

ATF_TC(libcam_get_device_name_starts_with_number);

ATF_TC_HEAD(libcam_get_device_name_starts_with_number, tc)
{
	atf_tc_set_md_var(tc, "descr", 
			  "test cam_get_device with a device name that starts with a number.");
}

ATF_TC_BODY(libcam_get_device_name_starts_with_number, tc)
{
	char* path = "1ada";
	char  dev_name[10];
	int   devnamelen = 10;
	int   unit = 0;
	int   result = 0;
	struct cam_device * dev;

	atf_tc_expect_fail("Passing in 1ada, a bad device path.");

	ATF_CHECK(cam_get_device(path, dev_name, devnamelen, &unit) == 0);
}

ATF_TC(libcam_get_device_valid_device);

ATF_TC_HEAD(libcam_get_device_valid_device, tc)
{
	atf_tc_set_md_var(tc, "descr", "test cam_get_device with a valid device name.");
}

ATF_TC_BODY(libcam_get_device_valid_device, tc)
{
	char* path = "/dev/foo1";
	char  dev_name[10];
	int   devnamelen = 10;
	int   unit = 0;
	int   result = 0;
	int expected_unit = 1;
	char* expected_dev_name = "foo";
	struct cam_device * dev;

	atf_tc_expect_pass();

	result = cam_get_device(path, dev_name, devnamelen, &unit);

	if(result != 0)
		atf_tc_fail("Expected 0, got %d", result);

	if(unit != expected_unit)
		atf_tc_fail("Unit num does not match expected unit num. \
			    Expected: %d. Got: %d", expected_unit, unit);

	if(strcmp(expected_dev_name, dev_name))
		atf_tc_fail("dev_name and expected_dev_name did not match. \
			    Expected %s. Got %s.", expected_dev_name, dev_name);

	atf_tc_pass();
}

/* cam_open_device tests */

ATF_TC(libcam_open_device_not_exists);

ATF_TC_HEAD(libcam_open_device_not_exists, tc)
{
	atf_tc_set_md_var(tc, "descr", "test cam_open_device with a device that doesn't exist.");
}

ATF_TC_BODY(libcam_open_device_not_exists, tc)
{
	char* path = "/dev/foo1";
	static struct cam_device * result;
	
	result = cam_open_device(path, O_RDONLY);

	if(result != NULL)
		atf_tc_fail("Expected null, but got a device struct pointer back.");

	atf_tc_pass();
}

ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, libcam_get_device_null_path);
	ATF_TP_ADD_TC(tp, libcam_get_device_empty_path);
	ATF_TP_ADD_TC(tp, libcam_get_device_name_starts_with_number);
	ATF_TP_ADD_TC(tp, libcam_get_device_no_text_after_slash);
	ATF_TP_ADD_TC(tp, libcam_get_device_valid_device);
	ATF_TP_ADD_TC(tp, libcam_open_device_not_exists);

	return atf_no_error();
}
