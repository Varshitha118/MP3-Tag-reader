#include <stdio.h>
void help()
{
    printf("\n ---------------- MP3 TAG READER HELP FUNCTION ------------------ \n");

    printf("Enter -v to view all MP3 tags\n");
    printf("Enter -e to edit MP3 tags\n");
    printf("Enter -h to display help menu\n");
                                                                                     
    printf("\nENTER TAG TO EDIT:\n");
    printf("Enter -t to Edit the tag Title\n");
    printf("Enter -a to Edit the tag Artist\n");
    printf("Enter -A to Edit the tag Album\n");
    printf("Enter -y to Edit the tag Year\n");
    printf("Enter -g to Edit the tag Genre\n");
    printf("Enter -c to Edit the tag Comment\n");

    printf("\nExample:\n");
    printf("Enter option (-v / -e / -h): -e\n");
    printf("Enter what you want to edit (-t/-a/-A/-y/-g/-c): -t\n");

}
