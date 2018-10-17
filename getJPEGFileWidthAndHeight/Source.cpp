#include <iostream>

#include "../libjpeg9c/cdjpeg.h"		/* Common decls for cjpeg/djpeg applications */
#include "../libjpeg9c/jversion.h"		/* for version message */

#define JMESSAGE(code,string)	string ,

static const char * const cdjpeg_message_table[] = {
#include "../libjpeg9c/cderror.h"
	NULL
};

#pragma comment(lib,"libjpeg9c.lib")

int main(int argc, char* argv[])
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	/* Initialize the JPEG decompression object with default error handling. */
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	/* Add some application-specific error messages (from cderror.h) */
	jerr.addon_message_table = cdjpeg_message_table;
	jerr.first_addon_message = JMSG_FIRSTADDONCODE;
	jerr.last_addon_message = JMSG_LASTADDONCODE;

	FILE * input_file;
	if ((input_file = fopen("d:/w22077.jpg", READ_BINARY)) == NULL) {
		fprintf(stderr, "can't open file!\n");
		exit(EXIT_FAILURE);
	}	

	/* Specify data source for decompression */
	jpeg_stdio_src(&cinfo, input_file);

	/* Read file header, set default decompression parameters */
	(void)jpeg_read_header(&cinfo, TRUE);

	std::cout << "image_width:" << cinfo.image_width << ",image_height:" << cinfo.image_height << std::endl;

	jpeg_destroy_decompress(&cinfo);

	/* Close files, if we opened them */
	if (input_file != stdin)
		fclose(input_file);

	return 0;
}