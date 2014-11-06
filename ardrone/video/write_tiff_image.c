void write_tiff_image(image_file_name, array) {

	char image_file_name[];
	short **array;

	FILE *image_file;
	int bytes_written,
	closed,
	i,
	position,
	written;

	float a;

	long line_length,
	offset;

	struct tiff_header_struct image_header;
	read_tiff_header(image_file_name, &image_header);
	
	image_file = fopen(image_file_name, "rb+");
	position = fseek(image_file,
	image_header.strip_offset,
	SEEK_SET);

	for(i=0; i<image_header.image_length; i++){
		bytes_written = write_line(image_file, array,
		i, &image_header,
		0, image_header.image_width);
	} /* ends loop over i */

	closed = fclose(image_file);
} /* ends write_tiff_image */