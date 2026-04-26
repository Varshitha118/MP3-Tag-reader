#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void edit(FILE *fp, const char *tag, const char *new_data)
{
    FILE *temp = fopen("temp.mp3", "wb");  // create temp file
    if (!temp)
    {
        printf("File cannot open\n");
        return;
    }

    unsigned char header[10];   // ID3 header buffer
    fread(header, 10, 1, fp);   // read header
    fwrite(header, 10, 1, temp);    // write header

    while (1)
    {
        char frame_id[5];   // frame ID
        unsigned char size_bytes[4];       // frame size bytes
        unsigned char flags[2];                    // frame flags
        unsigned int size = 0;                // frame size

        if (fread(frame_id, 4, 1, fp) != 1)       // read frame ID
            break;

        frame_id[4] = '\0';        

        fread(size_bytes, 4, 1, fp);   // read size
        fread(flags, 2, 1, fp);   // read flags

        for (int i = 0; i < 4; i++) // convert size to int
            size = (size << 8) | size_bytes[i];

        if (size == 0)   // end of frames
            break;

        if (frame_id[0] != 'T' && strcmp(frame_id, "COMM") != 0)
        {
            fwrite(frame_id, 4, 1, temp);   // copy frame ID
            fwrite(size_bytes, 4, 1, temp);    // copy size
            fwrite(flags, 2, 1, temp);   // copy flags

            char *skip = malloc(size);   
            fread(skip, size, 1, fp);    // read data
            fwrite(skip, size, 1, temp);   // write data
            free(skip);       // free buffer
            continue;
        }

        unsigned char encoding;     // text encoding
        fread(&encoding, 1, 1, fp);     // read encoding

        char *info = malloc(size);    // allocate info buffer
        fread(info, size - 1, 1, fp);    // read frame data

        if (!strcmp(frame_id, "COMM") && !strcmp(tag, "COMM"))
        {
            const char *lang = "eng";    // language code
            const char *desc = "";  // empty description

            unsigned int new_size =
                1 + 3 + strlen(desc) + 1 + strlen(new_data); // COMM size

            fwrite("COMM", 4, 1, temp);  // write COMM ID

            unsigned char s[4];   // new size bytes
            s[0] = (new_size >> 24) & 0xFF;
            s[1] = (new_size >> 16) & 0xFF;
            s[2] = (new_size >> 8) & 0xFF;
            s[3] = new_size & 0xFF;
            fwrite(s, 4, 1, temp);    // write new size

            fwrite(flags, 2, 1, temp);  // write flags

            unsigned char enc = 0x00;  
            fwrite(&enc, 1, 1, temp);     // write encoding
            fwrite(lang, 3, 1, temp);  // write language
            fwrite(desc, strlen(desc), 1, temp);  // write description
            fputc('\0', temp);      // description terminator
            fwrite(new_data, strlen(new_data), 1, temp); // write comment
        }
        else if (!strcmp(frame_id, tag))
        {
            unsigned int new_size = strlen(new_data) + 1; // text size

            fwrite(frame_id, 4, 1, temp);    // write frame ID

            unsigned char s[4];     // new size bytes
            s[0] = (new_size >> 24) & 0xFF;
            s[1] = (new_size >> 16) & 0xFF;
            s[2] = (new_size >> 8) & 0xFF;
            s[3] = new_size & 0xFF;
            fwrite(s, 4, 1, temp);    // write size

            fwrite(flags, 2, 1, temp);    // write flags

            unsigned char enc = 0x00;  // encoding
            fwrite(&enc, 1, 1, temp);     // write encoding
            fwrite(new_data, new_size - 1, 1, temp);  // write text
        }
        else
        {
            fwrite(frame_id, 4, 1, temp);    // copy frame ID
            fwrite(size_bytes, 4, 1, temp);    // copy size
            fwrite(flags, 2, 1, temp);     // copy flags
            fwrite(&encoding, 1, 1, temp);    // copy encoding
            fwrite(info, size - 1, 1, temp);  // copy data
        }

        free(info);           // free buffer
    }

    char ch;            // audio byte
    while (fread(&ch, 1, 1, fp))      // copy audio data
        fwrite(&ch, 1, 1, temp);

    fclose(fp);              // close original
    fclose(temp);      // close temp

    remove("sample (1).mp3");        // delete old file
    rename("temp.mp3", "sample (1).mp3");     // rename temp

    printf("Successfully Edited\n");         // success message
}

