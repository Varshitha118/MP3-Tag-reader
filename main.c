#include <stdio.h>
#include <string.h>

void view(FILE *fp);             
void edit(FILE *fp, const char *tag, const char *new_data);
void help(FILE *fp);

int main()
{
    char option[3];      // stores -v or -e
    char tag[5];     // frame id
    char value[100];    // to store new tag value

    FILE *fp;   // file pointer
    if ((fp = fopen("sample (1).mp3", "rb")) == NULL)  //to  open file
    {
        printf("file not found\n");
        return 0;
    }

    char buffer[4];     // ID3 buffer
    fread(buffer, 3, 1, fp);         // read header
    buffer[3] = '\0';    // to terminate null

    if (strcmp(buffer, "ID3") != 0)   // check mp3
    {
        printf("It is not mp3\n");
        fclose(fp);
        return 0;
    }

    rewind(fp);  

    printf("Enter option (-v / -e / -h): ");       // user choice
    scanf("%s", option);         // read option

    if (strcmp(option, "-v") == 0)         // view option
    {
        view(fp);       // call view
        fclose(fp);         // close file
    }
    else if (strcmp(option, "-e") == 0)
    {
        fclose(fp);

        char option[3];
        char tag[5];
        char value[100];

        printf("Enter what you want to edit (-t/-a/-A/-y/-g/-c): ");
        scanf("%s", option);

        // tag based on option
        if (strcmp(option, "-t") == 0)
            strcpy(tag, "TIT2");      // Title
        else if (strcmp(option, "-a") == 0)
            strcpy(tag, "TPE1");      // Artist
        else if (strcmp(option, "-A") == 0)
            strcpy(tag, "TALB");      // Album
        else if (strcmp(option, "-y") == 0)
            strcpy(tag, "TYER");      // Year
        else if (strcmp(option, "-g") == 0)
            strcpy(tag, "TCON");      // Genre
        else if (strcmp(option, "-c") == 0)
            strcpy(tag, "COMM");      // Comment
        else
        {
            printf("Invalid edit option\n");
            return 0;
        }

        printf("Enter new value: ");
        getchar();  // clear buffer
        fgets(value, sizeof(value), stdin);

        int i = 0;           // index
        while (value[i] != '\0')   // remove newline
        {
            if (value[i] == '\n')
            {
                value[i] = '\0';
                break;
            }
            i++;
        }

        fp = fopen("sample (1).mp3", "rb");  // reopen file
        edit(fp, tag, value);       // edit tag
    }
    else if (strcmp(option, "-h") == 0)
    {
        help(fp);
        fclose(fp);
    }
    else
    {
        printf("Invalid option\n");  // wrong input
        fclose(fp);
    }

    return 0;   
}
