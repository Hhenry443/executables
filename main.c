#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    struct dirent *de;
    
    DIR *dr = opendir(".");

    if (dr == NULL) {
        printf("Couldn't open current directory");
        return 0;
    }

    while ((de = readdir(dr)) != NULL) {
        if (de->d_type == DT_REG) {
            struct stat sb;

            size_t cwd_buf_len = 128;
            char *cwd_buf = malloc(sizeof(char) * cwd_buf_len);

            getcwd(cwd_buf, cwd_buf_len);

            size_t filepath_len = 256;
            char *filepath = malloc(sizeof(char) * filepath_len);

            snprintf(filepath, filepath_len, "%s/%s", cwd_buf, de->d_name);

            stat(filepath, &sb);

            // S_IXUSR is a bit flag that we can check to see if the user as write permissions.
            if (sb.st_mode & S_IXUSR) {
                printf("%s: Executable\n", de->d_name);
            } else {
                printf("%s: Not Executable\n", de->d_name);
            }
        }

    }

    return 0;
}
