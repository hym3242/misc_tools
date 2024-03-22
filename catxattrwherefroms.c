// directly outputs the bplist in kMDItemWhereFroms xattr to stdout. use plutil to view it later.
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/xattr.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\nargs: ", argv[0]);
		for(int i=0;i<argc;i++){
			fprintf(stderr,"%d\n",i);
			write(2,argv[i],strlen(argv[i]));
			write(2,"\n",1);
		}
        return 1;
    }

    const char *file_path = argv[1];
    const char *attr_name = "com.apple.metadata:kMDItemWhereFroms";
    ssize_t buffer_size;

    // Determine the buffer size needed
    buffer_size = getxattr(file_path, attr_name, NULL, 0, 0, 0);
    if (buffer_size < 0) {
        //perror("Error getting size of xattr");
        return 2;
    }

    // Allocate buffer for the attribute value
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        //fprintf(stderr, "Memory allocation failed\n");
        return 3;
    }

    // Read the attribute value
    if (getxattr(file_path, attr_name, buffer, buffer_size, 0, 0) < 0) {
        //perror("Error reading xattr");
        free(buffer);
        return 4;
    }

    // Output the attribute value
    fwrite(buffer, 1, buffer_size, stdout);

    free(buffer);
    return 0;
}
